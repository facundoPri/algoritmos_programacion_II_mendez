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

// Insertar a Lista
void DadaUnaListaVaciaYUnElemento_CuandoIngresoElementoALista_EntoncesObtengoUnaListaConCantidadIncrementada() {
  lista_t *lista = lista_crear();
  void *elemento = (void *)1;
  lista_insertar(lista, elemento);

  pa2m_afirmar(lista->cantidad == 1, "La lista tiene cantidad igual a 1");

  lista_insertar(lista, elemento);
  pa2m_afirmar(lista->cantidad == 2, "La lista tiene cantidad igual a 2");

  lista_insertar(lista, elemento);
  pa2m_afirmar(lista->cantidad == 3, "La lista tiene cantidad igual a 3");

  free(lista->nodo_inicio->siguiente->siguiente);
  free(lista->nodo_inicio->siguiente);
  free(lista->nodo_inicio);
  free(lista);
}

void DadaUnaListaVaciaYUnElemento_CuandoIngresoElementoALista_EntoncesElNodoInicialYFinalDeLaListaApuntanAlNodoDelElemento() {
  lista_t *lista = lista_crear();
  void *elemento = (void *)1;
  lista_insertar(lista, elemento);

  pa2m_afirmar(lista->nodo_inicio->elemento == elemento,
               "El elemento del nodo_inicial corresponde al elemento pasado");
  pa2m_afirmar(lista->nodo_fin->elemento == elemento,
               "El elemento del nodo_fin corresponde al elemento pasado");

  free(lista->nodo_inicio);
  free(lista);
}

void DadaUnaListaNoVaciaYUnElemento_CuandoIngresoElementoALista_EntoncesElNodoFinalDelaListaYElPenultimoNodoApuntanAlNodoDelElemento() {
  lista_t *lista = lista_crear();
  void *elemento = (void *)1;
  lista_insertar(lista, elemento);
  void *nuevo_elemento = (void *)2;
  nodo_t *penultimo_nodo = lista->nodo_fin;
  lista_insertar(lista, nuevo_elemento);

  pa2m_afirmar(lista->nodo_fin->elemento == nuevo_elemento,
               "El elemento del nodo_final corresponde al elemento pasado");
  pa2m_afirmar(penultimo_nodo->siguiente == lista->nodo_fin,
               "El penultimo nodo apunta a nuevo nodo");

  free(lista->nodo_inicio->siguiente);
  free(lista->nodo_inicio);
  free(lista);
}

void DadaUnaListaInvalidaYUnElemento_CuandoIgresoElementoALista_EntoncesObtengoMenosUno() {
  pa2m_afirmar(lista_insertar(NULL, (void *)1) == -1,
               "Devuelve -1 cuando lista es un elemento NULL")
}

// Insertar a lista en posicion

void DadaUnaListaElementoYPosicion_CuandoIngresoElementoEnPosicion_EntoncesLaCantidadDeNodosSeIncrementa() {
  lista_t *lista = lista_crear();
  void *elemento = (void *)1;
  lista_insertar_en_posicion(lista, elemento, 0);
  pa2m_afirmar(lista->cantidad == 1, "Cantidad de elementos igual a 1");

  lista_insertar_en_posicion(lista, elemento, 1);
  pa2m_afirmar(lista->cantidad == 2, "Cantidad de elementos igual a 2");

  lista_insertar_en_posicion(lista, elemento, 1);
  pa2m_afirmar(lista->cantidad == 3, "Cantidad de elementos igual a 3");

  free(lista->nodo_inicio->siguiente->siguiente);
  free(lista->nodo_inicio->siguiente);
  free(lista->nodo_inicio);
  free(lista);
}

void DadaUnaListaUnElementoYZeroComoPosicion_CuandoIngresoElementoAListaEnPosicion_EntoncesSeLeAgregaElNodoDelElementoAlPrincipio() {
  lista_t *lista = lista_crear();
  void *elemento = (void *)1;
  lista_insertar_en_posicion(lista, elemento, 0);
  pa2m_afirmar(lista->nodo_inicio->elemento == elemento,
               "Nuevo elemento agregado al principio, cuando lista vacia");

  lista_insertar_en_posicion(lista, elemento, 0);
  pa2m_afirmar(
      lista->nodo_inicio->elemento == elemento,
      "Nuevo elemento agregado al principio, cuando lista no esta vacia");
  free(lista->nodo_inicio->siguiente);
  free(lista->nodo_inicio);
  free(lista);
}

void DadaUnaListaUnElementoYUnaPosicionMayorALaCantidad_CuandoIngresoElementoAListaEnPosicion_EntoncesSeAgregaNodoDelElementoAlFinal() {
  lista_t *lista = lista_crear();
  void *elemento = (void *)1;
  lista_insertar_en_posicion(lista, elemento, 10);
  pa2m_afirmar(lista->nodo_fin->elemento == elemento,
               "Nuevo elemento agregado al final");

  free(lista->nodo_inicio);
  free(lista);
}

void DadaUnaListaUnElementoYUnaPosicionTresVeces_CuandoIngresoElementoAListaEnPosicion_EntoncesLaListaContieneTresNodosEnlazados() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)3;

  lista_insertar_en_posicion(lista, elemento_uno, 0);
  lista_insertar_en_posicion(lista, elemento_tres, 2);
  lista_insertar_en_posicion(lista, elemento_dos, 1);

  pa2m_afirmar(lista->nodo_inicio->elemento == elemento_uno,
               "El primer elemento corresponde");
  pa2m_afirmar(lista->nodo_inicio->siguiente->elemento == elemento_dos,
               "El segundo elemento corresponde");
  pa2m_afirmar(lista->nodo_fin->elemento == elemento_tres,
               "El ultimo elemento corresponde");

  free(lista->nodo_inicio->siguiente->siguiente);
  free(lista->nodo_inicio->siguiente);
  free(lista->nodo_inicio);
  free(lista);
}

