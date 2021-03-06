#ifndef _GRAGH_H_
#define _GRAGH_H_

#define N 100
#define COMMAND_N 20

#include <iostream>
#include <string>
#include "extended_queue.h"
#include "linked_list.h"

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
    string vertices[N];
    List<int> neighbors[N];
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
            cout << vertices[i] << " ";
            visited[i] = true;
        }

        int next;
        for(int j=0;j<neighbors[i].size();j++){
            neighbors[i].retrieve(j+1,next);
            if(!visited[next]) q.append(next);
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
    cout << vertices[index]<<" ";
    visited[index] = true;
    int next;
    for(int j=0;j<neighbors[index].size();j++){
        neighbors[index].retrieve(j+1,next);
        if(!visited[next]) recursive_dfs(next,visited);
    } 
    
}

void Graph::add_vertice()
{
    cout << "input a vertice name: ";
    cin >> vertices[len++];
}
void Graph::print_vertices()
{
    for(int i=0;i<len;i++) cout << i << " " << vertices[i]<< endl;
}
void Graph:: add_link()
{
    int i,j;
    cout << "input the indices of two vertices: ";
    cin >> i >> j;
    if(i<len&&j<len&&i!=j) neighbors[i].insert(1,j);
}
void Graph::print()
{
    print_vertices();
    for(int i=0;i<len;i++){
        //cout << "hello"<< neighbors[i].size() << endl;
        for(int j=0;j<neighbors[i].size();j++){
            int next;
            neighbors[i].retrieve(j+1,next);
            cout << vertices[i] << " ——> " <<vertices[next] << endl;
        }
    }
        
}

#endif