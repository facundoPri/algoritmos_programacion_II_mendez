#include <stdlib.h>
typedef struct pieza {
  char* nombre;
  int x;
  int y;
}pieza_t;

typedef struct jugador{
  int cantidad_piezas;
  pieza_t *piezas[16];
}jugador_t;

typedef struct tablero{
 jugador_t *jugador_bancas;
 jugador_t *jugador_negras;
 int turno;
}tablero_t;

char *piezas[16]={"peon","peon","peon","peon","peon","peon","peon","peon","caballo","caballo","torre","torre","rey","reina"};

int main(){
  tablero_t tablero;

  jugador_t *jugador_b =calloc(1, sizeof(jugador_t));
  if (!jugador_b)return -1;
  jugador_t *jugador_n =calloc(1, sizeof(jugador_t));
  if (!jugador_n){
    free(jugador_b);
    return -1;
  }
  tablero.jugador_bancas = jugador_b;
  tablero.jugador_negras = jugador_n;
  tablero.jugador_bancas->cantidad_piezas=16;
  tablero.jugador_negras->cantidad_piezas=16;

  for (int i = 0; i<16;i++){
    pieza_t pieza;
    pieza.nombre=piezas[i];
    tablero.jugador_bancas->piezas[i]=&pieza;
  }
  for (int i = 0; i<16;i++){
    pieza_t pieza;
    pieza.nombre=piezas[i];
    tablero.jugador_negras->piezas[i]=&pieza;
  }

}
