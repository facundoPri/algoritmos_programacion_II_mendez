#include "agenda.h"
#include <stdbool.h>

bool item_es_impar_y_empieza_con_v(item_agenda_t *item) {
  if (item->numero % 2 != 0)
    return false;

  if (item->nombre[0] != 'v')
    return false;

  return true;
}

int main() {
  agenda_t *agenda = agenda_crear("Facundo");

  // Hacemos algo

  agenda_agregar_contacto(agenda, "Facundo", 1234567);
  agenda_agregar_contacto(agenda, "Mariano", 1234567);
  agenda_agregar_contacto(agenda, "Valen", 1234567);
  agenda_agregar_contacto(agenda, "Gabriel", 1234567);

  agenda_mostrar(agenda);

  agenda_mostrar_si(agenda, item_es_impar_y_empieza_con_v);

  agenda_destruir(agenda);
  return 0;
}
