#include "stdafx.h"


template <typename T> int sequentialSearch(const std::vector<T>& vec, T target)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == target)
		{
			return i;
		}
	}
	return -1;
}

template <typename T> int binarySearch(const std::vector<T>& vec, T target, int start, int end, bool maxFlag = true)
{
	int middle = (end - start) / 2 + start;
	if (vec[middle] == target)
	{
		return middle;
	}

	if (maxFlag)
	{
		if (vec[middle] > target)
		{
			return binarySearch(vec, target, middle + 1, end, maxFlag);
		}
		else
		{
			return binarySearch(vec, target, start, middle, maxFlag);
		}
	}
	else
	{
		if (vec[middle] > target)
		{
			return binarySearch(vec, target, start, middle, maxFlag);
		}
		else
		{
			return binarySearch(vec, target, middle + 1, end, maxFlag);
		}
	}
}