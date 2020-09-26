#include <iostream>
#include "sort.hpp"

using namespace std;

int main()
{
	std::vector<int> a = { 3,5,1,9,4,7,6 };
	std::vector<int> output = mergeSort<int>(a, 0, a.size() - 1, false);
	for (int i = 0; i < output.size(); i++)
	{
		cout << output[i] << ' ';
	}
	cout << endl;
	return 0;
}