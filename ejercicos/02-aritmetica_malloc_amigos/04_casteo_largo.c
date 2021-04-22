#include <stdio.h>

//NOTA: Cuando las variables están en el stack, gcc las puede
//organizar de diferente forma.

void modificar_algo(char* byte){
  (*(long*)byte) += 0x0505050505;
}

int main(){
  char a='A',b='B',c='C',d='D',e='E',f='F',g='G',h='H',i='I';

  modificar_algo(&e);

  printf("a=%c, b=%c, c=%c, d=%c, e=%c, f=%c, g=%c, h=%c, i=%c\n",
	 a, b, c, d, e, f, g, h, i);
}
