/*
 * Diagrame cómo queda el Stack y el Heap al
 * finalizar la ejecución.
 */
void sumar_uno(int *numero) { (*numero)++; }

int main() {
  int a = 8;
  sumar_uno(&a);
  printf("%i", a);
}

/*
Tenemos a en el stack
sumar_uno recibe un puntero y le suma uno al valor del puntero
le pasamos la direccion de a (&a) a la funcion sumar_uno
Esta le suma uno a nuetra variable a
*/
