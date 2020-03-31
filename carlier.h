#pragma once
#include "carlier.h"

#include <vector>


#include "rpq.h"

struct parametrsCarlier
{
	int Cmax = 0;
	std::vector<int> C, S, C_q;
	std::vector<parametrs> pi;
};
extern parametrsCarlier UB;

parametrsCarlier Schrage_carlier(const std::vector<parametrs>& dane);
parametrsCarlier calculate_C(const std::vector<parametrs>& dane);
std::vector<parametrs> Carlier(std::vector<parametrs> dane);
int b_max(std::vector<int> tablica_Cq, int Cmax);
int sum_help(int k, int b, std::vector<parametrs> pi);
int a_min(std::vector<parametrs> pi, int q_b, int Cmax, int b);
int c_max(std::vector<parametrs> tablica_pi, int q_b, int a, int b);