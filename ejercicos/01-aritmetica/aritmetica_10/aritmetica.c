/*
 * Diagrame cómo queda el Stack y el Heap al 
 * finalizar la ejecución.
 * Libere la memoria reservada.
 * Determinar que se imprime por pantalla.
 */

#include <stdio.h>

int main(){
	
	int*** a = malloc(sizeof(int**));
	int* b = malloc(4*sizeof(int));
	*a = &b;

	b[0] = 2;
	b[2] = 2;
	*((**a)+1) = 0;
	*((**a)+3) = 0;

	printf("%i%i%i%i", *(**a), b[1], *((**a)+2), b[3]);

	/*
	 * ...
	 */

	return 0;
}