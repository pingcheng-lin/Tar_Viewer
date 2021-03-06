#include <stdlib.h>
#include "stack.h"

struct stack* head1 = NULL;
struct stack* head2 = NULL;
struct stack* a;//verify who want to push

void push(struct stack* this, int x)
{
    if(this->data == 0)//push the first one of each list
    {
        this->data = x;
        if(head1 == NULL)
        {
            head1 = this;
            a = this;
        }
        else
            head2 = this;
    }
    else
    {
        struct stack* temp = malloc(sizeof(struct stack));
        temp->data = x;
        if(this == a)
        {
            temp->next = head1;
            head1 = temp;
        }
        else
        {
            temp->next = head2;
            head2 = temp;
        }
    }
}

int pop(struct stack* this)
{
    struct stack* temp;
    if(this == a)
    {
        temp = head1;
        head1 = head1->next;
    }
    else
    {
        temp = head2;
        head2 = head2->next;
    }
    int t = temp->data;
    free(temp);
    return t;
}

struct stack* new_stack()
{
    struct stack* stk = malloc(sizeof(struct stack));
    stk->data = 0;
    stk->next = NULL;
    return stk;
}

void delete_stack(struct stack* stk)
{
    free(stk);
}
