/* 1.Calcular la complejidad computacional del siguiente algoritmo */
int sum = 0;                   // S1

for (int n = N; n > 0; n /= 2) // S2
  for (int i = 0; i < n; i++)  // S3
    sum++;                     // S4

/*
Respuesta:
O(seq) = MAX(S1, S2)
S1 = O(1)

n   | iteraciones i
N   | N
N/2 | N/2
N/4 | N/4
.   | .
.   | .
.   | .
1   | 1

El la primer pasada del S2, S3 itera N veces
En la segunda pasada del S2, S3 itera N/2 (la mitad)

N+N/2+N/4+N/8+...+1
N(1/2+1/4+1/8+...+1)
N(2) <- tiende a 2
2N
O(N)
*/

/* 2. Encuentre, si es posible, una solución para la siguiente ecuación de recurrencia */

/*
Respuesta:

T(n) = 2 T(n/3) +n, T(1) = 1

A = 2;B = 3; C = 1

log3(2) = 0.631
log3(2) < C

logB(A)<C -> T(n) = O(n^C)

T(n) = O(n^1)
T(1) = O(1^1) = 1 V

*/
