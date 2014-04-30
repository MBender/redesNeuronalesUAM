CC=g++
CFLAGS=
CFLAGSA=-g -Wall
SRC=cargar.cpp cargar.h
AUTOENCODER=autoEncoder.cpp
CREADOR=creadorDeImagenes.cpp

autoEncoder:  $(SRC) $(AUTOENCODER)
	$(CC) $(CFLAGS) $(SRC) $(AUTOENCODER) -o autoEncoder

creadorDeImagenes:  $(CREADOR)
	$(CC) $(CFLAGS) $(CREADOR) -o creador

clean: 
	rm -f autoEncoder creador
