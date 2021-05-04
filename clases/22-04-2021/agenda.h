#ifndef __AGENDA_H_
#define __AGENDA_H_

typedef struct {
  char *nombre;
  int numero;
} item_agenda_t;

typedef struct {
  char *nombre;
  int cantidad_entradas;
  item_agenda_t *entradas;
} agenda_t;

agenda_t *agenda_crear(const char *nombre);
agenda_t *agenda_agregar_contacto(agenda_t *agenda, const char *nombre,
                                  int telefono);

void agenda_mostrar(agenda_t *agenda);
void agenda_mostrar_si(agenda_t *agenda, bool (*criterio)(item_agenda_t *));

void agenda_destruir(agenda_t *agenda);

#endif // __AGENDA_H_
