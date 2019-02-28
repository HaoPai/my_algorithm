#include <iostream>
using namespace std;

const int maxstack = 10;

enum Error_code { success ,overflow , underflow };

typedef float Stack_entry;

class Stack {
public:
	Stack();
	bool empty() const;
	Error_code pop();
	Error_code top(Stack_entry &item) const;
	Error_code push(const Stack_entry &item);
private:
	int count;
	Stack_entry entry[maxstack];
};

Error_code Stack::push(const Stack_entry &item)
{
	Error_code outcome = success;
	if(count >= maxstack)
		outcome = overflow;
	else
		entry[count++]= item;
	return outcome;
}

Error_code Stack::pop()
{
	Error_code outcome = success;
	if(count == 0)
		outcome = underflow;
	else
		--count;
	return outcome;
}

Error_code Stack::top(Stack_entry &item) const
{
	Error_code outcome = success;
	if(count == 0 )
		outcome = underflow;
	else
		item = entry[count-1];
	return outcome;
}

bool Stack::empty() const
{
	bool outcome = true;
	if(count > 0)
		outcome = false;
	return outcome;
}

Stack::Stack()
{
	count = 0;
}

char get_command()
{
	char command;
	bool waiting = true;
	cout << "Selcet command and press <Enter>:";
	while(waiting){
		cin >> command;
		command= tolower(command);
		if(command == '?'||command =='='||command == '+'||
		command == '-'||command == '*'||command =='/'||
		command == 'q')  waiting = false;
		else
		{
			cout << "Please enter a valid command:" << endl
			<< "[?] push to stack [=] print top "<<endl
			<< "[Q] quit." << endl;
		}
	}
	return command;
}

bool do_command(char command , Stack &numbers)
{
	float p;
	switch(command){
	case '?':
		cout << "enter a real number:"<<flush;
		cin >> p;
		if(numbers.push(p)==overflow)
			cout << "Warning : Stack full, lost number" <<endl;
		break;
	case '=':
		if(numbers.top(p) == underflow)
			cout << "Stack empty" <<endl;
		else
			cout << p << endl;
		break;
	case 'q':
		return false;
	}
	return true;
}
int main()	
{
	Stack stored_numbers;
	while(do_command(get_command(),stored_numbers));
	return 0;
}
	
