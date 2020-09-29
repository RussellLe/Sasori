#include "string_algorithm.h"


int kmpFindStr(std::string baseStr, std::string targetStr)
{
	std::vector<int> partialTable;
	partialTable.resize(targetStr.size());
	partialTable[0] = 0;

	int j = 0;
	for (int i = 1; i < targetStr.size(); i++)
	{
		if (targetStr[i] == targetStr[j])
		{
			j++;
			partialTable[i] = j;
		}
		else
		{
			j = 0;
		}
	}

	int i = 0;
	while(i<baseStr.size())
	{
		bool findFlag = true;
		for (int k = 0; k < targetStr.size(); k++)
		{
			if (baseStr[i + k] != targetStr[k])
			{
				findFlag = false;
				if (k == 0)
				{
					i++;
				}
				else
				{
					i = i + k - partialTable[k - 1];
				}
				break;
			}
		}
		if (findFlag)
		{
			return i;
		}
	}
	return -1;
}