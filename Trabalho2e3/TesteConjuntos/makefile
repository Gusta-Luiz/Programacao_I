# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = teste_Conjunto.o libconjunto.o  liblistaord.o libfila.o 
     
all: teste_Conjunto.o libconjunto.o 
	$(CC) -o teste_Conjunto teste_Conjunto.o libconjunto.o $(LDFLAGS)

libconjunto.o: libconjunto.c
	$(CC) -c $(CFLAGS) libconjunto.c

teste_Conjunto.o: teste_Conjunto.c
	$(CC) -c $(CFLAGS) teste_Conjunto.c

clean:
	rm -f $(objects) teste_Conjunto


