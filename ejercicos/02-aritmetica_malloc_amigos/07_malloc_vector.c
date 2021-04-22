#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//¿Por qué no funciona?

char* agregar_texto(char* string, char* texto){
  int tamanio_actual = 0;
  if(string != NULL)
    tamanio_actual = strlen(string);

  char* nuevo_string = realloc(string, tamanio_actual+strlen(texto)+1);
  if(nuevo_string==NULL)
    return string;

  strcpy(string+tamanio_actual, texto);
  return string;
}

int main(){
  char* string = NULL;

  string = agregar_texto(string, "Hola");
  string = agregar_texto(string, " ");
  string = agregar_texto(string, "Mundo");
  string = agregar_texto(string, "!");

  printf("%s\n", string);
}
