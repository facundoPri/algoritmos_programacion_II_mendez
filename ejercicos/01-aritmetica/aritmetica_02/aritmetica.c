/*
 * ¿Por qué es incorrecto el siguiente código?
 */

int main() {
  int *p_numero;
  *p_numero = 8;

  return 0;
}

/*
R: Por que el puntero no esta apuntando a nada
Entonces asignarle un valor es lo mismo que asignarselo a nada
*/
