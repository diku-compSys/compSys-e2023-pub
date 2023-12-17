#include "read_exec.h"
#include "assembly.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024
char line[MAXLINE];
char hexes[4][9]; // 8+1 for zero termination
char symbol[1024];
char opcode[8], args[16], rest[24];

int is_hex(char c)
{
  if (c >= '0' && c <= '9')
    return 1;
  if (c >= 'a' && c <= 'f')
    return 1;
  return 0;
}

int to_hex(char c)
{
  if (c >= '0' && c <= '9')
    return c - '0';
  if (c >= 'a' && c <= 'f')
    return c - 'a' + 10;
  if (c >= 'A' && c <= 'F')
    return c - 'A' + 10;
  return 0; // silence a warning
}

int to_hex2(char a, char b)
{
  return to_hex(a) * 16 + to_hex(b);
}

// count number of 2-digit hexes in "size" strings of max 4 hexes each
int count_hexes(char hexes[][9], int size)
{
  int num = 0;
  for (int k = 0; k < size; ++k)
  {
    for (int i = 0; i < 8; i++)
    {
      if (is_hex(hexes[k][i]))
        num++;
      else
        return num / 2;
    }
  }
  return num / 2;
}

int read_exec(struct memory *mem, struct assembly *as, const char *name, FILE *log_file)
{
  FILE *fp;
  fp = fopen(name, "r");
  if (fp == NULL)
  {
    printf("Error: could not open file '%s'. Exiting\n", name);
    exit(-1);
  }
  int count = 0;
  int start_addr = -1; // invalid starting addr
  while (fgets(line, MAXLINE, fp))
  {
    // remove any trailing newline:
    int last = strlen(line) - 1;
    if (line[last] == '\n')
      line[last] = 0;
    char *msg = "Ukendt";
    unsigned int addr;
    unsigned int a;            // value
    int num_hex = 0;
    int n = sscanf(line, " %x %s%s%s%s*c[ ]*c[]", &addr, hexes[0], hexes[1], hexes[2], hexes[3]);
    if (n >= 2)
    {
      num_hex = count_hexes(hexes, n - 1);
    }
    if (num_hex)
    {
   
      msg = "Data";
      for (int i = 0; i < num_hex; ++i)
      {
        int block = i / 4;
        int disp = (i % 4) * 2;
        int data = to_hex2(hexes[block][disp], hexes[block][disp + 1]);
        memory_wr_b(mem, addr, data);
        ++addr;
      }
    }
    else if ((n = sscanf(line, " %x: %x %7s %15s %23s", &addr, &a, opcode, args, rest)) >= 2)
    {
      msg = "Insn";
      memory_wr_w(mem, addr, a);
      if (n > 2)
      {
        char text[64];
        if (n == 3)
        {
          sprintf(text, "%-8s", opcode);
        }
        else if (n == 4)
        {
          sprintf(text, "%-8s %-16s", opcode, args);
        }
        else if (n == 5)
        {
          sprintf(text, "%-8s %-16s %-24s", opcode, args, rest);
        }
        assembly_set(as, addr, text);
      }
    }
    else if (sscanf(line, "%x <%s", &addr, symbol) == 2)
    {
      msg = "Entry";
      // sscanf included the terminating ">:" in the string, check for it here:
      if (strcmp(symbol, "_start>:") == 0)
      {
        msg = "Start";
        start_addr = addr;
      }
    }
    ++count;
    if (log_file)
      fprintf(log_file, "%d -- %s -- %s\n", count, msg, line);
  }
  if (start_addr != -1)
    return start_addr;
  printf("Start symbol not found in file. Terminating");
  exit(-1);
  return 0; // silence warning
}
