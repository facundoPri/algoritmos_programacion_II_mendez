/*
 * Diagrame cómo queda el Stack y el Heap al
 * finalizar la ejecución.
 */

int main() {
  int a;
  int *p_numero = &a;
  *p_numero = 8;
}

/*
1- int a en stack
2- int puntero p_numero en stack = direccion de a
3- valore del puntero = 8
*/
