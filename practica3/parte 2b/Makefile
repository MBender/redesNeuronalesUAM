CC=g++
CFLAGS=-g -Wall
SRC=neuron.cpp neuron.h cargar.cpp cargar.h
PERCEPTRON=perceptron.cpp perceptron.h main_perceptron.cpp

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