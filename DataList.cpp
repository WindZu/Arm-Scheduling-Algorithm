#include "DataList.h"

DataList::DataList()
{
	this->head = NULL;
}
DataList::~DataList()
{}

void DataList::addNode(int data)
{
	Node *temp = new Node(data);

	if (this->head == NULL)
	{
		this->head = temp;
	}
	else
	{
		Node *p = this->head;
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = temp;
	}
}