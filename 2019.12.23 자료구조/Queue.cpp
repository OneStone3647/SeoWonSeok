#include <iostream>

using namespace std;

struct Queue
{
	int data;
	Queue* Next;
};

void Enqueue(Queue** front, Queue** rear, int data)
{
	Queue* tmp = new Queue;
	tmp->data = data;
	tmp->Next = NULL;
	// 초기상태
	if (*front == NULL && *rear == NULL)
	{
		*front = tmp;
		*rear = tmp;
	}
	else
	{
		(*rear)->Next = tmp;
		*rear = tmp;
	}
}

void Dequeue(Queue** front, Queue** rear)
{
	if (*front != NULL && *rear != NULL)
	{
		Queue* tmp;
		tmp = *front;
		*front = (*front)->Next;
		delete tmp;
		if (*front == NULL)
		{
			*rear = NULL;
		}
	}
}

void print(Queue** front, Queue** rear)
{
	cout << "--------------" << endl;
	cout << "Front : " << *front << endl;
	if (*front != NULL)
	{
		cout << "Front Data : " << (*front)->data << endl;
		cout << "Front Next : " << (*front)->Next << endl;
	}
	cout << "Rear : " << *rear << endl;
	if (*rear != NULL)
	{
		cout << "Rear Data : " << (*rear)->data << endl;
		cout << "Rear Next : " << (*rear)->Next << endl;
	}
	cout << "--------------" << endl;
}

void main()
{
	Queue* Front = NULL;
	Queue* Rear = NULL;
	Enqueue(&Front, &Rear, 10);
	print(&Front, &Rear);
	Enqueue(&Front, &Rear, 7);
	print(&Front, &Rear);
	Enqueue(&Front, &Rear, 23);
	print(&Front, &Rear);
	while (Front != NULL && Rear != NULL)
	{
		Dequeue(&Front, &Rear);
		cout << "Dequeue" << endl;
		print(&Front, &Rear);
	}
}