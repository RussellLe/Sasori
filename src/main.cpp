#include <iostream>
#include "sort.hpp"
#include "linked_list.hpp"
#include "search.hpp"
#include "binary_search_tree.hpp"

using namespace std;

int main()
{
	std::vector<int> a = { 16,4,10,14,7,9,3,2,8,1 };
	std::vector<int> output=heapSort<int>(a, false);
	for (int i = 0; i < output.size(); i++)
	{
		cout << output[i] << ' ';
	}
	cout << endl;
	return 0;
}