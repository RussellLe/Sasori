#include "stdafx.h"


template <typename T> class TreeNode
{
public:
	T value;
	std::shared_ptr<TreeNode<T>> fatherPtr;
	std::shared_ptr<TreeNode<T>> leftPtr;
	std::shared_ptr<TreeNode<T>> rightPtr;

public:
	TreeNode(T theValue);
};

template <typename T> TreeNode<T>::TreeNode(T theValue)
{
	value = theValue;
	fatherPtr = nullptr;
	leftPtr = nullptr;
	rightPtr = nullptr;
}



template <typename T> class BinarySearchTree
{
public:
	std::shared_ptr<TreeNode<T>> root;
	int size;

public:
	BinarySearchTree(T rootValue);
	bool addNode(T value);
	std::vector<T> DLR();
	std::vector<T> LDR();
	std::vector<T> LRD();
	bool deleteNode(T value);

protected:
	std::shared_ptr<TreeNode<T>> findLeaf_(T value, std::shared_ptr<TreeNode<T>> ergodicCursor);	//get node father position
	std::shared_ptr<TreeNode<T>> findNode_(T value, std::shared_ptr<TreeNode<T>> ergodicCursor);	//get node position
	void DLR_(std::vector<T>& vec, std::shared_ptr<TreeNode<T>> ergodicCursor);
	void LDR_(std::vector<T>& vec, std::shared_ptr<TreeNode<T>> ergodicCursor);
	void LRD_(std::vector<T>& vec, std::shared_ptr<TreeNode<T>> ergodicCursor);

protected:
	std::vector<T> LDRs_;
};

template <typename T> BinarySearchTree<T>::BinarySearchTree(T rootValue)
{
	root = std::make_shared<TreeNode<T>>(rootValue);
	size = 1;
}

template <typename T> bool BinarySearchTree<T>::addNode(T value)
{
	std::shared_ptr<TreeNode<T>> newNode = std::make_shared<TreeNode<T>>(value);
	std::shared_ptr<TreeNode<T>> ergodicCursor = findLeaf_(value, root);

	if (ergodicCursor == nullptr)
	{
		return false;
	}

	if (ergodicCursor->value < value)
	{
		ergodicCursor->rightPtr = newNode;
	}
	else if (ergodicCursor->value > value)
	{
		ergodicCursor->leftPtr = newNode;
	}
	else
	{
		return false;
	}
	newNode->fatherPtr = ergodicCursor;

	if (!LDRs_.empty())
	{
		for (auto iter = LDRs_.begin(); iter < LDRs_.end(); iter++)
		{
			if (*iter > value)
			{
				LDRs_.insert(iter,value);
			}
		}
	}

	return true;
}

template <typename T> std::shared_ptr<TreeNode<T>> BinarySearchTree<T>::findLeaf_(T value, std::shared_ptr<TreeNode<T>> ergodicCursor)
{
	if (ergodicCursor->value < value)
	{
		if (ergodicCursor->rightPtr == nullptr)
		{
			return ergodicCursor;
		}
		return findLeaf_(value, ergodicCursor->rightPtr);
	}
	else if (ergodicCursor->value > value)
	{
		if (ergodicCursor->leftPtr == nullptr)
		{
			return ergodicCursor;
		}
		return findLeaf_(value, ergodicCursor->leftPtr);
	}
	else
	{
		return nullptr;
	}
}

template <typename T> std::shared_ptr<TreeNode<T>> BinarySearchTree<T>::findNode_(T value, std::shared_ptr<TreeNode<T>> ergodicCursor)
{
	if (ergodicCursor->value == value)
	{
		return ergodicCursor;
	}

	if (ergodicCursor->value > value)
	{
		if (ergodicCursor->leftPtr == nullptr)
		{
			return nullptr;
		}
		return findNode_(value, ergodicCursor->leftPtr);
	}
	else
	{
		if (ergodicCursor->rightPtr == nullptr)
		{
			return nullptr;
		}
		return findNode_(value, ergodicCursor->rightPtr);
	}
}

template <typename T> std::vector<T> BinarySearchTree<T>::DLR()
{
	std::vector<T> output;
	DLR_(output, root);
	return output;
}

template <typename T> std::vector<T> BinarySearchTree<T>::LDR()
{
	std::vector<T> output;
	LDR_(output, root);
	return output;
}

template <typename T> std::vector<T> BinarySearchTree<T>::LRD()
{
	std::vector<T> output;
	LRD_(output, root);
	return output;
}

template <typename T> bool BinarySearchTree<T>::deleteNode(T value)
{
	std::shared_ptr<TreeNode<T>> node = findNode_(value, root);
	if (node->leftPtr != nullptr && node->rightPtr != nullptr)
	{
		if (LDRs_.empty())
		{
			LDRs_ = LDR();
		}
		for (auto iter = LDRs_.begin(); iter < LDRs_.end(); iter++)
		{
			if (*iter > value)
			{
				deleteNode(*iter);
				node->value = *iter;
				LDRs_.erase(iter);
				return true;
			}
		}
	}

	if (node->leftPtr != nullptr)
	{
		T newValue = node->leftPtr->value;
		deleteNode(newValue);
		node->value = newValue;
	}
	else if (node->rightPtr != nullptr)
	{
		T newValue = node->rightPtr->value;
		deleteNode(newValue);
		node->value = newValue;
	}
	else
	{
		T fatherValue = node->fatherPtr->value;
		if (fatherValue < value)
		{
			node->fatherPtr->rightPtr = nullptr;
			node->fatherPtr = nullptr;
		}
		else
		{
			node->fatherPtr->leftPtr = nullptr;
			node->fatherPtr = nullptr;
		}
	}
	return true;
}


template <typename T> void BinarySearchTree<T>::DLR_(std::vector<T>& vec, std::shared_ptr<TreeNode<T>> ergodicCursor)
{
	vec.push_back(ergodicCursor->value);
	if (ergodicCursor->leftPtr != nullptr)
	{
		DLR_(vec, ergodicCursor->leftPtr);
	}
	if (ergodicCursor->rightPtr != nullptr)
	{
		DLR_(vec, ergodicCursor->rightPtr);
	}
}

template <typename T> void BinarySearchTree<T>::LDR_(std::vector<T>& vec, std::shared_ptr<TreeNode<T>> ergodicCursor)
{
	if (ergodicCursor->leftPtr != nullptr)
	{
		LDR_(vec, ergodicCursor->leftPtr);
	}
	vec.push_back(ergodicCursor->value);
	if (ergodicCursor->rightPtr != nullptr)
	{
		LDR_(vec, ergodicCursor->rightPtr);
	}
}

template <typename T> void BinarySearchTree<T>::LRD_(std::vector<T>& vec, std::shared_ptr<TreeNode<T>> ergodicCursor)
{
	if (ergodicCursor->leftPtr != nullptr)
	{
		LRD_(vec, ergodicCursor->leftPtr);
	}
	if (ergodicCursor->rightPtr != nullptr)
	{
		LRD_(vec, ergodicCursor->rightPtr);
	}
	vec.push_back(ergodicCursor->value);
}