#ifndef SRC_AVL_TREE_H_
#define SRC_AVL_TREE_H_

void avl_tree_set_comparator(int (*comp)(void * left, void *right));
void avl_tree_create();
void avl_tree_insert(void * key, void * value);
void * avl_tree_find(void * key);
void avl_tree_remove(void * key);



#endif /* SRC_AVL_TREE_H_ */
