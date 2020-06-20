#if !defined TORRECARTONI_H
#define TORRECARTONI_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	unsigned int p; //peso
	unsigned int a; //altezza
	unsigned int l; //limite peso nel livello superiore
} cartone;


typedef struct {
	size_t altezza;
	size_t *sol;
	size_t n_elements;
} pila;



extern void	TorreCartoni(cartone *c, int n);

#endif //TORRECARTONI_H