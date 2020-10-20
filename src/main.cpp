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
	LinkedGraph<string> g;
	std::vector<string> points = { "Oradea","Zerind","Arad","Timisoara",
		"Lugoj","Mehadia","Drobeta","Sibiu","Rimnicu Vilcea",
		"Craiova","Pitesti","Fagaras","Bucharest","Giurgiu","Urziceni","Neamt","Iasi","Vaslui","Hirsova","Eforie" };
	for (int i = 0; i < points.size(); i++)
	{
		g.addPoint(points[i]);
	}
	g.addTwowayLink("Oradea", "Zerind", 71);
	g.addTwowayLink("Oradea", "Sibiu", 151);
	g.addTwowayLink("Zerind", "Arad", 75);
	g.addTwowayLink("Arad", "Sibiu", 140);
	g.addTwowayLink("Arad", "Timisoara", 118);
	g.addTwowayLink("Timisoara", "Lugoj", 111);
	g.addTwowayLink("Lugoj", "Mehadia", 70);
	g.addTwowayLink("Mehadia", "Drobeta", 75);
	g.addTwowayLink("Sibiu", "Rimnicu Vilcea", 80);
	g.addTwowayLink("Sibiu", "Fagaras", 99);
	g.addTwowayLink("Drobeta", "Craiova", 120);
	g.addTwowayLink("Craiova", "Rimnicu Vilcea", 146);
	g.addTwowayLink("Craiova", "Pitesti", 138);
	g.addTwowayLink("Rimnicu Vilcea", "Pitesti", 97);
	g.addTwowayLink("Pitesti", "Bucharest", 101);
	g.addTwowayLink("Fagaras", "Bucharest", 211);
	g.addTwowayLink("Bucharest", "Giurgiu", 90);
	g.addTwowayLink("Bucharest", "Urziceni", 85);
	g.addTwowayLink("Urziceni", "Hirsova", 98);
	g.addTwowayLink("Hirsova", "Eforie", 86);
	g.addTwowayLink("Urziceni", "Vaslui", 142);
	g.addTwowayLink("Vaslui", "Iasi", 92);
	g.addTwowayLink("Iasi", "Neamt", 87);


	string s1, s2;
	while (cin >> s1 >> s2)
	{
		auto output = g.heuristicSearch(s1, s2, 3);
		cout << output.first << endl;
		for (int i = 0; i < output.second.size(); i++)
		{
			cout << output.second[i] << ' ';
		}
		cout << endl;
	}
	/*auto output = g.getMultiSourceCost_(3);
	string s1, s2;
	while (cin >> s1 >> s2)
	{
		std::pair<string, string> tmp(s1, s2);
		cout << output[tmp] << endl;
	}
	cout << endl;*/
	return 0;
}