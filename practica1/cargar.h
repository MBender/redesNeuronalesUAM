#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib> 

using namespace std;

typedef pair<vector<float>, vector<int> > Caso;
typedef vector<Caso> Test;
 
 Test cargar(string archivo);