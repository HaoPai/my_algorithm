#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>
#define COMMAND_N 100
using namespace std;

class List{
public:
    int norder;
    string command[COMMAND_N];
    void (List::*method[COMMAND_N])();
    List();
    void input();
    void print();
    void to_file();
    void stl_sort();
    virtual void linear_search(){};
    virtual void binary_search(){};
    virtual void gen_rand(){};
    virtual void bubble_sort(){};
    virtual void select_sort(){};
    virtual void insert_sort(){};
    virtual void shell_sort(){};
    virtual void merge_sort(){};
    virtual void heap_sort(){};
    virtual void quick_sort(){};
protected:
    vector<int> data;
};

List::List()
{
    norder = 4;
    command[0] = "input";
    command[1] = "print";
    command[2] = "to_file";
    command[3] = "stl_sort";
    method[0] = &List::input;
    method[1] = &List::print;
    method[2] = &List::to_file;
    method[3] = &List::stl_sort;
}


void List :: input()
{
    data.clear();
    ifstream in("data.txt");
    int temp;
    while(in.peek()!=EOF){
        in >> temp;
        data.push_back(temp);
    }
    in.close();
}

void List::print()
{
    int n = data.size();
    for(int i=0;i<n;i++)
        cout << data[i] << " ";
    cout << endl;
}



void List::to_file()
{
    int n = data.size();
    ofstream out("out.txt");
    for(int i=0;i<n;i++)
        out << data[i] << " ";
    out << endl;
    out.close();
}

void List::stl_sort()
{
    sort(data.begin(),data.end());
}


#endif

