#include<iostream>
#include<stack>
#include<string>

using namespace std;

class person 
{
	string name;
	string address;
};

int main()
{
	person p[10];
	int n;
	double item;
	stack<double> numbers;
	cout << "Type in an integer n followed by n decimalnumbers."<<endl
	     <<"the numbers will be printed in reverse order."<<endl;
	cin >> n;
	for(int i=0;i<n;i++)
	{
		cin >> item;
		numbers.push(item);
	}
	cout << endl << endl;
	while(!numbers.empty())
	{
		cout << numbers.top()<<" ";
		numbers.pop();
	}
	cout << endl;
}
