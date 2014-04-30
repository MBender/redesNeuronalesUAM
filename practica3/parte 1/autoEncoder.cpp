#include <math.h> 
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib> 
#include "cargar.h"
#define nuevoCero 0.01

double sigmoideBipolar (double x) {
	return ((double)2/(1+exp(-x))) - 1;
}

double derivadaSigmoideBipolar (double x) {
	return (double)1/2*(1+sigmoideBipolar(x))*(1-sigmoideBipolar(x));
}

class perceptron {
	public:

	vector<double> capaX;
	vector<double> capaZ_in;
	vector<double> capaZ_out;
	vector<double> capaY_in;
	vector<double> capaY_out;
	vector<vector<double> > W_J_K;
	vector<double> W_0_K;
	vector<vector<double> > V_I_J;
	vector<double> V_0_J;
	vector<double> delta_K;
	vector<vector<double> > Delta_W_J_K;
	vector<double> Delta_W_0_K;
	vector<double> delta_in_J;
	vector<double> delta_J;
	vector<vector<double> > Delta_V_I_J;
	vector<double> Delta_V_0_J;
	int cantidadEnEntrada;
	int cantidadEnCapaOculta;
	int cantidadEnSalida;
	float learn_rate;

	perceptron (int cantEntrada, int cantCapaOculta, int cantSalida, float rate) {

		//inicializo cantidades
		cantidadEnEntrada = cantEntrada;
		cantidadEnCapaOculta = cantCapaOculta;
		cantidadEnSalida = cantSalida;
		learn_rate = rate;

		//inicializo las capas
		capaX = vector<double> (cantidadEnEntrada, 0);
		capaZ_in = vector<double> (cantidadEnCapaOculta, 0);
		capaZ_out = vector<double> (cantidadEnSalida, 0);
		capaY_in = vector<double> (cantidadEnSalida, 0);
		capaY_out = vector<double> (cantidadEnSalida, 0);

		//inicializo los links
		W_J_K = vector<vector<double> > (cantidadEnCapaOculta , vector<double> (cantidadEnSalida, 0));
		W_0_K = vector<double> (cantidadEnSalida, 0);
		V_I_J = vector<vector<double> > (cantidadEnEntrada, vector<double> (cantidadEnCapaOculta , 0));
		V_0_J = vector<double> (cantidadEnCapaOculta, 0);

		//pongo los valores random
		srand (time(NULL));

		for(vector<vector<double> >::iterator itColumna = W_J_K.begin(); itColumna != W_J_K.end(); itColumna++) {
			for(vector<double>::iterator it = itColumna->begin(); it != itColumna->end(); it++) {
				*it = ((double) rand() / (RAND_MAX) ) - 0.5;
			}
		}

		for(vector<double>::iterator it = W_0_K.begin(); it != W_0_K.end(); it++) {
			*it = ((double) rand() / (RAND_MAX) ) - 0.5;
		}

		for(vector<vector<double> >::iterator itColumna = V_I_J.begin(); itColumna != V_I_J.end(); itColumna++) {
			for(vector<double>::iterator it = itColumna->begin(); it != itColumna->end(); it++) {
				*it = ((double) rand() / (RAND_MAX) ) - 0.5;
			}
		}

		for(vector<double>::iterator it = V_0_J.begin(); it != V_0_J.end(); it++) {
			*it = ((double) rand() / (RAND_MAX) ) - 0.5;
		}

		//Inicializo los deltas y Deltas
		delta_K = vector<double> (cantidadEnSalida,0);
		Delta_W_J_K = vector<vector<double> > (cantidadEnCapaOculta, vector<double> (cantidadEnSalida , 0));
		Delta_W_0_K = vector<double> (cantidadEnSalida, 0);
		delta_in_J = vector<double> (cantidadEnCapaOculta,0);
		delta_J = vector<double> (cantidadEnCapaOculta,0);
		Delta_V_I_J = vector<vector<double> > (cantidadEnEntrada , vector<double> (cantidadEnCapaOculta, 0));
		Delta_V_0_J = vector<double> (cantidadEnCapaOculta, 0);
	}

