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
    herbivore->energy = 3;  // Energía inicial del herbívoro
    herbivore->alive = 1;    // Marca el herbívoro como vivo
    herbivore->age = 0;    // Marca el herbívoro como joven
    grid[x][y] = 'H';        // Usar 'H' para representar un herbívoro en la cuadrícula
}

// Comportamiento de los herbívoros
void herbivore_behavior(char grid[MATRIX_SIZE][MATRIX_SIZE], int x, int y, Herbivore *herbivore) {
    herbivore->age++; // Incrementar la edad del herbívoro
    // Edad del herbívoro. Si es mayor a 10, se considera anciano y muere
    if (herbivore->age >= 10) {
        grid[x][y] = '.';
        printf("Herbívoro muerto en (%d, %d) por vejez\n", x, y);
        return;
    }

    // Direcciones de movimiento: arriba, abajo, izquierda, derecha
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int found_food = 0;

    for (int i = 0; i < 4; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];

        // Verificar límites y buscar comida
        if (new_x >= 0 && new_x < MATRIX_SIZE && new_y >= 0 && new_y < MATRIX_SIZE) {
            if (grid[new_x][new_y] == 'P') { // Comida encontrada
                grid[new_x][new_y] = 'H'; // Mover herbívoro a la nueva celda
                grid[x][y] = '.'; // Vaciar celda anterior
                if (herbivore->energy > 4){
                    printf("El herviboro en la celda (%d, %d) ya no puede sumar energia \n", new_x, new_y);
                } else {
                    herbivore->energy++;
                }
                found_food = 1;
                break;

            }
        }
    }

    // Si no se encontró comida, moverse a una celda vacía aleatoria adyacente
    if (!found_food) {
        int random_dir = rand() % 4;
        int new_x = x + directions[random_dir][0];
        int new_y = y + directions[random_dir][1];

        if (new_x >= 0 && new_x < MATRIX_SIZE && new_y >= 0 && new_y < MATRIX_SIZE) {
            if (grid[new_x][new_y] == '.') {
                grid[new_x][new_y] = 'H';
                grid[x][y] = '.';
            }
        }

        herbivore->energy--; // Perder energía al moverse
    }

    // Verificar si el herbívoro debe reproducirse
    if (herbivore->energy >= 3) { // Condición de reproducción
        for (int i = 0; i < 4; i++) {
            int new_x = x + directions[i][0];
            int new_y = y + directions[i][1];

            if (new_x >= 0 && new_x < MATRIX_SIZE && new_y >= 0 && new_y < MATRIX_SIZE) {
                if (grid[new_x][new_y] == '.') {
                    grid[new_x][new_y] = 'H'; // Crear nuevo herbívoro
                    printf("Herbívoro nuevo creado en (%d, %d)\n", new_x, new_y);
                    herbivore->energy -= 2; // Costo de energía al reproducirse
                    break;
                }
            }
        }
    }

    // Verificar si el herbívoro muere
    if (herbivore->energy <= 0) {
        grid[x][y] = '.';
        printf("Herbívoro muerto en (%d, %d)\n", x, y);
    }
}

// Inicializa un carnívoro en una posición específica
void initialize_carnivore(Carnivore *carnivore, char grid[MATRIX_SIZE][MATRIX_SIZE], int x, int y) {
    carnivore->x = x;
    carnivore->y = y;
    carnivore->energy = 20;  // Energía inicial del carnívoro
    carnivore->alive = 1;    // Marca el carnívoro como vivo
    carnivore->age = 0;    // Marca el carnívoro como joven
    grid[x][y] = 'C';        // Usar 'C' para representar un carnívoro en la cuadrícula
}

// Comportamiento de los carnívoros
void carnivore_behavior(char grid[MATRIX_SIZE][MATRIX_SIZE], int x, int y, Carnivore *carnivore) {
    carnivore->age++; // Incrementar la edad del herbívoro
    // Edad del carnívoro. Si es mayor a 15, se considera anciano y muere
    if (carnivore->age >= 15) {
        grid[x][y] = '.';
        printf("Carnivoro muerto en (%d, %d) por vejez\n", x, y);
        return;
    }

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int found_food = 0;

    for (int i = 0; i < 4; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];

        if (new_x >= 0 && new_x < MATRIX_SIZE && new_y >= 0 && new_y < MATRIX_SIZE) {
            if (grid[new_x][new_y] == 'H') { // Comida encontrada
                grid[new_x][new_y] = 'C'; // Mover carnívoro a la nueva celda
                grid[x][y] = '.'; // Vaciar celda anterior

                if (carnivore->energy > 4){
                    printf("El Carnivoro en la celda (%d, %d) ya no puede sumar energia \n", new_x, new_y);
                }else {
                    carnivore->energy++; // Ganar energía

                }
                found_food = 1;
                break;
            }
        }
    }

    if (!found_food) {
        int random_dir = rand() % 4;
        int new_x = x + directions[random_dir][0];
        int new_y = y + directions[random_dir][1];

        if (new_x >= 0 && new_x < MATRIX_SIZE && new_y >= 0 && new_y < MATRIX_SIZE) {
            if (grid[new_x][new_y] == '.') {
                grid[new_x][new_y] = 'C';
                grid[x][y] = '.';
            }
        }

        carnivore->energy--; // Perder energía al moverse
    }

    // Reproducción
    if (carnivore->energy >= 5) { // Condición de reproducción
        for (int i = 0; i < 4; i++) {
            int new_x = x + directions[i][0];
            int new_y = y + directions[i][1];

            if (new_x >= 0 && new_x < MATRIX_SIZE && new_y >= 0 && new_y < MATRIX_SIZE) {
                if (grid[new_x][new_y] == '.') {
                    grid[new_x][new_y] = 'C'; // Crear nuevo carnívoro
                    printf("Carnívoro nuevo creado en (%d, %d)\n", new_x, new_y);
                    carnivore->energy -= 3; // Costo de energía al reproducirse
                    break;
                }
            }
        }
    }

    // Muerte
    if (carnivore->energy <= 0) {
        grid[x][y] = '.';
        printf("Carnívoro muerto en (%d, %d)\n", x, y);
    }
}