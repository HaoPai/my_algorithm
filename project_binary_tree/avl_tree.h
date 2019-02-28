#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_
#include "search_tree.h"
template <class Record>
struct AVL_node : public Binary_node<Record> {
//data member
    Balance_factor balance;
//constructors
    AVL_node();
    AVL_node(const Record &);
//functions 
    void set_balance(Balance_factor b);
    Balance_factor get_balance()const;
};

template <class Record>
AVL_node<Record>::AVL_node()
{
    balance = equal_height;
}
template <class Record>
AVL_node<Record>::AVL_node(const Record &y)
{
    Binary_node<Record>:: data = y;
    balance = equal_height;
}


template <class Record>
void AVL_node<Record>::set_balance(Balance_factor b)
{
    balance = b;
}

template <class Record>
Balance_factor AVL_node<Record>::get_balance()const
{
    return balance;
}

template <class Record>
class AVL_tree: public Search_tree<Record>
{
public:
    Error_code insert(const Record &new_data);
    Error_code remove(Record &old_data);
private:
    Error_code avl_insert(Binary_node<Record>* &sub_root,const Record &new_data, bool &taller );
    void left_balance(Binary_node<Record>* &sub_root);
    void right_balance(Binary_node<Record>* &sub_root);
    void rotate_left(Binary_node<Record>* &sub_root);
    void rotate_right(Binary_node<Record>* &sub_root);
    Error_code avl_remove(Record &old_data, Binary_node<Record>* &sub_root, bool &shorter);
    void remove_right_node(Record &data,Binary_node<Record>* &subroot,bool &shorter);
    void adjust_right(Binary_node<Record>* &sub_root,bool &shorter);
    void adjust_left(Binary_node<Record>* &sub_root,bool &shorter);
    
};

