#include "stack.h"

Block::Block(){
    data = 0;
    next = nullptr;
}
Block::Block(int x){
    data = x;
    next = nullptr;
}
Stack::Stack(){
    head = nullptr;
}
void Stack::push(int x){
    if(head == nullptr){
        head = new Block(x);;
    }
    else{
        Block *ptr =  new Block(x);
        ptr->next = head;
        head = ptr;
    }
}
int Stack::pop(){
    int temp = head->data;
    Block *tptr = head;
    head = head->next;
    delete tptr;
    return temp;
}
