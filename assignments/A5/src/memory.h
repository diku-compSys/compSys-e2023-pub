#ifndef __MEMORY_H__
#define __MEMORY_H__

struct memory;

// opret/nedlæg lager
struct memory *memory_create();
void memory_delete(struct memory *);

// skriv word/halfword/byte til lager
void memory_wr_w(struct memory *mem, int addr, int data);
void memory_wr_h(struct memory *mem, int addr, int data);
void memory_wr_b(struct memory *mem, int addr, int data);

// læs word/halfword/byte fra lager - data er nul-forlænget
int memory_rd_w(struct memory *mem, int addr);
int memory_rd_h(struct memory *mem, int addr);
int memory_rd_b(struct memory *mem, int addr);
#endif
