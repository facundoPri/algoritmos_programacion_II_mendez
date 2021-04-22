#include <stdio.h>

//Obtener los 2 bytes que componen el short

int main(){
  short numero = 0x4241;
  char byte1, byte2;

  char* pnumero = (char*)&numero;
  
  //Obtener primer y segundo byte
  byte1=???
  byte2=???

  printf("Numero: %hu, primer byte: %x, segundo byte: %x\n",
	 numero,
	 byte1,
	 byte2);
}
