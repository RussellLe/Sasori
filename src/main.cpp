#include <iostream>
#include "sort.hpp"
#include "search.hpp"
#include "binary_search_tree.hpp"
#include "string_algorithm.h"
#include "trie.h"
#include "automaton.h"
#include "scapegoat_tree.hpp"
#include "disjoint_set.hpp"
#include "segment_tree.hpp"
#include "graph.hpp"


using namespace std;

int main()
{
	LinkedGraph<int> g;
	for (int i = 1; i < 10; i++)
	{
		g.addPoint(i);
	}
	g.addLink(1, 3);
	g.addLink(1, 7);
	g.addLink(1, 4);
	g.addLink(4, 8);
	g.addLink(7, 9);
	g.addLink(3, 8);
	g.addLink(8, 5);
	auto output = g.bfs(1);
	for (int i = 0; i < output.size(); i++)
	{
		cout << output[i] << ' ';
	}
	cout << endl;
	return 0;
}