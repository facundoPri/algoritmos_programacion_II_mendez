# TP1 Salón de Fama

## Solucion implementada
API que permite agreagar entrenadores pokemon, junto con su equipo, al salón de fama y luego filtrarlos por su cantidad de victorias.

## Aclaraciones
Todavia hay una cierta cantidad de memoria que necesita ser liberada, pero no llegue a hacer todavia, y si es posible una reentrega estara hecho

## Temas teoricos
### Heap y stack: Para qué y Como se utiliza cada uno?
El stack es una parte de la memoria que cada sistema operativo, reserva para almacenar ciertas variables y fucniones. En C esta se utiliza cada vez que creamos una variable, o llamamos una funcion.
El heap es una parte de la memoria, mucho mas grande, que nos permite trabajar de forma dinamica. Para manejarla se requiere el uso de funciones epeciales, como malloc,realloc,calloc,free, etc.

### Malloc/Realloc/Free: Como y para qué se utilizan?
Malloc se utiliza para reserva una porcion de memoria en el heap, esta devuelve un void pointer, con la direccion inicial de esta memoria reservada y para esto tiene que resicibir el tamaño de la memoria que nos interesa.
Realloc es muy parecida a malloc pero nos permite modificar un pedazo de memoria reservado si este exite.
Free se utiliza para liberar memoria reservada, esta recibe un puntero que referencie la memoria que queremos liberar y la libera, desreferenciandola del heap