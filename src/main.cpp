#include <iostream>
#include "sort.hpp"
#include "linked_list.hpp"

using namespace std;

int main()
{
	LinkedList<int> ll(3);
	for (int i = 5; i < 11; i++)
	{
		ll.addNode(i);
	}
	ll.deleteNodeByIndex(5);
	ll.deleteNodeByValue(7);
	ll.insertNode(999, 5);
	std::vector<int> output = ll.getAllElement();
	for (int i = 0; i < output.size(); i++)
	{
		cout << output[i] << endl;
	}
	return 0;
}