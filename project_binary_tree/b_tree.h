#ifndef _B_TREE_H_
#define _B_TREE_H_
#include "global.h"
template <class Record , int order>
struct B_node{
//data menbers:
    int count;
    Record data[order -1];
    B_node<Record,order> *branch[order];
//coonstructor 
    B_node();
};

template <class Record,int order>
B_node<Record,order>::B_node()
{
    count =0;
}

template <class Record,int order>
class B_tree{
public:
    B_tree();
    Error_code search_tree(Record &target);
    Error_code insert(const Record &new_entry);
    Error_code remove(const Record &target);
    void traversal(void (*visit)(Record &x));
private:
    B_node<Record,order> *root;
    Error_code recursive_search_tree(B_node<Record,order> *sub_root,Record &target);
    Error_code search_node(B_node<Record,order> *current,const Record &target,int &position);
    Error_code push_down(B_node<Record,order> *current,const Record &new_entry,Record &median,B_node<Record,order> *&right_branch);
    void push_in(B_node<Record,order> *current,const Record &new_entry,B_node<Record,order> *right_branch, int position);
    void split_node(B_node<Record,order> *current,const Record &new_entry,B_node<Record,order> *extra_branch,int position,B_node<Record,order> *&right_half, Record &median);
    void recursive_traversal(B_node<Record,order> *current,void (*visit)(Record &x));
    Error_code recursive_remove(B_node<Record,order> *current,const Record &target);
    void remove_data(B_node<Record,order> *current,int position);
    void copy_in_predecessor(B_node<Record,order> *current,int position);
    void restore(B_node<Record,order> *current,int position);
    void move_left(B_node<Record,order> *current,int position);
    void move_right(B_node<Record,order> *current,int position);
    void combine(B_node<Record,order> *current,int position);    
};

template <class Record,int order>
B_tree<Record,order>::B_tree()
{
    root = NULL;
}

template <class Record,int order>
Error_code B_tree<Record,order>::search_tree(Record &target)
{
    return recursive_search_tree(root,target);
}

template <class Record,int order>
Error_code B_tree<Record,order>::recursive_search_tree(B_node<Record,order> *current, Record &target)
{
    Error_code result= not_present;
    int position;
    if(current!=NULL)
    {
        result = search_node(current,target,position);
        if(result == not_present)
            result = recursive_search_tree(current->branch[position],target);
        else
            target = current->data[position];
    }
    return result;
}

template <class Record,int order>
Error_code B_tree<Record,order>::search_node(B_node<Record,order> *current,const Record &target,int &position)
{
    position =0;
    while(position < current->count&& target > current->data[position])
        position ++;
    if(position<current->count&&target==current->data[position])
        return success;
    else
        return not_present;
}

template <class Record,int order>
Error_code B_tree<Record,order>::insert(const Record &new_entry)
{
    Record median;
    B_node<Record,order> *right_branch,*new_root;
    Error_code result = push_down(root,new_entry,median,right_branch);
    if(result == overflow){
        new_root = new B_node<Record,order>;
        new_root->count =1;
        new_root->data[0] = median;
        new_root->branch[0] = root;
        new_root->branch[1] = right_branch;
        root= new_root;
        result= success;
    }
    return result;
}

template <class Record,int order>
Error_code B_tree<Record,order>::push_down(B_node<Record,order> *current,const Record &new_entry,Record &median,B_node<Record,order> *&right_branch)
{
    Error_code result;
    int position;
    if(current == NULL){
        median = new_entry;
        right_branch= NULL;
        result = overflow;
    }
    else {
        if(search_node(current,new_entry,position)==success)
            result = duplicate_error;
        else {
            Record extra_entry;
            B_node<Record,order> *extra_branch;
            result = push_down(current->branch[position],new_entry,extra_entry,extra_branch);
            if(result == overflow){
                if(current->count < order -1){
                    result = success;
                    push_in(current,extra_entry,extra_branch,position);
                }
                else split_node(current,extra_entry,extra_branch,position,right_branch,median);
            }
        }
    }
    return result;
}

template <class Record,int order>
void B_tree<Record,order>::push_in(B_node<Record,order> *current,const Record &new_entry, B_node<Record,order> *right_branch,int position)
{
    for(int i = current->count;i>position;i--){
        current->data[i]=current->data[i-1];
        current->branch[i+1]=current->branch[i];
    }
    current ->data[position]= new_entry;
    current->branch[position+1]=right_branch;
    current->count ++;
}

template <class Record,int order>
void B_tree<Record,order>::split_node(B_node<Record,order> *current,const Record &extra_entry,B_node<Record,order> *extra_branch,int position,B_node<Record,order>* &right_half,Record &median)
{
    right_half = new B_node<Record,order>;
    int mid = order/2;
    if(position <= mid){
        for(int i=mid;i<order-1;i++){
            right_half->data[i-mid]=current->data[i];
            right_half->branch[i-mid+1]= current->branch[i+1];
        }
        current->count = mid;
        right_half->count = order - mid -1;
        push_in(current,extra_entry,extra_branch,position);
    }
    else {
        mid++;
        for(int i = mid; i< order -1; i++){
            right_half->data[i-mid] = current->data[i];
            right_half->branch[i-mid+1]= current->branch[i+1];
        }
        current->count = mid;
        right_half->count = order -mid -1;
        push_in(right_half,extra_entry,extra_branch,position-mid);
    }
    median = current->data[current->count -1];
    right_half->branch[0]=current->branch[current->count];
    current->count --;
}

