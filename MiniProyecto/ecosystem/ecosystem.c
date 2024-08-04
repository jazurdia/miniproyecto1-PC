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
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (ecosystem->grid[i][j].entity == NULL) {
                printf(".");
            } else {
                // Determina el tipo de entidad y la imprime
                if (((Plant *)ecosystem->grid[i][j].entity)->alive) {
                    printf("P");
                } else if (((Herbivore *)ecosystem->grid[i][j].entity)->alive) {
                    printf("H");
                } else if (((Carnivore *)ecosystem->grid[i][j].entity)->alive) {
                    printf("C");
                }
            }
        }
        printf("\n");
    }
}