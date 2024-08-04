#include <stdio.h>
#include "ecosystem.h"
#include "../configs.h"
#include "../entities/entities.h"

void initialize_ecosystem(Ecosystem *ecosystem) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            ecosystem->grid[i][j].x = i;
            ecosystem->grid[i][j].y = j;
            ecosystem->grid[i][j].entity = NULL; // No hay entidad en la celda
        }
    }
}

void print_ecosystem(const Ecosystem *ecosystem) {
    printf("  ");  // Espacio inicial para la etiqueta de columna
    // Imprimir encabezados de columnas
    for (int j = 0; j < MATRIX_SIZE; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < MATRIX_SIZE; i++) {
        printf("%2d ", i);  // Imprimir etiqueta de fila

        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (ecosystem->grid[i][j].entity == NULL) {
                printf(".  ");  // Espacio adicional para alineación
            } else {
                // Intentamos identificar el tipo de entidad basado en el 'label'
                char label = ecosystem->grid[i][j].label;

                switch (label) {
                    case 'P':
                        printf("P  ");
                        break;
                    case 'H':
                        printf("H  ");
                        break;
                    case 'C':
                        printf("C  ");
                        break;
                    default:
                        printf("?  ");
                        break;
                }
            }
        }
        printf("\n");
    }
}