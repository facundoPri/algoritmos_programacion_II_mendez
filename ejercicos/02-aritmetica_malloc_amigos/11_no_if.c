#include <stdio.h>

//Reescribir sin usar IF

int main(){

  for(int i=0;i<9;i++){
    int n = i%3;

    if(n==0) printf("%i: SI\n", n);
    if(n==1) printf("%i: NO\n", n);
    if(n==2) printf("%i: NO SE\n", n);
  }
  
  return 0;
}
