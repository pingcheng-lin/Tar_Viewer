#ifndef __STACK_H__
#define __STACK_H__

struct stack {
    int data;
    struct stack *next;
};

extern void push(struct stack* this, int x);
extern int pop(struct stack* this);
extern struct stack* new_stack();
extern void delete_stack(struct stack* stk);

#endif