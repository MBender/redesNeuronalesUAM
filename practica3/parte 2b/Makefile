CC=g++
CFLAGS=-g -std=c++0x -Wall
SRC=neuron.cpp neuron.h series.cpp series.h
PERCEPTRON=perceptron.cpp perceptron.h main_series.cpp

perceptron:  $(SRC) $(PERCEPTRON)
	$(CC) $(CFLAGS) $(SRC) $(PERCEPTRON)  -o perceptron

clean: 
	rm -f perceptron

help:
	@echo ""
	@echo "Como invocar al perceptron:"
	@echo "./perceptron <neuronas> <constante entrenamiento> <particion entrenamiento> <nombre archivo train> <OPCIONAL:nombre arhcivo test>"
	@echo "también puedes hacer ./perceptron <fichero>"
	@echo "dejamos esa forma de debug por comodidad"