#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <queue>
#include "schrage.h"
#include "carlier.h"

using namespace std;

string names[6] = {"data10.txt", "data20.txt", "data50.txt", "data100.txt", "data200.txt", "data500.txt"};
parametrsCarlier UB;


int main() {
	//Size of names[]
	
	double srednia=0;
	long long sredni_czas_carlier = 0;
	for (int d = 0; d < 6; d++) {
		vector<parametrs> dane;
		int n, k;
		ifstream file;
		file.open(names[d], ios::out);
		file >> n >> k;
		for (int i = 0; i < n; i++) {
			parametrs temp;
			file >> temp.r >> temp.p >> temp.q;
			temp.ID = i + 1;
			dane.push_back(temp);
		}
		file.close();
		//Wywolanie algorytmu Carlier oraz policzenie Cmax funkcja Calculate oraz policzenie sredniego czasu
		UB.Cmax = INT16_MAX;
		
		//auto start = chrono::steady_clock::now();
		calculate(Carlier(dane), n);
		//auto end = chrono::steady_clock::now();
		//sredni_czas_carlier += chrono::duration_cast<chrono::microseconds>(end - start).count();
		
		
		//Czesc kodu do liczenia poszczegolnych PRD
	/*	float temp[6] = { 641,1267,1492,3070,6398,14785 };
		float tempcmax = Schrage_pmtm_priority_queue(dane);
		cout << "Cmax: " << tempcmax << endl;
		float prd = 100*float(tempcmax - temp[d]) / temp[d];
		cout << "Prd: " << prd << endl;*/

		//Obliczanie czasow wykonywania algorytmow
		/*Schrage(dane);
		Schrage_pmtm(dane);
		Schrage_prority_queue(dane);
		Schrage_pmtm_priority_queue(dane);
		cout << endl;*/
	}
	//cout << "Carlier time:" << sredni_czas_carlier / 100 << endl;
	return 0;
}





