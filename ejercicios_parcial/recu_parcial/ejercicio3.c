typedef struct nodo{
  int valor;
  struct nodo *izquierda;
  struct nodo *centro;
  struct nodo *derecha;
}nodo_t;

int sumar_valores(nodo_t *nodo, int *contador){
  int suma = nodo->valor ;
  if (nodo->izquierda){
  suma = suma + sumar_valores(nodo->izquierda, contador) ;
  }
  if (nodo->centro){
  suma = suma + sumar_valores(nodo->centro,contador) ;
  }
  if (nodo->derecha){
  suma = suma + sumar_valores(nodo->derecha, contador) ;
  }
  (*contador)++;
  return suma;
}

int calcular_promedio(arbol_t* arbol){
  if (!arbol)return 0;
  int contador=0;
  int suma = sumar_valores(arbol->nodo_raiz, &contador)
  return suma/contador;
}


int main(){

}
