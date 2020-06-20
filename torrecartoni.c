#include "torrecartoni.h"

void addPack(pila *current, cartone *c, size_t current_index, bool *pack_usati) {
	current->sol[current->n_elements] = current_index;
	current->n_elements++;
	current->altezza += c[current_index].a;
	pack_usati[current_index] = true;
}
void deletePack(pila *current, cartone *c, size_t current_index, bool *pack_usati) {
	current->n_elements--;
	current->altezza -= c[current_index].a;
	pack_usati[current_index] = false;
}
bool canAddElement(pila *current, cartone *c, size_t current_index) {
	size_t peso = 0;
	for (size_t i = 0; i < current->n_elements; i++) {
		peso += c[current->sol[i]].p;
	}

	if (peso > c[current_index].l) {
		return false;
	}

	return true;
}
void updateBest(pila *dest, const pila *source, unsigned int n) {
	dest->altezza = source->altezza;
	dest->n_elements = source->n_elements;
	for (unsigned int i = 0; i < n; i++) {
		dest->sol[i] = source->sol[i];
	}
}
void printSolution(pila *best) {
	for (size_t i = 0; i < best->n_elements; i++) {
		printf("\t%u\n", best->sol[i]);
	}

	printf("\nAltezza: %d cm", best->altezza);
}

void Backtrack(int n, cartone *c, int livello, pila *current, pila *best, bool *pack_usati) {
	if (livello == n) {
		if (current->altezza > best->altezza) {
			updateBest(best, current, n);
		}
		return;
	}

	for (int j = 0; j < n; j++) {
		if (pack_usati[j] == false) {
			if (canAddElement(current, c, j)) {
				addPack(current, c, j, pack_usati);
				Backtrack(n, c, livello + 1, current, best, pack_usati);
				deletePack(current, c, j, pack_usati);
			}
			else {
				Backtrack(n, c, n, current, best, pack_usati);
			}
		}
	}
}



void TorreCartoni(cartone *c, int n) {
	pila current, best;
	bool *pack_usati;
	
	current.altezza = 0;
	current.sol = malloc(n * sizeof(size_t));
	current.n_elements = 0;

	best.altezza = 0;
	best.sol = malloc(n * sizeof(size_t));
	best.n_elements = 0;

	pack_usati = calloc(n, sizeof(bool));


	Backtrack(n, c, 0, &current, &best, pack_usati);

	printSolution(&best);


	free(best.sol);
	free(current.sol);
	free(pack_usati);
	
}
