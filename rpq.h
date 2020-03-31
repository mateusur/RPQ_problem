#pragma once
#include "rpq.h"

#include <vector>


struct parametrs
{
	int r;
	int p;
	int q;
	int ID;
};
long long calculate(const std::vector<parametrs>& dane, int n);
int max(const int& first, const int& second);
int min(const int& first, const int& second);
int RPQ_without_sort(const std::vector<parametrs>& dane);
int RPQ_with_sort(const std::vector<parametrs>& dane);