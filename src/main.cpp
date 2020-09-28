#include <iostream>
#include "sort.hpp"
#include "linked_list.hpp"
#include "search.hpp"
#include "binary_search_tree.hpp"

using namespace std;

int main()
{
	std::vector<int> a = { 3,5,1,9,6,2,7,4,8 };
	quickSort<int>(a, 0, a.size() - 1, true);
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i] << ' ';
	}
	cout << endl;
	return 0;
}