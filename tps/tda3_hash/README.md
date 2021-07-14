# TDA Hash

---

## Teoría

### Que es una tabla hash?

Es una estructura de datos que permite asociar claves con valores.
Gracias a esta asociación y a una función (función hash) podemos saber donde se encuentra un valor almacenado en memoria, lo que nos posibilita hacer en promedio búsquedas en tiempo constante O(1).

### Tipos de tablas

Existen las tablas hash abiertas (de direccionamiento cerrado) y las tablas hash cerradas (de direccionamiento abierto) y estas de diferencian en la forma de manejar las colisiones.

#### Tablas hash abiertas (direccionamiento cerrado)

Las tablas hash abiertas utilizan listas internas para almacenar valores que colisionaron.
Después de pasar la clave por la función de hash puede pasar que la posición obtenida ya contienen un valor. En estos casos para las tablas hash abiertas se encadenan los valores, de modo que el valor encontrado en dicha posición ahora estará encadenado con el nuevo valor y asi sera para cada valor que caiga en alguna posición donde ya existe un valor, se encadena con el ultimo valor encadenado.
Este comportamiento afecta la implementación de primitivas como insertar, obtener, quitar y destruir, ya que una vez que se encuentra la posición del valor, gracias a la función hash, hay que verificar si es necesario recorrer una lista enlazada o no;

#### Tablas hash cerradas (direccionamiento abierto)

Las tablas hash cerradas a diferencia de las tablas hash abiertas no utilizan ninguna estructura externa (como las listas) para almacenas sus valores.
Estas, en caso de colisión buscan una posición alternativa para almacenar el valor deseado. Ejemplos de métodos para buscar esta posición alternativa son:

- Probing lineal
- Probing cuadrático
- Hash doble

En el caso de probing lineal, que es el método utilizado en esta implementación, consiste en una vez que se obtiene la posición dada por la función hash y colisionar hacer (posición+1)%capacidad. Osea buscar la siguiente posición y verifica que este adentro de la capacidad de nuestra tabla hash, esto se tiene que hacer hasta encontrar una posición libre para ingresar el valor.

---

## Implementación

### Estructuras utilizadas

Se utilizaron dos estructuras para la implementación una para el hash, que contiene la capacidad de este, la cantidad de valores guardados, el destructor de valores y la tabla que es un puntero doble de tipo par (la otra estructura).
La estructura par permite almacenar la clave y el elemento juntos.

### Funciones auxiliares

#### funcion_hash

Recibe una string y devuelve la suma de cada uno de los caracteres.
Esta funcion es utilizada siempre que queremos saber el lugar de un valor según su clave;

#### duplicar_string

Recibe una string y devuelve una copia de ese string.
Se utilizo especialmente en el momento de almacenar alguna clave.
Duplicando la clave nos certificamos que no haya una forma externa de modificar una clave ya almacenada en el hash

#### crear_par

Recibe una clave string y un elemento para crear un puntero de tipo par_t y devolverlo.
En esta funcion es donde se utiliza duplicar_string para almacenar las claves

#### reinsertar_elementos

Recibe un hash, una lista de pares y el tamano de esa lista,
Inserta los elementos de la lista en el hash y devuelve 0 en exito o -1 en error.
Esta funcion fue utilizada para reinsertar los valores de la tabla hash una despues de aumentar su capacidad.

#### destruir_par

Recibe la funcion destructora de elementos, si existe, y el par a ser eliminado Aplica la funcion destructora en el elemento y libera la memoria usada.

### destruir_tabla

Recibe la tabla que se busca liberar de la memoria, el tamaño de esta, la cantidad de elementos que contiene y la funcion destructora.
Libera la memoria llamando destruir_par, para cada par y libera la tabla.

#### rehasear

Recibe una tabla hash, duplica el tamaño y reinserta los elementos que antes estaban en la tabla, en caso de error el hash vuelve a su estado anterior devuelve -1 en caso de error y 0 en caso de exito.
Esta funcion hace una copia de las componentes de hash, crea una nueva tabla con el doble de capacidad y reinicia la cantidad de elementos en el hash, ya que en el momento se encuentra con 0.
Utilizando la copia de la tabla antigua y la funcion reinsertar_elementos volvemos a insertar cada uno de los valores en sus nuevas posiciones. Si esta operacion llega a dar un error se utiliza la copia del hash par volver a su estado anterior y se libera la memoria de la nueva tabla.
Si todo salio bien se libera de la memoria la tabla antigua.

