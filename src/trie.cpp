#include "trie.h"


TrieNode::TrieNode(char theValue)
{
	value = theValue;
	isWord = false;
}

std::shared_ptr<TrieNode> TrieNode::getLinkNode(char linkValue)
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

Trie::Trie()
{
	root = std::make_shared<TrieNode>(' ');
}

bool Trie::addWord(std::string word)
{
	std::shared_ptr<TrieNode> ergodicCursor = root;
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
	return true;
}

bool Trie::checkWord(std::string word)
{
	std::shared_ptr<TrieNode> ergodicCursor = root;
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

std::shared_ptr<TrieNode> Trie::addLinkNode(std::shared_ptr<TrieNode> fatherNode, char linkValue)
{
	std::shared_ptr<TrieNode> newNode = std::make_shared<TrieNode>(linkValue);
	fatherNode->linkNodes.push_back(newNode);
	return newNode;
}