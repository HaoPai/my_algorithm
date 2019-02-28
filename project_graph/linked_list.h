#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include <cstddef>
#include "error_code.h"

using namespace std;

template <class List_entry>
struct List_node{
//data member
    List_entry entry;
    List_node<List_entry> *next;
//constructors
    List_node();
    List_node(const List_entry &item,List_node *link = NULL);
};

template <class List_entry>
List_node<List_entry>::List_node(){
    next = NULL;
}

template <class List_entry>
List_node<List_entry>::List_node(const List_entry &item,List_node<List_entry> *link){
    entry = item;
    next = link;
}

template <class List_entry>
class List{
public:
    List();
    bool empty() const;
    int size() const;
    void clear();
    Error_code insert(int position,const List_entry &item);//position start from 1
    Error_code retrieve(int position,List_entry &x) const;
    Error_code remove(int position,List_entry &x);
protected:
    int count;
    List_node<List_entry> head;
    List_node<List_entry> *tail;
    List_node<List_entry>* get_position(int position) const;
};

template <class List_entry>
List<List_entry>::List(){
    count = 0;
    head.next = NULL;
}

template <class List_entry>
bool List<List_entry> :: empty()const{
    return count == 0;
}

template <class List_entry>
int List<List_entry>::size()const{
    return count;
}

template <class List_entry>
void List<List_entry> :: clear(){
    count =0;
    List_node<List_entry> *p = head->next,*q;
    while(p!=NULL){
        q = p;
        p = p->next;
        delete q;
    }
    head ->next = NULL;
}

template <class List_entry>
Error_code List<List_entry> :: insert(int position,const List_entry &item){
    if(position<1||position > count +1 ) return overflow;
    List_node<List_entry> *new_node;
    List_node<List_entry> *previous;
    if(position == 1) previous = &head;
    else previous = get_position(position-1);
    new_node = new List_node<List_entry>(item,previous->next);
    previous->next = new_node;
    count ++;
    return success;
}

template <class List_entry>
List_node<List_entry>* List<List_entry> :: get_position(int position)const
//precondition: position is a valid integer
{
    List_node<List_entry> *location  = head.next;
    while(position-- >1 ) location = location ->next;
    return location;
}

template <class List_entry>
Error_code List<List_entry> :: retrieve(int position,List_entry &x) const {
    if(position<1||position>count) return overflow;
    List_node<List_entry> *p = get_position(position);
    x = p->entry;
    return success;
}

template <class List_entry>
Error_code List<List_entry> :: remove(int position,List_entry &x){
    if(position<1||position>count) return underflow;
    List_node<List_entry> *previous,*p;
    if(position == 1 ) previous = &head;
    else previous = get_position(position -1);
    p = previous ->next;
    x = p->entry;
    previous ->next = p->next;
    delete p;
    count --;
    return success;
}


#endif