	void entrenar(Test & data, int lim) {
		cout << "Inicia entrenamiento\t Iteraciones: " << lim << "\t Learn Rate: " << learn_rate << endl;
		int iteraciones = 0;
		while(iteraciones++ < lim) {//&& correctos < data.size()) {
			double ecm_distancia = 0;
			int correctos = 0;
			double porcentajeDistancia = 0;
			for(vector<Caso>::iterator itCaso = data.begin(); itCaso != data.end(); itCaso++) {
				//Cargo la entrada
				for(int i = 0; i < cantidadEnEntrada; i++) {
					capaX[i] = itCaso->first[i];
				}
				//Propago a la capa oculta
				for(int j = 0; j < cantidadEnCapaOculta; j++) {
					capaZ_in[j] = V_0_J[j];
					for(int i = 0; i < cantidadEnEntrada; i++) {
						capaZ_in[j] += capaX[i]*V_I_J[i][j];
					}
					capaZ_out[j] = sigmoideBipolar(capaZ_in[j]);
				}
				//Propago a capa final
				for(int k = 0; k < cantidadEnSalida; k++) {
					capaY_in[k] = W_0_K[k];
					for(int j = 0; j < cantidadEnCapaOculta; j++) {
						capaY_in[k] += capaZ_out[j]*W_J_K[j][k];
					}
					capaY_out[k] = sigmoideBipolar(capaY_in[k]);
				}

				//BACKPROPAGATION
				//step 6
				for(int k = 0; k < cantidadEnSalida; k++) {
					delta_K[k] = (itCaso->second[k] - capaY_out[k])*derivadaSigmoideBipolar(capaY_in[k]);
				}
				for(int k = 0; k < cantidadEnSalida; k++) {
					for(int j = 0; j < cantidadEnCapaOculta; j++) {
						Delta_W_J_K[j][k] = learn_rate*delta_K[k]*capaZ_out[j];
					}
					Delta_W_0_K[k] = learn_rate*delta_K[k];
				}

				//step 7
				for(int j = 0; j < cantidadEnCapaOculta; j++) {
					delta_in_J[j] = 0;
					for(int k = 0; k < cantidadEnSalida; k++) {
						delta_in_J[j] += delta_K[k]*W_J_K[j][k];
					}
					delta_J[j] = delta_in_J[j]*derivadaSigmoideBipolar(capaZ_in[j]);
				}

				for(int j = 0; j < cantidadEnCapaOculta; j++) {
					for(int i = 0; i < cantidadEnEntrada; i++) {
						Delta_V_I_J[i][j] = learn_rate * delta_J[j] * capaX[i];
					}
					Delta_V_0_J[j] = learn_rate * delta_J[j];
				}

				//Step 8
				for(int k = 0; k < cantidadEnSalida; k++) {
					W_0_K[k] += Delta_W_0_K[k];
					for(int j = 0; j < cantidadEnCapaOculta; j++) {
						W_J_K[j][k] += Delta_W_J_K[j][k];
					}
				}

				for(int j = 0; j < cantidadEnCapaOculta; j++) {
					V_0_J[j] += Delta_V_0_J[j];
					for(int i = 0; i < cantidadEnEntrada; i++) {
						V_I_J[i][j] += Delta_V_I_J[i][j];
					}
				}

				//Calculo la distancia
				int distancia = 0;
				for(int k = 0; k < cantidadEnSalida; k++) {
					if( !( (itCaso->second[k] > 0 && capaY_out[k] > nuevoCero) || (itCaso->second[k] < 0 && capaY_out[k] < -1*nuevoCero) ) ) {
						distancia++;
					}
				}
				if(distancia == 0)
					correctos++; 
				ecm_distancia += (double) distancia*distancia / data.size();
				porcentajeDistancia += (double) distancia / cantidadEnEntrada;
			}
			ecm_distancia = sqrt(ecm_distancia);
		}
		cout << "Finaliza entrenamiento" << endl;
	}

