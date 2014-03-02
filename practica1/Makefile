CC=g++
SRC=neuron.cpp neuron.h cargar.cpp cargar.h
PERCEPTRON=perceptron.cpp perceptron.h main_perceptron.cpp
ADALINE=adaline.cpp adaline.h main_adaline.cpp
MCCULLOH=mcculloh.cpp

perceptron:  $(SRC) $(PERCEPTRON)
	$(CC) $(SRC) $(PERCEPTRON)  -o perceptron

adaline: $(ADALINE) $(SRC)
	$(CC) $(ADALINE) $(SRC) -o adaline

mcculloh: $(MCCULLOH) $(SRC) 
	$(CC) $(MCCULLOH) $(SRC) -o mcculloh