// Borrar ultimo elemento de lista
// Lista esta vacia
void DadaUnaListaVacia_CuandoIntentoBorrarElUltimoElemento_EntoncesObtengoMenosUno() {
  lista_t *lista = lista_crear();
  pa2m_afirmar(lista_borrar(lista) == -1,
               "Borrar ultimo elemento de lista vacia devuele -1");

  free(lista);
}
// Lista NULL
void DadaUnaListaNula_CuandoIntentoBorrarElUltimoElemento_EntoncesObtengoMenosUno() {
  pa2m_afirmar(lista_borrar(NULL) == -1,
               "Borrar ultimo elemento de lista Nula devuele -1");
}
// Borrar un elemento de la lista hace con que la cantidad disminuya
void DadaUnaLista_CuandoBorroElUltimoElemento_EntoncesLaCantidadDeNodosDisminuye() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)3;
  lista_insertar(lista, elemento_uno);
  lista_insertar(lista, elemento_dos);
  lista_insertar(lista, elemento_tres);

  pa2m_afirmar(lista->cantidad == 3, "Lista contiene 3 nodos");
  lista_borrar(lista);
  pa2m_afirmar(lista->cantidad == 2, "Lista contiene 2 nodos");
  lista_borrar(lista);
  pa2m_afirmar(lista->cantidad == 1, "Lista contiene 1 nodo");
  lista_borrar(lista);
  pa2m_afirmar(lista->cantidad == 0, "Lista contiene 0 nodos");

  free(lista);
}

// Chequear que el ultimo elemento se borre
void DadaUnaLista_CuandoBorroElUltimoElemento_EntoncesLaListaCambiaDeUltimoElemento() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)3;
  // printf("%i",*(int*)lista->nodo_fin);
  lista_insertar(lista, elemento_uno);
  lista_insertar(lista, elemento_dos);
  lista_insertar(lista, elemento_tres);

  lista_borrar(lista);
  pa2m_afirmar(lista->nodo_fin->elemento == elemento_dos,
               "Al borrar el ultimo elemento, nodo_fin apunta al anterior [1]");
  lista_borrar(lista);
  pa2m_afirmar(lista->nodo_fin->elemento == elemento_uno,
               "Al borrar el ultimo elemento, nodo_fin apunta al anterior [2]");

  free(lista->nodo_inicio);
  free(lista);
}
// Borrar el ultimo elemento de una lista con un elemento hace que esta este
// vacia y los nodos apunten a null
void DadaUnaListaConUnElemento_CuandoBorroElUltimoElemento_EntoncesLaListaQuedaVaciaYConSusNodosApundandoANULL() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  lista_insertar(lista, elemento_uno);

  lista_borrar(lista);
  pa2m_afirmar(lista->nodo_inicio == NULL, "El nodo inicio apunta a NULL");
  pa2m_afirmar(lista->nodo_fin == NULL, "El nodo fin apunta a NULL");
  pa2m_afirmar(lista->cantidad == 0, "La cantidad de la lista es 0");

  free(lista);
}

// Borrar elemento en posicion
// Al borrar dismiuir canditad
void DadaListaYPosicion_CuandoBorroElementoEnPosicion_EntoncesLaListaDisminuyeSuCantidad() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)3;
  void *elemento_cuatro = (void *)4;
  lista_insertar(lista, elemento_uno);
  lista_insertar(lista, elemento_dos);
  lista_insertar(lista, elemento_tres);
  lista_insertar(lista, elemento_cuatro);

  lista_borrar_de_posicion(lista, 0);
  pa2m_afirmar(lista->cantidad == 3, "La lista tiene 3 elementos 3/4");
  lista_borrar_de_posicion(lista, 1);
  pa2m_afirmar(lista->cantidad == 2, "La lista tiene 2 elementos 2/4");
  lista_borrar_de_posicion(lista, 1);
  pa2m_afirmar(lista->cantidad == 1, "La lista tiene 1 elementos 1/4");
  lista_borrar_de_posicion(lista, 10);
  pa2m_afirmar(lista->cantidad == 0, "La lista tiene 0 elementos 0/4");

  free(lista);
}
// Si la posicion es mayor a la cantidad entonces borrar ultimo
void DadaListaYPosicionMayorACantidad_CuandoIntentoBorrarElementoEnPosicio_EntocesBorroElUltimoElemento() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)3;
  lista_insertar(lista, elemento_uno);
  lista_insertar(lista, elemento_dos);
  lista_insertar(lista, elemento_tres);

  lista_borrar_de_posicion(lista, 10);
  pa2m_afirmar(
      lista->nodo_fin->elemento == elemento_dos,
      "Se borro el ultimo elemento cuando paso posicion mayor a cantidad");
  lista_borrar_de_posicion(lista, 10);
  pa2m_afirmar(lista->nodo_fin->elemento == elemento_uno,
               "Se borro el ultimo elemento de la lista");
  pa2m_afirmar(lista->nodo_fin->elemento == lista->nodo_inicio->elemento,
               "El nodo_fin y nodo_incio apuntan al mismo nodo, cantidad = 1");
  lista_borrar_de_posicion(lista, 10);
  pa2m_afirmar(lista->nodo_fin == NULL,
               "Lista sin elementos, nodo_fin apunta a NULL");
  pa2m_afirmar(lista->nodo_inicio == NULL,
               "Lista sin elementos, nodo_inicio apunta a NULL");

  free(lista);
}
// Borrar en lista vacia
void DadaListaVaciaYPosicion_CuandoIntentoBorrarElementoEnPosicion_EntoncesObtengoMenosUno() {
  lista_t *lista = lista_crear();
  pa2m_afirmar(lista_borrar_de_posicion(lista, 10) == -1,
               "Borrar elemento en posicion 10 en lista vacia devuelve -1");
  pa2m_afirmar(lista_borrar_de_posicion(lista, 0) == -1,
               "Borrar elemento en posicion 0 en lista vacia devuelve -1");

  free(lista);
}

