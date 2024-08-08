#include <stdio.h>
#include "ecosystem.h"
#include "../configs.h"
#include "../entities/entities.h"
#include <windows.h>


void initialize_ecosystem(Ecosystem *ecosystem) {
#pragma omp parallel for collapse(2)
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            ecosystem->grid[i][j].x = i;
            ecosystem->grid[i][j].y = j;
            ecosystem->grid[i][j].entity = NULL; // No hay entidad en la celda
            ecosystem->grid[i][j].label = '.'; // Etiqueta por defecto
        }
    }
}

void enable_virtual_terminal_processing() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

// Definición de colores ANSI
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_ORANGE  "\x1b[33m"  // Naranja puede ser representado con amarillo
#define ANSI_COLOR_RESET   "\x1b[0m"

void print_ecosystem(const Ecosystem *ecosystem) {
    printf("  ");  // Espacio inicial para la etiqueta de columna
    // Imprimir encabezados de columnas
    for (int j = 0; j < MATRIX_SIZE; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < MATRIX_SIZE; i++) {
        printf("%2d ", i);  // Imprimir etiqueta de fila

        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (ecosystem->grid[i][j].entity == NULL) {
                printf(".  ");  // Espacio adicional para alineación
            } else {
                // Intentamos identificar el tipo de entidad basado en el 'label'
                char label = ecosystem->grid[i][j].label;

                switch (label) {
                    case 'P':
                        printf(ANSI_COLOR_GREEN "P  " ANSI_COLOR_RESET);
                        break;
                    case 'H':
                        printf(ANSI_COLOR_BLUE "H  " ANSI_COLOR_RESET);
                        break;
                    case 'C':
                        printf(ANSI_COLOR_ORANGE "C  " ANSI_COLOR_RESET);
                        break;
                    default:
                        printf("?  ");
                        break;
                }
            }
        }
        printf("\n");
    }
}