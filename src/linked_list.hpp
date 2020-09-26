#include "stdafx.h"


template <typename T> class Node
{
public:
	T value;
	std::shared_ptr<Node<T>> prePtr;
	std::shared_ptr<Node<T>> nextPtr;
	
public:
	Node(T theValue);
};

template <typename T> Node<T>::Node(T theValue)
{
	value = theValue;
	prePtr = nullptr;
	nextPtr = nullptr;
}

template <typename T> class LinkedList
{
public:
	std::shared_ptr<Node<T>> headNode;
	std::shared_ptr<Node<T>> tailNode;
	int size;

public:
	LinkedList(T headValue);
	bool addNode(T value);
	bool deleteNodeByValue(T value);
	bool deleteNodeByIndex(int index);
	bool insertNode(T value, int index);
	bool updateNodeValue(T value, int index);
	std::vector<T> getAllElement();

protected:
	bool deleteNode_(std::shared_ptr<Node<T>> node);
	std::shared_ptr<Node<T>> getNodeByValue_(T value);
	std::shared_ptr<Node<T>> getNodeByIndex_(int index);
};

template <typename T> LinkedList<T>::LinkedList(T headValue)
{
	headNode = std::make_shared<Node<T>>(headValue);
	tailNode = headNode;
	size = 1;
}

template <typename T> bool LinkedList<T>::addNode(T value)
{
	std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(value);
	newNode->prePtr = tailNode;
	newNode->nextPtr = headNode;
	headNode->prePtr = newNode;

	tailNode->nextPtr = newNode;
	tailNode = tailNode->nextPtr;
	size++;
	return true;
}

template <typename T> std::vector<T> LinkedList<T>::getAllElement()
{
	std::vector<T> output;

	std::shared_ptr<Node<T>> ergodicCursor = headNode;
	for (int i = 0; i < size; i++)
	{
		output.push_back(ergodicCursor->value);
		ergodicCursor = ergodicCursor->nextPtr;
	}
	return output;
}

template <typename T> bool LinkedList<T>::deleteNode_(std::shared_ptr<Node<T>> node)
{
	node->prePtr->nextPtr = node->nextPtr;
	node->nextPtr->prePtr = node->prePtr;
	node->prePtr = nullptr;
	node->nextPtr = nullptr;
	return true;
}

template <typename T> bool LinkedList<T>::deleteNodeByValue(T value)
{
	std::shared_ptr<Node<T>> ergodicCursor = getNodeByValue_(value);
	if (ergodicCursor == nullptr)
	{
		return false;
	}
	deleteNode_(ergodicCursor);
	size--;
	return true;
}

template <typename T> bool LinkedList<T>::deleteNodeByIndex(int index)
{
	std::shared_ptr<Node<T>> ergodicCursor = getNodeByIndex_(index);
	if (ergodicCursor == nullptr)
	{
		return false;
	}
	deleteNode_(ergodicCursor);
	size--;
	return true;
}

template <typename T> bool LinkedList<T>::insertNode(T value, int index)
{
	std::shared_ptr<Node<T>> insertNode = std::make_shared<Node<T>>(value);
	std::shared_ptr<Node<T>> ergodicCursor = getNodeByIndex_(index);
	if (ergodicCursor == nullptr)
	{
		return false;
	}

	insertNode->prePtr = ergodicCursor->prePtr;
	insertNode->nextPtr = ergodicCursor;
	ergodicCursor->prePtr->nextPtr = insertNode;
	ergodicCursor->prePtr = insertNode;
	size++;
	if (index == 1)
	{
		headNode = insertNode;
	}

	return true;
}

template <typename T> std::shared_ptr<Node<T>> LinkedList<T>::getNodeByValue_(T value)
{
	std::shared_ptr<Node<T>> ergodicCursor = headNode;
	
	int sizeTmp = size;
	for (int i = 1; i <= sizeTmp; i++)
	{
		if (ergodicCursor->value == value)
		{
			return ergodicCursor;
		}
		ergodicCursor = ergodicCursor->nextPtr;
	}
	ergodicCursor = nullptr;
	return ergodicCursor;
}

template <typename T> std::shared_ptr<Node<T>> LinkedList<T>::getNodeByIndex_(int index)
{
	std::shared_ptr<Node<T>> ergodicCursor = headNode;

	int sizeTmp = size;
	for (int i = 1; i <= sizeTmp; i++)
	{
		if (i == index)
		{
			return ergodicCursor;
		}
		ergodicCursor = ergodicCursor->nextPtr;
	}
	ergodicCursor = nullptr;
	return ergodicCursor;
}

template <typename T> bool LinkedList<T>::updateNodeValue(T value, int index)
{
	std::shared_ptr<Node<T>> ergodicCursor = getNodeByIndex_(index);
	if (ergodicCursor == nullptr)
	{
		return false;
	}

	ergodicCursor->value = value;
	return true;
}