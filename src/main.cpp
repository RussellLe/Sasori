#include <iostream>
#include "sort.hpp"
#include "linked_list.hpp"
#include "search.hpp"
#include "binary_search_tree.hpp"

using namespace std;

int main()
{
	BinarySearchTree<int> bst(7);
	for (int i = 1; i <10; i++)
	{
		if (i != 7)
		{
			bst.addNode(i);
		}
	}
	bst.deleteNode(7);
	std::vector<int> output = bst.DLR();
	for (int i = 0; i < output.size(); i++)
	{
		cout << output[i] << ' ';
	}
	cout << endl;
	return 0;
}