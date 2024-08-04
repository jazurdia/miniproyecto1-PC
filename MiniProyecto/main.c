#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ecosystem/ecosystem.h"
#include "ecosystem/ecosystem.c"
#include "entities/entities.c"
#include "entities/entities.h"
#include "configs.h"

int main() {
    // Inicializar el generador de números aleatorios
    srand(time(NULL));

    // Crear e inicializar la matriz del ecosistema
    Ecosystem ecosystem;
    initialize_ecosystem(&ecosystem);

    // Generar una cantidad aleatoria de plantas, herbívoros y carnívoros
    int num_plants = rand() % MAX_PLANTS + 1;
    int num_herbivores = rand() % MAX_HERBIVORES + 1;
    int num_carnivores = rand() % MAX_CARNIVORES + 1;

    printf("P: %d\n", num_plants);
    printf("H: %d\n", num_herbivores);
    printf("C: %d\n", num_carnivores);

    // Inicializar y colocar las plantas aleatoriamente en la cuadrícula
    for (int i = 0; i < num_plants; i++) {
        int x = rand() % MATRIX_SIZE;
        int y = rand() % MATRIX_SIZE;
        Plant plant;
        initialize_plant(&plant, ecosystem.grid, x, y);
    }

    // Inicializar y colocar los herbívoros aleatoriamente en la cuadrícula
    for (int i = 0; i < num_herbivores; i++) {
        int x = rand() % MATRIX_SIZE;
        int y = rand() % MATRIX_SIZE;
        Herbivore herbivore;
        initialize_herbivore(&herbivore, ecosystem.grid, x, y);
    }

    // Inicializar y colocar los carnívoros aleatoriamente en la cuadrícula
    for (int i = 0; i < num_carnivores; i++) {
        int x = rand() % MATRIX_SIZE;
        int y = rand() % MATRIX_SIZE;
        Carnivore carnivore;
        initialize_carnivore(&carnivore, ecosystem.grid, x, y);
    }

    // Imprimir la matriz del ecosistema
    print_ecosystem(&ecosystem);

    return 0;
}
