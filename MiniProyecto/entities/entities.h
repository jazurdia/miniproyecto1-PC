#ifndef ENTITIES_H
#define ENTITIES_H
#include "../configs.h"

typedef struct {
    int x, y;      // Posición de la planta en la cuadrícula
    int energy;    // Energía de la planta
    int alive;     // Estado de la planta (1: viva, 0: muerta)
} Plant;

typedef struct {
    int x, y;      // Posición del herbívoro en la cuadrícula
    int energy;    // Energía del herbívoro
    int alive;     // Estado del herbívoro (1: vivo, 0: muerto)
} Herbivore;

typedef struct {
    int x, y;      // Posición del carnívoro en la cuadrícula
    int energy;    // Energía del carnívoro
    int alive;     // Estado del carnívoro (1: vivo, 0: muerto)
} Carnivore;

// Funciones para inicializar las entidades
void initialize_plant(Plant *plant, char grid[MATRIX_SIZE][MATRIX_SIZE], int x, int y);
void plant_behavior(char grid[MATRIX_SIZE][MATRIX_SIZE], int x, int y);

void initialize_herbivore(Herbivore *herbivore, char grid[MATRIX_SIZE][MATRIX_SIZE], int x, int y);
void initialize_carnivore(Carnivore *carnivore, char grid[MATRIX_SIZE][MATRIX_SIZE], int x, int y);

#endif
