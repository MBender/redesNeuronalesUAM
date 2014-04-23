#ifndef __SERIES_H__
#define __SERIES_H__

#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib> 
#include "perceptron.h"

using namespace std;


//typedef std::unique_ptr<perceptron> perceptronPtr;

void adapta_fichero_serie(string nombre_entrada, string nombre_salida, int np, 
	int nneurons);

#endif