# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects =libfila.o testa_fila.o
     
all: libfila.o testa_fila.o
	$(CC) -o teste libfila.o testa_fila.o $(LDFLAGS)

libfila.o: libfila.c
	$(CC) -c $(CFLAGS) libfila.c

testa_fila.o: testa_fila.c
	$(CC) -c $(CFLAGS) testa_fila.c

testa_fila: testa_fila.o libfila.o
	$(CC) -o testa_fila testa_fila.o libfila.o $(LDFLAGS)

clean:
	rm -f $(objects) testa_fila teste

