#ifndef _ALPHABETIC_H_
#define _ALPHABETIC_H_
#include <iostream>
#include "b_tree.h"
using namespace std;
void print_char(char &);
void print_char(char &x)
{
    cout << x << endl;
}
class Alphabetic : public B_tree<char,5>{
public:
    void search();
    void insert();
    void traversal();
    void remove();
private:
};

void Alphabetic::search()
{
    cout << "search function called!"<<endl;
}

void Alphabetic::insert()
{
    char c;
    cout << "please input a alphabetic char: ";
    cin >> c;
    B_tree<char,5>::insert(c);
}

void Alphabetic::traversal()
{
    B_tree<char,5>::traversal(print_char);
}
void Alphabetic::remove()
{
    cout << "please input the char to be removed: ";
    char c;
    cin >> c;
    B_tree<char,5>::remove(c);
}
#endif
