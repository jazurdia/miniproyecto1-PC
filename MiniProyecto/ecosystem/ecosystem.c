#include <stdio.h>
#include "ecosystem.h"
#include "../configs.h"



// Inicializa la matriz del ecosistema con un valor predeterminado
void initialize_ecosystem(Ecosystem *ecosystem) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            ecosystem->grid[i][j] = '.';  // Usar '.' para representar una celda vacía
        }
    }
}

// Imprime la matriz del ecosistema con formato mejorado
void print_ecosystem(const Ecosystem *ecosystem) {
    // Imprimir encabezado de columnas
    printf("   ");
    for (int j = 0; j < MATRIX_SIZE; j++) {
        printf(" %2d", j);
    }
    printf("\n");

    // Imprimir línea superior
    printf("   +");
    for (int j = 0; j < MATRIX_SIZE; j++) {
        printf("---");
    }
    printf("+\n");

    // Imprimir cada fila con líneas divisorias
    for (int i = 0; i < MATRIX_SIZE; i++) {
        printf("%2d |", i); // Número de fila
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf(" %c ", ecosystem->grid[i][j]);
        }
        printf("|\n");
    }

    // Imprimir línea inferior
    printf("   +");
    for (int j = 0; j < MATRIX_SIZE; j++) {
        printf("---");
    }
    printf("+\n");
}
