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
	bool addFlow(T firstPoint, T secondPoint, int flow);
	std::vector<T> bfs(T startPoint);
	std::vector<T> dfs(T startPoint);
	std::vector<T> topologicalSort();
	std::vector<std::pair<std::pair<T, T>, int>> miniSpanningTree();
	std::map<T, std::pair<int, std::vector<T>>> dijkstraPath(T startPoint);
	std::vector<T> bidirectionalSearch(T startPoint, T endPoint);
	std::pair<int, std::vector<T>> heuristicSearch(T startPoint, T endPoint, double alpha = 3);
	int maximumFlow(T source, T sink);

public:
	bool isPointExist(T point);

protected:
	std::map<T, int> incomeTable;
	std::map<T, int> outTable;
	std::map<std::pair<T, T>, int> edgeWeightTable;
	std::map<std::pair<T, T>, int> edgeFlowTable;

public:
	void dfs_(T nextPoint, std::vector<T>& output, std::map<T, bool>& visitTable);
	std::map<std::pair<T, T>, int> getMultiSourceCost_(double alpha = 3);
	int geometryTriangleCost_(int costFirst, int costSecond, double alpha);
	bool dfsDinic_(T nowPoint, std::vector<T>& augPath, const std::map<std::pair<T, T>, int>& edgeResidueTable, const std::map<T, std::vector<T>>& levelLinkTable, const T& sink, int& minResidue);
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
	edgeFlowTable[edgePointPair] = 0;
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
	edgeFlowTable.erase(edgePointPair);
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
		edgeFlowTable[edgePointPair] = 0;
	}
	if (!secondIter->second->isNodeExist(firstPoint))
	{
		secondIter->second->addNode(firstPoint);
		//incomeTable[firstPoint] += 1;
		//outTable[secondPoint] += 1;

		std::pair<T, T> edgePointPair(secondPoint, firstPoint);
		edgeWeightTable[edgePointPair] = -1 * weight;
		edgeFlowTable[edgePointPair] = 0;
	}
	return true;
}

template <typename T> bool LinkedGraph<T>::addFlow(T firstPoint, T secondPoint, int flow)
{
	std::pair<T, T> edgeForwardPair(firstPoint, secondPoint);
	std::pair<T, T> edgeBackwardPair(secondPoint, firstPoint);

	edgeFlowTable[edgeForwardPair] += flow;
	edgeFlowTable[edgeBackwardPair] -= flow;
	return true;
}