template <class Record,int order>
void B_tree<Record,order>::traversal(void (*visit)(Record &x))
{
    recursive_traversal(root,visit);
}

template <class Record,int order>
void B_tree<Record,order>::recursive_traversal(B_node<Record,order> *current,void (*visit)(Record &x))
{
    if(current!=NULL&&current->count>0){
        for(int i=0;i<current->count;i++){
            (*visit)(current->data[i]);
        }
        for(int i=0;i<current->count+1;i++)
            recursive_traversal(current->branch[i],visit);
    }
}

template <class Record , int order>
Error_code B_tree<Record,order>::remove(const Record &target)
{
    Error_code result;
    result = recursive_remove(root,target);
    if(root!=NULL&&root->count ==0){
        B_node<Record,order> *old_root = root;
        root = root->branch[0];
        delete old_root;
    }
    return result;
}
template <class Record,int order>
Error_code B_tree<Record,order>::recursive_remove(B_node<Record,order> *current,const Record &target)
{
    Error_code result;
    int position;
    if(current == NULL) result == not_present;
    else {
        if(search_node(current,target,position)==success){
            result = success;
            if(current->branch[position]!=NULL){
                copy_in_predecessor(current,position);
                recursive_remove(current->branch[position],current->data[position]);
            }
            else remove_data(current,position);
        }
        else result =recursive_remove(current->branch[position],target);
        if(current->branch[position]!=NULL)
            if(current->branch[position]->count <(order-1)/2)
                restore(current,position);
    }
    return result;
}

template <class Record,int order>
void B_tree<Record,order>::copy_in_predecessor(B_node<Record,order> *current,int position)
{
    B_node<Record,order> *leaf = current->branch[position];
    while(leaf->branch[leaf->count]!=NULL)
        leaf = leaf->branch[leaf->count];
    current->data[position]=leaf->data[leaf->count - 1];
}
template <class Record,int order>
void B_tree<Record,order>::remove_data(B_node<Record,order> *current,int position)
{
    for(int i = position;i<current->count -1;i++)
        current->data[i]=current->data[i+1];
    current->count--;
}
template <class Record,int order>
void B_tree<Record,order>::restore(B_node<Record,order> *current,int position)
{
    
    if(position == current ->count)
        if(current->branch[position-1]->count > (order-1)/2)
            move_right(current,position-1);
        else
            combine(current,position);
    else if(position == 0)
        if(current->branch[1]->count > (order-1)/2)
            move_left(current,1);
        else
            combine(current,1);
    else
        if(current->branch[position-1]->count > (order-1)/2)
            move_right(current,position-1);
        else if(current->branch[position+1]->count > (order -1)/2)
            move_left(current,position+1);
        else
            combine(current,position);
}

template <class Record,int order>
void B_tree<Record,order>::move_left(B_node<Record,order> *current,int position)
{
    B_node<Record,order> *left_branch = current->branch[position-1], 
                         *right_branch = current->branch[position];
    left_branch->data[left_branch->count]=current->data[position-1];
    left_branch->branch[++left_branch->count]=right_branch->branch[0];
    current->data[position-1]=right_branch->data[0];
    right_branch->count--;
    for(int i = 0;i<right_branch->count;i++){
        right_branch->data[i]=right_branch->data[i+1];
        right_branch->branch[i]=right_branch->branch[i+1];
    }
    right_branch->branch[right_branch->count]=right_branch->branch[right_branch->count + 1];
}

template <class Record,int order>
void B_tree<Record,order>::move_right(B_node<Record,order> *current,int position)
{
    B_node<Record,order> *left_branch = current->branch[position-1];
    B_node<Record,order> *right_branch = current->branch[position];
    right_branch[right_branch->count+1]=right_branch[right_branch->count];
    for(int i = right_branch->count;i>0;i--){
        right_branch->data[i]=right_branch->data[i-1];
        right_branch->branch[i]=right_branch->branch[i-1];
    }
    right_branch->count++;
    right_branch->data[0] = current->data[position];
    right_branch->branch[0]=left_branch->branch[left_branch->count --];
    current->data[position]=left_branch->data[left_branch->count];
}
    
  template <class Record,int order>
void B_tree<Record,order>::combine(B_node<Record,order> *current,int position)
{
    int i;
    B_node<Record,order> *left_branch = current->branch[position-1],
                         *right_branch = current->branch[position];
    left_branch->data[left_branch->count]=current->data[position-1];
    left_branch->branch[++left_branch->count] = right_branch->branch[0];
    for(i=0;i<right_branch->count;i++){
        left_branch->data[left_branch->count]=right_branch->data[i];
        left_branch->branch[++left_branch->count]=right_branch->branch[i+1];          
    }
    current->count --;
    for(i=position-1;i<current->count;i++){
        current->data[i]=current->data[i+1];
        current->branch[i+1]=current->branch[i+2];
    }
    delete right_branch;
}
         
#endif