#### buscar_par_desde_posicion

Recibe un hash, una clave, y la posicion desde donde se empieza a buscar.
Devuelve el par encontrado con misma clave o NULL en caso que encuentre
un lugar vacio en la tabla del hash.
Forma directa de obtener un par este estando corrido por una colicion o no

#### buscar_posicion_siguiente_par

Recibe un hash, una clave, y la posicion desde donde se empieza a buscar.
Devuelve la posicion donde se encuentra el par con misma clave o la posicion donde se encontro un espacio libre en la memoria.
Caso error devuelve 0.
Muy parecida a la funcion de arriba pero devuelve la posicion del par, permitiendonos saber la posicion donde se encuantra un par o donde hay un espacio vacio para insertar uno nuevo.

#### reordenar_elementos_siguientes

Recibe un hash y la posicion donde se borro un elemento.
Busca elementos en la tabla que se encuentren fuera de orden, para rellenar la posicion vacia. Hace esto con todos los elementos fuera de orden hasta encontrarse con otro espacio vacio en la tabla del hash

#### funcion_hash_posicion

Recibe un hash y una clave, devuelve la posicion de la clave en la tabla hash.
Esta funcion llama la funcion hash y le aplica el modulo de la capacidad del hash

### Crear hash

Recibe la funcion destruir, para permitirle al usuario liberar la memoria de los elementos almacenados, y la capacidad inicial.
Si la capacidad inicial pasada es menor a 3 entonces el hash sera creado con una capacidad inicial igual a 3.
Esta funcion reserva la memoria necesaria para el hash, guarda la capacidad y el destructor pasados, reserva la memoria necesaria para una tabla del tamaño de la capacidad inicial de hash y por ultimo devuelve un puntero al hash creado.

### Insertar en hash

Recibe el hash y la clave y elemento del par a insertar. Devuelve 0 en caso de exito y -1 si ocurre algun error.
Primero verifica que no haya que rehashear, verificando que el factor carga de la tabla al insertar un nuevo par no se sea mayor que 0.75. Si hay que rehashear se llama la funcion rehashear pasando el hash.
Haciendole el modulo de la capacidad del hash al valor que devuelva la funcion hash podemos obtener la posicion que deberia tener el elemento.
Si esta posicion esta vacia se crea el par y se inserta en la tabla.
Caso contrario buscamos la posicion en que se encuentra actualmente el, si la clave ya esta en la tabla, o la siguiente posicion disponible para almacenarla, utilizando la funcion buscar_posicion_siguiente_par. 
Si la clave ya fue almacenada en la tabla hash hay que cambiarle el valor almacenado, para hacer esto removemos el par clave valor e insertamos un par con misma clave y valor pasado. Esto se hace para poder liberar la memoria reservada cuando duplicamos la clave.
Si la clave no esta presente en la tabla creamos un par clave valor y lo insertamos en posicion.

### Quitar de hash

Recibe el hash y la clave y devuelve 0 en caso de exito y -1 si ocurre algun error.
Se busca la posicion donde deberia estar la clave con la funcion hash, esta posicion es pasada a la funcion buscar_posicion_siguiente_par para verificar que este ahi y sino seguir buscando.
Si no se encuentra ningun par en esa posicion se devueleve error.
Caso contrario liberamos la memoria usada por el par con la funcion destruir_par.
Por ultimo el valor de la pocicion a 0 y restamos la cantidad de elementos en la tabla

### Obtener en hash

Recibe el hash y la clave y devuelve el elemento en caso de encontrarlo o NULL si no lo encuentra.
Para esto utiliza la funcion buscar_par_desde_posicion que nos devuelve el par encontrado o NULL en caso de no encontralo.
Si se encuentra un par devolvemos el elemento que contiene, sino, devolvemos NULL.

### Cantidad en hash

Recibe un hash y devuelve el valor que se encuentra en hash->cantidad.

### Contenido en hash

Recibe un hash y una clave y devuelve un booleano diciendo si la clave esta o no en el hash.
Utiliza la primitiva obtener y pasa su resultado a bool

### Destruir hash

Recibe un hash y libera la memoria utilizada.
Utiliza la funcion destruir_tabla y libera la memoria utilizada por el hash.

### Iterador

Recibe un hash, una funcion y un valor auxiliar y devuelve la cantidad de elemento que pudo iterar.
Itera la tabla hash y para cada clave encontrada ejecuta la funcion pasada, si la funcion devuelve true entonces se deja de iterar.
