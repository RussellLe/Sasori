#include <iostream>
#include "sort.hpp"
#include "linked_list.hpp"
#include "search.hpp"
#include "binary_search_tree.hpp"
#include "string_algorithm.h"

using namespace std;

int main()
{
	int f=kmpFindStr("helloworld", "worl");
	cout << f << endl;
	return 0;
}