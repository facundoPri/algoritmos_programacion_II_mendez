## Teorema maestro
- El teorema maestro nos ayuda a resolver un ecuacion de recurrencia
- Teorema se aplica para algoritmos de divicion y conquista
    - Si tenemos un algoritmo cuya ecuacion de recurrencia es:
        T(n) = A * T(n/B) + f(n^C)
        A -> Cantidad de llamados recursivos
        B -> proporcion del tamaño original con el que llamamos recusivamente
        f(n^C) -> el costo de partir y juntar (todo lo que no son llamados recursivos)

    Se compara la parte recursiva con la no recursiva y le tiempo de ejecucion es la mayor

    => logB(A) vs C
    logB(A)<C -> T(n) = O(n^C)
    logB(A)=C -> O(n^C*logB(A)) = O(n^C*log(n))
    logB(A)>C -> O(n^logB(A))

- Ejemplo Mergesort:
    T(n) = 2T(n/2) + f(n)
    A = 2; B = 2; C = 1:

    log2(2) = 1 = C
    => O(n^C*logn) = O(n*log*n)

- Ejemplo Busqueda Binaria:
    T(n) = T(n/2) + f(1)
    A = 1;B = 2; C = 0;
    C = 0 -> Ya que no hay ninguna llamada no recursiva
    => f(n) == 1

    log2(1) = 0 = C
    => O(n^c logn) = O(logn)

## Ecuacion de recurrencia Divide y conquista
T(n) = A * T(n/B) + f(n^C)
A -> Cantidad de llamadas recursivas del algoritmo
B -> Cantidad de elementos en el que se reduce el segmenteo de datos por llamada
f(n^C) -> el costo de partir y juntar (todo lo que no son llamados recursivos)

## Ejemplo peor caso quicksort
A = 2
B = 2
C = 2 -> f(n^2)
=> log2(2) = 1 < C
=> O(n^C) == O(n^2)

## Calcular complejidad del siguiente codigo en C:
- Separer por sequiecias de aciones
- O(seq) = max(S1,S2,..., Sn-2, Sn-1, Sn)
Ejemplo 1:

S1 int producto = 1;
S2 for (int i = 0; i<=n ; i++)
    printf("%i", i);
S3 for (int j = i; j<=n;j++)
S4  for (int k= 243; k >=1; k/= 3)
     producto = (k *j)

-> Como S4 esta adentro de S3 entonces S3 me dara el tiempo
O(seq) = max(T(S1), T(S2), T(S3))

T(S1) = O(1)
T(S2) = O(n)

T(S3):
  T(S3) * T(S4)
  -> T(S4) ==> Habria que dividir -> Cuando hacemos diviciones tiende a log n
  -> T(S3) = n
  => n * log n

## QuickSort
### Pero caso
Es cuando tenemos un vector ordenado y utilizamos uno de los extremos como pivote
Ejemplo:
v = {2,4,6,8,10,12,14,16} pivote es el ultimo
    2,3,6,8,10,12,14 |16|
    2,3,6,8,10,12 |14| 16
    2,3,6,8,10 |12| 14,16
    2,3,6,8 |10| 12,14,16
    2,3,6 |8| 10,12,14,16
    2,3 |6| 8,10,12,14,16
    2 |3| 6,8,10,12,14,16
    |2| 3,6,8,10,12,14,16

    2,3,6,8,10,12,14,16

Recorrimos item por item que es lo mismo a n^2


