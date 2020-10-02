#include "string_algorithm.h"


int kmp(std::string baseStr, std::string targetStr)
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

std::pair<std::string, std::vector<int>> manacher(std::string baseStr)
{
	std::vector<int> output;

	const char splitToken = '#';
	for (int i = 0; i < baseStr.size(); i++)
	{
		baseStr.insert(i, 1, splitToken);
		i++;
	}
	baseStr.insert(baseStr.size(), 1, splitToken);
	output.resize(baseStr.size());

	int mx = 0, mid = 0;
	output[0] = 0;
	for (int i = 1; i < baseStr.size(); i++)
	{
		if (i < mx)
		{
			output[i] = std::min(output[2 * mid - i], mx - i);
		}
		else
		{
			output[i] = 1;
		}

		while (i - output[i] >= 0 && baseStr[i - output[i]] == baseStr[i + output[i]])
		{
			output[i]++;
		}
		if (i + output[i] > mx)
		{
			mx = i + output[i];
			mid = i;
		}
	}

	std::pair<std::string, std::vector<int>> outputPair(baseStr, output);
	return outputPair;
}