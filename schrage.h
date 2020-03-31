#pragma once
#include "schrage.h"

#include <vector>
#include <queue>
#include "rpq.h"


struct Scompare_r
{
	bool operator()(parametrs const& p1, parametrs const& p2) {
		return p1.r > p2.r;
	}
};

struct Scompare_q
{
	bool operator()(parametrs const& p1, parametrs const& p2) {
		return p1.q < p2.q;
	}
};
 static long long sredni_czas = 0;
 static long long sredni_czas_pmtm = 0;
 static long long sredni_czas_queue = 0;
 static long long sredni_czas_pmtm_queue = 0;
int Schrage(const std::vector<parametrs>& dane);
int Schrage_pmtm(const std::vector<parametrs>& dane);
int Schrage_pmtm_priority_queue(const std::vector<parametrs>& dane);
int Schrage_prority_queue(const std::vector<parametrs>& dane);

bool compare_q(const parametrs& a, const parametrs& b);
bool compare_r(const parametrs& a, const parametrs& b);

