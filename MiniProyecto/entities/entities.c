#include "entities.h"

// Inicializa una planta en una posición específica
void initialize_plant(Plant *plant, char grid[MATRIX_SIZE][MATRIX_SIZE], int x, int y) {
    plant->x = x;
    plant->y = y;
    plant->energy = 1;  // Energía inicial de la planta
    plant->alive = 1;   // Marca la planta como viva
    grid[x][y] = 'P';   // Usar 'P' para representar una planta en la cuadrícula
}

// Comportamiento de reproducción y muerte de la planta
void plant_behavior(char grid[MATRIX_SIZE][MATRIX_SIZE], int x, int y) {
    float reproduction_chance = PLANTS_EXPAND_PROB;

    // Posiciones relativas para las celdas adyacentes
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int surrounded_by_plants = 1;  // Asumimos que está rodeada por plantas hasta verificar

    // Intentar reproducir en cada dirección adyacente
    for (int i = 0; i < 4; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];

        // Verificar si la posición es válida
        if (new_x >= 0 && new_x < MATRIX_SIZE && new_y >= 0 && new_y < MATRIX_SIZE) {
            // Si hay una celda vacía o un no-planta, no está completamente rodeada por plantas
            if (grid[new_x][new_y] == '.') {
                surrounded_by_plants = 0;  // No está rodeada solo por plantas
                // Intentar reproducir si hay espacio vacío
                if ((rand() / (float)RAND_MAX) < reproduction_chance) {
                    grid[new_x][new_y] = 'P'; // Colocar una nueva planta
                    printf("Planta nueva creada en (%d, %d)\n", new_x, new_y);
                }
            } else if (grid[new_x][new_y] != 'P') {
                surrounded_by_plants = 0; // No está rodeada solo por plantas
            }
        }
    }

    // Si está completamente rodeada por plantas, la planta muere
    if (surrounded_by_plants) {
        grid[x][y] = '.';  // Eliminar la planta
        printf("Planta eliminada en (%d, %d) por estar rodeada de leguchas\n", x, y);
    }
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
