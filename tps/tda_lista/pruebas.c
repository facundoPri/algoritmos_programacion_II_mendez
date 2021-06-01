#include "lista.h"
#include "pa2mm.h"

// Crear lista
void CuandoCreoLista_ObtengoPunteroListaConCantidad0YNodosEnNull() {
  lista_t *lista = lista_crear();

  pa2m_afirmar(lista->cantidad == 0, "La lista inicia con cantidad 0");
  pa2m_afirmar(lista->nodo_inicio == NULL,
               "La lista inicia con nodo_inicial nulo");
  pa2m_afirmar(lista->nodo_fin == NULL, "La lista inicia con nodo_fin nulo");

  free(lista);
}


int main() {
  pa2m_nuevo_grupo("Crear lista");
  CuandoCreoLista_ObtengoPunteroListaConCantidad0YNodosEnNull();


  return pa2m_mostrar_reporte();
}
