#ifndef _STACK_H_
#define _STACK_H_
#include <cstddef>
#include "error_code.h"
template <class Stack_entry>
struct Stack_node {
//data members
    Stack_entry entry;
    Stack_node *next;
// constructors
    Stack_node();
    Stack_node( const Stack_entry &item, Stack_node *link = NULL);
};

template <class Stack_entry>
Stack_node<Stack_entry> :: Stack_node()
{
    next = NULL;
}

template <class Stack_entry>
Stack_node<Stack_entry> :: Stack_node(const Stack_entry &item, Stack_node *link)
{
    entry = item;
    next = link;
}


template <class Stack_entry>
class Stack{
public:
    Stack();
    bool empty()const;
    Error_code push(const Stack_entry &item);
    Error_code pop();
    Error_code top(Stack_entry &item) const;
//safety features for for linked structrues
    ~Stack();
    Stack(const Stack<Stack_entry> &original);
    void operator = (const Stack<Stack_entry> &original);
protected:
    Stack_node<Stack_entry> *top_node;
};

template <class Stack_entry>
Stack<Stack_entry> :: Stack()
{
    top_node = NULL;
}

template <class Stack_entry>
bool Stack<Stack_entry> ::empty()const
{
    return top_node == NULL;
}
template <class Stack_entry>
Error_code Stack<Stack_entry> :: push (const Stack_entry &item)
{
    Stack_node<Stack_entry> *new_node = new Stack_node<Stack_entry>(item);
    if(new_node == NULL) return overflow;
    new_node -> next = top_node;
    top_node = new_node;
    return success;
}

template <class Stack_entry>
Error_code Stack<Stack_entry> :: pop()
{
    if(empty()) return underflow;
    Stack_node<Stack_entry> *old_top = top_node;
    top_node = old_top ->next;
    delete old_top;
    return success;
}

template <class Stack_entry>
Error_code Stack<Stack_entry> :: top( Stack_entry &item) const
{
    if(empty()) return underflow;
    item = top_node -> entry;
    return success;
}

template <class Stack_entry>
Stack<Stack_entry>::~Stack()
{
    while(!empty())
        pop();
}

template <class Stack_entry>
Stack<Stack_entry> :: Stack(const Stack<Stack_entry> &original)
{
    Stack_node<Stack_entry> *new_node,*original_node = original.top_node;
    if(original_node == NULL) top_node = NULL;
    else {
        top_node = new_node = new Stack_node<Stack_entry>(original_node->entry);
        while(original_node->next != NULL){
            original_node = original_node ->next;
            new_node -> next = new Stack_node<Stack_entry>(original_node->entry);
            new_node = new_node -> next;
        }
    }
}
template <class Stack_entry>
void Stack<Stack_entry>::operator = (const Stack<Stack_entry> &original)
{
    Stack_node<Stack_entry> *new_top,*new_node,*original_node = original.top_node;
    if(original_node == NULL) new_top = NULL;
    else {
        new_top = new_node = new Stack_node<Stack_entry>(original_node -> entry);
        while(original_node -> next != NULL){
            original_node = original_node -> next;
            new_node -> next = new Stack_node<Stack_entry>(original_node->entry);
            new_node = new_node ->next;
        }
    }
    while(!empty())
        pop();
    top_node = new_top;
}
#endif
