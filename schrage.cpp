
#include <vector>
#include "schrage.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include "rpq.h"
using namespace std;

int Schrage_pmtm_priority_queue(const vector<parametrs>& dane) {
	parametrs j, l;
	vector<parametrs> N, pi;
	priority_queue<parametrs, vector<parametrs>, Scompare_q> G_queue;
	int Cmax = 0, t = 0;
	N = dane;
	sort(N.begin(), N.end(), compare_r);
	l.r = 0;
	l.p = 0;
	l.q = INT32_MAX;
	//auto start = chrono::steady_clock::now();
	while (!G_queue.empty() || N.size() != 0) {
		while (N.size() != 0 && N[0].r <= t) {
			j = N[0];
			G_queue.push(j);
			N.erase(N.begin());

			if (j.q > l.q) {
				l.p = t - j.r;
				t = j.r;
				if (l.p > 0) {
					G_queue.push(l);
				}
			}
		}
		if (G_queue.empty()) {

			t = N[0].r;
		}
		else {

			j = G_queue.top();
			G_queue.pop();
			l = j;
			t += j.p;
			Cmax = max(Cmax, t + j.q);
		}
	}
	//auto end = chrono::steady_clock::now();
	//ofstream time_data;
	//time_data.open("Wyniki/Schrage_pmtm_priority_queue/Wyniki_" + to_string(dane.size()) + ".txt", ios::app);
	//time_data << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
	//time_data.close();
	//cout << "Schrage pmtm priority queue:"
	////cout << "Time : "
	//	<< chrono::duration_cast<chrono::microseconds>(end - start).count()
	//	<< endl;
	//sredni_czas_pmtm_queue += chrono::duration_cast<chrono::microseconds>(end - start).count();
	//cout << "Schrage pmtm priority queue:" << sredni_czas_pmtm_queue/ 100 << endl;
	return Cmax;
}

int Schrage_pmtm(const vector<parametrs>& dane) {
	 
	int t;
	parametrs j2;
	vector<parametrs> N, G, pi;
	N = dane;
	sort(N.begin(), N.end(), compare_r);
	t = 0;
	int Cmax = 0;
	parametrs l;
	l.r = 0;
	l.p = 0;
	l.q = INT32_MAX;
	//auto start = chrono::steady_clock::now();
	while (G.size() != 0 || N.size() != 0) {
		while (N.size() != 0 && N[0].r <= t) {
			j2 = N[0];
			G.push_back(N[0]);
			N.erase(N.begin());

			if (j2.q > l.q) {
				l.p = t - j2.r;
				t = j2.r;
				if (l.p > 0) {
					G.push_back(l);
				}
			}
		}
		if (G.empty()) {

			t = N[0].r;
		}
		else {
			sort(G.begin(), G.end(), compare_q);
			j2 = G[0];
			G.erase(G.begin());
			l = j2;
			t += j2.p;
			Cmax = max(Cmax, t + j2.q);
		}
	}
	//auto end = chrono::steady_clock::now();
	//ofstream time_data;
	//time_data.open("Wyniki/Schrage_pmtm/Wyniki_" + to_string(dane.size()) + ".txt", ios::app);
	//time_data << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
	//time_data.close();
	//auto czas = chrono::duration_cast<chrono::microseconds>(end - start).count();
	//cout << "Schrage pmtm:" << czas << endl;
	
	//sredni_czas_pmtm += czas;
	//cout <<"Schrage pmtm, sredni czas:" << double(sredni_czas_pmtm / 100) << endl;
	return Cmax;
}

int Schrage_prority_queue(const vector<parametrs>& dane) {
	int t;
	parametrs j2;
	vector<parametrs> N, pi;
	priority_queue<parametrs, vector<parametrs>, Scompare_q> G_queue;
	N = dane;
	sort(N.begin(), N.end(), compare_r);
	t = N[0].r;
	auto start = chrono::steady_clock::now();
	while (!G_queue.empty() || N.size() != 0) {
		while (N.size() != 0 && N[0].r <= t) {
			j2 = N[0];
			G_queue.push(j2);
			N.erase(N.begin());

		}
		if (!G_queue.empty()) {
			j2 = G_queue.top();
			G_queue.pop();
			pi.push_back(j2);
			t += j2.p;

		}
		else {
			sort(N.begin(), N.end(), compare_r);
			t = N[0].r;
		}
	}
	auto end = chrono::steady_clock::now();
	//ofstream time_data;
	//time_data.open("Wyniki/Schrage_priority_queue/Wyniki_" + to_string(dane.size()) + ".txt", ios::app);
	//time_data << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
	//time_data.close();
	//cout << "Schrage priority queue:" 
	////cout << "Time : "
	//	<< chrono::duration_cast<chrono::microseconds>(end - start).count()
	//	<< " us" << endl;
	auto czas = chrono::duration_cast<chrono::microseconds>(end - start).count() + calculate(pi, pi.size());
	sredni_czas_queue += czas;
	cout << "Schrage priority queue: " << double(sredni_czas_queue/100) << endl;
	return calculate(pi, pi.size());
}

int Schrage(const vector<parametrs>& dane) {
	//int k = 0;
	int t;
	parametrs j2;
	vector<parametrs> N, G, pi;
	N = dane;
	sort(N.begin(), N.end(), compare_r);
	t = N[0].r;
	auto start = chrono::steady_clock::now();
	while (G.size() != 0 || N.size() != 0) {
		while (N.size() != 0 && N[0].r <= t) {
			j2 = N[0];
			G.push_back(N[0]);
			N.erase(N.begin());

		}
		if (G.size() != 0) {

			sort(G.begin(), G.end(), compare_q);
			j2 = G[0];
			G.erase(G.begin());
			pi.push_back(j2);
			t += j2.p;
			/*k += 1;*/
		}
		else {

			sort(N.begin(), N.end(), compare_r);
			t = N[0].r;
		}
	}
	auto end = chrono::steady_clock::now();
	//ofstream time_data;
	//time_data.open("Wyniki/Schrage/Wyniki_" + to_string(dane.size()) + ".txt", ios::app);
	//time_data << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
	//time_data.close();
	//cout << "Schrage:" 
	////cout << "Time : "
	//	<< chrono::duration_cast<chrono::microseconds>(end - start).count()
	//	<< " us" << endl;
	auto czas = chrono::duration_cast<chrono::microseconds>(end - start).count() + calculate(pi, pi.size());
	sredni_czas += czas;
	cout << "Schrage: " << double(sredni_czas/100) << endl;
	return calculate(pi, pi.size());
}

bool compare_r(const parametrs& a, const parametrs& b) {
	return a.r < b.r;
}

bool compare_q(const parametrs& a, const parametrs& b) {
	return a.q > b.q;
}