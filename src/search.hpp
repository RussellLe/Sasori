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

template <typename T> int interpolationSearch(const std::vector<T>& vec, T target, int start, int end, bool maxFlag = true)
{
	int middle = start + (end - start) * (std::abs(target - vec[start])) / (std::abs(vec[end] - vec[start]));
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

template <typename T> int thirdsSearch(const std::vector<T>& vec, int left, int right, bool maxFlag = true)
{
	if (right - left <= 1)
	{
		return left;
	}

	int middleLeft = (left + right) / 2;
	int middleRight = (middleLeft + right) / 2;
	
	if (maxFlag)
	{
		if (vec[middleLeft] > vec[middleRight])
		{
			return thirdsSearch(vec, left, middleRight, maxFlag);
		}
		else
		{
			return thirdsSearch(vec, middleLeft, right, maxFlag);
		}
	}
	else
	{
		if (vec[middleLeft] < vec[middleRight])
		{
			return thirdsSearch(vec, left, middleRight, maxFlag);
		}
		else
		{
			return thirdsSearch(vec, middleLeft, right, maxFlag);
		}
	}
}