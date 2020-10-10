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
#include "segment_tree.hpp"

using namespace std;

int main()
{
	std::vector<int> initVec = { 3,7,9,1,6,2,5,8 };
	SegmentTree<int> smt(initVec);
	smt.add(1, 1, 5);
	return 0;
}