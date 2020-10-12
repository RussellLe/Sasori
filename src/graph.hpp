#include "stdafx.h"
#include "linked_list.hpp"

template <typename T> class LinkedGraph
{
public:
	std::unordered_map<T, std::shared_ptr<LinkedList<T>>> startPointContainer;

public:
	LinkedGraph();
	bool addPoint(T point);
	bool addLink(T startPoint, T endPoint);
	bool unLink(T startPoint, T endPoint);
	bool addTwowayLink(T firstPoint, T secondPoint);
};

template <typename T> LinkedGraph<T>::LinkedGraph()
{
	//
}

template <typename T> bool LinkedGraph<T>::addPoint(T point)
{
	auto iter = startPointContainer.find(point);
	if (iter != startPointContainer.end())
	{
		return false;
	}
	startPointContainer[point] = std::make_shared<LinkedList<T>>(point);
	return true;
}

template <typename T> bool LinkedGraph<T>::addLink(T startPoint, T endPoint)
{
	auto startIter = startPointContainer.find(startPoint);
	if (startIter == startPointContainer.end())
	{
		return false;
	}
	if (startPointContainer.find(endPoint) == startPointContainer.end())
	{
		return false;
	}
	if (startIter->second->isNodeExist(endPoint))
	{
		return false;
	}

	startIter->second->addNode(endPoint);
	return true;
}

template <typename T> bool LinkedGraph<T>::unLink(T startPoint, T endPoint)
{
	auto startIter = startPointContainer.find(startPoint);
	if (startIter == startPointContainer.end())
	{
		return false;
	}

	startIter->second->deleteNodeByValue(endPoint);
	return true;
}

template <typename T> bool LinkedGraph<T>::addTwowayLink(T firstPoint, T secondPoint)
{
	auto firstIter = startPointContainer.find(firstPoint);
	auto secondIter = startPointContainer.find(secondPoint);
	if (firstIter == startPointContainer.end() || secondIter == startPointContainer.end())
	{
		return false;
	}

	if (!firstIter->second->isNodeExist(secondPoint))
	{
		firstIter->second->addNode(secondPoint);
	}
	if (!secondIter->second->isNodeExist(firstPoint))
	{
		secondIter->second->addNode(firstPoint);
	}
	return true;
}