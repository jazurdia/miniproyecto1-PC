#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosystem/ecosystem.h"
#include "entities/entities.h"
// Define la cantidad inicial de cada tipo de entidad
#define INITIAL_PLANTS 5
#define INITIAL_HERBIVORES 3
#define INITIAL_CARNIVORES 2

int main() {
    Ecosystem ecosystem;
    initialize_ecosystem(&ecosystem);

    srand(43); // Inicializa la semilla para números aleatorios

    // Inicializa algunas plantas, herbívoros y carnívoros en posiciones aleatorias
    for (int i = 0; i < INITIAL_PLANTS; i++) {
        int x = rand() % MATRIX_SIZE;
        int y = rand() % MATRIX_SIZE;
        initialize_plant(&ecosystem, x, y, 1);
    }
    for (int i = 0; i < INITIAL_HERBIVORES; i++) {
        int x = rand() % MATRIX_SIZE;
        int y = rand() % MATRIX_SIZE;
        initialize_herbivore(&ecosystem, x, y, 1);
    }

    for (int i = 0; i < INITIAL_CARNIVORES; i++) {
        int x = rand() % MATRIX_SIZE;
        int y = rand() % MATRIX_SIZE;
        initialize_carnivore(&ecosystem, x, y, 1);
    }
    print_ecosystem(&ecosystem);
    // Simula la evolución del ecosistema por varios ciclos
    for (int cycle = 0; cycle < CICLOS; cycle++) {
        printf("Ciclo %d:\n", cycle);
        reset_has_moved(&ecosystem);
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                if (ecosystem.grid[i][j].entity != NULL) {
                    if (ecosystem.grid[i][j].label == 'P') {
                        plant_behavior(&ecosystem, i, j);
                    } else if (ecosystem.grid[i][j].label == 'H') {
                        herbivore_behavior(&ecosystem, i, j);
                    } else if (ecosystem.grid[i][j].label == 'C') {
                        carnivore_behavior(&ecosystem, i, j);
                    }
                }
            }
        }
        print_ecosystem(&ecosystem);
    }



    return 0;
}
