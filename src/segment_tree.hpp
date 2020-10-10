#include "stdafx.h"




template <typename T> class SegmentNode
{
public:
	T sum;
	int left;
	int right;
	T lazy;
	bool isLazy;
	SegmentNode(int left, int right);
};

template <typename T> SegmentNode<T>::SegmentNode(int left, int right)
{
	this->left = left;
	this->right = right;
	isLazy = false;
}


template <typename T> class SegmentTree
{
public:
	SegmentTree(std::vector<T> values);
	void add(T addition, int left, int right);	//add addition for every element in segment
	T query(T zeroLine, int left, int right);		//query summary in segment

protected:
	std::vector<std::shared_ptr<SegmentNode<T>>> segmentsContainer;

protected:
	void build(const std::vector<T>& values, int index, int left, int right);
	void add_(T addition, int index, int left, int right);
	void query_(int index, int left, int right, T& output);
	void pushDown(int index);
};

template <typename T> SegmentTree<T>::SegmentTree(std::vector<T> values)
{
	segmentsContainer.resize(4 * values.size());
	build(values, 0, 0, values.size() - 1);
}

template <typename T> void SegmentTree<T>::build(const std::vector<T>& values, int index, int left, int right)
{
	std::shared_ptr<SegmentNode<T>> leafPtr = std::make_shared<SegmentNode<T>>(left, right);
	if (left == right)
	{
		leafPtr->sum = values[left];
		segmentsContainer[index] = leafPtr;
		return;
	}

	int middle = (left + right) / 2;
	build(values, left(index), left, middle);
	build(values, right(index), middle + 1, right);
	leafPtr->sum = segmentsContainer[left(index)]->sum + segmentsContainer[right(index)]->sum;
	segmentsContainer[index] = leafPtr;
}

template <typename T> void SegmentTree<T>::add(T addition, int left, int right)
{
	add_(addition, 0, left, right);
}

template <typename T> void SegmentTree<T>::add_(T addition, int index, int left, int right)
{
	auto segNode = segmentsContainer[index];
	if (segNode->left >= left && segNode->right <= right)
	{
		segNode->sum += ((segNode->right - segNode->left + 1) * addition);
		if (segNode->left != segNode->right)
		{
			segNode->lazy = addition;
			segNode->isLazy = true;
		}
		//std::cout << "sum on [" << segNode->left << "," << segNode->right << "] is:" << segNode->sum << std::endl;
		return;
	}

	if (segNode->left > right || segNode->right < left)
	{
		return;
	}

	int middle = (segNode->left + segNode->right) / 2;
	if (left <= middle)
	{
		add_(addition, left(index), left, right);
	}
	if (right > middle)
	{
		add_(addition, right(index), left, right);
	}

	segNode->sum = segmentsContainer[left(index)]->sum + segmentsContainer[right(index)]->sum;
	//std::cout << "sum on [" << segNode->left << "," << segNode->right << "] is:" << segNode->sum << std::endl;
}

template <typename T> T SegmentTree<T>::query(T zeroLine, int left, int right)
{
	T output = zeroLine;
	query_(0, left, right, output);
	return output;
}

template <typename T> void SegmentTree<T>::query_(int index, int left, int right, T& output)
{
	auto segNode = segmentsContainer[index];
	if (segNode->left >= left && segNode->right <= right)
	{
		output += segNode->sum;
		std::cout << output << std::endl;
		return;
	}
	if (segNode->left > right || segNode->right < left)
	{
		return;
	}

	pushDown(index);
	int middle = (segNode->left + segNode->right) / 2;
	if (left <= middle)
	{
		query_(left(index), left, right, output);
	}
	if (right > middle)
	{
		query_(right(index), left, right, output);
	}
}

template <typename T> void SegmentTree<T>::pushDown(int index)
{
	auto segNode = segmentsContainer[index];
	if (!segNode->isLazy)
	{
		return;
	}

	auto leftNode = segmentsContainer[left(index)];
	auto rightNode = segmentsContainer[right(index)];
	if (leftNode == nullptr || rightNode == nullptr)
	{
		return;
	}

	leftNode->sum += (leftNode->right - leftNode->left) * segNode->lazy;
	rightNode->sum += (rightNode->right - rightNode->left) * segNode->lazy;

	leftNode->lazy = segNode->lazy;
	leftNode->isLazy = true;
	rightNode->lazy = segNode->lazy;
	rightNode->isLazy = true;

	segNode->isLazy = false;
}