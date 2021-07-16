#include <stdlib.h>

typedef struct verde {
  struct rojo *campo1;
  struct verde *campo2;
} verde_t;

typedef struct rojo {
  struct verde *campo1;
  struct verde campo2;
} rojo_t;

verde_t * crear_verde(rojo_t*apunta_rojo){
  verde_t * verde = calloc(1, sizeof(verde_t));
  if (!verde)return NULL;
  verde->campo1 = apunta_rojo;
  return verde;
}

int main(){
  rojo_t rojo_stack;
  rojo_stack.campo1 = &rojo_stack.campo2;
  rojo_stack.campo2.campo1 = NULL;

  rojo_stack.campo2.campo2 = crear_verde(&rojo_stack);
  if (!rojo_stack.campo2.campo2)return -1;

  rojo_stack.campo2.campo2->campo2 = crear_verde(&rojo_stack);
  if (!rojo_stack.campo2.campo2->campo2){
    free(rojo_stack.campo2.campo2);
    return -1;
  }

  rojo_stack.campo2.campo2->campo2->campo2 = crear_verde(&rojo_stack);
  if (!rojo_stack.campo2.campo2->campo2->campo2){
    free(rojo_stack.campo2.campo2->campo2);
    free(rojo_stack.campo2.campo2);
    return -1;
  }

  rojo_stack.campo2.campo2->campo2->campo2->campo2 = crear_verde(&rojo_stack);
  if (!rojo_stack.campo2.campo2->campo2->campo2){
    free(rojo_stack.campo2.campo2->campo2->campo2);
    free(rojo_stack.campo2.campo2->campo2);
    free(rojo_stack.campo2.campo2);
    return -1;
  }

  rojo_t * rojo_heap = calloc(1, sizeof(rojo_t));
  if (!rojo_heap){
    free(rojo_stack.campo2.campo2->campo2->campo2->campo2);
    free(rojo_stack.campo2.campo2->campo2->campo2);
    free(rojo_stack.campo2.campo2->campo2);
    free(rojo_stack.campo2.campo2);
    return -1;
  }

  rojo_heap->campo1 = &rojo_heap->campo2;
  rojo_heap->campo2.campo1 = &rojo_stack;
  rojo_stack.campo2.campo2->campo2->campo2->campo2->campo2 = rojo_heap->campo1;

  // liberar memoria
  free(rojo_heap);
  free(rojo_stack.campo2.campo2->campo2->campo2->campo2);
  free(rojo_stack.campo2.campo2->campo2->campo2);
  free(rojo_stack.campo2.campo2->campo2);
  free(rojo_stack.campo2.campo2);

  return 0;
}
