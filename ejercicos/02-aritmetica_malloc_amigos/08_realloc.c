#include <stdio.h>
#include <stdlib.h>

//¿Qué problema hay con el realloc?
//¿Cómo lo '''arreglamos'''?

int main(){

  void *datos = NULL;

  for(size_t i=0;i<3;i++){
    datos = realloc(datos, i*1024*1024*1024*100);
    printf("Dirección del bloque asignado: %p\n", datos);
  }
}
