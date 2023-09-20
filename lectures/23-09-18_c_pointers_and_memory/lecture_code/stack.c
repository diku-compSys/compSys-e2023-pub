#include <stdio.h>
#include <assert.h>

struct stack {
  int elements[3];
  int top; // first free elements
};

void stack_init(struct stack *s) {
  s->top = 0;
}

int stack_push(struct stack *s, int x) {
  if (s->top == 3) {
    return 1;
  }
  s->elements[s->top] = x;
  s->top = s->top + 1;
  return 0;
}

int main(void) {
  struct stack s;
  stack_init(&s);
  printf("Initial top: %d\n", s.top);
  assert(stack_push(&s, 100) == 0);
  assert(stack_push(&s, 200) == 0);
  assert(stack_push(&s, 300) == 0);
  printf("Final top: %d\n", s.top);
}
