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
	int a, b;
	while (cin >> a >> b)
	{
		cout << fastPower(a, b) << endl;
	}
	return 0;
}