#include "entities.h"

// Inicializa una planta en una posición específica
void initialize_plant(Plant *plant, char grid[MATRIX_SIZE][MATRIX_SIZE], int x, int y) {
    plant->x = x;
    plant->y = y;
    plant->energy = 1;  // Energía inicial de la planta
    plant->alive = 1;   // Marca la planta como viva
    grid[x][y] = 'P';   // Usar 'P' para representar una planta en la cuadrícula
}

// Inicializa un herbívoro en una posición específica
void initialize_herbivore(Herbivore *herbivore, char grid[MATRIX_SIZE][MATRIX_SIZE], int x, int y) {
    herbivore->x = x;
    herbivore->y = y;
    herbivore->energy = 10;  // Energía inicial del herbívoro
    herbivore->alive = 1;    // Marca el herbívoro como vivo
    grid[x][y] = 'H';        // Usar 'H' para representar un herbívoro en la cuadrícula
}

// Inicializa un carnívoro en una posición específica
void initialize_carnivore(Carnivore *carnivore, char grid[MATRIX_SIZE][MATRIX_SIZE], int x, int y) {
    carnivore->x = x;
    carnivore->y = y;
    carnivore->energy = 20;  // Energía inicial del carnívoro
    carnivore->alive = 1;    // Marca el carnívoro como vivo
    grid[x][y] = 'C';        // Usar 'C' para representar un carnívoro en la cuadrícula
}
