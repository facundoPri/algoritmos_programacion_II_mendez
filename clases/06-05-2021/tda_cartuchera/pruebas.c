#include "cartuchera.h"
#include "pa2mm.h"

void dadaUnaCApacidad_cuandoCreoUnaCartucheraConEsaCapacidad_SeCreaUnaCartucheraConEsaCapacidad() {
  size_t capacidad = 10;
  cartuchera_t *c = cartuchera_crear(capacidad);
  pa2m_afirmar(c != NULL,
               "se puede crear una crtuchera con una capacidad dada");
  pa2m_afirmar(c->capacidad == capacidad,
               "La capacidad de la cartuchera es la pedida");

  cartuchera_destruir(c);
}

void dadaUnaCapacidadCero_CuandoCreoUnaCartucheraConEsaCapacidad_NoSeCrearUnaCatuchera() {
  size_t capacidad = 0;
  cartuchera_t *c = cartuchera_crear(capacidad);
  pa2m_afirmar(c != NULL, "No se puede crear una cartchera con capacidad cero");
}

int main() {
  pa2m_nuego_grupo("Pruebas de cartuchera");
  dadaUnaCApacidad_cuandoCreoUnaCartucheraConEsaCapacidad_SeCreaUnaCartucheraConEsaCapacidad();

  return pa2m_mostrar_reporte();
}
