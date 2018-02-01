#include <iostream>
using namespace std;
class Node {
public:
	int data;
	bool state;
	Node *next;

	Node();
	Node(int data);
	~Node();
};

