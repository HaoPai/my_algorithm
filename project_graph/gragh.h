#ifndef _GRAGH_H_
#define _GRAGH_H_

#define N 100
#define COMMAND_N 20

#include <iostream>
#include <string>
#include "extended_queue.h"
#include "linked_list.h"


struct Cross_node{
    int tail;
    int head;
    int weight;
    Cross_node *t_link;
    Cross_node *h_link;
    Cross_node();
};

 Cross_node :: Cross_node(){
    tail = head = weight = -1;
    h_link = t_link = NULL;
}
   


struct V_node{
    string name;
    Cross_node *out,
               *in;
    V_node();
};

V_node :: V_node()
{
    out = in = NULL;
}





class Graph{
public:
    Graph();
    void add_vertice();
    void add_link();
    void print();
    int norder;
    string command[COMMAND_N];
    void (Graph:: *method[COMMAND_N])();
    void BFS();
    void DFS();
private:
    int len;
    V_node vertices[N];
    void print_vertices();
    void recursive_dfs(int vertice,bool visited[]);
    void auxiliary_bfs(int vertice,bool visited[]);
};


Graph::Graph()
{
    norder = 5;
    command[0] = "print";
    command[1] = "add_vertice";
    command[2] = "add_link";
    command[3] = "DFS";
    command[4] = "BFS";
    method[0] = &Graph::print;
    method[1] = &Graph::add_vertice;
    method[2] = &Graph::add_link;
    method[3] = &Graph::DFS;
    method[4] = &Graph::BFS;
    len = 0;
}

void Graph::BFS()
{
    bool *visited = new bool[len];
    for(int i=0;i<len;i++) visited[i] = false;
    for(int i=0;i<len;i++) if(!visited[i])
        auxiliary_bfs(i,visited);
    delete []visited;
    cout << endl;
}

void Graph::auxiliary_bfs(int index,bool visited[])
{
    Queue<int> q;
    q.append(index);
    while(!q.empty()){
        int i;
        q.retrieve(i);
        q.serve();

        if(!visited[i]){
            cout << vertices[i].name << " ";
            visited[i] = true;
        }

        Cross_node *p = vertices[i].out;
        while(p!=NULL){
            if(!visited[p->head]) q.append(p->head);
            p = p->h_link;
        }
    }
}

void Graph::DFS()
{
    bool *visited = new bool[len];
    for(int i=0;i<len;i++) visited[i] = false;
    for(int i=0;i<len;i++) if(!visited[i])
        recursive_dfs(i,visited);
    delete []visited;
    cout << endl;
}

void Graph::recursive_dfs(int index,bool visited[])
{
    cout << vertices[index].name<<" ";
    visited[index] = true;
    Cross_node *p = vertices[index].out;
    while(p!=NULL){
        if(!visited[p->head]) recursive_dfs(p->head,visited);
        p = p->h_link;
    }  
}

void Graph::add_vertice()
{
    cout << "input a vertice name: ";
    cin >> vertices[len++].name;
}

void Graph::print_vertices()
{
    for(int i=0;i<len;i++) cout << i << " " << vertices[i].name<< endl;
}

void Graph:: add_link()
{
    int i,j;
    cout << "input the indices of two vertices: ";
    cin >> i >> j;
    if(i==j){
        cout << "wrong link, can not link to itself!" << endl;
        return;
    }
    Cross_node *new_cross = new Cross_node();
    Cross_node *previous,*p;
    new_cross->tail = i;
    new_cross->head = j;

    if(vertices[i].out == NULL){
        vertices[i].out = new_cross;
    }else if(new_cross->head < vertices[i].out ->head){
        new_cross->h_link = vertices[i].out;
        vertices[i].out = new_cross;
    }else if(vertices[i].out->head < new_cross->head){
        previous = vertices[i].out;
        p = previous->h_link;
        while(p!=NULL&&p->head < new_cross->head){
            previous = p;
            p = previous->h_link;
        }
        if(p!=NULL && p->head == new_cross->head) cout << "add_link error, you have added the link already!" <<endl;
        else{
            new_cross->h_link = p;
            previous ->h_link = new_cross;
        }
    }else cout << "add_link error, you have added the link already!" <<endl;


    if(vertices[j].in == NULL){
        vertices[j].in = new_cross;
    }else if(new_cross->tail < vertices[j].in ->tail){
        new_cross->t_link = vertices[j].in;
        vertices[j].in = new_cross;
    }else if(new_cross->tail > vertices[j].in->tail){
        previous = vertices[j].in;
        p = previous->t_link;
        while(p!=NULL&&p->tail < new_cross->tail){
            previous = p;
            p = previous->t_link;
        }
        if(p!=NULL && p->tail == new_cross->tail) cout << "add_link error, you have added the link already!" <<endl;
        else{
            new_cross->t_link = p;
            previous ->t_link = new_cross;
        }
    }else cout << "add_link error, you have added the link already!" <<endl;
}

void Graph::print()
{
    print_vertices();
    cout << endl;
    for(int i=0;i<len;i++){
        Cross_node *p = vertices[i].out;
        while(p!=NULL){
            cout << vertices[p->tail].name << "————>" <<vertices[p->head].name << endl;
            p = p-> h_link;
        }
    }

    // for(int i=0;i<len;i++){
    //     Cross_node *p = vertices[i].in;
    //     while(p!=NULL){
    //         cout <<vertices[p->head].name << "<————" << vertices[p->tail].name << endl;
    //         p = p-> t_link;
    //     }
    // }
        
}

#endif