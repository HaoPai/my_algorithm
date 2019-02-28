#ifndef _GRAGH_H_
#define _GRAGH_H_

#define N 100
#define COMMAND_N 20

#include <iostream>
#include <string>
#include "extended_queue.h"
#include "linked_list.h"


struct Edge_node{
    int node_one;
    int node_two;
    int weight;
    Edge_node *link_one;
    Edge_node *link_two;
    Edge_node();
};

 Edge_node :: Edge_node(){
    node_one = node_two = weight = -1;
    link_one = link_two = NULL;
}
   


struct V_node{
    string name;
    Edge_node *first_edge;
    V_node();
};

V_node :: V_node()
{
    first_edge = NULL;
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
    void make_order(int &i,int &j);
    int compare(int node, Edge_node *p,Edge_node *q);
    void link(int node,Edge_node *p,Edge_node *q);
    Edge_node * get_next(int node,Edge_node *p);
    int get_index(int node,Edge_node *p);
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

void Graph::make_order(int &i, int &j)
{
    if(i>j){
        int temp = i;
        i = j;
        j = temp;
    }
}

int Graph::compare(int node,Edge_node *p,Edge_node *q){
    int first,second;
    if(node == p->node_one){
        first = p->node_two;
    }else{
        first = p->node_one;
    }

    if(node == q->node_one){
        second = q->node_two;
    }else{
        second = q->node_one;
    }
    return first - second;
}

void Graph::link(int node,Edge_node *p,Edge_node *q)
{
    if(node == p->node_one) p->link_one = q;
    else p->link_two = q;
}

Edge_node* Graph:: get_next(int node,Edge_node *p)
{
    if(p->node_one == node) return p->link_one;
    else return p->link_two;
}

int  Graph::get_index(int node,Edge_node *p)
{
    if(node == p->node_one) return p->node_two;
    else return p->node_one;
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

        Edge_node *p = vertices[i].first_edge;
        while(p!=NULL){
            int j = get_index(i,p);
            if(!visited[j]) q.append(j);
            p = get_next(i,p);
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
    Edge_node *p = vertices[index].first_edge;
    while(p!=NULL){
        int j = get_index(index,p);
        if(!visited[j])
            recursive_dfs(j,visited);
        p = get_next(index,p);
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
    Edge_node *new_edge = new Edge_node();
    Edge_node *previous,*p;
    make_order(i,j);
    new_edge->node_one = i;
    new_edge->node_two = j;

    if(vertices[i].first_edge == NULL){
        vertices[i].first_edge = new_edge;
    }else if(compare(i,new_edge,vertices[i].first_edge)<0){
        link(i,new_edge,vertices[i].first_edge);
        vertices[i].first_edge = new_edge;
    }else if(compare(i,new_edge,vertices[i].first_edge)>0){
        previous = vertices[i].first_edge;
        p = get_next(i,previous);
        while(p!=NULL&&compare(i,new_edge,p)>0){
            previous = p;
            p = get_next(i,previous);
        }
        if(p!=NULL && compare(i,new_edge,p)==0) cout << "add_link error, you have added the link already!" <<endl;
        else{
            link(i,new_edge,p);
            link(i,previous,new_edge);
        }
    }else cout << "add_link error, you have added the link already!" <<endl;


    if(vertices[j].first_edge == NULL){
        vertices[j].first_edge = new_edge;
    }else if(compare(j,new_edge,vertices[j].first_edge)<0){
        link(j,new_edge,vertices[j].first_edge);
        vertices[j].first_edge = new_edge;
    }else if(compare(j,new_edge,vertices[j].first_edge)>0){
        previous = vertices[j].first_edge;
        p = get_next(j,previous);
        while(p!=NULL&&compare(j,new_edge,p)>0){
            previous = p;
            p = get_next(j,previous);
        }
        if(p!=NULL && compare(j,new_edge,p)==0) cout << "add_link error, you have added the link already!" <<endl;
        else{
            link(j,new_edge,p);
            link(j,previous,new_edge);
        }
    }else cout << "add_link error, you have added the link already!" <<endl;


    
}

void Graph::print()
{
    print_vertices();
    cout << endl;
    for(int i=0;i<len;i++){
        //cout << vertices[i].name <<":"<<endl;
        Edge_node *p = vertices[i].first_edge;
        while(p!=NULL){
            if(p->node_one == i)
                cout << vertices[p->node_one].name << "————" <<vertices[p->node_two].name << endl;
            p = get_next(i,p);
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