template <class Record>
Error_code AVL_tree<Record>::insert(const Record &new_data)
{
    bool taller;
    return avl_insert(Binary_tree<Record>::root,new_data,taller);
}
template <class Record>
Error_code AVL_tree<Record>::remove(Record &old_data)
{
    bool shorter;
    return avl_remove(old_data,Binary_tree<Record>::root,shorter);
}
template <class Record>
Error_code AVL_tree<Record>::avl_remove(Record &old_data, Binary_node<Record>* &sub_root, bool &shorter)
{
    Error_code result = success;
    if(sub_root == NULL){
        result =  not_present;
        shorter = false;
    }
    else if(sub_root->data == old_data){ 
        Binary_node<Record> *to_delete = sub_root;
        if(sub_root->left == NULL){
            shorter = true;
            sub_root = sub_root ->right;
            delete to_delete;
        }
        else if(sub_root ->right == NULL){
            shorter = true;
            sub_root = sub_root->left;
            delete to_delete;
        }
        else{
            remove_right_node(sub_root->data,sub_root->left,shorter);
            if(shorter == true)
                adjust_left(sub_root,shorter);
    
        }    
    }
    else if(old_data < sub_root->data){
        result =  avl_remove(old_data,sub_root->left,shorter);
        if(shorter == true)
            adjust_left(sub_root,shorter);
    }
    else{
        result =  avl_remove(old_data,sub_root->right,shorter);
        if(shorter == true)
            adjust_right(sub_root,shorter);
    }
    return result;
}
template <class Record>
void AVL_tree<Record>::remove_right_node(Record &data,Binary_node<Record>* &sub_root,bool &shorter)
{
    if(sub_root -> right == NULL){
        data = sub_root->data;
        Binary_node<Record> *to_delete = sub_root;
        sub_root = sub_root -> left;
        delete to_delete;
        shorter = true;
    }
    else{
        remove_right_node(data,sub_root->right,shorter);
        if(shorter == true)
            adjust_right(sub_root,shorter);
    }
}
template <class Record>
void AVL_tree<Record>::adjust_right(Binary_node<Record>* &sub_root,bool &shorter)
{
    Binary_node<Record> *left_tree = sub_root->left;
    switch(sub_root->get_balance()){
        case equal_height:
            sub_root->set_balance(left_higher);
            shorter = false;
            break;
        case left_higher:
            if(left_tree->get_balance()== equal_height )
                shorter = false;
            left_balance(sub_root);
            break;
        case right_higher:
            sub_root->set_balance(equal_height);
            break;
    }
}
template <class Record>
void AVL_tree<Record>::adjust_left(Binary_node<Record>* &sub_root,bool &shorter)
{
    switch(sub_root->get_balance()){
    case equal_height:
        sub_root->set_balance(right_higher);
        shorter = false;
        break;
    case left_higher:
        sub_root->set_balance(equal_height);
        break;
    case right_higher:
        Binary_node<Record> *right_tree = sub_root -> right;
        if(right_tree->get_balance()== equal_height)
            shorter = false;
        right_balance(sub_root);
        break;
    }
}
template<class Record>
Error_code AVL_tree<Record>::avl_insert(Binary_node<Record>* &sub_root,const Record &new_data,bool &taller)
{
    Error_code result = success;
    if(sub_root == NULL){
        sub_root = new AVL_node<Record>(new_data);
        taller = true;
    }
    else if (new_data == sub_root->data){
        result = duplicate_error;
        taller = false;
    }
    else if(new_data < sub_root -> data){
        result = avl_insert(sub_root->left,new_data,taller);
        if(taller == true)
            switch(sub_root->get_balance()){
            case left_higher:
                left_balance(sub_root);
                taller = false;
                break;
            case equal_height:
                sub_root->set_balance(left_higher);
                break;
            case right_higher:
                sub_root -> set_balance(equal_height);
                taller = false;
                break;
            }
    }
    else{
        result = avl_insert(sub_root->right,new_data,taller);
        if(taller == true)
            switch(sub_root->get_balance()){
            case left_higher:
                sub_root ->set_balance(equal_height);
                taller = false;
                break;
            case equal_height:
                sub_root -> set_balance(right_higher);
                break;
            case right_higher:
                right_balance(sub_root);
                taller = false;
                break;
            }
        }
    return result;
}
template <class Record>
void AVL_tree<Record>::left_balance(Binary_node<Record>* &sub_root)
{
    Binary_node<Record>* &left_tree = sub_root -> left;
    switch(left_tree->get_balance()){
    case left_higher:
        sub_root -> set_balance(equal_height);
        left_tree -> set_balance(equal_height);
        rotate_right(sub_root);
        break;
    case equal_height:
        sub_root-> set_balance(left_higher);
        left_tree-> set_balance(right_higher);
        rotate_right(sub_root);
        break;
    case right_higher:
        Binary_node<Record> *sub_tree = left_tree -> right;
        switch(sub_tree->get_balance()){
            case equal_height:
                sub_root -> set_balance(equal_height);
                left_tree -> set_balance(equal_height);
                break;
            case left_higher:
                left_tree-> set_balance(equal_height);
                sub_root -> set_balance(right_higher);
                break;
            case right_higher:
                left_tree -> set_balance(left_higher);
                sub_root -> set_balance(equal_height);
                break;
        }
        sub_tree -> set_balance(equal_height);
        rotate_left(sub_root->left);
        rotate_right(sub_root);
        break;
    }      
}
template <class Record>
void AVL_tree<Record>::right_balance(Binary_node<Record>* &sub_root)
{
    Binary_node<Record>* &right_tree = sub_root->right;
    switch(right_tree->get_balance()){
    case right_higher:
        sub_root -> set_balance(equal_height);
        right_tree -> set_balance(equal_height);
        rotate_left(sub_root);
        break;
    case equal_height:
        sub_root->set_balance(right_higher);
        right_tree->set_balance(left_higher);
        rotate_left(sub_root);
        break;
    case left_higher:
        Binary_node<Record> *sub_tree = right_tree -> left;
        switch(sub_tree->get_balance()){
            case equal_height:
                sub_root -> set_balance(equal_height);
                right_tree -> set_balance(equal_height);
                break;
            case left_higher:
                sub_root -> set_balance(equal_height);
                right_tree -> set_balance(right_higher);
                break;
            case right_higher:
                sub_root -> set_balance(left_higher);
                right_tree -> set_balance(equal_height);
                break;
        }
        sub_tree -> set_balance(equal_height);
        rotate_right(right_tree);
        rotate_left(sub_root);
        break;
    }
}
template <class Record>
void AVL_tree<Record>::rotate_left(Binary_node<Record>* &sub_root)
{
    if(sub_root == NULL || sub_root->right == NULL)
        cout << "Warning: program error detected in rotate_left" << endl;
    else {
        Binary_node<Record> *right_tree = sub_root ->right;
        sub_root->right = right_tree -> left;
        right_tree->left = sub_root;
        sub_root = right_tree;
    }
}

template <class Record>
void AVL_tree<Record>::rotate_right(Binary_node<Record>* &sub_root)
{
    if(sub_root == NULL || sub_root -> left == NULL)
        cout << "Warning : program error detected in rotate_right" << endl;
    else{
        Binary_node<Record> *left_tree = sub_root ->left;
        sub_root->left = left_tree ->right;
        left_tree -> right = sub_root;
        sub_root = left_tree;
    }
}

#endif