// Borrar en lista nula
void DadaListaNulaYPosicion_CuandoIntentoBorrarElementoEnPosicion_EntoncesObtengoMenosUno() {
  pa2m_afirmar(lista_borrar_de_posicion(NULL, 10) == -1,
               "Borrar elemento en posicion 10 en lista nula devuelve -1");
  pa2m_afirmar(lista_borrar_de_posicion(NULL, 0) == -1,
               "Borrar elemento en posicion 0 en lista nula devuelve -1");
}

// Cuando borro un elemento en el medio los nodos siguen conectados
void DadaListaYPosicion_CuandoBorroElementoEnPosicion_EntoncesLosNodosSiguenConectados() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)3;
  void *elemento_cuatro = (void *)4;
  lista_insertar(lista, elemento_uno);
  lista_insertar(lista, elemento_dos);
  lista_insertar(lista, elemento_tres);
  lista_insertar(lista, elemento_cuatro);

  lista_borrar_de_posicion(lista, 2);
  pa2m_afirmar(lista->nodo_inicio->siguiente->elemento == elemento_dos &&
                   lista->nodo_inicio->siguiente->siguiente->elemento ==
                       elemento_cuatro,
               "Despues de borrar elemento en posicion 2 los elementos que "
               "antes estaban en posicion 1 y 3 se unen");

  free(lista->nodo_inicio->siguiente->siguiente);
  free(lista->nodo_inicio->siguiente);
  free(lista->nodo_inicio);
  free(lista);
}

// Obtener elemento de lista en posicion
// Testear con 4 elementos
void DadaListaCon4ElementosYPosiciones_CuandoBuscoElementos_EntoncesObtengoElElementoDeseado() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)3;
  void *elemento_cuatro = (void *)4;
  lista_insertar(lista, elemento_uno);
  lista_insertar(lista, elemento_dos);
  lista_insertar(lista, elemento_tres);
  lista_insertar(lista, elemento_cuatro);

  pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == elemento_uno,
               "Obtengo elemento uno");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == elemento_dos,
               "Obtengo elemento dos");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == elemento_tres,
               "Obtengo elemento tres");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 3) == elemento_cuatro,
               "Obtengo elemento cuatro");

  free(lista->nodo_inicio->siguiente->siguiente->siguiente);
  free(lista->nodo_inicio->siguiente->siguiente);
  free(lista->nodo_inicio->siguiente);
  free(lista->nodo_inicio);
  free(lista);
}
// Lista Nula
void DadaListaNulaYPosicion_CuandoBuscoElemento_EntoncesObtengoNULL() {
  pa2m_afirmar(lista_elemento_en_posicion(NULL, 0) == NULL,
               "Buscar en lista nula devuelve NULL");
}
// Lista Vacia
void DadaListaVaciaYPosicion_CuandoBuscoElemento_EntoncesObtengoNULL() {
  lista_t *lista = lista_crear();
  pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL,
               "Buscar en lista vacia devuelve NULL");

  free(lista);
}
// Posicion mayor a la cantidad devuelve null
void DadaListaYPosicionMayorACantidad_CuandoBuscoElemento_EntoncesObtengoNull() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  lista_insertar(lista, elemento_uno);
  lista_insertar(lista, elemento_dos);

  pa2m_afirmar(lista_elemento_en_posicion(lista, 3) == NULL,
               "Buscar en posicion mayor a cantidad devuelve NULL");

  free(lista->nodo_inicio->siguiente);
  free(lista->nodo_inicio);
  free(lista);
}

// Obtener ultimo elemento en lista
// Lista vacia devuelve NULL
void DadaListaVacia_CuandoBuscoUltimoElemento_EntoncesObtengoNULL() {
  lista_t *lista = lista_crear();
  pa2m_afirmar(lista_ultimo(lista) == NULL,
               "Buscar el ultimo elemento de una lista vacia devuelve NULL");

  free(lista);
}
// Lista nula devuelve NULL
void DadaListaNula_CuandoBuscoUltimoElemento_EntoncesObtengoNULL() {
  pa2m_afirmar(lista_ultimo(NULL) == NULL,
               "Buscar el ultimo elemento de una lista nula devuelve NULL");
}
// Testear 2 ejemplos
void DadaListaConDosElementos_CuandoBuscoUltimoElemento_EntoncesObtengoElElemento() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  lista_insertar(lista, elemento_uno);
  lista_insertar(lista, elemento_dos);

  pa2m_afirmar(lista_ultimo(lista) == elemento_dos,
               "El ultimo elemento de la lista corresponde [1]");

  lista_borrar(lista);
  pa2m_afirmar(lista_ultimo(lista) == elemento_uno,
               "El ultimo elemento de la lista corresponde [2]");

  free(lista->nodo_inicio);
  free(lista);
}

// Verificar si la lista esta vacia
// Recibe una lista vacia
void DadaListaVacia_CuandoVerificoSiEstaVacia_EntoncesObtengoTrue() {
  lista_t *lista = lista_crear();
  pa2m_afirmar(lista_vacia(lista) == true, "La lista vacia esta vacia");

  free(lista);
}
// Recibe una lista nula
void DadaListaNula_CuandoVerificoSiEstaVacia_EntoncesObtengoTrue() {
  pa2m_afirmar(lista_vacia(NULL) == true, "La lista nula cuenta como vacia");
}
// Recibe una lista no vacia
void DadaListaNoVacia_CuandoVerificoSiEstaVacia_EntoncesObtengoFalse() {
  lista_t *lista = lista_crear();

  void *elemento_uno = (void *)1;
  lista_insertar(lista, elemento_uno);

  pa2m_afirmar(lista_vacia(lista) == false, "La lista no vacia, no esta vacia");

  free(lista->nodo_inicio);
  free(lista);
}

