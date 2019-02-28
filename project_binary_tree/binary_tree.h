#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_
#include <stdlib.h>
#include <iostream>
#include "global.h"

using namespace std;

template <class Entry>
struct  Binary_node {
//data members:
    Entry data;
    Binary_node<Entry> *left;
    Binary_node<Entry> *right;
// constructers:
    Binary_node();
    Binary_node(const Entry &x);
//virtual functions 
    virtual void set_balance(Balance_factor b);
    virtual Balance_factor get_balance() const;
};

template <class Entry>
void Binary_node<Entry>::set_balance(Balance_factor b)
{
}

template <class Entry>
Balance_factor Binary_node<Entry>::get_balance() const
{
    return equal_height;
}

template <class Entry>
class Binary_tree {
public:
    Binary_tree();
    bool empty() const;
    int height() const;
    //int size() const;
    //void clear();
    Error_code insert(const Entry &x);
    void preorder(void (*visit)(Entry &));
    void inorder(void (*visit)(Entry &));
    void postorder(void (*visit)(Entry &));
    //Binary_tree(const Binary_tree<Entry> &original);
    //Binary_tree & operator = (const Binary_tree<Entry> &original);
      
protected:
    Binary_node<Entry>* root;

    //functions 
    void recursive_preorder(Binary_node<Entry> *sub_root,void (*visit)(Entry&));
    void recursive_inorder(Binary_node<Entry> *sub_root,void (*visit)(Entry&));
    void recursive_postorder(Binary_node<Entry> *sub_root,void (*visit)(Entry&));
    Error_code recursive_insert( Binary_node<Entry>* &subroot,const Entry &x);
int recursive_height(Binary_node<Entry> *sub_root) const;
};


template <class Entry>
Binary_node<Entry> :: Binary_node()
{
    left = NULL;
    right = NULL;
}

template <class Entry>
Binary_node<Entry>::Binary_node(const Entry  &x)
{
    data = x;
    left = NULL;
    right = NULL;
}

template <class Entry>
Binary_tree<Entry>::Binary_tree()
{
    root = NULL;
}

template <class Entry>
bool Binary_tree<Entry>::empty() const
{
    return root == NULL;
}

template <class Entry>
int Binary_tree<Entry>::height() const
{
    return recursive_height(root);
}

template <class Entry>
int Binary_tree<Entry>::recursive_height(Binary_node<Entry> *sub_root) const
{
    if(sub_root == NULL)
        return 0;
    else{
        int left = recursive_height(sub_root->left);
        int right = recursive_height(sub_root->right);
        return (left > right)? (left+1):(right+1);
    }
}
template <class Entry>
Error_code Binary_tree<Entry>::recursive_insert(Binary_node<Entry>* &sub_root,const Entry &x)
{
    if(sub_root == NULL)
    {
        sub_root = new Binary_node<Entry>(x);
        if(sub_root == NULL)
            return overflow;
        else
            return success;
    }
    else if(x > sub_root->data)
        return recursive_insert(sub_root->right,x);
    else
        return recursive_insert(sub_root->left,x);
}
    
template <class Entry>
Error_code Binary_tree<Entry>::insert(const Entry &x)
{
    recursive_insert(root,x);
}


template <class Entry>
void Binary_tree<Entry>::preorder(void (*visit)(Entry &))
{
    cout <<"pre_order traverse the tree" << endl;
    recursive_preorder(root,visit);
}

template <class Entry>
void Binary_tree<Entry>::inorder(void (*visit)(Entry &))
{
    recursive_inorder(root,visit);
}

template <class Entry>
void Binary_tree<Entry>::postorder(void (*visit)(Entry &))
{
    recursive_postorder(root,visit);
}

template <class Entry>
void Binary_tree<Entry>::recursive_preorder(Binary_node<Entry> *sub_root,void (*visit)(Entry &x))
{
    if(sub_root!=NULL){
        (*visit)(sub_root->data);
        recursive_preorder(sub_root->left,visit);
        recursive_preorder(sub_root->right,visit);
    }
}
template <class Entry>
void Binary_tree<Entry>::recursive_inorder(Binary_node<Entry> *sub_root,void (*visit)(Entry &x))
{
    if(sub_root!=NULL){
        recursive_inorder(sub_root->left,visit);
        (*visit)(sub_root->data);
        recursive_inorder(sub_root->right,visit);
    }
}
   
template <class Entry>
void Binary_tree<Entry>::recursive_postorder(Binary_node<Entry> *sub_root,void (*visit)(Entry &x))
{
    if(sub_root!=NULL){
        recursive_postorder(sub_root->left,visit);
        recursive_postorder(sub_root->right,visit);
        (*visit)(sub_root->data);
    }
}
#endif
