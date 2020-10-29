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
#include "math.hpp"


using namespace std;

int main()
{
	LinkedGraph<int> g;
	for (int i = 1; i <= 7; i++)
	{
		g.addPoint(i);
	}
	g.addLink(1, 2, 4);
	g.addLink(1, 3, 10);
	g.addLink(2, 3, 1);
	g.addLink(2, 4, 2);
	g.addLink(3, 4, 5);
	g.addLink(2, 5, 7);
	g.addLink(3, 6, 3);
	g.addLink(4, 5, 6);
	g.addLink(4, 6, 1);
	g.addLink(6, 5, 5);
	g.addLink(5, 7, 9);
	g.addLink(6, 7, 6);

	g.addFlow(1, 2, 3);
	g.addFlow(1, 3, 3);
	g.addFlow(2, 3, 1);
	g.addFlow(2, 4, 0);
	g.addFlow(3, 4, 1);
	g.addFlow(2, 5, 2);
	g.addFlow(3, 6, 3);
	g.addFlow(4, 5, 0);
	g.addFlow(4, 6, 1);
	g.addFlow(6, 5, 0);
	g.addFlow(6, 7, 4);
	g.addFlow(5, 7, 2);

	cout << g.maximumFlow(1, 7) << endl;
	return 0;
}