// Verificar canditad de elementos en lista
// Listas y nulas tienen 0 elementos
void DadaUnaListaNulaOVacia_CuandoVerificoLaCantidad_EntocesObtengo0() {
  pa2m_afirmar(lista_elementos(NULL) == 0, "Listas nulas tiene 0 elementos");

  lista_t *lista = lista_crear();
  pa2m_afirmar(lista_elementos(lista) == 0, "Listas vacias tiene 0 elementos");
  free(lista);
}
// Listas con elementos tiene una cantidad mayor a 0
void DadaUnaListaConElementos_CuandoVerificoLaCantidad_EntoncesObtengoSuCantidad() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;

  pa2m_afirmar(lista_elementos(lista) == 0, "Lista con 0 elementos");
  lista_insertar(lista, elemento_uno);
  pa2m_afirmar(lista_elementos(lista) == 1, "Lista con 1 elemento");
  lista_insertar(lista, elemento_dos);
  pa2m_afirmar(lista_elementos(lista) == 2, "Lista con 2 elementos");

  free(lista->nodo_inicio->siguiente);
  free(lista->nodo_inicio);
  free(lista);
}

// Apilar lista
// Agrega elementos al principio de la lista
void DadaListaYElemento_CuandoApiloElemento_EntoncesSeAgregaNodoAlPrincipioDeLaLista() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;

  lista_apilar(lista, elemento_uno);
  pa2m_afirmar(lista->nodo_inicio->elemento == elemento_uno,
               "Nuevo elemento agregado al principio de la lista (1)");
  lista_apilar(lista, elemento_dos);
  pa2m_afirmar(lista->nodo_inicio->elemento == elemento_dos,
               "Nuevo elemento agregado al principio de la lista (2)");

  free(lista->nodo_inicio->siguiente);
  free(lista->nodo_inicio);
  free(lista);
}
// Cuando lista nula devuleve -1
void DadaListaNulaYElemento_CuandoIntentoApilarElemento_EntoncesObtengoMenosUno() {
  pa2m_afirmar(lista_apilar(NULL, (void *)1) == -1,
               "Pasar una lista nula devuelve -1");
}
// Cuando lista vacia nodo incial y final apuntan al elemento agregado
void DadaListaVaciaYElemento_CuandoApiloElemento_EntoncesNodoInicioYFinApuntanAlElemento() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;

  lista_apilar(lista, elemento_uno);
  pa2m_afirmar(lista->nodo_inicio->elemento == elemento_uno &&
                   lista->nodo_fin->elemento == elemento_uno,
               "Nodo inicio y fin apuntan al elemento nuevo");

  free(lista->nodo_inicio);
  free(lista);
}

// Desapilar lista
// Lista nula
void DadaListaNula_CuandoIntentoDesapilarLista_EntoncesObtengoMenosUno() {
  pa2m_afirmar(lista_desapilar(NULL) == -1, "Pasar una lista nula devuelve -1");
}
// Lista vacia
void DadaListaVacia_CuandoIntentoDesapilarLista_EntoncesObtengoMenosUno() {
  lista_t *lista = lista_crear();
  pa2m_afirmar(lista_desapilar(lista) == -1,
               "Pasar una lista nula devuelve -1");

  free(lista);
}
// Eliminar elementos el principio de la lista
void DadaListaNoVacia_CuandoDesapiloLista_EntoncesSegundoElementoPasaAPrimerLugarYDesapilo() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)3;

  lista_apilar(lista, elemento_uno);
  lista_apilar(lista, elemento_dos);
  lista_apilar(lista, elemento_tres);

  lista_desapilar(lista);
  pa2m_afirmar(lista->nodo_inicio->elemento == elemento_dos,
               "Se desapilo correctamente un elemento de la lista");
  lista_desapilar(lista);
  pa2m_afirmar(lista->nodo_inicio->elemento == elemento_uno,
               "Se desapilo correctamente otro elemento de la lista");
  lista_desapilar(lista);
  pa2m_afirmar(lista->nodo_inicio == NULL && lista_vacia(lista),
               "Se desapilo correctamente otro elemento de la lista y la lista "
               "esta vacia");
  pa2m_afirmar(
      lista_desapilar(lista) == -1,
      "La lista no tiene mas elementos por lo tanto desapilar devuelve -1");

  free(lista);
}

// Mostrar tope
// Lista vacia devuelve NULL
void DadaUnaListaVacia_CuandoIntentoMostrarElTope_EntoncesObtengoNULL() {
  pa2m_afirmar(lista_tope(NULL) == NULL, "Lista Nula me devuelve NULL");
}
// Lista Nula devuelve NULL
void DadaUnaListaNula_CuandoIntentoMostrarElTope_EntoncesObtendoNULL() {
  lista_t *lista = lista_crear();
  pa2m_afirmar(lista_tope(lista) == NULL, "Lista vacia me devuelve NULL");

  free(lista);
}
// Lista no vacia devuelve el elemento que se encuentra en el nodos inicio
void DadaUnaListaNoVacia_CuandoIntentoMostrarElTope_EntoncesObtengoElElementoEnElNodoIncio() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)3;

  lista_apilar(lista, elemento_uno);
  lista_apilar(lista, elemento_dos);
  lista_apilar(lista, elemento_tres);

  pa2m_afirmar(lista_tope(lista) == elemento_tres,
               "El tope de la lista corresponde (1)");
  lista_desapilar(lista);
  pa2m_afirmar(lista_tope(lista) == elemento_dos,
               "El tope de la lista corresponde (2)");
  lista_desapilar(lista);
  pa2m_afirmar(lista_tope(lista) == elemento_uno,
               "El tope de la lista corresponde (3)");

  free(lista->nodo_inicio);
  free(lista);
}

