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
	std::vector<char> points = { 'a','b','c','d','e','f','g','h','i' };
	for (int i = 0; i < points.size(); i++)
	{
		g.addPoint(points[i]);
	}
	g.addTwowayLink('a', 'b', 4);
	g.addTwowayLink('a', 'h', 8);
	g.addTwowayLink('b', 'h', 11);
	g.addTwowayLink('b', 'c', 8);
	g.addTwowayLink('h', 'i', 7);
	g.addTwowayLink('h', 'g', 3);
	g.addTwowayLink('i', 'c', 2);
	g.addTwowayLink('i', 'g', 6);
	g.addTwowayLink('g', 'f', 2);
	g.addTwowayLink('c', 'd', 7);
	g.addTwowayLink('c', 'f', 9);
	g.addTwowayLink('d', 'f', 14);
	g.addTwowayLink('d', 'e', 9);
	g.addTwowayLink('f', 'e', 10);
	auto output = g.getMultiSourceCost_();
	for (auto iter = output.begin(); iter != output.end(); iter++)
	{
		cout << iter->first.first << ' ' << iter->first.second << ':' << iter->second << endl;
	}
	return 0;
}