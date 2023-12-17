#ifndef __LIB_H__
#define __LIB_H__

#define NULL 0

char inp();
void outp(char);
void terminate(int status);
int read_int_buffer(int file, int* buffer, int max_size);
int write_int_buffer(int file, int* buffer, int size);
int open_file(char* path, char* flags);
int close_file(int file);
void print_string(const char* p);
void read_string(char* buffer, int max_chars);
unsigned int str_to_uns(const char* str);
int uns_to_str(char* buffer, unsigned int val);
void* allocate(int size);
void release(void* mem);
#endif
