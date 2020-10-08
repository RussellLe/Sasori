#include "stdafx.h"


template <typename T> class ScapegoatTreeNode
{
public:
	T value;
	std::shared_ptr<ScapegoatTreeNode<T>> fatherPtr;
	std::shared_ptr<ScapegoatTreeNode<T>> leftPtr;
	std::shared_ptr<ScapegoatTreeNode<T>> rightPtr;
	
	int size;
	bool isDelete;

public:
	ScapegoatTreeNode(T theValue);
};

template <typename T> ScapegoatTreeNode<T>::ScapegoatTreeNode(T theValue)
{
	value = theValue;
	fatherPtr = nullptr;
	leftPtr = nullptr;
	rightPtr = nullptr;
	size = 0;
	isDelete = false;
}



template <typename T> class ScapegoatTree
{
private:
	const double alpha;

public:
	std::shared_ptr<ScapegoatTreeNode<T>> root;

public:
	ScapegoatTree(T rootValue, double theAlpha = 0.75);
	bool addNode(T value);
	std::vector<T> DLR();
	std::vector<T> LDR();
	std::vector<T> LRD();
	bool deleteNode(T value);

public:
	std::shared_ptr<ScapegoatTreeNode<T>> findLeaf_(T value, std::shared_ptr<ScapegoatTreeNode<T>> ergodicCursor);	//get node father position
	std::shared_ptr<ScapegoatTreeNode<T>> findNode_(T value, std::shared_ptr<ScapegoatTreeNode<T>> ergodicCursor);	//get node position
	void DLR_(std::vector<T>& vec, std::shared_ptr<ScapegoatTreeNode<T>> ergodicCursor);
	void LDR_(std::vector<T>& vec, std::shared_ptr<ScapegoatTreeNode<T>> ergodicCursor);
	void LRD_(std::vector<T>& vec, std::shared_ptr<ScapegoatTreeNode<T>> ergodicCursor);
	void updatePathSize_(std::shared_ptr<ScapegoatTreeNode<T>> leafCursor, std::shared_ptr<ScapegoatTreeNode<T>> rootCursor);
	bool isBalance(std::shared_ptr<ScapegoatTreeNode<T>> node);
	bool rebuild(std::shared_ptr<ScapegoatTreeNode<T>> node);
};

template <typename T> ScapegoatTree<T>::ScapegoatTree(T rootValue, double theAlpha)
	:alpha(theAlpha)
{
	root = std::make_shared<ScapegoatTreeNode<T>>(rootValue);
	root->size++;
}

template <typename T> bool ScapegoatTree<T>::addNode(T value)
{
	std::shared_ptr<ScapegoatTreeNode<T>> newNode = std::make_shared<ScapegoatTreeNode<T>>(value);
	std::shared_ptr<ScapegoatTreeNode<T>> ergodicCursor = findLeaf_(value, root);

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
	updatePathSize_(newNode, root);
	return true;
}

template <typename T> std::shared_ptr<ScapegoatTreeNode<T>> ScapegoatTree<T>::findLeaf_(T value, std::shared_ptr<ScapegoatTreeNode<T>> ergodicCursor)
{
	if (ergodicCursor->size > 5 && !isBalance(ergodicCursor))
	{
		rebuild(ergodicCursor);
	}

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

template <typename T> std::shared_ptr<ScapegoatTreeNode<T>> ScapegoatTree<T>::findNode_(T value, std::shared_ptr<ScapegoatTreeNode<T>> ergodicCursor)
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

template <typename T> std::vector<T> ScapegoatTree<T>::DLR()
{
	std::vector<T> output;
	DLR_(output, root);
	return output;
}

template <typename T> std::vector<T> ScapegoatTree<T>::LDR()
{
	std::vector<T> output;
	LDR_(output, root);
	return output;
}

template <typename T> std::vector<T> ScapegoatTree<T>::LRD()
{
	std::vector<T> output;
	LRD_(output, root);
	return output;
}

template <typename T> bool ScapegoatTree<T>::deleteNode(T value)
{
	
	return true;
}


template <typename T> void ScapegoatTree<T>::DLR_(std::vector<T>& vec, std::shared_ptr<ScapegoatTreeNode<T>> ergodicCursor)
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

template <typename T> void ScapegoatTree<T>::LDR_(std::vector<T>& vec, std::shared_ptr<ScapegoatTreeNode<T>> ergodicCursor)
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

template <typename T> void ScapegoatTree<T>::LRD_(std::vector<T>& vec, std::shared_ptr<ScapegoatTreeNode<T>> ergodicCursor)
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

template <typename T> void ScapegoatTree<T>::updatePathSize_(std::shared_ptr<ScapegoatTreeNode<T>> leafCursor, std::shared_ptr<ScapegoatTreeNode<T>> rootCursor)
{
	leafCursor->size++;
	if (leafCursor->fatherPtr != rootCursor->fatherPtr)
	{
		updatePathSize_(leafCursor->fatherPtr, rootCursor);
	}
}

template <typename T> bool ScapegoatTree<T>::isBalance(std::shared_ptr<ScapegoatTreeNode<T>> node)
{
	if (node->leftPtr == nullptr || node->rightPtr == nullptr)
	{
		return false;
	}
	if ((static_cast<double>(node->rightPtr->size) / static_cast<double>(node->size)) > alpha)
	{
		return false;
	}
	if ((static_cast<double>(node->leftPtr->size) / static_cast<double>(node->size)) > alpha)
	{
		return false;
	}
	return true;
}

template <typename T> bool ScapegoatTree<T>::rebuild(std::shared_ptr<ScapegoatTreeNode<T>> node)
{
	std::vector<T> output;
	LDR_(output, node);
	int middle = output.size() / 2;

	node->leftPtr = nullptr;
	node->rightPtr = nullptr;
	node->size = 1;
	node->value = output[middle];

	std::shared_ptr<ScapegoatTreeNode<T>> rightCursor = node;
	std::shared_ptr<ScapegoatTreeNode<T>> leftCursor = node;

	int offset = 1;
	while (1)
	{
		bool isUpdate = false;
		if (middle + offset < output.size())
		{
			std::shared_ptr<ScapegoatTreeNode<T>> newNode = std::make_shared<ScapegoatTreeNode<T>>(output[middle + offset]);
			newNode->fatherPtr = rightCursor;
			rightCursor->rightPtr = newNode;
			rightCursor = rightCursor->rightPtr;
			isUpdate = true;
			updatePathSize_(rightCursor, node);
		}
		if (middle - offset >= 0)
		{
			std::shared_ptr<ScapegoatTreeNode<T>> newNode = std::make_shared<ScapegoatTreeNode<T>>(output[middle - offset]);
			newNode->fatherPtr = leftCursor;
			leftCursor->leftPtr = newNode;
			leftCursor = leftCursor->leftPtr;
			isUpdate = true;
			updatePathSize_(leftCursor, node);
		}

		if (!isUpdate)
		{
			break;
		}

		offset++;
	}
	return true;
}