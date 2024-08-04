#ifndef ENTITIES_H
#define ENTITIES_H
#include "../configs.h"
#include "../ecosystem/ecosystem.h" // Incluir el archivo de encabezado del ecosistema para definir el tipo Ecosystem
#include <stdbool.h>

// Estructura para representar una planta
typedef struct {
    int x, y;      // Posición de la planta en la cuadrícula
    int energy;    // Energía de la planta
    int alive;     // Estado de la planta (1: viva, 0: muerta)
    char label;    // Etiqueta de la planta
    bool hasMovedInThisTurn; // Indica si la planta se ha movido en el turno actual
} Plant;

// Estructura para representar un herbívoro
typedef struct {
    int x, y;      // Posición del herbívoro en la cuadrícula
    int energy;    // Energía del herbívoro
    int alive;     // Estado del herbívoro (1: vivo, 0: muerto)
    int age;       // Edad del herbívoro
    char label;    // Etiqueta del herbívoro
    bool hasMovedInThisTurn; // Indica si la hervivoro se ha movido en el turno actual

} Herbivore;

// Estructura para representar un carnívoro
typedef struct {
    int x, y;      // Posición del carnívoro en la cuadrícula
    int energy;    // Energía del carnívoro
    int alive;     // Estado del carnívoro (1: vivo, 0: muerto)
    int age;       // Edad del carnívoro
    char label;    // Etiqueta del carnívoro
    bool hasMovedInThisTurn; // Indica si la canivoro se ha movido en el turno actual

} Carnivore;

// Funciones para inicializar las entidades
void initialize_plant(Ecosystem *ecosystem, int x, int y, bool hasMovedInThisTurn);
void initialize_herbivore(Ecosystem *ecosystem, int x, int y, bool hasMovedInThisTurn);
void initialize_carnivore(Ecosystem *ecosystem, int x, int y, bool hasMovedInThisTurn);

// Funciones de comportamiento de las entidades
void plant_behavior(Ecosystem *ecosystem, int x, int y);
void herbivore_behavior(Ecosystem *ecosystem, int x, int y);
void carnivore_behavior(Ecosystem *ecosystem, int x, int y);

#endif
