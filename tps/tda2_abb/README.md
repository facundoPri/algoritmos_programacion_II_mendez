# Teoria

## Que es un arbol?

Es una estuctura de datos no lineal, hecha por nodos enlazados, donde cada nodo puede apuntar a uno o vario nodos.

## Que es un arbol binario?

Es un arbol donde casa nodo puede apuntar a maximo dos nodos, normalmente denominados como nodo izquierdo y nodo derecho.

## Que es un arbol binario de busqueda?

Es un arbol binario que nos permite almacenar los datos de una forma ordenada. Lo que nos permite utilizar la busqueda binaria para buscar, adicionar y eliminar elementos de una manera rapida.

# Implementacion

### Crear Arbol

Para crear un arbol es necesario pasar una funcion para comparar los elemmentos, pero no es necesario pasar una funcion para destruirlos.

### Insertar nodo

Utiliza la funcion buscar_hoja para encontrar donde poner el elemento pasado;
La funcion buscar_hoja recorre el arbol de forma recursiva y utiliza el comparador para saber si tiene que ir al nodo izquierda o derecha del nodo actual. Como busca una hoja cuando encuentra NULL, crea un nodo en su lugar y lo devuelve.

### Borrar nodo

La funcion arbol_borrar utiliza la funcion borrar_nodo para encontrar y borrar los nodos que contengan el elemento se desee borrar.
La funcion borrar_nodo es una funcion recursiva que recibe un nodo, un elemento, la funcion de comparacion del arbol y una funcion que se encargue de liberar la memoria que utilice los elementos almacenados.
Esta empieza haciendo la comparacion entre el elemento pasado y el elemento del nodo, si no coinciden entonces va ver para que lado tiene que seguir buscando y llamar devuelta la funcion.
Una vez que se haya encontrado el nodo que contiene el elemento a borrar se verifica la cantidad de hijos que este tiene:

- Si no tiene ninguno entonces apenas va a eliminar el nodo utilizando la funcion destruir, la cual se encarga de liberar la memoria utilizada por el nodo y el elemento en caso de que se pase una funcion para hacer esto. Despues se hacer esto se devuelve null ya que su padre ahora tiene que apuntar a null.
- Caso que solo tenga un hijo entonces devolvemos este mismo y borramos el nodo.
- Ahora si el nodo tiene dos hijos se busca el mayor nodo de su subarbol izquierda, este nodo lo llamamos nodo_anterior_inorden. Como queremos borrar el nodo actual se borra y libera la memoria de elemento y lo remplazamos por el elemento del nodo_anterior_inorden. Y por ultimo se borra el nodo_anterior_inorden, pero sin eliminar su elemento ya que este ahora esta en nuestro nodo actual. Para borra el nodo_anterior_inorden se llama la misma funcion, pero sin pasar un destructor.

### Buscar nodo

Para buscar un elemento la funcion arbol_buscar utiliza la funcion buscar_nodo. La funcion buscar_nodo es una funcion recursiva que utiliza el comparador del arbol para ir nodo por nodo hasta encontrar el elemento que estamos buscando

### Arbol raiz

La funcion arbol_raiz devuele la raiz del arbol, mientras este arbol sea valido

### Arbol vacio

La funcion arbol_vacio verifica si la raiz del arbol existe o no

### Recorrer arbol inorden

Con la funcion arbol_recorrido_inorden se puede recorrer un arbol valio y obtener los elementos en ordenados de dicha forma pasandole un array y la cantidad de elemetos que queremos obtener.
Esta funcion utiliza una funcion recursiva llamada recorrer_inorden la cual recorre el arbol y los anota en un array hasta que no hayan mas elementos o hasta que el array se quede sin espacio

### Recorrer arbol preorden

Con la funcion arbol_recorrido_preorden se puede recorrer un arbol valio y obtener los elementos en ordenados de dicha forma pasandole un array y la cantidad de elemetos que queremos obtener.
Esta funcion utiliza una funcion recursiva llamada recorrer_preorden la cual recorre el arbol y los anota en un array hasta que no hayan mas elementos o hasta que el array se quede sin espacio

### Recorrer arbol_postorden

Con la funcion arbol_recorrido_postorden se puede recorrer un arbol valio y obtener los elementos en ordenados de dicha forma pasandole un array y la cantidad de elemetos que queremos obtener.
Esta funcion utiliza una funcion recursiva llamada recorrer_postorden la cual recorre el arbol y los anota en un array hasta que no hayan mas elementos o hasta que el array se quede sin espacio

### Destruir arbol

La funcion arbol_destruir utiliza a la funcion nodo_destruir para eliminar todos los nodos y despues destruye el arbol
Esta funcion nodo_destruir es muy parecida a la funcion recorrer_postorden pero en vez de anotar cada elemento en un array los para a la funcion destruir_nodo para que se libere la memoria del nodo y del elemento si necesario

### Iterador interno

La funcion abb_con_cada_elemento recibe un arbol una funcion que se debe aplicar acada elemento del arbol, un parametro extra para la funcion y el metodo para recorrerlo el arbol.
Como el usuario puede elegir la forma en que va a recorrer el arbol se crearon 3 funciones adicionales abb_inorden_con_cada_elemento, abb_preorden_con_cada_elemento y abb_postorden_con_cada_elemento.
Esta tres funciones son muy parecidad a las funciones de recorrer pero ademas de no recibir un array, estas cuentan con una funcion, el parametro extra y una booleano para detener el recorrido. La funcion se ejecuta con cada iteracion y su valor es guardado en este boolean, asi se sabe cuando es necesario dejar de iterar.
Para utilizar el iterador el usuario debe pasar una funcion valida, ya que si no se cuenta con una es recomendado el uso de uno de los iteradores anteriormente mencionado.
