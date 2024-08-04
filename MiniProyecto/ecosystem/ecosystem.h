#ifndef ECOSYSTEM_H
#define ECOSYSTEM_H
#include "../configs.h"

typedef struct {
    int x, y;
    void *entity; // Puntero genérico a una entidad
} Cell;

typedef struct {
    Cell grid[MATRIX_SIZE][MATRIX_SIZE];
} Ecosystem;

void initialize_ecosystem(Ecosystem *ecosystem);
void print_ecosystem(const Ecosystem *ecosystem);

#endif
