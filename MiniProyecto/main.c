#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosystem/ecosystem.h"
#include "entities/entities.h"
#include "configs.h"
#include <omp.h>
#include <unistd.h>

void initialize_Plants(Ecosystem *ecosystem) {
#pragma omp parallel for
    for (int i = 0; i < INITIAL_PLANTS; i++) {
        int x, y;
        int found = 0;
        while (!found) {
            x = rand() % MATRIX_SIZE;
            y = rand() % MATRIX_SIZE;
#pragma omp critical
            {
                if (ecosystem->grid[x][y].entity == NULL) {
                    initialize_plant(ecosystem, x, y, 1);
                    found = 1;
                }
            }
        }
    }
}

void initialize_herbivores(Ecosystem *ecosystem) {
#pragma omp parallel for
    for (int i = 0; i < INITIAL_HERBIVORES; i++) {
        int x, y;
        int found = 0;
        while (!found) {
            x = rand() % MATRIX_SIZE;
            y = rand() % MATRIX_SIZE;
#pragma omp critical
            {
                if (ecosystem->grid[x][y].entity == NULL) {
                    initialize_herbivore(ecosystem, x, y, 1);
                    found = 1;
                }
            }
        }
    }
}

void initialize_carnivores(Ecosystem *ecosystem) {
#pragma omp parallel for
    for (int i = 0; i < INITIAL_CARNIVORES; i++) {
        int x, y;
        int found = 0;
        while (!found) {
            x = rand() % MATRIX_SIZE;
            y = rand() % MATRIX_SIZE;
#pragma omp critical
            {
                if (ecosystem->grid[x][y].entity == NULL) {
                    initialize_carnivore(ecosystem, x, y, 1);
                    found = 1;
                }
            }
        }
    }
}


int main() {
    Ecosystem ecosystem;
    initialize_ecosystem(&ecosystem);

    srand(70); // Inicializa la semilla para números aleatorios

    // Inicializa algunas plantas, herbívoros y carnívoros en posiciones aleatorias

    initialize_Plants(&ecosystem);
    initialize_herbivores(&ecosystem);
    initialize_carnivores(&ecosystem);


    print_ecosystem(&ecosystem);
    // Simula la evolución del ecosistema por varios ciclos
    for (int cycle = 0; cycle < CICLOS; cycle++) {
//        sleep(1);

        reset_has_moved(&ecosystem);
#pragma omp parallel for collapse(2)
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
        if (cycle % 100 == 0) {
            printf("Ciclo %d:\n", cycle);
            print_ecosystem(&ecosystem);
        }
    }
    print_ecosystem(&ecosystem);



    return 0;
}
