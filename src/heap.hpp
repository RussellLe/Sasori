#include "stdafx.h"


template <typename T> class BinaryHeap
{
public:
	std::vector<T> heapContainer;
	
public:
	bool addElement(T value);
	bool buildMaxHeap();
	bool buildMinHeap();
	bool isEmpty();
	T getRootElement();
	bool eraseRootElement();
public:
	bool maxHeapify_(int index);
	bool minHeapify_(int index);
};

template <typename T> bool BinaryHeap<T>::addElement(T value)
{
	heapContainer.push_back(value);
	return true;
}

template <typename T> bool BinaryHeap<T>::buildMaxHeap()
{
	for (int i = heapContainer.size() - 1; i >= 0; i--)
	{
		maxHeapify_(i);
	}
	return true;
}

template <typename T> bool BinaryHeap<T>::buildMinHeap()
{
	for (int i = heapContainer.size() - 1; i >= 0; i--)
	{
		minHeapify_(i);
	}
	return true;
}

template <typename T> bool BinaryHeap<T>::isEmpty()
{
	return heapContainer.empty();
}

template <typename T> T BinaryHeap<T>::getRootElement()
{
	return heapContainer[0];
}

template <typename T> bool BinaryHeap<T>::eraseRootElement()
{
	heapContainer.erase(heapContainer.begin());
	return true;
}

template <typename T> bool BinaryHeap<T>::maxHeapify_(int index)
{
	if (index >= heapContainer.size())
	{
		return false;
	}

	if (left(index) >= heapContainer.size() && right(index) >= heapContainer.size())
	{
		return true;
	}

	int largestIndex = index;
	if (left(index) < heapContainer.size())
	{
		if (heapContainer[left(index)] > heapContainer[largestIndex])
		{
			largestIndex = left(index);
		}
	}
	if (right(index) < heapContainer.size())
	{
		if (heapContainer[right(index)] > heapContainer[largestIndex])
		{
			largestIndex = right(index);
		}
	}

	if (largestIndex != index)
	{
		int swapTmp = heapContainer[index];
		heapContainer[index] = heapContainer[largestIndex];
		heapContainer[largestIndex] = swapTmp;
	}
	else
	{
		return true;
	}

	return maxHeapify_(largestIndex);
}

template <typename T> bool BinaryHeap<T>::minHeapify_(int index)
{
	if (index >= heapContainer.size())
	{
		return false;
	}

	if (left(index) >= heapContainer.size() && right(index) >= heapContainer.size())
	{
		return true;
	}

	int minimumIndex = index;
	if (left(index) < heapContainer.size())
	{
		if (heapContainer[left(index)] < heapContainer[minimumIndex])
		{
			minimumIndex = left(index);
		}
	}
	if (right(index) < heapContainer.size())
	{
		if (heapContainer[right(index)] < heapContainer[minimumIndex])
		{
			minimumIndex = right(index);
		}
	}

	if (minimumIndex != index)
	{
		int swapTmp = heapContainer[index];
		heapContainer[index] = heapContainer[minimumIndex];
		heapContainer[minimumIndex] = swapTmp;
	}
	else
	{
		return true;
	}

	return minHeapify_(minimumIndex);
}