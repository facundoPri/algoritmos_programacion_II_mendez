# TP2 Salon de la fama reloaded

## Estructuras

### Salon

Un salon necesita almacenar entrenadores, y se debe poder filtrarlos, manteniendo cierto orden.
Por eso mismo se opto por el uso de un abb para almacenar los entrenadores, ya que nos permite manteniendo un orden ( alfabético en el caso ) y a su vez aprovechar la búsqueda binaria, para encontrar los entrenadores relativamente rápido.
Por mas que los entrenadores no podían estar repetidos no se opto por una tabla hash, ya que este implicaría ordenar todos los entrenadores en orden alfabético, cada vez que se realiza un filtro, y al ser esta la funcion mas costosa de la aplicación, lo que se ganaba con una búsqueda un poco mas rápida, no compensaba.

### Entrenador

Un entrenador esta compuesto por su nombre, sus victorias y sus pokemones. Estos pokemones tiene que estar almacenados de manera que se puedan encontrar rápidamente para obtener sus atributos y para filtrar los entrenadores.
La prioridad del contenedor de los pokemones es la búsqueda, pero a su vez también es importante mantener el orden de agregado, ya que esto puede terminar influyendo en las batallas.
En un principio implemente el contenedor de pokemones como una tabla hash, ya que esta me permite tener la búsqueda mas rápida posible y para crear un orden de llegada implemente un sistema de id autoincrementable, pero llegue al problema de que si un entrenador quería tener un pokemon repetido no se podia. Por lo tanto la opción restante fue utilizar nuevamente un abb.
Este abb preserva la funcion de id autoinclementable ya que me permite utilizar el nombre del pokemon para la búsqueda binaria, y cuando necesito del orden de llegada reordenarlos con ese orden.

## Otras decisiones de implementación

### Uso de hash para los comando y reglas

Para evitar utilizar un fila de ifs y hacer el código mas modular y mantenible, se opto por separar los comandos y reglas en tablas hash estática, las cuales se crean una vez que se inicializa em programa. Haciéndolas estáticas evitamos estar creando un hash nuevo para las reglas y comando todo el tiempo, y el uso de hashes nos permite agregar un comando o regla nueva de manera bastante simple, apenas agregándolos al hash.
Por otro lado esta implementación le termina generando al usuario la necesidad de liberar la memoria de estas dos tablas hash.

### Generación de listas ordenadas

Hay una funcion en el archivo entrenadores llamada entrenador_lista_ordenada_pokemones que recibe un entrenador y un numero, esta funcion le permite tener una lista ordenada por orden de llegada con la cantidad pasada de pokemones.
Como los pokemones están almacenados en un abb y este ordena los pokemones utilizando su nombre, si al usuario le importa el orden de llegada, pasar el abb a lista me devuelve un orden indeseado. Para esto esta el id autoincrementable, se crea una funcion que define quien llego antes y después, si esta funcion se la pasamos a un abb, ya tenemos una forma de ordenar los pokemones con ese orden.
Lo que hace esta funcion es agregarlos a este nuevo abb, que tiene un nuevo parámetro de ordenamiento, y después pasarlo a una lista, obteniendo una lista ordenada por llegada.
Puede ser que obtener directamente la lista y después ordenarla con quicksort o mergesort termine siendo mas rapido, pero siendo que es poco probable que un entrenador tenga miles pokemones, esta implementación es adecuada.

### Uso de hash para obtener atributos de pokemon

Para obtener los atributos del pokemon utilizar un hash es lo mas adecuado, ya que nos permite hacer una búsqueda inmediata y a su vez tener una interfaz intuitiva, ya que apenas se necesita poner el nombre del atributo y se obtiene el valor, parecido al uso de un diccionario en otros lenguajes.
