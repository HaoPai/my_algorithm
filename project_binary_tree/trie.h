#ifndef _TRIE_H_
#define _TRIE_H_
#include <stdio.h>
#include <iostream>
#include "global.h"
#include "key.h"
using namespace std;
const int num_chars = 28;
template <class Record>
struct Trie_node{
//data members
    Record *data;
    Trie_node *branch[num_chars];
//constructors
    Trie_node();
};

template <class Record>
Trie_node<Record>::Trie_node()
{
    int i;
    for(i=0;i<num_chars;i++)
        branch[i] = NULL;
    data = NULL;
}

template <class Record>
class Trie{
public:
    Error_code trie_search(const Key &target,Record &x)const;
    Error_code insert(const Record &new_entry);
    void traversal(void (*visit)(Record &x))const;
    Trie();
private:
    Trie_node<Record> *root;
    void recursive_traversal(Trie_node<Record> *sub_root,void (*visit)(Record &x)) const;
};

template <class Record>
Trie<Record>::Trie()
{
    root = NULL;
}
template <class Record>
Error_code Trie<Record> :: trie_search(const Key &target,Record &x) const
{
    int position = 0;
    char next_char;
    Trie_node<Record> *location = root;
    while(location != NULL && (next_char = target.key_letter(position))!=' '){
        location = location-> branch[alphabetic_order(next_char)];
        position++;
    }
    if(location !=  NULL && location-> data != NULL){
        x = *(location->data);
        return success;
    }
    else
        return not_present;
}

template <class Record>
Error_code Trie<Record>::insert(const Record &new_entry)
{
    Error_code result = success;
    if(root == NULL){ root = new Trie_node<Record>;}
    int position = 0;
    char next_char;
    Trie_node<Record> *location = root;
    while(location!=NULL && (next_char = new_entry.key_letter(position))!=' '){
        int next_position = alphabetic_order(next_char);
        if(location->branch[next_position]==NULL)
            location->branch[next_position]= new Trie_node<Record>;
        location = location->branch[next_position];
        position++;
    }
    if(location->data != NULL) result = duplicate_error;
    else location->data = new Record(new_entry);
    return result;
}

template <class Record>
void Trie<Record>::traversal(void (*visit)(Record &x)) const
{
    recursive_traversal(root,visit);
}    

template <class Record>
void Trie<Record>::recursive_traversal(Trie_node<Record> *sub_root,void (*visit)(Record &x))const
{
    if(sub_root != NULL){
        if(sub_root->data!= NULL) (*visit)(*(sub_root->data));       
        int i;
        for(i=0;i<num_chars;i++)
            recursive_traversal(sub_root->branch[i],visit);
    }
}
#endif
