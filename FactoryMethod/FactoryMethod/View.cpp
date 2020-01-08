#include "View.h"



View::View()
{
}


View::~View()
{
}

MyView::MyView()
{
	cout << "Create MyView" << endl;
}

MyView::~MyView()
{
	cout << "Destroy MyView" << endl;
}

void MyView::Render()
{
	cout << "Render MyView" << endl;
}