// Encolar Lista
// Agrega elemento al final de la lista
void DadaListaYElemento_CuandoEncoloElemento_EntoncesLaListaSeIncrementaYSeLeAgregaNodoAlFinal() {
  lista_t *lista = lista_crear();

  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)3;

  lista_encolar(lista, elemento_uno);
  pa2m_afirmar(lista->nodo_fin->elemento == elemento_uno,
               "Nuevo elemento al final");
  pa2m_afirmar(lista->cantidad == 1, "Cantidad de la lista = 1");

  lista_encolar(lista, elemento_dos);
  pa2m_afirmar(lista->nodo_fin->elemento == elemento_dos,
               "Nuevo elemento al final");
  pa2m_afirmar(lista->cantidad == 2, "Cantidad de la lista = 2");

  lista_encolar(lista, elemento_tres);
  pa2m_afirmar(lista->nodo_fin->elemento == elemento_tres,
               "Nuevo elemento al final");
  pa2m_afirmar(lista->cantidad == 3, "Cantidad de la lista = 3");

  free(lista->nodo_inicio->siguiente->siguiente);
  free(lista->nodo_inicio->siguiente);
  free(lista->nodo_inicio);
  free(lista);
}
// Lista nula devuelve -1
void DadaListaNula_CuandoIntentoEncolarElemento_EntoncesObtengoMenosUno() {
  pa2m_afirmar(lista_encolar(NULL, (void *)1),
               "Encolar en lista nula devuelve -1");
}
// Lista vacia nodo incial y final apuntal al nuevo elemento
void DadaListaVacia_CuandoIntentoEncolarElemento_EntoncesNodoInicioYFinApuntanAlNuevoElemento() {
  lista_t *lista = lista_crear();

  void *elemento_uno = (void *)1;
  lista_encolar(lista, elemento_uno);
  pa2m_afirmar(lista->nodo_inicio->elemento == elemento_uno &&
                   lista->nodo_fin->elemento == elemento_uno,
               "Nodo Inicio y fin apunta a nuevo elemento");

  free(lista->nodo_inicio);
  free(lista);
}

// Desencolar lista
// Remueve el primer elemento de la lista
void DadaLista_CuandoDesencolo_EntoncesListaPierdePrimerElementoYNodoInicioApuntaAlProximo() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  lista_encolar(lista, elemento_uno);
  lista_encolar(lista, elemento_dos);

  lista_desencolar(lista);
  pa2m_afirmar(lista->nodo_inicio->elemento == elemento_dos,
               "Elemento despues del desencolado corresponde");

  free(lista->nodo_inicio);
  free(lista);
}
// Lista nula y vacia  devuelve -1
void DadaListaNulaOVacia_CuandoIntentoDesencolar_EntoncesObtengoMenosUno() {
  pa2m_afirmar(lista_desencolar(NULL) == -1,
               "Desencolar lista Nula devuelve -1");
  lista_t *lista = lista_crear();
  pa2m_afirmar(lista_desencolar(lista) == -1,
               "Desencolar lista vacia devuelve -1");

  free(lista);
}

// Mostrar primero
// Muestra elemento en nodo inicio
void DadaLista_CuandoMuestoPrimerElemento_EntoncesObtengoElElementoEnElNodoInicio() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  lista_encolar(lista, elemento_uno);

  pa2m_afirmar(lista_primero(lista) == elemento_uno,
               "El Primer elemento corresponde");

  free(lista->nodo_inicio);
  free(lista);
}
// Pra listas nulas o vacias devuelve NULL
void DadaListaNulaOVacia_CuandoIntentoMostrarPrimerElemento_EntoncesObtengoNULL() {
  pa2m_afirmar(lista_primero(NULL) == NULL,
               "Mostrar primer elemento de lista nula devuelve NULL");
  lista_t *lista = lista_crear();
  pa2m_afirmar(lista_primero(lista) == NULL,
               "Mostrar primer elemento de lista vacia devuelve NULL");

  free(lista);
}

// Iterador externo
// Si la lista es invalida o vacia el iterador devuelve NULL
void DadaListaNula_CuandoIntentoCrearIterador_EntoncesObtengoNULL() {
  lista_iterador_t *iterador_uno = lista_iterador_crear(NULL);

  pa2m_afirmar(iterador_uno == NULL,
               "Crear iterador con lista nula devuelve null")
}
// Si la lista es valida el iterador la guarda y tiene un nodo corriente
// apuntado al nodo incial de la lista
void DadaListaValida_CuandoCreoIterador_EntoncesObtengoPunteroAlIteradorApuntandoAListaYNodoInicio() {
  lista_t *lista_vacia = lista_crear();
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  lista_insertar(lista, elemento_uno);
  lista_insertar(lista, elemento_dos);

  lista_iterador_t *iterador_lista_vacia = lista_iterador_crear(lista_vacia);

  pa2m_afirmar(iterador_lista_vacia->corriente == NULL &&
                   iterador_lista_vacia->lista == lista_vacia,
               "Se pudo crear lista vacia y nodo corriente apunta a null");

  lista_iterador_t *iterador_lista_normal = lista_iterador_crear(lista);

  pa2m_afirmar(
      iterador_lista_normal->corriente == lista->nodo_inicio &&
          iterador_lista_normal->lista == lista,
      "Se pudo crear lista no vacia y nodo corriente apunta al nodo inicio");

  lista_destruir(lista_vacia);
  lista_destruir(lista);

  lista_iterador_destruir(iterador_lista_vacia);
  lista_iterador_destruir(iterador_lista_normal);
}

