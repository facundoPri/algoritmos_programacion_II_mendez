#include <stdio.h>

char una_funcion(int a, double b){
  printf("a: %i, b: %f\n", a,b);
  return 0;
}

int main(){

  int a=5;
  double b=62.7;
  
  una_funcion(a,b);

  char (*nombre_puntero_funcion)(int, double) = una_funcion;

  nombre_puntero_funcion = una_funcion;

  nombre_puntero_funcion(a,b);

  (*nombre_puntero_funcion)(a,b);

  return 0;
}
