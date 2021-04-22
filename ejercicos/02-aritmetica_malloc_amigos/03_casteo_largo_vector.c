#include <stdio.h>

// Ojo con los casteos+punteros.

void modificar_algo(char* byte){
  (*(int*)byte) += 0x05050505; //21559051525
}

int main(){
  char vector[9];

  for(int i=0;i<9;i++){
    vector[i] = 'A'+i;
  }

  modificar_algo((vector)+4);

  printf("a=%c, b=%c, c=%c, d=%c, e=%c, f=%c, g=%c, h=%c, i=%c\n",
	 vector[0], vector[1], vector[2], vector[3], vector[4],
	 vector[5], vector[6], vector[7], vector[8]);
}