	void testear(Test data , string org) {
		string ub (org);
		ub += ".EntradaYSalida.out";

		ofstream escribir;
		escribir.open(ub.c_str());

		double ecm_distancia = 0;
		int correctos = 0;
		for(vector<Caso>::iterator itCaso = data.begin(); itCaso != data.end(); itCaso++) {
			//Cargo la entrada
			for(int i = 0; i < cantidadEnEntrada; i++) {
				capaX[i] = itCaso->first[i];
			}

			//Propago a la capa oculta
			for(int j = 0; j < cantidadEnCapaOculta; j++) {
				capaZ_in[j] = V_0_J[j];
				for(int i = 0; i < cantidadEnEntrada; i++) {
					capaZ_in[j] += capaX[i]*V_I_J[i][j];
				}
				//Imprimo la activaci'on de cada neurona
				capaZ_out[j] = sigmoideBipolar(capaZ_in[j]);
			}

			//Propago a capa final
			for(int k = 0; k < cantidadEnSalida; k++) {
				capaY_in[k] = W_0_K[k];
				for(int j = 0; j < cantidadEnCapaOculta; j++) {
					capaY_in[k] += capaZ_out[j]*W_J_K[j][k];
				}
				capaY_out[k] = sigmoideBipolar(capaY_in[k]);
			}

			//Calculo la distancia
			int distancia = 0;
			for(int k = 0; k < cantidadEnSalida; k++) {
				if( !( (itCaso->second[k] > 0 && capaY_out[k] > nuevoCero) || (itCaso->second[k] < 0 && capaY_out[k] < -1*nuevoCero) ) )
					distancia++;
			}
			if(distancia == 0)
				correctos++;

			for(int i = 0; i < cantidadEnEntrada; i++) {
				if(capaX[i] > nuevoCero)
					escribir << 1;
				else if(capaX[i] < -1*nuevoCero)
					escribir << 0;
				escribir << " | ";
			}
			escribir << "\t";
			for(int k = 0; k < cantidadEnSalida; k++) {
				if(capaY_out[k] > nuevoCero)
					escribir << 1;
				else if(capaY_out[k] < -1*nuevoCero)
					escribir << 0;
				else
					escribir << '_';
				escribir << " | ";
			}
			escribir << endl;
		
			ecm_distancia += (double) distancia*distancia / data.size();
		}
		cout  << "Correctos: " << correctos << "/" << data.size() << "\tECM: " << ecm_distancia << endl; 
		escribir.close();
	}

	void imprimirInformacion(string org) {
		string ub (org);
		ub += ".infoRed.out";
		ofstream escribir;
		escribir.open(ub.c_str());

		escribir << cantidadEnEntrada << "\t" << cantidadEnCapaOculta << "\t" << cantidadEnSalida << endl << endl;

		for(int j = 0; j < cantidadEnCapaOculta; j++) {
			escribir << V_0_J[j] << "\t";
		}
		escribir << endl;
		for(int i = 0; i < cantidadEnEntrada; i++) {
			for(int j = 0; j < cantidadEnCapaOculta; j++) {
				escribir << V_I_J[i][j] << "\t";
			}
			escribir << endl;
		}
		escribir << endl;
		for(int k = 0; k < cantidadEnSalida; k++) {
			escribir << W_0_K[k] << "\t";
		}
		escribir << endl;
		for(int j = 0; j < cantidadEnCapaOculta; j++) {
			for(int k = 0; k < cantidadEnSalida; k++) {
				escribir << W_J_K[j][k] << "\t";
			}
			escribir << endl;
		}
		escribir.close();
	}

};

int main(int argc, char **argv) {
	if(argc==5) {
		int cantidadOculta = atoi(argv[1]);
		float learn_rate = atof(argv[2]);
		int lim = atoi(argv[3]);
		cout << "Cargando archivo..." << endl;
		Test t = cargar(argv[4]);
		int cantidadEnEntrada, cantidadEnSalida;
		cantidadEnEntrada = t[0].first.size();
		cantidadEnSalida = t[0].second.size();
		perceptron p (cantidadEnEntrada, cantidadOculta, cantidadEnSalida, learn_rate);
		p.entrenar(t, lim);
		p.testear(t, argv[4]);
		p.imprimirInformacion(argv[4]);
	} else {
		cout << "Forma de uso:" << endl;
		cout << "\t ./autoEncoder <#Neuronas Ocultas> <Tasa de Aprendizaje> <#Iteraciones> <Archivo de entrada>" << endl;
		cout << "En \"<Archivo de entrada>.EntradaYSalida.out\" encontraras la salida de la red" << endl;
		cout << "En \"<Archivo de entrada>.infoRed.out\" encontraras la informacion de la red" << endl;
		cout << "Recomendamos utilizar archivos de entrada con la codificacion -0.9 y 0.9" << endl;
	}
	return 0;
}