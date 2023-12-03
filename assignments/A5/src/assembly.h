#ifndef __ASSEMBLY_H__
#define __ASSEMBLY_H__

struct assembly;

// opret og slet fortegnelse over assemblerkode
struct assembly *assembly_create();
void assembly_delete(struct assembly *);

// tilføj assemblerkode knyttet til addresse
void assembly_set(struct assembly *as, int addr, const char *text);

// find assemblerkode knyttet til addresse
const char *assembly_get(struct assembly *as, int addr);

#endif
