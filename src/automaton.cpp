#include "automaton.h"

ACNode::ACNode(char theValue)
{
	value = theValue;
	isWord = false;
	failLink = nullptr; 
	father = nullptr;
	finalStr = "";
}

std::shared_ptr<ACNode> ACNode::getLinkNode(char linkValue)
{
	for (int i = 0; i < linkNodes.size(); i++)
	{
		if (linkNodes[i]->value == linkValue)
		{
			return linkNodes[i];
		}
	}
	return nullptr;
}

ACAutomaton::ACAutomaton()
{
	root = std::make_shared<ACNode>(' ');
}

bool ACAutomaton::addWord(std::string word)
{
	std::shared_ptr<ACNode> ergodicCursor = root;
	for (int i = 0; i < word.size(); i++)
	{
		auto linkCursor = ergodicCursor->getLinkNode(word[i]);
		if (linkCursor == nullptr)
		{
			ergodicCursor = addLinkNode(ergodicCursor, word[i]);
		}
		else
		{
			ergodicCursor = linkCursor;
		}
	}
	ergodicCursor->isWord = true;
	ergodicCursor->finalStr = word;
	return true;
}

bool ACAutomaton::checkWord(std::string word)
{
	std::shared_ptr<ACNode> ergodicCursor = root;
	for (int i = 0; i < word.size(); i++)
	{
		ergodicCursor = ergodicCursor->getLinkNode(word[i]);
		if (ergodicCursor == nullptr)
		{
			return false;
		}
	}
	if (!ergodicCursor->isWord)
	{
		return false;
	}
	return true;
}

void ACAutomaton::buildFailLinks()
{
	std::queue<std::shared_ptr<ACNode>> q;
	q.push(root);
	while (!q.empty())
	{
		auto nowNode = q.front();
		q.pop();
		for (auto iter = nowNode->linkNodes.begin(); iter < nowNode->linkNodes.end(); iter++)
		{
			q.push(*iter);
		}

		if (nowNode == root)
		{
			continue;
		}

		if (nowNode->father->failLink == nullptr)
		{
			nowNode->failLink = root;
			continue;
		}

		auto realFail = nowNode->father->failLink->getLinkNode(nowNode->value);
		if (realFail == nullptr)
		{
			nowNode->failLink = root;
			continue;
		}
		nowNode->failLink = realFail;
	}
}

std::map<std::string, int> ACAutomaton::run(std::string baseStr)
{
	std::map<std::string, int> output;

	std::shared_ptr<ACNode> ergodicCursor = root;
	for (int i = 0; i < baseStr.size(); i++)
	{
		auto preCursor = ergodicCursor;
		ergodicCursor = ergodicCursor->getLinkNode(baseStr[i]);
		if (ergodicCursor == nullptr)
		{
			if (preCursor == root)
			{
				ergodicCursor = root;
				continue;
			}
			ergodicCursor = preCursor->failLink;
			i--;
			continue;
		}

		if (ergodicCursor->isWord)
		{
			auto iter = output.find(ergodicCursor->finalStr);
			if (iter != output.end())
			{
				iter->second += 1;
			}
			else
			{
				output.insert(std::pair<std::string, int>(ergodicCursor->finalStr, 1));
			}
		}
	}
	return output;
}

std::shared_ptr<ACNode> ACAutomaton::addLinkNode(std::shared_ptr<ACNode> fatherNode, char linkValue)
{
	std::shared_ptr<ACNode> newNode = std::make_shared<ACNode>(linkValue);
	newNode->father = fatherNode;
	fatherNode->linkNodes.push_back(newNode);
	return newNode;
}