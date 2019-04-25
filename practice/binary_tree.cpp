#include <iostream>
#include <vector>

#define N 10
using namespace std;

struct Node {
    int data;
    Node *left,*right;
    Node();
};

Node :: Node()
{
    left = right = NULL;
}

class Tree {
public:
    Tree();
    void insert(int n);
    void print();
private:
    Node *root;
    void recursive_traverse(Node *p,vector<int> &l);
    void recursive_insert(Node* &p,int n);
};

Tree :: Tree()
{
    root = NULL;
}

void Tree :: recursive_insert(Node* &p, int n)
{
    if(p == NULL){
        p = new Node();
        p->data = n;
    }else if(n < p->data) recursive_insert(p->left,n);
    else if(n > p->data) recursive_insert(p->right,n);
    else cout << "wrong number." << endl;
}

void Tree :: insert( int n)
{
    recursive_insert(root,n);
}

void Tree :: recursive_traverse(Node *p, vector<int> &l)
{
    if(p){
        recursive_traverse(p->left,l);
        l.push_back(p->data);
        recursive_traverse(p->right,l);
    }
}

void Tree :: print()
{
    vector<int> list;
    recursive_traverse(root,list);
    int n = list.size();
    for(int i=0;i<n;i++)
        cout << list[i] << " ";
    cout << endl;
}

int main()
{
    Tree T;
    int array[N] = {16,5,8,7,4,9,3,1,2,20};
    for(int i=0;i<N;i++)
        T.insert(array[i]);
    T.print();
    return 0;
}
