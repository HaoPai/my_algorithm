#ifndef _EXTENDED_QUEUE_H_
#define _EXTENDED_QUEUE_H_
#include "queue.h"

template <class Queue_entry>
class Extended_queue : public Queue<Queue_entry>{
public:
    bool full()const;
    int size() const;
    void clear();
    Error_code serve_and_retrieve(Queue_entry &item);
};

template <class Queue_entry>
bool Extended_queue<Queue_entry>::full()const
{
    return false;
}

template <class Queue_entry>
int Extended_queue<Queue_entry>::size()const
{
    Queue_node<Queue_entry> *window = Queue<Queue_entry> ::front;
    int count;
    while(window!=NULL){
        count ++;
        window = window -> next;
    }
    return count;
}

template <class Queue_entry> 
void Extended_queue<Queue_entry>::clear()
{
    while(!Queue<Queue_entry>::empty())
        Queue<Queue_entry>::serve();
}

template <class Queue_entry>
Error_code Extended_queue<Queue_entry> :: serve_and_retrieve(Queue_entry &item)
{
    if(Queue<Queue_entry>::empty()) return underflow;
    item = Queue<Queue_entry>::front -> entry;
    Queue<Queue_entry>::serve();
    return success;
}
#endif
