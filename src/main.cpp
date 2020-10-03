#include <iostream>
#include "sort.hpp"
#include "linked_list.hpp"
#include "search.hpp"
#include "binary_search_tree.hpp"
#include "string_algorithm.h"
#include "trie.h"
#include "automaton.h"

using namespace std;

int main()
{
	ACAutomaton acm;
	acm.addWord("ash");
	acm.addWord("bcd");
	acm.addWord("sher");
	acm.addWord("sha");
	acm.addWord("she");
	std::string baseStr = "qweashealnbcdashereterbshecdsha";
	acm.buildFailLinks();
	auto output = acm.run(baseStr);
	for (auto iter = output.begin(); iter != output.end(); iter++)
	{
		cout << iter->first << ' ' << iter->second << endl;
	}
	return 0;
}