#include <iostream>
#include "Node.h"
using namespace std;

class DataList
{
public:
	Node * head;
	DataList();
	~DataList();

	void addNode(int data);//��ĩ����ӽڵ�
};