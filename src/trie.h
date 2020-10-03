#pragma once
#include "stdafx.h"



class TrieNode
{
public:
	char value;
	std::vector<std::shared_ptr<TrieNode>> linkNodes;
	bool isWord;

public:
	TrieNode(char theValue);
	std::shared_ptr<TrieNode> getLinkNode(char linkValue);
};

class Trie
{
public:
	std::shared_ptr<TrieNode> root;

public:
	Trie();
	bool addWord(std::string word);
	bool checkWord(std::string word);

protected:
	std::shared_ptr<TrieNode> addLinkNode(std::shared_ptr<TrieNode> fatherNode, char linkValue);
};