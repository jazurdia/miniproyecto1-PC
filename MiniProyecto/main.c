#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosystem/ecosystem.h"
#include "entities/entities.h"
#include "configs.h"
#include <omp.h>
#include <unistd.h>


/*
* Inicializa las plantas en el grid (Ecosistema), 
usando la función initialize_plant y asignando valores aleatorios a las posiciones x, y.
Esta función es parallelizable, ya que cada planta se inicializa de forma independiente.
* @param ecosystem: Ecosistema
*/
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

/*
* Inicializa los herbívoros en el grid (Ecosistema),
usando la función initialize_herbivore y asignando valores aleatorios a las posiciones x, y.
Esta función es parallelizable, ya que cada herbívoro se inicializa de forma independiente.
* @param ecosystem: Ecosistema
*/
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

/*
* Inicializa los carnívoros en el grid (Ecosistema),
usando la función initialize_carnivore y asignando valores aleatorios a las posiciones x, y.
Esta función es parallelizable, ya que cada carnívoro se inicializa de forma independiente.
* @param ecosystem: Ecosistema
*/
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
    omp_set_num_threads(3);
#pragma omp parallel sections
    {
#pragma omp section
        {
            initialize_Plants(&ecosystem);
        }
#pragma omp section
        {
            initialize_herbivores(&ecosystem);
        }
#pragma omp section
        {
            initialize_carnivores(&ecosystem);
        }
    }

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
        if (cycle % 1000 == 0) {
            printf("Ciclo %d:\n", cycle);
            print_ecosystem(&ecosystem);
        }
    }
    printf("Ciclo %d:\n", CICLOS);
    print_ecosystem(&ecosystem);

    return 0;
}
