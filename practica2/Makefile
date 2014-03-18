CC=g++
CFLAGS=-g -Wall
SRC=neuron.cpp neuron.h cargar.cpp cargar.h
PERCEPTRON=perceptron.cpp perceptron.h main_perceptron.cpp

perceptron:  $(SRC) $(PERCEPTRON)
	$(CC) $(CFLAGS) $(SRC) $(PERCEPTRON)  -o perceptron

clean: 
	rm -f perceptron
