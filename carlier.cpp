#include "carlier.h"
#include <iostream>
#include "rpq.h"
#include "schrage.h"
using namespace std;

vector<parametrs> Carlier(std::vector<parametrs> dane) {
	parametrsCarlier U = Schrage_carlier(dane);
	if (U.Cmax < UB.Cmax) {
		UB = U;
	}
	int b = b_max(U.C_q, U.Cmax);
	int a = a_min(U.pi, U.pi[b].q, U.Cmax, b);
	int c = c_max(U.pi, U.pi[b].q, a, b);
	if (c == -1) {
		return UB.pi;
	}
	int r_min = 999999, q_min = 999999, q_old = U.pi[c].q, p_sum2 = 0, r_old = U.pi[c].r;
	for (int i = c + 1; i < b + 1; i++) {
		r_min = min(r_min, U.pi[i].r);
		q_min = min(q_min, U.pi[i].q);
		p_sum2 += U.pi[i].p;
	}
	U.pi[c].r = max(U.pi[c].r, r_min + p_sum2);
	int LB = Schrage_pmtm(U.pi);
	//int LB = Schrage_pmtm_priority_queue(U.pi);
	if (LB < UB.Cmax) {
		Carlier(U.pi);
	}
	U.pi[c].r = r_old;
	U.pi[c].q = max(U.pi[c].q, q_min + p_sum2);
	LB = Schrage_pmtm(U.pi);
	//LB = Schrage_pmtm_priority_queue(U.pi);
	if (LB < UB.Cmax) {
		Carlier(U.pi);
	}
	U.pi[c].q = q_old;
	return UB.pi;
}

int b_max(std::vector<int> tablica_Cq, int Cmax) {
	for (int i = tablica_Cq.size() - 1; i > -1; i--) {
		if (Cmax == tablica_Cq[i]) return i;
	}
	return 0;
}

int sum_help(int k, int b, std::vector<parametrs> pi) {
	// CZY TUTAJ POWINNO BYC B+1 czy B??
	int sum = 0;
	if (k > b) return sum;
	for (int i = k; i < b + 1; i++) {
		sum += pi[i].p;
	}
	return sum;
}

int a_min(std::vector<parametrs> pi, int q_b, int Cmax, int b) {
	// CZY TUTAJ POWINNO BYC B+1 czy B??
	for (int i = 0; i < pi.size(); i++) {
		int temp = pi[i].r + sum_help(i, b, pi) + q_b;
		if (Cmax == temp)
			return i;
	}
	return -1;
}

int c_max(std::vector<parametrs> tablica_pi, int q_b, int a, int b) {
	//dobry zakres?
	int temp1 = b - 1;
	int temp2 = a - 1;
	for (int i = temp1; i > temp2; i--) {
		int temp = tablica_pi[i].q;
		if (temp < q_b) return i;
	}
	return -1;
}

parametrsCarlier calculate_C(const std::vector<parametrs>& dane) {
	auto n = dane.size();
	parametrsCarlier anwser;
	anwser.pi = dane;
	anwser.S.push_back(dane[0].r);
	anwser.C.push_back(anwser.S[0] + dane[0].p);
	anwser.C_q.push_back(anwser.C[0] + dane[0].q);
	anwser.Cmax = anwser.C[0] + dane[0].q;
	for (int i = 1; i < n; i++) {
		anwser.S.push_back(max(dane[i].r, anwser.C[i - 1]));
		anwser.C.push_back(anwser.S[i] + dane[i].p);
		anwser.C_q.push_back(anwser.C[i] + dane[i].q);
		anwser.Cmax = max(anwser.Cmax, anwser.C[i] + dane[i].q);
	}

	return anwser;
}

parametrsCarlier Schrage_carlier(const std::vector<parametrs>& dane) {
	//int k = 0;
	int t;
	parametrs j2;
	vector<parametrs> N, G, pi;
	N = dane;
	sort(N.begin(), N.end(), compare_r);
	t = N[0].r;

	while (G.size() != 0 || N.size() != 0) {
		while (N.size() != 0 && N[0].r <= t) {
			j2 = N[0];
			G.push_back(N[0]);
			N.erase(N.begin());

		}
		if (G.size() != 0) {

			std::sort(G.begin(), G.end(), compare_q);
			j2 = G[0];
			G.erase(G.begin());
			pi.push_back(j2);
			t += j2.p;
			/*k += 1;*/
		}
		else {

			std::sort(N.begin(), N.end(), compare_r);
			t = N[0].r;
		}
	}

	return calculate_C(pi);
}


//Algorytm Carlier
//vector<parametrs> Carlier(vector<parametrs> dane) {
//	
//	parametrsCarlier J = calculate_C(dane, dane.size()); // Funckja Calculate lecz zwracajaca nie tylko Cmax dla danego pi, lecz takze zwracajaca informacje o C,S,C+q
//	parametrsCarlier UB, U;
//	int b, a, c;
//	UB.Cmax = INT32_MAX;
//	U = Schrage_carlier(J.pi);
//	if (U.Cmax < UB.Cmax) {
//		UB = U;
//		UB.pi = U.pi;
//	}
//	U.C_q;
//	b = b_max(J.C_q, J.Cmax);
//	a = a_min(J.pi, J.pi[b].q, J.Cmax, b);
//	//cout << b << " " << a;
//	c = c_max(J.pi, J.pi[b].q, a, b);
//	//cout << b << " " << a << " " << c;
//	if (c == -1) {
//		return UB.pi;
//	}
//	int r_min = 999999, q_min = 999999, q_old = J.pi[c].q, p_sum2 = 0, r_old = J.pi[c].r;
//
//	for (int i = c + 1; i < b + 1; i++) { // dobry zakres?
//		r_min = min(r_min, J.pi[i].r);
//		q_min = min(q_min, J.pi[i].q);
//		p_sum2 += J.pi[i].p;
//	}
//
//	dane[c].r = max(dane[c].r, r_min + p_sum2);//Powienem operowac na dane[] czy na J.pi[] ?- teoretycznie J zawiera dane[] + informacje o S,C,C+q
//	J.pi[c].r = max(J.pi[c].r, r_min + p_sum2);
//	int LB = Schrage_pmtm(J.pi);
//	LB = max(r_min + q_min + p_sum2, LB);
//	if (LB < UB.Cmax) {
//		Carlier(J.pi);
//	}
//	J.pi[c].r = r_old;
//	dane[c].r = r_old;
//	dane[c].q = max(dane[c].q, q_min + p_sum2);
//	J.pi[c].q = max(J.pi[c].q, q_min + p_sum2);
//	LB = Schrage_pmtm(dane);
//	LB = max(r_min + q_min + p_sum2, LB);
//	if (LB < UB.Cmax) {
//		Carlier(J.pi);
//	}
//	J.pi[c].q = q_old;
//	dane[c].q = q_old;
//}
//
