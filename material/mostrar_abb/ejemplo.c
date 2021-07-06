#include "mostrar_abb.h"
#include "abb.h"
#include <stdio.h>

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

int main(){
    int elementos[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
    abb_t* abb = arbol_crear(comparar_int, NULL);

    arbol_insertar(abb, elementos+12);
    arbol_insertar(abb, elementos+20);
    arbol_insertar(abb, elementos+22);
    arbol_insertar(abb, elementos+21);
    arbol_insertar(abb, elementos+23);
    arbol_insertar(abb, elementos+13);
    arbol_insertar(abb, elementos+14);
    arbol_insertar(abb, elementos+8);
    arbol_insertar(abb, elementos+10);
    arbol_insertar(abb, elementos+4);
    arbol_insertar(abb, elementos+2);
    arbol_insertar(abb, elementos+6);
    arbol_insertar(abb, elementos+9);
    arbol_insertar(abb, elementos+11);
    arbol_insertar(abb, elementos+1);
    arbol_insertar(abb, elementos+3);
    arbol_insertar(abb, elementos+5);
    arbol_insertar(abb, elementos+7);

    mostrar_abb(abb, formatear_int);

    arbol_destruir(abb);
    return 0;
}
