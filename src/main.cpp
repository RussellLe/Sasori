#include <iostream>
#include "sort.hpp"
#include "search.hpp"
#include "binary_search_tree.hpp"
#include "string_algorithm.h"
#include "trie.h"
#include "automaton.h"
#include "scapegoat_tree.hpp"
#include "segment_tree.hpp"
#include "graph.hpp"


using namespace std;

int main()
{
	LinkedGraph<int> g;

	for (int i = 0; i < 15; i++)
	{
		g.addPoint(i);
	}
	g.addTwowayLink(0, 4);
	g.addTwowayLink(1, 4);
	g.addTwowayLink(2, 5);
	g.addTwowayLink(3, 5);
	g.addTwowayLink(4, 6);
	g.addTwowayLink(5, 6);
	g.addTwowayLink(6, 7);
	g.addTwowayLink(7, 8);
	g.addTwowayLink(8, 9);
	g.addTwowayLink(8, 10);
	g.addTwowayLink(9, 11);
	g.addTwowayLink(9, 12);
	g.addTwowayLink(10, 13);
	g.addTwowayLink(10, 14);
	auto output=g.bidirectionalSearch(0,14);
	for (int i = 0; i < output.size(); i++)
	{
		cout << output[i] << ' ';
	}
	cout << endl;
	return 0;
}