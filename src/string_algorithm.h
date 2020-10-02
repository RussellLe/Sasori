#pragma once
#include "stdafx.h"


int kmp(std::string baseStr, std::string targetStr);

std::pair<std::string, std::vector<int>> manacher(std::string baseStr);