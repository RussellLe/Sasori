#include <iostream>
#include "sort.hpp"
#include "linked_list.hpp"
#include "search.hpp"
#include "binary_search_tree.hpp"
#include "heap.hpp"

using namespace std;

int main()
{
	std::vector<int> a = { 16,4,10,14,7,9,3,2,8,1 };
	BinaryHeap<int> h;
	for (int i = 0; i < a.size(); i++)
	{
		h.addElement(a[i]);
	}
	h.buildMinHeap();
	for (int i = 0; i < h.heapContainer.size(); i++)
	{
		cout << h.heapContainer[i] << ' ';
	}
	cout << endl;
	return 0;
}