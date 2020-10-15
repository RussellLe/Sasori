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
	LinkedGraph<char> g;

	vector<char> points = { 'a','b','c','d','e','f','g' };
	for (int i = 0; i < points.size(); i++)
	{
		g.addPoint(points[i]);
	}
	g.addLink('a','b',5);
	g.addLink('a', 'c',2);
	g.addLink('b','d',1);
	g.addLink('b','e',6);
	g.addLink('c','d',6);
	g.addLink('c','f',8);
	g.addLink('d','e',1);
	g.addLink('d','f',2);
	g.addLink('e','g',7);
	g.addLink('f', 'g', 3);
	auto output = g.dijkstraPath('a');
	for (auto iter = output.begin(); iter != output.end(); iter++)
	{
		cout << iter->first << "     ";
		for (int i = 0; i < iter->second.second.size(); i++)
		{
			cout << iter->second.second[i] << ' ';
		}
		cout << "    " << iter->second.first << endl;
	}
	cout << endl;
	return 0;
}