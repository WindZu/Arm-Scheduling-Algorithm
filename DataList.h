#include <iostream>
#include "Node.h"
using namespace std;

class DataList
{
public:
	Node * head;
	DataList();
	~DataList();

	void addNode(int data);//在末端添加节点
};