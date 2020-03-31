
#include "rpq.h"
#include <algorithm>
#include <chrono>
#include <iostream>



#include "schrage.h"


long long calculate(const std::vector<parametrs>& dane, int n) {
	std::vector<int> S, C;
	int Cmax;
	//auto start = std::chrono::steady_clock::now();
	S.push_back(dane[0].r);
	C.push_back(S[0] + dane[0].p);
	Cmax = C[0] + dane[0].q;
	for (int i = 1; i < n; i++) {
		S.push_back(max(dane[i].r, C[i - 1]));
		C.push_back(S[i] + dane[i].p);
		Cmax = std::max(Cmax, C[i] + dane[i].q);
	}
	//auto end = std::chrono::steady_clock::now();
	//std::cout << "Czas w calculate:	" << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us"<< std::endl;
	//auto czas = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	//std::cout << "Czas w calculate: " << czas << std::endl;
	//return czas;
	return Cmax;
}
int max(const int& first, const int& second) {
	return first > second ? first : second;
}
int min(const int& first, const int& second) {
	return first > second ? second : first;
}

int RPQ_without_sort(const std::vector<parametrs>& dane) {

	/*for (const auto& i : dane) {
		cout << i.ID << " ";
	}*/
	/*cout << "RPQ without sort" << endl;*/
	return calculate(dane, dane.size());
}
int RPQ_with_sort(const std::vector<parametrs>& dane) {
	std::vector<parametrs> N;
	N = dane;
	std::sort(N.begin(), N.end(), compare_r);
	/*cout << "RPQ with sort" << endl;*/
	return calculate(N, N.size());
}