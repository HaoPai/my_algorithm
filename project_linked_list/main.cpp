#include <iostream>
#include "linked_list.h"
#include "utility.h"

using namespace std;

class Numbers : List<int>{
public:
    Numbers();
    void print();
    void insert();
    void remove();
    void retrieve();
    void size();
    int norder;
    string command[5];
    void (Numbers:: *method[5])();
private:
};


Numbers :: Numbers()
{
    norder = 5;
    command[0] = "print";
    command[1] = "insert";
    command[2] = "remove";
    command[3] = "retrieve";
    command[4] = "size";

    method[0] = &Numbers::print;
    method[1] = &Numbers::insert;
    method[2] = &Numbers::remove;
    method[3] = &Numbers::retrieve;
    method[4] = &Numbers::size;
}

void Numbers::print()
{
    List_node<int> *p = head.next;
    while(p!=NULL){
        cout << p->entry << " ";
        p = p->next;
    }
    cout << endl;
}
void Numbers::insert()
{
    cout << "input  position and a integer: ";
    int position,num;
    cin >>position >> num;
    if(List<int> :: insert(position,num)!=success)   cout << "insert error!" << endl;
}
void Numbers::remove()
{
    cout << "input a position: ";
    int position,num;
    cin >> position;
    if(List<int> ::remove(position,num) == success)
        cout << num << endl;
    else cout << "remove error!"  << endl;
}

void Numbers::retrieve()
{
    cout << "input a position: ";
    int position,num;
    cin >> position;
    if(List<int> ::retrieve(position,num) == success)
        cout << num << endl;
    else cout << "retrieve error!"  << endl;
}

void Numbers::size()
{
    cout << "the size is :" << count << endl;
}

int main()
{
    Numbers n;
    Shell<Numbers> run(n);
    run.main();
    return 0;

}