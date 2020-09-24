#include "stdafx.h"


template <typename T> bool bubbleSort(std::vector<T> &vec, bool maxFlag = true)
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = i + 1; j < vec.size(); j++)
		{
			if (maxFlag)
			{
				if (vec[j] > vec[i])
				{
					T tmp = vec[i];
					vec[i] = vec[j];
					vec[j] = tmp;
				}
			}
			else 
			{
				if (vec[j] < vec[i])
				{
					T tmp = vec[i];
					vec[i] = vec[j];
					vec[j] = tmp;
				}
			}
		}
	}
	return true;
}