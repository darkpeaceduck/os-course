#include "threads.h"
#include "allocator.h"
#include <stddef.h>
#include "utils.h"
#include "lock.h"
#include "memory.h"
#include "print.h"

#define THREAD_STACK_START_SIZE 8192

#define DEFAULT_PRIORITY_NUM 20

static thread_t * volatile current_thread;
struct list_head * volatile  queues;
static size_t volatile queues_num;

struct  list_head * volatile terminated_threads;
static void * volatile terminated_threads_lock;

static const float quant_diff_q = 0.01;
static float volatile current_thread_working_elapsed_time = 0;

static thread_t * volatile current_thread = NULL;
static thread_t * volatile cleaner_thread;

static void * volatile threads_lock;

void thread_exit(thread_t * thread) {
	lock(threads_lock);
	if(thread->status != TERMINATED) {
		thread->status = TERMINATED;
		list_del(&thread->list);

		lock(terminated_threads_lock);
		list_add(&thread->list, terminated_threads);
		unlock(terminated_threads_lock);
	}

	unlock(threads_lock);
}

static void * cleaner_body(void * arg) {
	while(1) {
		void * freeing_stack = NULL;
		lock(terminated_threads_lock);
		if(!list_empty(terminated_threads)){
			thread_t * thread = LIST_ENTRY(list_first(terminated_threads), thread_t, list);
			freeing_stack = thread->stack;
			list_del(&thread->list);
		}
		unlock(terminated_threads_lock);
		if(freeing_stack) {
			free(freeing_stack);
		}
		thread_yield();
	}
	return arg;
}

static void create_helper_threads() {
	cleaner_thread = thread_create(cleaner_body, NULL);
}

void thread_manager_init(int32_t queues_num_arg) {
	if(queues_num_arg == -1){
		queues_num_arg = DEFAULT_PRIORITY_NUM;
	}
	queues_num = queues_num_arg;
	queues = malloc(queues_num * sizeof(struct list_head));
	for(size_t i = 0; i < queues_num; i++) {
		list_init(&queues[i]);
	}
	terminated_threads = malloc(sizeof(struct list_head));
	list_init(terminated_threads);
	terminated_threads_lock = lock_create();
	threads_lock = lock_create();
	create_helper_threads();
}

static thread_t * thread_allocate() {
	thread_t * thread = (thread_t *) malloc(sizeof(thread_t));
	thread->stack = (void *)((virt_t)malloc(THREAD_STACK_START_SIZE) + THREAD_STACK_START_SIZE - 1);
	return thread;
}

thread_t * thread_create(void * (*entry)(void *) , void * arg) {
	lock(threads_lock);
	thread_t * thread = thread_allocate();

	thread->arg = arg;
	thread->entry = entry;
	thread->result = NULL;
	thread->status = READY_TO_START;
	thread->priority = 0;
	list_init(&thread->list);
	list_add_tail(&thread->list, &queues[thread->priority]);

	unlock(threads_lock);
	return thread;
}

static void try_wrapper_entry(thread_t * thread){
	if(thread->status == READY_TO_START) {
		thread->status = RUNNING;
		unlock(threads_lock);

		thread->result = thread->entry(thread->arg);
		thread_exit(thread);
		while(1) {
			thread_yield();
		}
	}
}

static void switch_context(thread_t * new_thread) {
	if(current_thread != NULL) {
		__asm__ volatile(
			"push %rbp; \
			 push %rbx;\
			 push %r12;\
			 push %r13;\
			 push %r14;\
			 push %r15;\
			 pushf;"
		);

		__asm__ volatile("movq %%rsp, %0" : "=r"(current_thread->stack));
	}

	__asm__ volatile("movq %0, %%rsp" :: "a"(new_thread->stack));
	current_thread = new_thread;
	try_wrapper_entry(current_thread);

	__asm__ volatile(
		"popf;\
		 pop %r15;\
		 pop %r14;\
		 pop %r13;\
		 pop %r12;\
		 pop %rbx;\
		 pop %rbp; "
	);
}

static void thread_move_up_priority(thread_t * thread) {
	if(thread->priority < queues_num - 1){
		list_del(&thread->list);
		thread->priority++;
		list_add_tail(&thread->list, &queues[thread->priority]);
	}
}