// Si el iterador que recibe la funcion lista_iterador_tiene_siguiente no es
// valido esta devuelve false
void DadoIteradorInvalido_CuandoVerificoSiHaySiguiente_EntoncesObtengoFalse() {
  bool tiene_siguiente = lista_iterador_tiene_siguiente(NULL);
  pa2m_afirmar(tiene_siguiente == false,
               "Iterador NULL no tiene siguiente elemento")
}
// La funcion lista_iterador_tiene_siguiente devuelve true si el proximo nodo es
// valido
void DadoIteradorConProximoNodoValido_CuandoVerificoSiHaySiguiente_EntoncesObtengoTrue() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  lista_insertar(lista, elemento_uno);
  lista_insertar(lista, elemento_dos);

  lista_iterador_t *iterador_lista = lista_iterador_crear(lista);
  bool tiene_siguiente = lista_iterador_tiene_siguiente(iterador_lista);

  pa2m_afirmar(tiene_siguiente == true, "Iterador tiene siguiente");

  lista_destruir(lista);
  lista_iterador_destruir(iterador_lista);
}
// La funcion lista_iterador_tiene_siguiente devuelve false si el nodo corriente
// apunta a NULL
void DadoIteradorConNodoCorrienteNull_CuandoVerificoSiHaySiguiente_EntoncesObtengoFalse() {
  lista_t *lista = lista_crear();

  lista_iterador_t *iterador_lista = lista_iterador_crear(lista);
  bool tiene_siguiente = lista_iterador_tiene_siguiente(iterador_lista);

  pa2m_afirmar(tiene_siguiente == false,
               "Iterador con lista vacia o con nodo corriente apunando a null "
               "no tiene siguiente");

  lista_destruir(lista);
  lista_iterador_destruir(iterador_lista);
}

// La funcion lista_iterador_avanza recibe un iterador invalido entonces no hace
// nada y devuelve false
void DadoIteradorInvalido_CuandoIntentoAvanzar_EntoncesObtengoFalseEIteradorNoAvanza() {
  bool pudo_avanzar = lista_iterador_avanzar(NULL);

  pa2m_afirmar(pudo_avanzar == false,
               "Intentar avanzar en interador NULL no es posible")
}
// Se puede avanzar entonces la funcion lista_iterador_avanza devuelve true y
// avanza al siguiente nodo en la lista
void DadoIteradorYSePuedeAvanzar_CuandoIntentoAvanzar_EntoncesObtengoTrueEIteradorAvanza() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)2;
  lista_insertar(lista, elemento_uno);
  lista_insertar(lista, elemento_dos);
  lista_insertar(lista, elemento_tres);

  lista_iterador_t *iterador_lista = lista_iterador_crear(lista);

  pa2m_afirmar(iterador_lista->corriente->elemento == elemento_uno,
               "Elemento corriente corresponde");

  bool tiene_siguiente = lista_iterador_tiene_siguiente(iterador_lista);
  pa2m_afirmar(tiene_siguiente == true, "Iterador tiene siguiente");
  bool pudo_avanzar = lista_iterador_avanzar(iterador_lista);
  pa2m_afirmar(pudo_avanzar == true, "Iterador pudo avanzar");
  pa2m_afirmar(iterador_lista->corriente->elemento == elemento_dos,
               "Elemento corriente corresponde");

  tiene_siguiente = lista_iterador_tiene_siguiente(iterador_lista);
  pa2m_afirmar(tiene_siguiente == true, "Iterador tiene siguiente");
  pudo_avanzar = lista_iterador_avanzar(iterador_lista);
  pa2m_afirmar(pudo_avanzar == true, "Iterador pudo avanzar");
  pa2m_afirmar(iterador_lista->corriente->elemento == elemento_tres,
               "Elemento corriente corresponde");

  tiene_siguiente = lista_iterador_tiene_siguiente(iterador_lista);
  pa2m_afirmar(tiene_siguiente == true,
               "Iterador tiene siguiente pero es null");
  pudo_avanzar = lista_iterador_avanzar(iterador_lista);
  pa2m_afirmar(pudo_avanzar == false, "Iterador no pudo avanzar");
  pa2m_afirmar(iterador_lista->corriente == NULL,
               "Elemento corriente apunta a NULL");

  tiene_siguiente = lista_iterador_tiene_siguiente(iterador_lista);
  pa2m_afirmar(tiene_siguiente == false, "Iterador no tiene siguiente");
  pudo_avanzar = lista_iterador_avanzar(iterador_lista);
  pa2m_afirmar(pudo_avanzar == false, "Iterador no pudo avanzar");
  pa2m_afirmar(iterador_lista->corriente == NULL,
               "Elemento corriente apunta a NULL");

  lista_destruir(lista);
  lista_iterador_destruir(iterador_lista);
}
// Se llama la funcion lista_iterador_avanzar desde una lista vacia
void DadoIteradorListaVacia_CuandoIntentoAvanzar_EntoncesObtengoFalseEIteradorNoAvanza() {
  lista_t *lista = lista_crear();
  lista_iterador_t *iterador_lista = lista_iterador_crear(lista);

  pa2m_afirmar(iterador_lista->corriente == NULL,
               "Nodo corriente apunta a NULL");
  bool pudo_avanzar = lista_iterador_avanzar(iterador_lista);
  pa2m_afirmar(pudo_avanzar == false, "Iterador no pudo avanzar");

  lista_destruir(lista);
  lista_iterador_destruir(iterador_lista);
}

// La funcion lista_iterador_elemento_actual recibe un iterador invalido
// entonces devuelve NULL
void DadoIteradorInvalido_CuandoBuscoElementoActual_EntoncesObtengoNull() {
  pa2m_afirmar(
      lista_iterador_elemento_actual(NULL) == NULL,
      "Lista_iterador_elemento_actul recibe iterador NULL y devuelve NULL");
}
// El elemento actual es valido asi que lista_iterador_elemento_actual devuelve
// el elemento actual
void DadoIteradorConNodoCorrienteValido_CuandoBuscoElementoActual_EntoncesObtengoElElementoDelNodoCorriente() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)2;
  lista_insertar(lista, elemento_uno);
  lista_insertar(lista, elemento_dos);
  lista_insertar(lista, elemento_tres);

  lista_iterador_t *iterador_lista = lista_iterador_crear(lista);

  pa2m_afirmar(
      lista_iterador_elemento_actual(iterador_lista) == elemento_uno,
      "Lista_iterador_elemento_actual devuelve elemento correspontiente");
  lista_iterador_avanzar(iterador_lista);
  pa2m_afirmar(
      lista_iterador_elemento_actual(iterador_lista) == elemento_dos,
      "Lista_iterador_elemento_actual devuelve elemento correspontiente");
  lista_iterador_avanzar(iterador_lista);
  pa2m_afirmar(
      lista_iterador_elemento_actual(iterador_lista) == elemento_tres,
      "Lista_iterador_elemento_actual devuelve elemento correspontiente");
  lista_iterador_avanzar(iterador_lista);
  pa2m_afirmar(
      lista_iterador_elemento_actual(iterador_lista) == NULL,
      "Lista_iterador_elemento_actual devuelve elemento NULL correspontiente");

  lista_destruir(lista);
  lista_iterador_destruir(iterador_lista);
}
// El elemento acutal es NULL asi que lista_iterador_elemento_actual devuelve
// NULL
void DadoIteradorConNodoCorrienteNULL_CuandoBuscoElementoActual_EntoncesObtengoNULL() {
  lista_t *lista = lista_crear();

  lista_iterador_t *iterador_lista = lista_iterador_crear(lista);

  pa2m_afirmar(lista_iterador_elemento_actual(iterador_lista) == NULL,
               "Lista_iterador_elemento_actual devuelve elemento NULL "
               "correspontiente cuando lista esta vacia");

  lista_destruir(lista);
  lista_iterador_destruir(iterador_lista);
}

