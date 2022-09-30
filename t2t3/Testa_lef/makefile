# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects =liblef.o testa_lef.o
     
all: liblef.o testa_lef.o
	$(CC) -o teste liblef.o testa_lef.o $(LDFLAGS)

liblef.o: liblef.c
	$(CC) -c $(CFLAGS) liblef.c

testa_lef.o: testa_lef.c
	$(CC) -c $(CFLAGS) testa_lef.c

testa_lef: testa_lef.o liblef.o
	$(CC) -o testa_lef testa_lef.o liblef.o $(LDFLAGS)

clean:
	rm -f $(objects) testa_lef teste

