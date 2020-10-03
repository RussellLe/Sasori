#pragma once
#include "stdafx.h"


class ACNode
{
public:
	char value;
	std::vector<std::shared_ptr<ACNode>> linkNodes;
	bool isWord;
	std::string finalStr;

	std::shared_ptr<ACNode> failLink;
	std::shared_ptr<ACNode> father;

public:
	ACNode(char theValue);
	std::shared_ptr<ACNode> getLinkNode(char linkValue);
};

class ACAutomaton
{
public:
	std::shared_ptr<ACNode> root;

public:
	ACAutomaton();
	bool addWord(std::string word);
	bool checkWord(std::string word);
	void buildFailLinks();
	std::map<std::string, int> run(std::string baseStr);

protected:
	std::shared_ptr<ACNode> addLinkNode(std::shared_ptr<ACNode> fatherNode, char linkValue);
};