// Chequear cantidad de iteraciones
void DadoIterador_CuandoItera_EntoncesFuncionaCorrectamente() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)3;
  lista_insertar(lista, elemento_uno);
  lista_insertar(lista, elemento_dos);
  lista_insertar(lista, elemento_tres);

  lista_iterador_t *iterador_lista = lista_iterador_crear(lista);

  size_t iteraciones = 0;
  while (lista_iterador_tiene_siguiente(iterador_lista)) {
    iteraciones++;
    lista_iterador_avanzar(iterador_lista);
  }
  pa2m_afirmar(iteraciones == lista->cantidad, "Se itero la lista entera");

  lista_destruir(lista);
  lista_iterador_destruir(iterador_lista);
}

// Iterador interno
bool si_es_dos_false(void *numero, void *context) {
  if (numero == (void *)2)
    return false;
  return true;
}
void DadaListaYNingunaFuncion_CuandoItera_EntoncesObtengo0Iteraciones() {
  lista_t *lista = lista_crear();
  lista_iterador_t *iterador_lista = lista_iterador_crear(lista);

  size_t iteraciones = lista_con_cada_elemento(lista, NULL, NULL);
  pa2m_afirmar(iteraciones == 0, "Si no recibe funcion no itera");

  lista_destruir(lista);
  lista_iterador_destruir(iterador_lista);
}
void DadaListaYFuncion_CuandoItera_EntoncesObtengoLaCantidadCorrectaDeIteraciones() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)3;
  lista_insertar(lista, elemento_uno);
  lista_insertar(lista, elemento_dos);
  lista_insertar(lista, elemento_tres);

  lista_iterador_t *iterador_lista = lista_iterador_crear(lista);

  size_t iteraciones = lista_con_cada_elemento(lista, si_es_dos_false, NULL);
  pa2m_afirmar(iteraciones == 2, "Se itera dos veces");

  lista_destruir(lista);
  lista_iterador_destruir(iterador_lista);
}

