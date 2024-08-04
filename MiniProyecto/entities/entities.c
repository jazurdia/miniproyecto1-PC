#include "entities.h"
#include <stdlib.h>
#include <stdio.h>

// Setea el HasMovedInThisTurn de todas las entidades en el ecosistema a 0
void reset_has_moved(Ecosystem *ecosystem) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (ecosystem->grid[i][j].entity != NULL) {
                if (ecosystem->grid[i][j].label == 'P') {
                    ((Plant *)ecosystem->grid[i][j].entity)->hasMovedInThisTurn = 0;
                } else if (ecosystem->grid[i][j].label == 'H') {
                    ((Herbivore *)ecosystem->grid[i][j].entity)->hasMovedInThisTurn = 0;
                } else if (ecosystem->grid[i][j].label == 'C') {
                    ((Carnivore *)ecosystem->grid[i][j].entity)->hasMovedInThisTurn = 0;
                }
            }
        }
    }
}

// Inicializa una planta en una posición específica
void initialize_plant(Ecosystem *ecosystem, int x, int y, int hasMovedInThisTurn) {
    Plant *plant = (Plant *)malloc(sizeof(Plant));
    plant->x = x;
    plant->y = y;
    plant->energy = 1;
    plant->alive = 1;
    plant->label = 'P';
    plant->hasMovedInThisTurn = hasMovedInThisTurn;
    ecosystem->grid[x][y].entity = plant; // Guardar la planta en la celda
    ecosystem->grid[x][y].label = 'P'; // Cambiar la etiqueta de la celda
}

// Inicializa un herbívoro en una posición específica
void initialize_herbivore(Ecosystem *ecosystem, int x, int y, int hasMovedInThisTurn) {
    Herbivore *herbivore = (Herbivore *)malloc(sizeof(Herbivore));
    herbivore->x = x;
    herbivore->y = y;
    herbivore->energy = 3;
    herbivore->alive = 1;
    herbivore->age = 0;
    herbivore->label = 'H';
    herbivore->hasMovedInThisTurn = hasMovedInThisTurn;
    ecosystem->grid[x][y].entity = herbivore; // Guardar el herbívoro en la celda
    ecosystem->grid[x][y].label = 'H'; // Cambiar la etiqueta de la celda
}

// Inicializa un carnívoro en una posición específica
void initialize_carnivore(Ecosystem *ecosystem, int x, int y, int hasMovedInThisTurn) {
    Carnivore *carnivore = (Carnivore *)malloc(sizeof(Carnivore));
    carnivore->x = x;
    carnivore->y = y;
    carnivore->energy = 3;
    carnivore->alive = 1;
    carnivore->age = 0;
    carnivore->label = 'C';
    carnivore->hasMovedInThisTurn = hasMovedInThisTurn;
    ecosystem->grid[x][y].entity = carnivore; // Guardar el carnívoro en la celda
    ecosystem->grid[x][y].label = 'C'; // Cambiar la etiqueta de la celda
}

void plant_behavior(Ecosystem *ecosystem, int x, int y) {
    Plant *plant = (Plant *)ecosystem->grid[x][y].entity;
    if (plant == NULL || !plant->alive || plant->hasMovedInThisTurn == 1) return;
    plant->hasMovedInThisTurn = 1;
    float reproduction_chance = PLANTS_EXPAND_PROB;

    // Posiciones relativas para las celdas adyacentes
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int surrounded_by_plants = 1;

    // Intentar reproducir en cada dirección adyacente
    for (int i = 0; i < 4; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];

        if (new_x >= 0 && new_x < MATRIX_SIZE && new_y >= 0 && new_y < MATRIX_SIZE) {
            if (ecosystem->grid[new_x][new_y].entity == NULL) {
                surrounded_by_plants = 0;
                if ((rand() / (float)RAND_MAX) < reproduction_chance) {
                    initialize_plant(ecosystem, new_x, new_y, 1); // Crear nueva planta
                    printf("Planta nueva creada en (%d, %d)\n", new_x, new_y);
                }
            }
        }
    }

    // Si está completamente rodeada por plantas, la planta muere
    if (surrounded_by_plants) {
//        free(plant);
        ecosystem->grid[x][y].entity = NULL; // Eliminar la planta
        ecosystem->grid[x][y].label = '.'; // Cambiar la etiqueta de la celda
        printf("Planta eliminada en (%d, %d) por estar rodeada de otras plantas\n", x, y);
    }
}

