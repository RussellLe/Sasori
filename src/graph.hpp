#include "stdafx.h"
#include "linked_list.hpp"
#include "disjoint_set.hpp"

template <typename T> class LinkedGraph
{
public:
	std::unordered_map<T, std::shared_ptr<LinkedList<T>>> startPointContainer;

public:
	LinkedGraph();
	bool addPoint(T point);
	bool addLink(T startPoint, T endPoint, int weight = 0);
	bool unLink(T startPoint, T endPoint);
	bool addTwowayLink(T firstPoint, T secondPoint, int weight = 0);
	std::vector<T> bfs(T startPoint);
	std::vector<T> dfs(T startPoint);
	std::vector<T> topologicalSort();
	std::vector<std::pair<std::pair<T, T>, int>> miniSpanningTree();
	std::map<T, std::pair<int, std::vector<T>>> dijkstraPath(T startPoint);

protected:
	std::map<T, int> incomeTable;
	std::map<T, int> outTable;
	std::map<std::pair<T, T>, int> edgeWeightTable;

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

template <typename T> bool LinkedGraph<T>::addLink(T startPoint, T endPoint, int weight)
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

	std::pair<T, T> edgePointPair(startPoint, endPoint);
	edgeWeightTable[edgePointPair] = weight;
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

	std::pair<T, T> edgePointPair(startPoint, endPoint);
	edgeWeightTable.erase(edgePointPair);
	return true;
}

template <typename T> bool LinkedGraph<T>::addTwowayLink(T firstPoint, T secondPoint, int weight)
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

		std::pair<T, T> edgePointPair(firstPoint, secondPoint);
		edgeWeightTable[edgePointPair] = weight;
	}
	if (!secondIter->second->isNodeExist(firstPoint))
	{
		secondIter->second->addNode(firstPoint);
		incomeTable[firstPoint] += 1;
		outTable[secondPoint] += 1;

		std::pair<T, T> edgePointPair(secondPoint, firstPoint);
		edgeWeightTable[edgePointPair] = -1 * weight;
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

template <typename T> std::vector<std::pair<std::pair<T, T>, int>> LinkedGraph<T>::miniSpanningTree()
{
	std::vector<std::pair<std::pair<T, T>, int>> output;

	std::vector<std::pair<std::pair<T, T>, int>> sortedEdges;
	for (auto iter = edgeWeightTable.begin(); iter != edgeWeightTable.end(); iter++)
	{
		if (iter->second > 0)
		{
			std::pair<std::pair<T, T>, int> edgePair(iter->first, iter->second);
			if (sortedEdges.empty())
			{
				sortedEdges.push_back(edgePair);
				continue;
			}

			bool isInsert = false;
			for (int i = 0; i < sortedEdges.size(); i++)
			{
				if (sortedEdges[i].second > edgePair.second)
				{
					isInsert = true;
					sortedEdges.insert(sortedEdges.begin() + i, edgePair);
					break;
				}
			}

			if (!isInsert)
			{
				sortedEdges.push_back(edgePair);
			}
		}
	}

	DisjointSet<T> disjointSet;
	int pointCount = 0;
	for (auto iter = startPointContainer.begin(); iter != startPointContainer.end(); iter++)
	{
		disjointSet.addElement(iter->first);
		pointCount++;
	}
	
	for (int i = 0; i < sortedEdges.size(); i++)
	{
		auto nowEdge = sortedEdges[i];
		T startPoint = nowEdge.first.first;
		T endPoint = nowEdge.first.second;
		if (!disjointSet.isJoined(startPoint, endPoint))
		{
			output.push_back(nowEdge);
			disjointSet.merge(startPoint, endPoint);
		}
		
		if (output.size() >= pointCount - 1)
		{
			break;
		}
	}
	return output;
}

template <typename T> std::map<T, std::pair<int, std::vector<T>>> LinkedGraph<T>::dijkstraPath(T startPoint)
{
	std::map<T, std::pair<int, std::vector<T>>> output;
	
	for (auto iter = startPointContainer.begin(); iter != startPointContainer.end(); iter++)
	{
		std::vector<T> vecTmp;
		if (iter->first == startPoint)
		{
			std::pair<int, std::vector<T>> pairTmp(0, vecTmp);
			output[iter->first] = pairTmp;
		}
		else
		{
			std::pair<int, std::vector<T>> pairTmp(INT_MAX, vecTmp);
			output[iter->first] = pairTmp;
		}
	}

	std::queue<std::pair<T, std::vector<T>>> q;

	std::vector<T> originPath;
	originPath.push_back(startPoint);
	std::pair<T, std::vector<T>> startPointPair(startPoint, originPath);
	q.push(startPointPair);
	while (!q.empty())
	{
		auto nowPoint = q.front();
		q.pop();
		auto allLinkPoints = startPointContainer[nowPoint.first]->getAllElement();
		for (int i = 1; i < allLinkPoints.size(); i++)
		{
			T nextPoint = allLinkPoints[i];
			std::pair<T, T> edgePair(nowPoint.first, nextPoint);
			int weight = edgeWeightTable[edgePair] + output[nowPoint.first].first;
			if (weight > output[nextPoint].first)
			{
				continue;
			}

			std::vector<T> path(nowPoint.second);
			path.push_back(nextPoint);
			output[nextPoint].first = weight;
			output[nextPoint].second = path;
			std::pair<T, std::vector<T>> nextPointPair(nextPoint, path);
			q.push(nextPointPair);
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