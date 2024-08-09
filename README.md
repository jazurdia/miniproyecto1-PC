# Simulación de Ecosistema
*Miniproyecto de Computación Paralela*

---

Este proyecto implementa una simulación básica de un ecosistema en C. La simulación modela un ecosistema en una cuadrícula donde coexisten plantas, herbívoros y carnívoros. Las entidades pueden moverse, reproducirse y competir por recursos a lo largo de múltiples ciclos de simulación.

<br>

El proyecto fue desarrollado como parte del curso de Computación Paralela en la Universidad del Valle de Guatemala en Agosto de 2024

## Integrantes
* Javier Alejandro Azurdia Arrecis    | 21242 <br>
* Angel Sebastian Castellanos Pineda  | 21700 <br>
* Diego Alejandro Morales Escobar     | 21146 <br>

## Estructura del Proyecto

- **main.c**: Punto de entrada del programa. Aquí se inicializan las entidades y se controla el ciclo de simulación.
- **ecosystem.c / ecosystem.h**: Define la estructura del ecosistema y funciones para inicializar y mostrar el estado del ecosistema.
- **entities.c / entities.h**: Contiene la implementación de las plantas, herbívoros y carnívoros, así como su comportamiento.
- **configs.h**: Archivo de configuración que define los parámetros de la simulación como el tamaño de la matriz, probabilidades de expansión, número de ciclos, entre otros.
- **CMakeLists.txt**: Archivo para la configuración de la compilación del proyecto con CMake.

## Funcionalidades

1. **Inicialización del Ecosistema**: Se crea una cuadrícula de tamaño `MATRIX_SIZE` x `MATRIX_SIZE` donde se posicionan aleatoriamente plantas, herbívoros y carnívoros.
2. **Ciclo de Simulación**: En cada ciclo, las entidades pueden moverse, reproducirse o morir. El ciclo se repite hasta completar un número definido de ciclos (`CICLOS`).
3. **Salida Visual**: El estado del ecosistema se imprime en la consola, mostrando las posiciones de las entidades.

## Compilación

Para compilar este proyecto, es necesario tener instalado CMake. Una vez que tengas CMake configurado, puedes compilar el proyecto utilizando los siguientes comandos en la terminal:

```sh
mkdir build
cd build
cmake ..
make
```

## Ejecución

Después de compilar, puedes ejecutar la simulación con el siguiente comando:

```sh
./MiniProyecto
```

## Configuración

Los parámetros de la simulación, como el tamaño de la matriz o el número inicial de entidades, se pueden ajustar en el archivo `configs.h`:

```c
#define MATRIX_SIZE 60
#define INITIAL_PLANTS 30
#define INITIAL_HERBIVORES 25
#define INITIAL_CARNIVORES 15
```

## Créditos

Este proyecto fue desarrollado como parte de un laboratorio universitario para la clase de **Análisis y Diseño de Algoritmos**. La implementación aprovecha OpenMP para paralelizar ciertas operaciones, mejorando la eficiencia de la simulación.

oporciona una visión general del proyecto, incluyendo la estructura del código, funcionalidades clave, y las instrucciones para compilar y ejecutar la simulación.