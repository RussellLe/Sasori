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
	std::vector<T> bfs(T startPoint);
	std::vector<T> dfs(T startPoint);
	std::vector<T> topologicalSort();

public:
	std::map<T, int> incomeTable;
	std::map<T, int> outTable;

protected:
	void dfs_(T nextPoint, std::vector<T>& output, std::map<T, bool>& visitTable);
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
	incomeTable.insert(std::pair<T, int>(point, 0));
	outTable.insert(std::pair<T, int>(point, 0));
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
	incomeTable[endPoint] += 1;
	outTable[startPoint] += 1;
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
	incomeTable[endPoint] -= 1;
	outTable[startPoint] -= 1;
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
		incomeTable[secondPoint] += 1;
		outTable[firstPoint] += 1;
	}
	if (!secondIter->second->isNodeExist(firstPoint))
	{
		secondIter->second->addNode(firstPoint);
		incomeTable[firstPoint] += 1;
		outTable[secondPoint] += 1;
	}
	return true;
}

template <typename T> std::vector<T> LinkedGraph<T>::bfs(T startPoint)
{
	std::vector<T> output;
	std::map<T, bool> visitTable;

	std::queue<std::shared_ptr<LinkedList<T>>> q;
	q.push(startPointContainer[startPoint]);
	visitTable.insert(std::pair<T, bool>(startPoint, true));
	while (!q.empty())
	{
		auto nowNodeLink = q.front();
		q.pop();
		auto allLinkValues = nowNodeLink->getAllElement();
		output.push_back(allLinkValues[0]);
		for (int i = 1; i < allLinkValues.size(); i++)
		{
			auto isVisitIter = visitTable.find(allLinkValues[i]);
			if (isVisitIter != visitTable.end() && isVisitIter->second)
			{
				continue;
			}
			q.push(startPointContainer[allLinkValues[i]]);
			visitTable.insert(std::pair<T, bool>(allLinkValues[i], true));
		}
	}
	return output;
}

template <typename T> std::vector<T> LinkedGraph<T>::dfs(T startPoint)
{
	std::vector<T> output;
	std::map<T, bool> visitTable;
	dfs_(startPoint, output, visitTable);
	return output;
}

template <typename T> std::vector<T> LinkedGraph<T>::topologicalSort()
{
	std::vector<T> output;
	auto incomeTableCopy = incomeTable;
	std::queue<T> noIncomeNodes;
	for (auto iter = incomeTableCopy.begin(); iter != incomeTableCopy.end(); iter++)
	{
		if (iter->second == 0)
		{
			noIncomeNodes.push(iter->first);
		}
	}

	while (!noIncomeNodes.empty())
	{
		T nowNode = noIncomeNodes.front();
		noIncomeNodes.pop();
		output.push_back(nowNode);
		
		auto allLinkValues = startPointContainer[nowNode]->getAllElement();
		for (int i = 1; i < allLinkValues.size(); i++)
		{
			incomeTableCopy[allLinkValues[i]]--;
			if (incomeTableCopy[allLinkValues[i]] == 0)
			{
				noIncomeNodes.push(allLinkValues[i]);
			}
		}
	}
	return output;
}

template <typename T> void LinkedGraph<T>::dfs_(T nextPoint, std::vector<T>& output, std::map<T, bool>& visitTable)
{
	auto isVisitIter = visitTable.find(nextPoint);
	if (isVisitIter != visitTable.end() && isVisitIter->second)
	{
		return;
	}

	output.push_back(nextPoint);
	visitTable.insert(std::pair<T, bool>(nextPoint, true));
	auto nowNodeLink = startPointContainer[nextPoint];
	auto allLinkValues = nowNodeLink->getAllElement();
	for (int i = 1; i < allLinkValues.size(); i++)
	{
		dfs_(allLinkValues[i], output, visitTable);
	}
}