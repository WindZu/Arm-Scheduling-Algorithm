#include "Node.h"

Node::Node()
{
	this->next = NULL;
}
Node::Node(int data)
{
	this->data = data;
	this->state = false;
	this->next = NULL;

	void addNode(int data);
}

Node::~Node()
{}