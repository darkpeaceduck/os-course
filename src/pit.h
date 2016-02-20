
#ifndef PIT_H_
#define PIT_H_
#include <stdint.h>

#define PIT_CONTROL_PORT 0x43
#define PIT_DATA_PORT_CHANNEL_0 0x40
#define PIT_CONTROL_COMMAND (BIT(2) | BIT(4) | BIT(5))
#define PIT_COUNTER (BIT(16) - 1)

void pit_setup();
void pit_replace_vector(uint64_t handler);

#endif /* PIT_H_ */
