#ifndef SNOOP_H
#define SNOOP_H

#define SNOOP_STACK_SIZE 2000
#define SNOOP_MAX_LEN 236

extern int snoop_read_num;
void copy_snoop_read_buffer( uint8_t offset, int size_num, uint8_t *buffer );
void snoop_start_thread();

#endif
