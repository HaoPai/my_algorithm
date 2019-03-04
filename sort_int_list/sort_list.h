#ifndef _SORT_LIST_H_
#define _SORT_LIST_H_
#include <iostream>
#include <ctime>
#include "list.h"

using namespace std;

class Sort_list : public List {
public:
    Sort_list();
    void gen_rand();
    void bubble_sort();
    void select_sort();
    void insert_sort();
    void shell_sort();
    void merge_sort();
    void heap_sort();
    void quick_sort();
    void swap(int &a,int &b);
private:
    void leap_insert_sort(int start,int n, int leap);
    void aux_merge_sort(int start,int end, int array[]);
    int  partition(int start,int end);
    void aux_quick_sort(int start,int end);
    void build_max_heap();
    void adjust_down(int k,int max);
};

Sort_list :: Sort_list()
{
    command[norder] = "gen_rand";
    method[norder] = &List::gen_rand;
    norder ++;
    command[norder] = "bubble_sort";
    method[norder] = &List::bubble_sort;
    norder ++;
    command[norder] = "select_sort";
    method[norder] = &List::select_sort;
    norder ++;
    command[norder] = "insert_sort";
    method[norder] = &List::insert_sort;
    norder ++;
    command[norder] = "shell_sort";
    method[norder] = &List::shell_sort;
    norder ++;
    command[norder] = "merge_sort";
    method[norder] = &List::merge_sort;
    norder ++;
    command[norder] = "heap_sort";
    method[norder] = &List::heap_sort;
    norder ++;
    command[norder] = "quick_sort";
    method[norder] = &List::quick_sort;
    norder ++;
}

void Sort_list ::gen_rand()
{
    cout << "Input n , min , max : ";
    int  n,min,max;
    cin >> n >> min >> max;
    rand_file(n,min,max);
    input();
}

void Sort_list :: bubble_sort()
{
    int  n = data.size();
    for(int i=0;i<n-1;i++){
        bool flag = false;
        for(int j= n-1;j>i;j--) if(data[j] < data[j-1]){
            swap(data[j],data[j-1]);
            flag = true;
        }
        if(flag == false) return;
    }
}

void Sort_list::select_sort()
{
    int n = data.size();
    for(int i=0;i<n-1;i++){
        int min = i;
        for(int j=i+1;j<n;j++) if(data[j] < data[min]){
            min = j;
        }
        swap(data[i],data[min]);
    }
}

void Sort_list :: insert_sort()
{
    int n = data.size();
    for(int i=1;i<n;i++){
        int num = data[i];
        int j = i-1;
        while(j>=0&&num < data[j]){
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = num;
    }
}

void Sort_list :: shell_sort()
{
    int n = data.size();
    int leap = n/3 + 1;
    while(leap!=1){
        for(int i=0;i<leap;i++){
            leap_insert_sort(i,n-1,leap);
        }
        // cout << "leap = " << leap << " ";
        // print();
        leap = leap/3 +1;
    }
    insert_sort();
    //print();
}

void Sort_list::merge_sort()
{
   int n = data.size();
   int *array = new int[n];
   aux_merge_sort(0,n-1,array);
   delete []array;
}

void Sort_list :: heap_sort()
{
    build_max_heap();
    int n = data.size();
    for(int i=n-1;i>0;i--){
        swap(data[0],data[i]);
        adjust_down(0,i);
    }
}
void Sort_list :: quick_sort()
{
    int n = data.size();
    aux_quick_sort(0,n-1);
}

void Sort_list::swap(int &a,int &b){
    int temp = a;
    a= b;
    b= temp;
}

void Sort_list :: leap_insert_sort(int start,int MAX,int leap)
{
    for(int i= start + leap;i<=MAX ; i += leap){
        int num = data[i];
        int j = i - leap;
        while(j>=0&& num < data[j]){
            data[j+leap] = data[j];
            j-=leap;
        }
        data[j+leap] = num;
    }
}
void Sort_list :: aux_merge_sort(int start, int end, int array[])
{ 
    if(start >= end) return;
    int middle = (start + end)/2;
    aux_merge_sort(start,middle,array);
    aux_merge_sort(middle+1,end,array);
    int cursor = start,i=start,j=middle+1;
    while(i<=middle && j<= end){
        if(data[i] < data[j]) array[cursor++] = data[i++];
        else array[cursor++] = data[j++];
    }
    while(i<=middle) array[cursor++] = data[i++];
    while(j<=end) array[cursor++] = data[j++];
    for(int i = start;i<=end;i++) data[i] = array[i];
}

int Sort_list :: partition(int start,int end)
{
    int middle = (start + end) / 2;
    swap(data[start],data[middle]);
    int pivot = data[start];
    while(start < end){
        while(start<end && data[end] >= pivot) end --;
        data[start] = data[end];
        while(start < end && data[start] <= pivot) start ++;
        data[end] = data[start];
    }
    data[start] = pivot;
    return start;
}

void Sort_list :: aux_quick_sort(int start, int end)
{
    if(start < end){
        int pivot = partition(start,end);
        aux_quick_sort(start,pivot-1);
        aux_quick_sort(pivot+1,end);
    }
    
}

void Sort_list :: build_max_heap()
{
    int n = data.size();
    for(int i = n/2;i>=0;i--)
        adjust_down(i,n);
}

void Sort_list :: adjust_down(int k,int max)
{
    int item = data[k];
    for(int i=2*k +1;i<max; i = i*2 +1){
        if(i<max-1&&data[i] < data[i+1])
            i++;
        if(item >= data[i]) break;
        else{
            data[k] = data[i];
            k = i;
        }

    }
    data[k] = item;
}
#endif