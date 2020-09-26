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

template <typename T> std::vector<T> mergeSort(const std::vector<T>& vec, int start, int end, bool maxFlag = true)
{
	std::vector<T> output;

	int diff = end - start;
	if (diff == 1)
	{
		if (maxFlag)
		{
			if (vec[end] > vec[start])
			{
				output.push_back(vec[end]);
				output.push_back(vec[start]);
			}
			else
			{
				output.push_back(vec[start]);
				output.push_back(vec[end]);
			}
		}
		else
		{
			if (vec[end] < vec[start])
			{
				output.push_back(vec[end]);
				output.push_back(vec[start]);
			}
			else
			{
				output.push_back(vec[start]);
				output.push_back(vec[end]);
			}
		}
		return output;
	}
	else if (diff == 0)
	{
		output.push_back(vec[start]);
		return output;
	}

	int middle = start + (diff / 2);
	std::vector<T> leftOutput = mergeSort<T>(vec, start, middle, maxFlag);
	std::vector<T> rightOutput = mergeSort<T>(vec, middle + 1, end, maxFlag);

	int leftCursor = 0;
	int rightCursor = 0;
	for (int i = 0; i < leftOutput.size() + rightOutput.size(); i++)
	{
		if (leftCursor >= leftOutput.size())
		{
			output.push_back(rightOutput[rightCursor]);
			rightCursor++;
			continue;
		}
		if (rightCursor >= rightOutput.size())
		{
			output.push_back(leftOutput[leftCursor]);
			leftCursor++;
			continue;
		}
		T leftElement = leftOutput[leftCursor];
		T rightElement = rightOutput[rightCursor];
		if (maxFlag)
		{
			if (leftElement > rightElement)
			{
				output.push_back(leftElement);
				leftCursor++;
			}
			else
			{
				output.push_back(rightElement);
				rightCursor++;
			}
		}
		else
		{
			if (leftElement < rightElement)
			{
				output.push_back(leftElement);
				leftCursor++;
			}
			else
			{
				output.push_back(rightElement);
				rightCursor++;
			}
		}
	}
	return output;
}