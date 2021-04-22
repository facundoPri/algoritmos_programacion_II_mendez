/*
 * Reemplace los ???????? con expresiones
 * que hagan verdadera la condición.
 * Diagrame cómo queda el Stack y el Heap al
 * finalizar la ejecución.
 */

int main() {
  int numero;
  numero = 8;

  int *p_numero;
  p_numero = &numero;

  *p_numero = 10;

  int **p_p_numero;
  p_p_numero = &p_numero;

  **p_p_numero = 12;

  if (p_p_numero == &p_numero)
    printf("Son iguals.");

  if (*p_p_numero == p_numero)
    printf("Son iguals.");
  if (*p_p_numero == &numero)
    printf("Son iguals.");

  if (**p_p_numero == numero)
    printf("Son iguals.");
  if (**p_p_numero == *p_numero)
    printf("Son iguals.");
  if (**p_p_numero == 12)
    printf("Son iguals.");
}

/*
numero esta en el stack
p_numero esta en el stack y apunta a numero (almazena la direccion de numero)
Le asignamos al valor de lo que apunta p_numero 10
p_p_numero esta en stack y apunta a p_numero (almazena la direccion de p_numero)
Le asignamos al valor de lo que apunta lo que apunta p_p_numero (p_p_numero ->
p_numero -> numero)
*/
