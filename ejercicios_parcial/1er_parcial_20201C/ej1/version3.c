#include <stdlib.h>

typedef struct rojo{
  char campo1;
  struct rojo *campo2;
}rojo_t;

typedef struct azul{
  char campo1;
  struct rojo **campo2;
}azul_t;

int main(){
  azul_t *v1= malloc(1*sizeof(azul_t));
  if(!v1)return -1;

  v1->campo2 = malloc(4*sizeof(rojo_t*));
  if (!v1->campo2){
    free(v1);
    return -1;
  }

  for (int i =3;i>=0;i--){
    v1->campo2[i]= malloc(sizeof(rojo_t));
    if(!v1->campo2[i]){
      for(int j=3; j>i;j--){
        free(v1->campo2[j]);
      }
      free(v1->campo2);
      free(v1);
    }
    if(i<3){
      v1->campo2[i]->campo2 = v1->campo2[i+1];
    }
  }

  for (int i =3;i>=0;i--){
    free(v1->campo2[i]);
  }
  free(v1->campo2);
  free(v1);

  return 0 ;
}

