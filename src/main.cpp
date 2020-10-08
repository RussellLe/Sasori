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
	DisjointSet<int> ds;
	for (int i = 1; i < 100; i++)
	{
		ds.addElement(i);
	}
	ds.merge(3, 5);
	ds.merge(6, 7);
	ds.merge(1, 2);
	ds.merge(1, 3);
	cout << ds.isJoined(1, 4) << endl;
	cout << ds.isJoined(2, 5) << endl;
	cout << ds.isJoined(1, 6) << endl;
	ds.merge(3, 6);
	cout << ds.isJoined(1, 6) << endl;
	return 0;
}