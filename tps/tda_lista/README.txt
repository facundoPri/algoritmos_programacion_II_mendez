# Que es una lista?
Un lista es una estuctura de datos, que sirve para agrupar elementos.
Las listas nos permiten tener elementos donde todos tiene un sucesor (menos el ultimo) y un predecesor (menos el primero).
Las listas se pueden implementar como un vector estatico, un vector dinamico o una lista de nodos.
Existen varios tipos de listas de nodos y algunos de ellos son las listas simplemente enlazadas, doblemente enlazadas, circular y circular doblemente enlazada.
La implementacion de lista de este tda es una lista de nodos simplemente enlazadas.

# Implementacion
La estructura de la lista apunta al nodo inicial y al final. Para la funcion de creacion utilice un calloc que me permite ya inicializar los nodos a NULL, ya que la lista arranca vacia.
Para insertar un elemento a la lista es necesario reservar memoria para el nuevo nodo. Como esta funcion siempre agrega al final mi nuevo nodo, busco el nodo que se encuentra ahora al final. Este tiene que estar apuntado al nuevo nodo junto con el nodo_fin de la lista. Tambien necesito sumarle uno a la cantidad de nodos y verificar que este no sea el primer nodo que agrego, caso sea asi, el nodo_inicio tambien debe apuntar al nuevo nodo. 
Para recorrer los nodos cree una funcion auxiliar. Esta es una funcion recursiva, que recibe el nodo desde donde queremos recorrer y cuantos nodos adelante se encuentra el que buscamos. Esta funcion la utilice varias veces durante a implementacion.
Para insertar en posicion necesito verifica con que la posicion que recibo no sea mayor a la cantidad, si es asi directamente utilizo la funcion lista_insertar. Si la posicion es 0 entonces el nodo va al principio, para insertarlo ahi hago con que el nuevo nodo apunte al actual nodo_inicio y despues que nodo inicio apunte a el. Si no entra en estas condiciones significa que el nodo tiene que ser insertado en el medio de la lista, para eso utilizo la funcion recorrer_nodos, obteniendo el nodo anterior a la posicion deseada, ahora el nuevo nodo tiene que apuntar al nodo que apunte el nodo posterior y este pasa a apuntar al nuevo nodo. Por ultimo se incrementa la cantidad de nodos en la lista.
Para borrar el ultimo elemento verifico si la lista tenga mas de dos nodos, ya que si tiene dos eso significa que tengo que borrar el nodo_fin y hacer con que apunte al nodo_inicio, si tiene apenas un nodo entonces la lista queda vacia, si no tiene ninguno o la lista es nula devuelvo -1 ya que eso es invalido. Siendo la cantidad de la lista mayor a dos podemos utilizar la funcion recorrer_nodos para obtener el penultimo nodo, borrar el ultimo y hacer con que nodo_fin apunte al penultimo, ahora ultimo. Una vez echo esto le restamos uno a la cantidad.
Borrar en posicion verifica que la cantidad de nodos sea mayor que uno al igual que la funcion lista_borrar. Pero caso lo sea verifica que a posicion sea distinta a 0 o mayor que la cantidad de la lista. Si la posicion que recibe es igual a zero borramos el primer elemento, si la posicion es mayor que la cantidad ulilizamos la funcion lista_borrar. Si no entra en ninguno de los dos casos buscamos el nodo anterior al que queremos borrar con la funcion recorrer_nodos, y creamos un nodo auxiliar para el que queremos borrar, asi no perdemos su referencia, apuntamos en nodo_anterior al que apunta el nodo que vamos a borrar y borramos el nodo. Por ultimo restamos uno a la cantidad de nodos.
Obtener el elemento en posicion verifica que la lista y la posicion sean validas, caso lo sean devuelve el elemento del nodo que la funcion recorrer_nodos devuelve;
Para obtener el ultimo elemento verificamos con que la lista sea valida y devolvemos el elemento que se encuentra en el nodo_fin.
La funcion lista_vacia verifica que la lista no sea nula, que la canditad no sea 0, y que los nodos inicio y fin no apunten a NULL, caso contrario la lista esta vacia.
La funcion lista_elementos devuelve 0 si la lista es nula o si la cantidad es 0 y sino devuelve la cantidad de nodos en la lista
Para apilar utilizo la funcion lista_insertar_en_posicion para la primer posicion.
Para desapilar utilizo la funcion lista_borrar_de_posicion para la primer posicion tambien.
Lista_tope verifica que la lista tenga elementos y casi sea asi muestra el primero
Lista encolar utiliza insertar lista, que esta inserta los elementos al final
Lista desencolar hace lo mismo que la funcion par desapilar, ya que el comportamiento es le mismo
lista_primero funciona igual a lista_tope
lista_destruir borra el primer elemento en la lista para la cantidad de elemento que se encuentre en ella, y por ultimo libera la lista