#include "stdafx.h"



template <typename T> class DisjointSet
{
public:
	bool addElement(T element);
	T findRoot(T element);
	bool merge(T x, T y);
	bool isJoined(T x, T y);

protected:
	std::unordered_map<T, T> preMap;
};

template <typename T> bool DisjointSet<T>::addElement(T element)
{
	preMap.insert(std::pair<T, T>(element, element));
	return true;
}

template <typename T> T DisjointSet<T>::findRoot(T element)
{
	auto iter = preMap.find(element);
	if (iter == preMap.end())
	{
		throw "Element Not Exist";
	}

	T output = iter->second;
	if (iter->first != iter->second)
	{
		output = findRoot(iter->second);
	}
	iter->second = output;

	return output;
}

template <typename T> bool DisjointSet<T>::merge(T x, T y)
{
	T xRoot = findRoot(x);
	T yRoot = findRoot(y);
	if (xRoot == yRoot)
	{
		return false;
	}

	preMap[xRoot] = yRoot;
	return true;
}

template <typename T> bool DisjointSet<T>::isJoined(T x, T y)
{
	if (findRoot(x) != findRoot(y))
	{
		return false;
	}
	return true;
}