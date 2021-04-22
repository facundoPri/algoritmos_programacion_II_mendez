/*
 * Diagrame cómo queda el Stack y el Heap al
 * finalizar la ejecución.
 */

typedef struct cajon {
  int ancho;
  int largo;
  bool lleno;
} cajon_t;

int main() {
  cajon_t un_cajon;
  cajon_t *p_cajon = malloc(sizeof(cajon_t));

  /* Poner valor a los cajones */

  /* Que pasa aca? */
  // p_cajon = &un_cajon;
  // Si le pasamos a nuesto puntero la direccion del cajon en el stack perdemos
  // la referencia a la memoria reservada con malloc, impidiendo que la
  // modifiquemos y mas importante, la liveremos

  /* Que pasa aca? */
  /* cajon_t *p_cajon_otro = p_cajon; */
  // Aca estamos guardando un puntero en otro puntero, esto nos puede dejar con
  // un puntero, que una vez que se libere p_cajon ,nos apunte a basura

  free(p_cajon);
  return 0;
}

/*
Almazenamos una variable llamada un_cajon de tipo cajon en el stack
Creamos un puntero p_cajon de tipo cajon y lo apuntamos a la memoria que
liveramos com malloc
- Esta memoria tiene el tamaño necesario para guardar un cajon
Liberamos la memoria del puntero p_cajon
*/