int main() {
  pa2m_nuevo_grupo("Crear lista");
  CuandoCreoLista_ObtengoPunteroListaConCantidad0YNodosEnNull();

  pa2m_nuevo_grupo("Insertar a lista");
  DadaUnaListaVaciaYUnElemento_CuandoIngresoElementoALista_EntoncesObtengoUnaListaConCantidadIncrementada();
  DadaUnaListaVaciaYUnElemento_CuandoIngresoElementoALista_EntoncesElNodoInicialYFinalDeLaListaApuntanAlNodoDelElemento();
  DadaUnaListaNoVaciaYUnElemento_CuandoIngresoElementoALista_EntoncesElNodoFinalDelaListaYElPenultimoNodoApuntanAlNodoDelElemento();

  pa2m_nuevo_grupo("Insertar elemento en posicion");
  DadaUnaListaElementoYPosicion_CuandoIngresoElementoEnPosicion_EntoncesLaCantidadDeNodosSeIncrementa();
  DadaUnaListaUnElementoYZeroComoPosicion_CuandoIngresoElementoAListaEnPosicion_EntoncesSeLeAgregaElNodoDelElementoAlPrincipio();
  DadaUnaListaUnElementoYUnaPosicionMayorALaCantidad_CuandoIngresoElementoAListaEnPosicion_EntoncesSeAgregaNodoDelElementoAlFinal();
  DadaUnaListaUnElementoYUnaPosicionTresVeces_CuandoIngresoElementoAListaEnPosicion_EntoncesLaListaContieneTresNodosEnlazados();

  pa2m_nuevo_grupo("Borrar ultimo elemento de lista");
  DadaUnaListaVacia_CuandoIntentoBorrarElUltimoElemento_EntoncesObtengoMenosUno();
  DadaUnaListaNula_CuandoIntentoBorrarElUltimoElemento_EntoncesObtengoMenosUno();
  DadaUnaLista_CuandoBorroElUltimoElemento_EntoncesLaCantidadDeNodosDisminuye();
  DadaUnaLista_CuandoBorroElUltimoElemento_EntoncesLaListaCambiaDeUltimoElemento();
  DadaUnaListaConUnElemento_CuandoBorroElUltimoElemento_EntoncesLaListaQuedaVaciaYConSusNodosApundandoANULL();

  pa2m_nuevo_grupo("Borrar elemento en posicion");
  DadaListaYPosicion_CuandoBorroElementoEnPosicion_EntoncesLosNodosSiguenConectados();
  DadaListaNulaYPosicion_CuandoIntentoBorrarElementoEnPosicion_EntoncesObtengoMenosUno();
  DadaListaVaciaYPosicion_CuandoIntentoBorrarElementoEnPosicion_EntoncesObtengoMenosUno();
  DadaListaYPosicionMayorACantidad_CuandoIntentoBorrarElementoEnPosicio_EntocesBorroElUltimoElemento();
  DadaListaYPosicion_CuandoBorroElementoEnPosicion_EntoncesLaListaDisminuyeSuCantidad();

  pa2m_nuevo_grupo("Obtener elemento de lista en posicion");
  DadaListaCon4ElementosYPosiciones_CuandoBuscoElementos_EntoncesObtengoElElementoDeseado();
  DadaListaNulaYPosicion_CuandoBuscoElemento_EntoncesObtengoNULL();
  DadaListaVaciaYPosicion_CuandoBuscoElemento_EntoncesObtengoNULL();
  DadaListaYPosicionMayorACantidad_CuandoBuscoElemento_EntoncesObtengoNull();

  pa2m_nuevo_grupo("Obtener ultimo elemento en lista");
  DadaListaVacia_CuandoBuscoUltimoElemento_EntoncesObtengoNULL();
  DadaListaNula_CuandoBuscoUltimoElemento_EntoncesObtengoNULL();
  DadaListaConDosElementos_CuandoBuscoUltimoElemento_EntoncesObtengoElElemento();

  pa2m_nuevo_grupo("Verificas si la lista esta vacia");
  DadaListaVacia_CuandoVerificoSiEstaVacia_EntoncesObtengoTrue();
  DadaListaNula_CuandoVerificoSiEstaVacia_EntoncesObtengoTrue();
  DadaListaNoVacia_CuandoVerificoSiEstaVacia_EntoncesObtengoFalse();

  pa2m_nuevo_grupo("Verificar cantidad de elementos en lista");
  DadaUnaListaNulaOVacia_CuandoVerificoLaCantidad_EntocesObtengo0();
  DadaUnaListaConElementos_CuandoVerificoLaCantidad_EntoncesObtengoSuCantidad();

  pa2m_nuevo_grupo("Apilar lista");
  DadaListaYElemento_CuandoApiloElemento_EntoncesSeAgregaNodoAlPrincipioDeLaLista();
  DadaListaNulaYElemento_CuandoIntentoApilarElemento_EntoncesObtengoMenosUno();
  DadaListaVaciaYElemento_CuandoApiloElemento_EntoncesNodoInicioYFinApuntanAlElemento();

  pa2m_nuevo_grupo("Desapilar lista");
  DadaListaNula_CuandoIntentoDesapilarLista_EntoncesObtengoMenosUno();
  DadaListaVacia_CuandoIntentoDesapilarLista_EntoncesObtengoMenosUno();
  DadaListaNoVacia_CuandoDesapiloLista_EntoncesSegundoElementoPasaAPrimerLugarYDesapilo();

  pa2m_nuevo_grupo("Mostrar tope");
  DadaUnaListaVacia_CuandoIntentoMostrarElTope_EntoncesObtengoNULL();
  DadaUnaListaNula_CuandoIntentoMostrarElTope_EntoncesObtendoNULL();
  DadaUnaListaNoVacia_CuandoIntentoMostrarElTope_EntoncesObtengoElElementoEnElNodoIncio();

  pa2m_nuevo_grupo("Encolar lista");
  DadaListaYElemento_CuandoEncoloElemento_EntoncesLaListaSeIncrementaYSeLeAgregaNodoAlFinal();
  DadaListaNula_CuandoIntentoEncolarElemento_EntoncesObtengoMenosUno();
  DadaListaVacia_CuandoIntentoEncolarElemento_EntoncesNodoInicioYFinApuntanAlNuevoElemento();

  pa2m_nuevo_grupo("Desencolar lista");
  DadaLista_CuandoDesencolo_EntoncesListaPierdePrimerElementoYNodoInicioApuntaAlProximo();
  DadaListaNulaOVacia_CuandoIntentoDesencolar_EntoncesObtengoMenosUno();

  pa2m_nuevo_grupo("Mostrar Primero");
  DadaLista_CuandoMuestoPrimerElemento_EntoncesObtengoElElementoEnElNodoInicio();
  DadaListaNulaOVacia_CuandoIntentoMostrarPrimerElemento_EntoncesObtengoNULL();

  pa2m_nuevo_grupo("Iterador Externo");
  DadaListaNula_CuandoIntentoCrearIterador_EntoncesObtengoNULL();
  DadaListaValida_CuandoCreoIterador_EntoncesObtengoPunteroAlIteradorApuntandoAListaYNodoInicio();
  DadoIteradorInvalido_CuandoVerificoSiHaySiguiente_EntoncesObtengoFalse();
  DadoIteradorConProximoNodoValido_CuandoVerificoSiHaySiguiente_EntoncesObtengoTrue();
  DadoIteradorConNodoCorrienteNull_CuandoVerificoSiHaySiguiente_EntoncesObtengoFalse();
  DadoIteradorInvalido_CuandoIntentoAvanzar_EntoncesObtengoFalseEIteradorNoAvanza();
  DadoIteradorYSePuedeAvanzar_CuandoIntentoAvanzar_EntoncesObtengoTrueEIteradorAvanza();
  DadoIteradorListaVacia_CuandoIntentoAvanzar_EntoncesObtengoFalseEIteradorNoAvanza();
  DadoIteradorInvalido_CuandoBuscoElementoActual_EntoncesObtengoNull();
  DadoIteradorConNodoCorrienteValido_CuandoBuscoElementoActual_EntoncesObtengoElElementoDelNodoCorriente();
  DadoIteradorConNodoCorrienteNULL_CuandoBuscoElementoActual_EntoncesObtengoNULL();
  DadoIterador_CuandoItera_EntoncesFuncionaCorrectamente();

  pa2m_nuevo_grupo("Iterador Interno");
  DadaListaYNingunaFuncion_CuandoItera_EntoncesObtengo0Iteraciones();
  DadaListaYFuncion_CuandoItera_EntoncesObtengoLaCantidadCorrectaDeIteraciones();

  return pa2m_mostrar_reporte();
}
