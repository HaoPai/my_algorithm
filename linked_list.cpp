#include <iostream>
using namespace std;
typedef struct node 
{
	int num ;
	struct node *next;
}node,*List;

List createList()
{
	node* head = new node;
	if(head==NULL)
		return NULL;
	head->next = NULL;
	return head;
}

node* getPosition(int num,List L)
{
	if(num<0)
		return NULL;
	if(num==0)
		return L;
	node *p = L->next;
	while(num>0&&p->next!=NULL)
	{
		
	
bool addNode(int number, List L)
{
}	
