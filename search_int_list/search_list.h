#ifndef _search_list_h_
#define  _search_list_h_

#include <iostream>
#include "list.h"

class Search_list : public List{
public:
    Search_list();
    void linear_search();
    void binary_search();
private:
    int aux_binary_search(int s);
};

Search_list :: Search_list()
{
    command[norder] = "linear_search";
    method[norder] = &List::linear_search;
    norder ++;
    command[norder] = "binary_search";
    method[norder] = &List::binary_search;
    norder++;
}

void Search_list :: linear_search()
{
    int s;
    cout << "Input an item to search: ";
    cin >> s;
    int n = data.size();
    int i = 0;
    while(i<n&&data[i]!=s)
        i++;
    if(i<n) cout << "Found, index: " <<i << endl;
    else cout <<"Not found." << endl;
}

void Search_list :: binary_search()
{
    int s,index;
    cout << "Input an item to search: ";
    cin >> s;
    index = aux_binary_search(s);
    if(index >= 0) cout << "Found, index: " << index << endl;
    else  cout <<"Not found." << endl;
}

int Search_list :: aux_binary_search(int s)
{
    int low =0,hign = data.size(),middle;
    while(low<=hign){
        middle = (low+hign)/2;
        if(data[middle] == s) return middle;
        else if(s > data[middle]) low = middle +1;
        else hign = middle -1;
    }
    return -1;
}







#endif