static void thread_down_up_priority(thread_t * thread) {
	if(thread->priority > 0) {
		list_del(&thread->list);
		thread->priority--;
		list_add_tail(&thread->list, &queues[thread->priority]);
	}
}

static void thread_manage_switch() {
	for(size_t i = 0; i < queues_num; i++) {
		if(!list_empty(&queues[i])) {
			thread_t * thread = LIST_ENTRY(list_first(&queues[i]), thread_t, list);
			list_del(&thread->list);
			list_add_tail(&thread->list, &queues[i]);
			current_thread_working_elapsed_time = quant_diff_q * (i + 1);
			switch_context(thread);
			return;
		}
	}
}

void thread_yield() {
	lock(threads_lock);
	if(current_thread != NULL && current_thread->status == RUNNING) {
		if(current_thread_working_elapsed_time <= 0) {
			thread_down_up_priority(current_thread);
		} else {
			thread_move_up_priority(current_thread);
		}
	}
	thread_manage_switch();
	unlock(threads_lock);
}

void thread_manager_callback(float delta_time) {
	lock(threads_lock);
	current_thread_working_elapsed_time -= delta_time;
	if(current_thread_working_elapsed_time <= 0 || current_thread->status == TERMINATED) {
		unlock(threads_lock);
		thread_yield();
	} else {
		unlock(threads_lock);
	}
}

void thread_join(thread_t * thread) {
	bool is_terminated = false;
	while(!is_terminated){
		lock(threads_lock);
		is_terminated = thread->status == TERMINATED;
		unlock(threads_lock);
		thread_yield();
	}
}

thread_mutex * thread_mutex_create(){
	thread_mutex * mutex = malloc(sizeof(thread_mutex));
	mutex->owner = NULL;
	list_init(&mutex->sleeping_threads);
	return mutex;
}

void thread_mutex_destroy(thread_mutex * mutex){
	free(mutex);
}

static void thread_move_to_sleep(thread_t * thread) {
	list_del(&thread->list);
	thread->status = SLEEPING;
}

static void thread_wakeup(thread_t *thread) {
	list_add_tail(&thread->list, &queues[thread->priority]);
	thread->status = RUNNING;
}

void thread_mutex_lock(thread_mutex * mutex) {
	lock(threads_lock);
	if(mutex->owner == NULL || mutex->owner == current_thread){
		mutex->owner = current_thread;
		unlock(threads_lock);
	} else {
		thread_move_to_sleep(current_thread);
		list_add(&current_thread->list, &mutex->sleeping_threads);
		unlock(threads_lock);
		thread_yield();
	}
}

void thread_mutex_unlock(thread_mutex * mutex) {
	lock(threads_lock);
	if(mutex->owner == current_thread) {
		while(!list_empty(&mutex->sleeping_threads)){
			thread_t * thread = LIST_ENTRY(list_first(&mutex->sleeping_threads), thread_t, list);
			list_del(&thread->list);
			thread_wakeup(thread);
		}
		mutex->owner = NULL;
	}
	unlock(threads_lock);
}

thread_cond * thread_cond_create(){
	thread_cond * cond = malloc(sizeof(thread_cond));
	list_init(&cond->sleeping_threads);
	return cond;
}

void thread_cond_destroy(thread_cond * cond) {
	free(cond);
}

void thread_cond_wait(thread_cond * cond, thread_mutex * mutex){
	lock(threads_lock);
	thread_move_to_sleep(current_thread);
	list_add(&current_thread->list, &cond->sleeping_threads);
	unlock(threads_lock);
	thread_mutex_unlock(mutex);

	thread_yield();
	thread_mutex_lock(mutex);
}

void thread_cond_signal(thread_cond * cond) {
	lock(threads_lock);
	if(!list_empty(&cond->sleeping_threads)){
		thread_t * thread = LIST_ENTRY(list_first(&cond->sleeping_threads), thread_t, list);
		list_del(&thread->list);
		thread_wakeup(thread);
	}
	unlock(threads_lock);
}
void thread_cond_broadcast(thread_cond * cond) {
	lock(threads_lock);
	while (!list_empty(&cond->sleeping_threads)){
		thread_t * thread = LIST_ENTRY(list_first(&cond->sleeping_threads), thread_t, list);
		list_del(&thread->list);
		thread_wakeup(thread);
	}
	unlock(threads_lock);
}
