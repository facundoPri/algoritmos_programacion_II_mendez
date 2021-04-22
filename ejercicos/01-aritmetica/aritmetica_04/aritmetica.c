/*
 * ¿Por qué es incorrecto el siguiente código?
 */

int main() {
  int *p_numero = &a;
  int a;
  /* Correccion */
  /* int a; */
  /* int *p_numero = &a; */
  *p_numero = 8;

  return 0;
}

/*
R: Esto es incorreco ya que estamos queriendo asignarele a un puntero la
direccion de una variable que todavia no existe en el stack
*/
