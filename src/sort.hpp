#include "stdafx.h"
#include "heap.hpp"

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


template <typename T> void quickSort(std::vector<T>& vec, int begin, int end, bool maxFlag = true)
{
	if (begin < end)
	{
		T pivot = vec[end];

		int i = begin - 1;
		for (int j = begin; j < end; j++)
		{
			if (!maxFlag)
			{
				if (vec[j] < pivot)
				{
					i++;
					int swapTmp = vec[j];
					vec[j] = vec[i];
					vec[i] = swapTmp;
				}
			}
			else
			{
				if (vec[j] > pivot)
				{
					i++;
					int swapTmp = vec[j];
					vec[j] = vec[i];
					vec[i] = swapTmp;
				}
			}
		}
		int pivotIndex = i + 1;
		vec.insert(vec.begin() + pivotIndex, vec[end]);
		vec.erase(vec.begin() + end + 1);

		quickSort(vec, begin, pivotIndex - 1, maxFlag);
		quickSort(vec, pivotIndex + 1, end, maxFlag);
	}
}

template <typename T> std::vector<T> heapSort(std::vector<T> vec, bool maxFlag = true)
{
	std::vector<T> output;

	BinaryHeap<T> heap;
	for (auto iter = vec.begin(); iter < vec.end(); iter++)
	{
		heap.addElement(*iter);
	}

	while (!heap.isEmpty())
	{
		if (maxFlag)
		{
			heap.buildMaxHeap();
		}
		else
		{
			heap.buildMinHeap();
		}
		output.push_back(heap.getRootElement());
		heap.eraseRootElement();
	}
	return output;
}