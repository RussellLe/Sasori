#include <iostream>
#include "sort.cpp"

using namespace std;

int main()
{
	std::vector<int> a = { 3,5,1,9,4,7,6 };
	bool flag = bubbleSort<int>(a, false);
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i] << ' ';
	}
	cout << endl;
	return 0;
}