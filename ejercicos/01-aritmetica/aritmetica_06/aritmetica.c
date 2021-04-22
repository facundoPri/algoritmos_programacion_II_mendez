/*
 * Diagrame cómo queda el Stack y el Heap al
 * finalizar la ejecución.
 */
int *un_entero_en_el_heap(int numero) {
  int *aux = malloc(sizeof(int));
  *aux = numero;
  return aux;
}

int main() {
  int *un_entero = un_entero_en_el_heap(8);

  int a = *un_entero;
  printf("Numero de a= %i", a);
}

/*
la funcion un_entero_en_el_heap recibe un numero, crea un puntero en el stack y
reserva memoria en el heap para almacenar un entero
 - A este puntero le asigna el entero pasado por parametro y devuelve este
puntero
En el main guardamos el puntero que devuelve la funcion un_entero_en_el_heap en
un puntero un_entero Despues le asignamos el valor del putero a <a>
*/
