#include "salon.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    printf("Crear un salon usando el archivo 'salon_original.sal'\n");
    salon_t *salon = salon_leer_archivo("salon_original.sal");


    printf("\nObtener los entrenadores con al menos 3 ligas ganadas y mostrarlos por pantalla.\n");
    entrenador_t **tres_victorias_min = salon_obtener_entrenadores_mas_ganadores(salon, 3);
    for (int i = 0; i<vtrlen(tres_victorias_min);i++){
        salon_mostrar_entrenador(tres_victorias_min[i]);
    }

    printf("\nAgregar 2 entrenadores al salon con 5 y 7 victorias respectivamente.\n");
    entrenador_t *cinco_victorias =calloc(1,sizeof(entrenador_t));
    cinco_victorias->victorias = 5;
    entrenador_t *siete_victorias= calloc(1, sizeof(entrenador_t));
    siete_victorias->victorias = 7;
    salon= salon_agregar_entrenador(salon, cinco_victorias);
    salon= salon_agregar_entrenador(salon, siete_victorias);

    printf("\nObtener los entrenadores con al menos 5 ligas ganadas y mostrarlos por pantalla.\n");
    entrenador_t **cinco_victorias_min = salon_obtener_entrenadores_mas_ganadores(salon, 5);
    for (int i = 0; i<vtrlen(cinco_victorias_min);i++){
        salon_mostrar_entrenador(cinco_victorias_min[i]);
    }

    printf("\nGuardar el salon a un nuevo archivo 'salon_modificado.sal'\n");
    int entrenadores_guardados = salon_guardar_archivo(salon, "salon_modificado.sal");
    printf("%i entrenadores guardados", entrenadores_guardados);

    printf("\nSalir con valor de retorno 0\n");

    return 0;
}
