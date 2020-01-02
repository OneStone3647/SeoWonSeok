#include <iostream>

using namespace std;

struct Stack
{
	int data;
	Stack* link;
};

void push(Stack** top, int data)
{
	Stack* tmp = new Stack;
	tmp->link = *top;
	tmp->data = data;
	*top = tmp;
	cout << "top : " << (*top)->data << endl;
}

void pop(Stack** top)
{
	if (top == NULL)
	{
		return;
	}
	Stack* tmp = *top;
	*top = tmp->link;		
	cout << "tmp : " << tmp->data << endl;
	delete tmp;
}

void main()
{
	Stack* top = NULL;
	push(&top, 10);
	push(&top, 7);
	push(&top, 23);
	while (top != NULL)
	{
		pop(&top);
	}
}