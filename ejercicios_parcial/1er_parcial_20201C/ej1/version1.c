#include <stdio.h>
#include <stdlib.h>

typedef struct azul{
  char campo1;
  char ***campo2;
}azul_t;

int main(){
  azul_t *v1 = malloc(1*sizeof(azul_t));
  if (!v1)return -1;

  v1->campo2 = malloc(5*sizeof(char*));
  if (!v1->campo2) {
    free(v1);
    return -1;
  }

  char v_stack;
  char *v_heap = malloc(1*sizeof(char));
  if (!v_heap){
    free(v1->campo2);
    free(v1);
    return -1;
  }

  // Hacer los if para los malloc
  for (int i=0; i<5; i++){
    v1->campo2[i] = malloc((i+1)*sizeof(char*));
    if(!v1->campo2[i]){
      for(int k=0; k<i;k++){
       free(v1->campo2[k]);
      }
      free(v_heap);
      free(v1->campo2);
      free(v1);
      return -1;
    }
    for (int j=0; j<=i; j++){
      if (j%2 ==0){
        v1->campo2[i][j] = &v_stack;
      }else{
        v1->campo2[i][j] = v_heap;
      }
    }
  }
  free(v_heap);
  for(int i=0; i<5;i++){
    free(v1->campo2[i]);
  }
  free(v1->campo2);
  free(v1);

  return 0;
}
