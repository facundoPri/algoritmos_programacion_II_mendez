#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// strdup no lo podemos usar porque es POSIX pero no es C99
char *duplicar_strings(const char *s) {
  if (!s)
    return NULL;

  char *p = malloc(strlen(s) + 1);
  strcpy(p, s);
  return p;
}

void destruir_string(void *elemento) {
  if (elemento) {
    printf("(Destructor) Libero el vehiculo: %s\n", (char *)elemento);
    free(elemento);
  }
}

bool mostrar_patente(hash_t *hash, const char *clave, void *aux) {
  if (!clave)
    return true;

  aux = aux;
  hash = hash;

  printf("Patente en el hash: %s\n", clave);

  return false;
}

void guardar_vehiculo(hash_t *garage, const char *patente,
                      const char *descripcion) {
  int retorno = hash_insertar(garage, patente, duplicar_strings(descripcion));
  printf("Guardando vehiculo patente %s (%s): ", patente, descripcion);
  printf("%s\n", retorno == 0 ? "OK" : "ERROR");
}

void quitar_vehiculo(hash_t *garage, const char *patente) {
  int retorno = hash_quitar(garage, patente);
  printf("Retirando vehiculo patente %s: ", patente);
  printf("%s\n", retorno == 0 ? "OK" : "ERROR");
}

void verificar_vehiculo(hash_t *garage, const char *patente,
                        bool deberia_existir) {
  printf("Verifico el vehiculo patente %s: ", patente);
  bool retorno = hash_contiene(garage, patente);
  printf("%s\n", (retorno == deberia_existir) ? "OK" : "ERROR");
}

int main() {
  hash_t *hash = hash_crear(destruir_string, 10);

  printf("Agrego autos al garage\n");

  guardar_vehiculo(hash, "AC123BD", "Auto de Mariano");
  guardar_vehiculo(hash, "OPQ976", "Auto de Lucas");
  guardar_vehiculo(hash, "A421ACB", "Moto de Manu");
  guardar_vehiculo(hash, "AA442CD", "Auto de Guido");
  guardar_vehiculo(hash, "AC152AD", "Auto de Agustina");
  guardar_vehiculo(hash, "DZE443", "Auto de Jonathan");
  guardar_vehiculo(hash, "AA436BA", "Auto de Gonzalo");
  guardar_vehiculo(hash, "QDM443", "Auto de Daniela");
  guardar_vehiculo(hash, "BD123AC", "Auto de Pablo");
  guardar_vehiculo(hash, "CD442AA", "Auto de Micaela");
  guardar_vehiculo(hash, "PQO697", "Auto de Juan");
  guardar_vehiculo(hash, "DZE443", "Auto de Jonathan otra vez");
  guardar_vehiculo(hash, "AC152AD", "Auto de Agustina otra vez");

  verificar_vehiculo(hash, "QDM443", true);
  verificar_vehiculo(hash, "PQO697", true);

  quitar_vehiculo(hash, "QDM443");
  quitar_vehiculo(hash, "PQO697");

  verificar_vehiculo(hash, "QDM443", false);
  verificar_vehiculo(hash, "PQO697", false);

  size_t impresas = hash_con_cada_clave(hash, mostrar_patente, NULL);
  printf("Se mostraron %zu patentes con el iterador interno\n\n", impresas);

  hash_destruir(hash);

  return 0;
}
