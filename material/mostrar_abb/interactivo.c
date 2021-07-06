#include "mostrar_abb.h"
#include "abb.h"
#include <stdio.h>
#include <ctype.h>

void formatear_int(void* _i){
  int* i = _i;
  if(!i)
    printf("??");
  printf("%2d", *i);
}

int comparar_int(void* _i1, void* _i2){
  int* i1=_i1;
  int* i2=_i2;
  return *i1-*i2;
}

void destruir_int(void* i){
  free(i);
}

int main(int argc, char* argv[]){
  abb_t* abb = arbol_crear(comparar_int, destruir_int);

  printf("\n+<valor> inserta un valor, -<valor> elimina un valor, ?<valor> bsuca un valor, m muestra el arbol, q sale.\nLos valores deben estar entre 1 y 99, plis.\n");

  while(1){

    printf("> ");

    char c;
    int valor;
    
    scanf(" %c%i", &c, &valor);
    c = (char)tolower(c);

    if(c == 'q')
      break;

    if(c == 'm')
      mostrar_abb(abb, formatear_int);
    else if(valor>0 && valor<100){

      if(c == '+'){
        int* i = malloc(sizeof(int));
        *i = valor;
        arbol_insertar(abb, i);
      }
      else if (c == '-')
        arbol_borrar(abb, &valor);
      else if(c == '?'){
        int* encontrado = arbol_buscar(abb, &valor);
        if(encontrado)
          printf("Valor encontrado: %i\n", *encontrado);
        else printf("No encontré el valor D:\n");
      }
      else
        printf("Tenes que usar +<numero> o -<numero>");

      mostrar_abb(abb, formatear_int);
    }
  }

  arbol_destruir(abb);
}
