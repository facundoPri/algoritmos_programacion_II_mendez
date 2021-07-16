#include <stdlib.h>

typedef struct azul{
  char campo1;
  struct azul **campo2;
}azul_t;

int main(){
  azul_t * v1 = malloc(1*sizeof(azul_t));
  if(!v1)return -1;

  v1->campo2 = malloc(4*sizeof(azul_t*));
  if (!v1->campo2){
    free(v1);
    return -1;
  }
  for (int i =0; i<4;i++){
    v1->campo2[i]= malloc(1*sizeof(azul_t));
    if (!v1->campo2[i]){
      for (int j=0; j<i;j++){
        free(v1->campo2[j]);
      }
      free(v1->campo2);
      free(v1);
      return -1;
    }
  }
  for (int j=0; j<4;j++){
    free(v1->campo2[j]);
  }
  free(v1->campo2);
  free(v1);
  return 0;
}
