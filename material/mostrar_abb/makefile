VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2
CC = gcc
CFLAGS =-g -O0 -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror  -I cabeceras

all: clean correr-interactivo

ejemplo: abb.c mostrar_abb.c ejemplo.c
	$(CC) $(CFLAGS) abb.c mostrar_abb.c ejemplo.c -o ejemplo 2>&1

interactivo: abb.c mostrar_abb.c interactivo.c
	$(CC) $(CFLAGS) abb.c mostrar_abb.c interactivo.c -o interactivo 2>&1

correr-ejemplo: ejemplo
	valgrind $(VALGRIND_FLAGS) ./ejemplo 2>&1

correr-interactivo: interactivo
	valgrind $(VALGRIND_FLAGS) ./interactivo 2>&1

clean:
	rm -f ejemplo 2>&1