template <typename T> bool LinkedGraph<T>::isPointExist(T point)
{
	if (startPointContainer.find(point) == startPointContainer.end())
	{
		return false;
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

template <typename T> std::vector<T> LinkedGraph<T>::bidirectionalSearch(T startPoint, T endPoint)
{
	const int startFlag = 1;
	const int endFlag = 2;

	std::vector<T> output;
	std::map<T, std::pair<int, T>> visitTable;	//first:flag(1,2)      second:pre node
	
	std::queue<T> q1;
	std::queue<T> q2;
	q1.push(startPoint);
	q2.push(endPoint);

	std::pair<int, T> pair1(startFlag, startPoint);
	std::pair<int, T> pair2(endFlag, endPoint);
	visitTable[startPoint] = pair1;
	visitTable[endPoint] = pair2;
	
	T intersectPoint;
	T backwardPoint;
	while (true)
	{
		bool breakFlag = false;
		if (!q1.empty())
		{
			T nowPoint = q1.front();
			q1.pop();
			std::vector<T> allLinkPoints = startPointContainer[nowPoint]->getAllElement();
			for (int i = 1; i < allLinkPoints.size(); i++)
			{
				T nextPoint = allLinkPoints[i];
				auto visitIter = visitTable.find(nextPoint);
				if (visitIter != visitTable.end())
				{
					if (visitIter->second.first != startFlag)
					{
						intersectPoint = nextPoint;
						backwardPoint = nowPoint;
						breakFlag = true;
					}
					continue;
				}
				
				q1.push(nextPoint);
				std::pair<int, T> pairTmp(startFlag, nowPoint);
				visitTable[nextPoint] = pairTmp;
			}
			if (breakFlag)
			{
				break;
			}
		}

		if (!q2.empty())
		{
			T nowPoint = q2.front();
			q2.pop();
			std::vector<T> allLinkPoints = startPointContainer[nowPoint]->getAllElement();
			for (int i = 1; i < allLinkPoints.size(); i++)
			{
				T nextPoint = allLinkPoints[i];
				auto visitIter = visitTable.find(nextPoint);
				if (visitIter != visitTable.end())
				{
					if (visitIter->second.first != endFlag)
					{
						intersectPoint = nextPoint;
						backwardPoint = nowPoint;
						breakFlag = true;
					}
					continue;
				}

				q2.push(nextPoint);
				std::pair<int, T> pairTmp(endFlag, nowPoint);
				visitTable[nextPoint] = pairTmp;
			}
			if (breakFlag)
			{
				break;
			}
		}
	}
	std::stack<T> s1;
	while (true)
	{
		s1.push(backwardPoint);
		if (backwardPoint == visitTable[backwardPoint].second)
		{
			break;
		}
		backwardPoint = visitTable[backwardPoint].second;
	}
	while (!s1.empty())
	{
		output.push_back(s1.top());
		s1.pop();
	}
	while (true)
	{
		output.push_back(intersectPoint);
		if (intersectPoint == visitTable[intersectPoint].second)
		{
			break;
		}
		intersectPoint = visitTable[intersectPoint].second;
	}
	return output;
}

template <typename T> std::pair<int, std::vector<T>> LinkedGraph<T>::heuristicSearch(T startPoint, T endPoint, double alpha)
{
	std::vector<T> pathVec;
	int totalCost = 0;
	std::map<std::pair<T, T>, int> costTable = getMultiSourceCost_(alpha);

	std::queue<T> q;
	std::map<T, bool> visitTable;
	q.push(startPoint);
	visitTable[startPoint] = true;
	while (!q.empty())
	{
		T nowPoint = q.front();
		if (nowPoint == endPoint)
		{
			pathVec.push_back(nowPoint);
			break;
		}
		std::cout << nowPoint << std::endl;
		pathVec.push_back(nowPoint);
		q.pop();
		auto allLinkedPoints = startPointContainer[nowPoint]->getAllElement();

		T nextPoint;
		int minCost = INT_MAX;
		bool flag = false;
		for (int i = 0; i < allLinkedPoints.size(); i++)
		{
			if (visitTable.find(allLinkedPoints[i]) != visitTable.end() && visitTable[allLinkedPoints[i]])
			{
				continue;
			}
			std::pair<T, T> startNowPair(startPoint, allLinkedPoints[i]);
			std::pair<T, T> nowEndPair(allLinkedPoints[i], endPoint);
			int cost = costTable[nowEndPair];
			std::cout << "cost:" << cost << "   in:" << nowPoint << "  to  " << allLinkedPoints[i] << std::endl;
			if (cost < minCost)
			{
				flag = true;
				minCost = cost;
				nextPoint = allLinkedPoints[i];
			}
		}

		if (!flag)
		{
			continue;
		}

		q.push(nextPoint);
		visitTable[nextPoint] = true;
		std::pair<T, T> nowNextPair(nowPoint, nextPoint);
		totalCost += std::abs(edgeWeightTable[nowNextPair]);
	}

	std::pair<int, std::vector<T>> output(totalCost, pathVec);
	return output;
}

template <typename T> int LinkedGraph<T>::maximumFlow(T source, T sink)
{
	int output = 0;

	std::map<T, int> levelTable;
	std::map<std::pair<T, T>, int> edgeResidueTable;
	std::map<T, std::vector<T>> levelLinkTable;
	
	std::queue<T> q;
	q.push(source);
	levelTable[source] = 0;
	while (!q.empty())
	{
		T nowPoint = q.front();
		int nowLevel = levelTable[nowPoint];
		q.pop();
		std::vector<T> linkVec;

		auto allLinkPoints = startPointContainer[nowPoint]->getAllElement();
		for (int i = 1; i < allLinkPoints.size(); i++)
		{
			T nextPoint = allLinkPoints[i];
			auto levelIter = levelTable.find(nextPoint);
			if (levelIter == levelTable.end())
			{
				levelTable[nextPoint] = nowLevel + 1;
			}
			q.push(nextPoint);

			std::pair<T, T> nowNextPair(nowPoint, nextPoint);
			int residue = edgeWeightTable[nowNextPair] - edgeFlowTable[nowNextPair];
			if (residue <= 0)
			{
				continue;
			}
			edgeResidueTable[nowNextPair] = residue;
			linkVec.push_back(nextPoint);
		}
		levelLinkTable[nowPoint] = linkVec;
	}

	while (1)
	{
		T nowPoint = source;
		std::vector<T> augPath;
		augPath.push_back(nowPoint);
		int minResidue = INT_MAX;

		bool flag = dfsDinic_(nowPoint, augPath, edgeResidueTable, levelLinkTable, sink, minResidue);
		if (!flag)
		{
			break;
		}

		//std::cout << "path:";
		for (int i = 1; i < augPath.size(); i++)
		{
			//std::cout << augPath[i] << ' ';
			std::pair<T, T> edgePair(augPath[i - 1], augPath[i]);
			edgeResidueTable[edgePair] -= minResidue;
		}
		//std::cout << std::endl;
		//std::cout << minResidue << std::endl;
		output += minResidue;
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

template <typename T> int LinkedGraph<T>::geometryTriangleCost_(int costFirst, int costSecond, double alpha)
{
	int output = std::pow(costFirst, 2) + std::pow(costSecond, 2) - 2 * costFirst * costSecond * cos(alpha);
	return std::sqrt(output);
}

template <typename T> std::map<std::pair<T, T>, int> LinkedGraph<T>::getMultiSourceCost_(double alpha)
{
	std::map<std::pair<T, T>, int> output;
	std::map<T, T> preMap;
	std::map<T, bool> visitTable;

	std::map<T, int> pivotPointMap;
	std::vector<T> topoSortedVec = topologicalSort();
	pivotPointMap[topoSortedVec[topoSortedVec.size() / 4]] = 1;
	pivotPointMap[topoSortedVec[topoSortedVec.size() / 4 * 2]] = 1;
	pivotPointMap[topoSortedVec[topoSortedVec.size() / 4 * 3]] = 1;

	for (auto iter = pivotPointMap.begin(); iter != pivotPointMap.end(); iter++)
	{
		T pivotPoint = iter->first;
		std::cout << "pivot Point:" << pivotPoint << std::endl;
		std::queue<T> q;
		q.push(pivotPoint);
		preMap[pivotPoint] = pivotPoint;
		visitTable[pivotPoint] = true;
		while (!q.empty())
		{
			T nowPoint = q.front();
			q.pop();
			auto allLinkedPoints = startPointContainer[nowPoint]->getAllElement();
			for (int i = 0; i < allLinkedPoints.size(); i++)
			{
				if (visitTable.find(allLinkedPoints[i]) != visitTable.end() && visitTable[allLinkedPoints[i]] == true)
				{
					continue;
				}
				q.push(allLinkedPoints[i]);
				preMap[allLinkedPoints[i]] = nowPoint;
				visitTable[allLinkedPoints[i]] = true;
			}
			if (nowPoint == pivotPoint)
			{
				continue;
			}

			std::pair<T, T> pairForward(pivotPoint, nowPoint);
			std::pair<T, T> pairBackward(nowPoint, pivotPoint);
			if (preMap[nowPoint] == pivotPoint)
			{
				int cost = std::abs(edgeWeightTable[pairForward]);
				output[pairForward] = cost;
				output[pairBackward] = cost;
				continue;
			}

			T prePoint = preMap[nowPoint];
			std::pair<T, T> prePivotPair(prePoint, pivotPoint);
			std::pair<T, T> nowPrePair(nowPoint, prePoint);
			int prePivotCost = output[prePivotPair];
			int nowPreCost = std::abs(edgeWeightTable[nowPrePair]);
			int nowPivotCost = geometryTriangleCost_(prePivotCost, nowPreCost, alpha);
			output[pairForward] = nowPivotCost;
			output[pairBackward] = nowPivotCost;
		}
	}

	for (auto outerIter = startPointContainer.begin(); outerIter != startPointContainer.end(); outerIter++)
	{
		for (auto innerIter = next(outerIter); innerIter != startPointContainer.end(); innerIter++)
		{
			std::pair<T, T> pairForward(innerIter->first, outerIter->first);
			std::pair<T, T> pairBackward(outerIter->first, innerIter->first);

			int finalCost = -1;
			if (edgeWeightTable.find(pairForward) != edgeWeightTable.end())
			{
				finalCost = std::abs(edgeWeightTable[pairForward]);
			}
			else
			{
				int totalCost = 0;
				for (auto iter = pivotPointMap.begin(); iter != pivotPointMap.end(); iter++)
				{
					int cost = -1;
					T pivotPoint = iter->first;
					std::pair<T, T> outerPivotPair(outerIter->first, pivotPoint);
					std::pair<T, T> innerPivotPair(innerIter->first, pivotPoint);
					int outerPivotCost = output[outerPivotPair];
					int innerPivotCost = output[innerPivotPair];
					cost = geometryTriangleCost_(outerPivotCost, innerPivotCost, alpha) * iter->second;
					totalCost += cost;
				}
				finalCost = totalCost / pivotPointMap.size();
			}

			output[pairForward] = finalCost;
			output[pairBackward] = finalCost;
		}
	}
	return output;
}

template <typename T> bool LinkedGraph<T>::dfsDinic_(T nowPoint, std::vector<T>& augPath, const std::map<std::pair<T, T>, int>& edgeResidueTable, const std::map<T, std::vector<T>>& levelLinkTable, const T& sink, int& minResidue)
{
	bool flag = false;

	if (nowPoint == sink)
	{
		return true;
	}

	auto linkVec = levelLinkTable.find(nowPoint)->second;
	for (int i = 0; i < linkVec.size(); i++)
	{
		T nextPoint = linkVec[i];
		std::pair<T, T> edgePair(nowPoint, nextPoint);
		int residue = edgeResidueTable.find(edgePair)->second;

		if (residue <= 0)
		{
			continue;
		}
		augPath.push_back(nextPoint);
		flag = dfsDinic_(nextPoint, augPath, edgeResidueTable, levelLinkTable, sink, minResidue);

		if (!flag)
		{
			augPath.pop_back();
			continue;
		}
		
		if (residue < minResidue)
		{
			minResidue = residue;
		}

		break;
	}
	return flag;
}