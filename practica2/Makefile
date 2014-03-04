CC=g++
CFLAGS=-g
SRC=neuron.cpp neuron.h cargar.cpp cargar.h
PERCEPTRON=perceptron.cpp perceptron.h main_perceptron.cpp
ADALINE=adaline.cpp adaline.h main_adaline.cpp
MCCULLOH=mcculloh.cpp

perceptron:  $(SRC) $(PERCEPTRON)
	$(CC) $(CFLAGS) $(SRC) $(PERCEPTRON)  -o perceptron

adaline: $(ADALINE) $(SRC)
	$(CC) $(CFLAGS) $(ADALINE) $(SRC) -o adaline

mcculloh: $(MCCULLOH) $(SRC) 
	$(CC) $(CFLAGS) $(MCCULLOH) $(SRC) -o mcculloh

clean: 
	rm -f adaline
	rm -f perceptron
	rm -f adaline-unknown
	rm -f perceptron-unknown
