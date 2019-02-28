#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <cstddef>
#include "error_code.h"
template <class Queue_entry>
struct Queue_node{
//data members
    Queue_entry entry;
    Queue_node *next;
// constructors
    Queue_node();
    Queue_node(const Queue_entry &item,Queue_node *link = NULL);
};

template <class Queue_entry>
Queue_node<Queue_entry>::Queue_node()
{
    next = NULL;
}

template <class Queue_entry>
Queue_node<Queue_entry>::Queue_node(const Queue_entry &item, Queue_node<Queue_entry> *link)
{
    entry = item;
    next = link;
}

template <class Queue_entry>
class Queue {
public:
    Queue();
    bool empty()const;
    Error_code append(const Queue_entry &item);
    Error_code serve();
    Error_code retrieve(Queue_entry &item)const;
// safety features for linked structures
    ~Queue();
    Queue(const Queue &original);
    void operator = (const Queue &original);
protected:
    Queue_node<Queue_entry> *front,*rear;
};

template <class Queue_entry>
Queue<Queue_entry>::Queue()
{
    front = rear = NULL;
}

template <class Queue_entry>
bool Queue<Queue_entry> :: empty() const
{
    return front == NULL;
}

template <class Queue_entry>
Error_code Queue<Queue_entry> :: append(const Queue_entry &item)
{
    Queue_node<Queue_entry> *new_node = new Queue_node<Queue_entry>(item);
    if(new_node == NULL) return overflow;
    if(rear == NULL){
        front = rear = new_node;
    }
    else {
        rear -> next = new_node;
        rear = new_node;
    }
    return success;
}

template <class Queue_entry>
Error_code Queue<Queue_entry> :: serve()
{
    if(empty()) return underflow;
    Queue_node<Queue_entry> *old_front = front;
    front = front -> next;
    if(front == NULL) rear = NULL;
    delete old_front;
    return success;
}

template <class Queue_entry>
Error_code Queue<Queue_entry>::retrieve(Queue_entry &item)const
{
    if(empty()) return underflow;
    item = front -> entry;
    return success;
}
template <class Queue_entry>
Queue<Queue_entry>::~Queue()
{
    while(!empty())
        serve();
}

template <class Queue_entry>
Queue<Queue_entry>::Queue(const Queue<Queue_entry> &original)
{  
    Queue_node<Queue_entry> *original_node = original.front;
    if(original_node != NULL){
        front = rear = new Queue_node<Queue_entry>(original_node->entry);
        while(original_node->next != NULL){
            original_node = original_node -> next;
            rear -> next = new Queue_node<Queue_entry>(original_node->entry);
            rear = rear ->next;
        }
    }
    else front = rear = NULL;
}
 
template <class Queue_entry>
void Queue<Queue_entry>:: operator = (const Queue<Queue_entry> &original)
{
    while(!empty())
        serve();
    Queue_node<Queue_entry> *original_node = original.front;
    if(original_node != NULL){
        front = rear = new Queue_node<Queue_entry>(original_node -> entry);
        while(original_node -> next != NULL){
            original_node = original_node -> next;
            rear -> next = new Queue_node<Queue_entry>(original_node ->entry);
            rear = rear -> next;
        }
    }
}

#endif
