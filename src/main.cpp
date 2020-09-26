#include <iostream>
#include "sort.hpp"
#include "linked_list.hpp"
#include "search.hpp"

using namespace std;

int main()
{
	std::vector<int> a = { 3,5,1,9,4,7,2,6,8 };
	std::vector<int> output = mergeSort(a, 0, a.size() - 1, true);
	int index = sequentialSearch<int>(output, 1);
	for (int i = 0; i < output.size(); i++)
	{
		cout << output[i] << ' ';
	}
	cout << endl;
	cout << index << endl;
	cout << output[index] << endl;
	return 0;
}