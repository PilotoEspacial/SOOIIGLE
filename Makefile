DIROBJ := obj/
DIREXE := exec/
DIRHEA := include/
DIRSRC := src/

CFLAGS	:= -I$(DIRHEA) -c -pthread -std=c++11
CC := g++

dirs:
	mkdir -p $(DIREXE) $(DIROBJ)

SSOOIIGLE:
	$(CC) $(DIRSRC)SSOOIIGLE.cpp -o $(DIROBJ)SOOIIGLE.o $(CFLAGS)
	
main:
	$(CC) -o $(DIREXE)SSOOIIGLE $(DIROBJ)SOOIIGLE.o -pthread -std=c++11

prueba1:
	$(DIREXE)SSOOIIGLE "VIVE TU SUEÑO - JOHN MAXWELL" no 8

prueba2:
	$(DIREXE)SSOOIIGLE "17 LEYES DEL TRABAJO EN EQUIPO" trabajo 6