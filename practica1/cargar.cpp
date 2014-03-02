#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib> 
#include "cargar.h"

Test cargar(string archivo) {
	ifstream leer;
	leer.open(archivo.c_str());
	int entradas, salidas;
	leer >> entradas >> salidas;
	Test losTests;
	while(!leer.eof()) {
		losTests.push_back( Caso ( vector<float> (entradas, 0), vector<int> (salidas, 0) ) );
		for(int i = 0; i < entradas; i++) {
			leer >> losTests.back().first[i];
		}
		for(int j = 0; j < salidas; j++) {
			leer >> losTests.back().second[j];
		}
	}
	leer.close();
	losTests.pop_back();
	//srand(unsigned(time(NULL)));
	srand(1);
	random_shuffle ( losTests.begin(), losTests.end());

// For debugging purpose
/*	for(Test::iterator it = losTests.begin(); it != losTests.end(); ++it) {
		for(vector<float>::iterator it2 = it->first.begin(); it2 != it->first.end(); ++it2) {
			cerr << *it2 << " " ;
		}
		cerr << " / " ;
		for(vector<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
			cerr << *it2 << " " ;
		}
		cerr << endl;
	}*/

	return losTests;
}	