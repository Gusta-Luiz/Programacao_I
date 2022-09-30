# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects =libconjunto.o testa_conjunto.o
     
all: libconjunto.o testa_conjunto.o
	$(CC) -o teste libconjunto.o testa_conjunto.o $(LDFLAGS)

libconjunto.o: libconjunto.c
	$(CC) -c $(CFLAGS) libconjunto.c

testa_conjunto.o: testa_conjunto.c
	$(CC) -c $(CFLAGS) testa_conjunto.c

testa_conjunto: testa_conjunto.o libconjunto.o
	$(CC) -o testa_conjunto testa_conjunto.o libconjunto.o $(LDFLAGS)

clean:
	rm -f $(objects) testa_conjunto teste

