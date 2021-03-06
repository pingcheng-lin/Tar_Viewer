#ifndef __STACK_H__
#define __STACK_H__

class Block {
public:
    Block();
    Block(int x);
    int data;
    Block *next;
};

class Stack {
friend class Block;
private:
    Block *head;
public:
    Stack();
    void push(int x);
    int pop();
};

#endif