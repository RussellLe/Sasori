#include <iostream>
#include "sort.hpp"
#include "linked_list.hpp"
#include "search.hpp"
#include "binary_search_tree.hpp"
#include "string_algorithm.h"
#include "trie.h"
#include "automaton.h"
#include "scapegoat_tree.hpp"
#include "disjoint_set.hpp"

using namespace std;

int main()
{
	ScapegoatTree<int> sgt(3);
	for (int i = 1; i < 100; i++)
	{
		sgt.addNode(i);
		if (i >= 10 && i % 5 == 0)
		{
			sgt.deleteNode(i - 5);
		}
	}
	auto output = sgt.DLR();
	for (int i = 0; i < output.size(); i++)
	{
		cout << output[i] << ' ';
	}
	cout << endl;
	return 0;
}