void herbivore_behavior(Ecosystem *ecosystem, int x, int y) {
    Herbivore *herbivore = (Herbivore *)ecosystem->grid[x][y].entity;
    if (herbivore == NULL || !herbivore->alive || herbivore->hasMovedInThisTurn == 1) return;
    herbivore->hasMovedInThisTurn = 1;

    herbivore->age++;
    if (herbivore->age >= 10) {
//        free(herbivore);
        ecosystem->grid[x][y].entity = NULL;
        ecosystem->grid[x][y].label = '.';
        printf("Herbivoro muerto en (%d, %d) por vejez\n", x, y);
        return;
    }

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int found_food = 0;

    if (herbivore->energy > 2) {
        for (int i = 0; i < 4; i++) {
            int new_x = x + directions[i][0];
            int new_y = y + directions[i][1];

            if (new_x >= 0 && new_x < MATRIX_SIZE && new_y >= 0 && new_y < MATRIX_SIZE) {
                if (ecosystem->grid[new_x][new_y].entity == NULL) {
                    //Crear un nuevo herbivoro en la misma celda
                    initialize_herbivore(ecosystem, new_x, new_y, 1);
                    herbivore->energy -= 2;
                    printf("Herbivoro creado en (%d, %d)\n", new_x, new_y);
                    break;
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];

        if (new_x >= 0 && new_x < MATRIX_SIZE && new_y >= 0 && new_y < MATRIX_SIZE) {
            if (ecosystem->grid[new_x][new_y].label == 'P') {
                Plant *plant = (Plant *)ecosystem->grid[new_x][new_y].entity;
                if (plant->alive) {
//                    free(plant);
                    ecosystem->grid[new_x][new_y].entity = herbivore;
                    ecosystem->grid[x][y].entity = NULL;
                    ecosystem->grid[x][y].label = '.';
                    herbivore->x = new_x;
                    herbivore->y = new_y;
                    ecosystem->grid[new_x][new_y].label = 'H';
                    if (herbivore->energy > 4){
                        printf("Herbivoro en (%d, %d) comio una planta, pero no obtendra mas energia \n", new_x, new_y);
                    }else{
                        herbivore->energy += 1;
                    }

                    found_food = 1;
                    printf("Herbivoro en (%d, %d) comio una planta\n", new_x, new_y);
                    break;
                }
            }
        }
    }

    if (!found_food) {
        int random_dir = rand() % 4;
        int new_x = x + directions[random_dir][0];
        int new_y = y + directions[random_dir][1];

        if (new_x >= 0 && new_x < MATRIX_SIZE && new_y >= 0 && new_y < MATRIX_SIZE) {
            if (ecosystem->grid[new_x][new_y].entity == NULL) {
                ecosystem->grid[new_x][new_y].entity = herbivore;
                ecosystem->grid[x][y].entity = NULL;
                ecosystem->grid[x][y].label = '.';
                herbivore->x = new_x;
                herbivore->y = new_y;
                ecosystem->grid[new_x][new_y].label = 'H';
                printf("Herbivoro en (%d, %d) se movio a (%d, %d)\n", x, y, new_x, new_y);
            }
        }
        herbivore->energy--;
    }

    if (herbivore->energy <= 0) {
//        free(herbivore);
        ecosystem->grid[x][y].entity = NULL;
        ecosystem->grid[x][y].label = '.';
        printf("Herbivoro muerto en (%d, %d) por falta de energia\n", x, y);
    }
}

void carnivore_behavior(Ecosystem *ecosystem, int x, int y) {
    Carnivore *carnivore = (Carnivore *)ecosystem->grid[x][y].entity;
    if (carnivore == NULL || !carnivore->alive || carnivore->hasMovedInThisTurn == 1) return;
    carnivore->hasMovedInThisTurn = 1;

    carnivore->age++;
    if (carnivore->age >= 15) {
//        free(carnivore);
        ecosystem->grid[x][y].entity = NULL;
        ecosystem->grid[x][y].label = '.';
        printf("Carnivoro muerto en (%d, %d) por vejez\n", x, y);
        return;
    }


    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int found_food = 0;

    if (carnivore->energy >= 2) {
        for (int i = 0; i < 4; i++) {
            int new_x = x + directions[i][0];
            int new_y = y + directions[i][1];

            if (new_x >= 0 && new_x < MATRIX_SIZE && new_y >= 0 && new_y < MATRIX_SIZE) {
                if (ecosystem->grid[new_x][new_y].entity == NULL) {
                    //Crear un nuevo carnivoro en la misma celda
                    initialize_carnivore(ecosystem, new_x, new_y, 1);
                    carnivore->energy -= 2;
                    printf("Carnivoro creado en (%d, %d)\n", new_x, new_y);
                    break;
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];

        if (new_x >= 0 && new_x < MATRIX_SIZE && new_y >= 0 && new_y < MATRIX_SIZE) {
            if (ecosystem->grid[new_x][new_y].label == 'H') {
                Herbivore *herbivore = (Herbivore *)ecosystem->grid[new_x][new_y].entity;
                if (herbivore->alive) {
//                    free(herbivore);
                    ecosystem->grid[new_x][new_y].entity = carnivore;
                    ecosystem->grid[new_x][new_y].entity = carnivore;
                    ecosystem->grid[new_x][new_y].label = 'C';
                    ecosystem->grid[x][y].entity = NULL;
                    ecosystem->grid[x][y].label = '.';
                    carnivore->x = new_x;
                    carnivore->y = new_y;
                    if (carnivore->energy > 4){
                        printf("Carnivoro en (%d, %d) comio una planta, pero no obtendra mas energia \n", new_x, new_y);
                    }else{
                        carnivore->energy += 1;
                    }
                    found_food = 1;
                    printf("Carnivoro en (%d, %d) comio un herbivoro\n", new_x, new_y);
                    break;
                }
            }
        }
    }

    if (!found_food) {
        int random_dir = rand() % 4;
        int new_x = x + directions[random_dir][0];
        int new_y = y + directions[random_dir][1];

        if (new_x >= 0 && new_x < MATRIX_SIZE && new_y >= 0 && new_y < MATRIX_SIZE) {
            if (ecosystem->grid[new_x][new_y].entity == NULL) {
                ecosystem->grid[new_x][new_y].entity = carnivore;
                ecosystem->grid[new_x][new_y].label = 'C';
                ecosystem->grid[x][y].entity = NULL;
                ecosystem->grid[x][y].label = '.';
                carnivore->x = new_x;
                carnivore->y = new_y;
                ecosystem->grid[new_x][new_y].label = 'C';
                printf("Carnivoro en (%d, %d) se movio a (%d, %d)\n", x, y, new_x, new_y);
            }
        }
        carnivore->energy--;
    }



    if (carnivore->energy <= 0) {
        ecosystem->grid[x][y].entity = NULL;
        ecosystem->grid[x][y].label = '.';
        printf("Carnivoro muerto en (%d, %d) por falta de energia\n", x, y);
    }
}
