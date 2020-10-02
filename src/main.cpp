#include <iostream>
#include "sort.hpp"
#include "linked_list.hpp"
#include "search.hpp"
#include "binary_search_tree.hpp"
#include "string_algorithm.h"

using namespace std;

int main()
{
	auto output=manacher("ababa");
	for (int i = 0; i < output.first.size(); i++)
	{
		cout << output.first[i] << ' ';
	}
	cout << endl;
	for (int i = 0; i < output.second.size(); i++)
	{
		cout << output.second[i] << ' ';
	}
	cout << endl;
	return 0;
}