#include <iostream>
#include "sort.hpp"
#include "linked_list.hpp"
#include "search.hpp"
#include "binary_search_tree.hpp"
#include "string_algorithm.h"
#include "trie.h"
#include "automaton.h"
#include "scapegoat_tree.hpp"

using namespace std;

int main()
{
	ScapegoatTree<int> st1(3, 0.6);
	for (int i = 1; i < 100; i++)
	{
		st1.addNode(i);
	}
	std::vector<int> output = st1.DLR ();
	for (int i = 0; i < output.size(); i++)
	{
		cout << output[i] << ' ';
	}
	cout << endl;
	cout << st1.isBalance(st1.root) << endl;
	cout << st1.root->size << endl;
	cout << st1.root->leftPtr->size << endl;
	cout << st1.root->rightPtr->size << endl;
	return 0;
}