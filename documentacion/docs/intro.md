---
sidebar_position: 1
---

# Sobre el proyecto

*Miniproyecto de Computación Paralela*


Este proyecto implementa una simulación básica de un ecosistema en C. La simulación modela un ecosistema en una cuadrícula donde coexisten plantas, herbívoros y carnívoros. Las plantas pueden nacer, reproducirse y morir. Los herbívoros y carnívoros pueden hacer lo mismo, además de comer y moverse. Los herbívoros comen plantas y los carnívoros comen herbívoros. Los herbívoros y carnívoros pueden morir de hambre si no comen lo suficiente.

El proyecto fue desarrollado como parte del curso de Computación Paralela en la Universidad del Valle de Guatemala en Agosto de 2024

## Ejecución del proyecto

Para poder ejecutar este proyecto primero se debe obtener el código fuente localizado en el [repositorio](https://github.com/jazurdia/miniproyecto1-PC.git)

Una vez hecho esto se recomienda el uso del [IDE CLion](https://www.jetbrains.com/es-es/clion/download/#section=windows) para la ejecución del mismo, en donde se debe abrir el proyecto llamadado `miniproyecto1-PC` y ejecutar el archivo llamado `CMakeLists.txt`.
Una vez hecho esto es posible ejecutar el archivo principal llamado `main.c`, el cual iniciará la ejecución de la simulación.

:::tip

Para una correcta visualización del output del proyecto se recomienda activar la simulación de la terminal dentro del IDE, se puede guiar de esto [Enable terminal emulation in output console](https://www.jetbrains.com/help/clion/terminal-in-the-output-console.html#enable)

:::

## Integrantes

* Javier Alejandro Azurdia Arrecis    | 21242
* Angel Sebastian Castellanos Pineda  | 21700
* Diego Alejandro Morales Escobar     | 21146

## Diseño de las entidades

### Estructuras de Datos para Entidades 
Las entidades se definen usando estructuras en C, que permiten almacenar múltiples atributos relacionados en una sola unidad lógica. Las estructuras principales son Plant, Herbivore, y Carnivore, cada una de las cuales incluye las coordenadas x y y para su ubicación en una cuadrícula, un valor de energy para su energía, un indicador alive para el estado de vida, y un label para diferenciarlas dentro de la cuadrícula. Además, se incluye un campo hasMovedInThisTurn para rastrear si la entidad ha realizado alguna acción durante el turno actual​.

### Plantas 
Las plantas son entidades estáticas que pueden reproducirse bajo ciertas condiciones. Su comportamiento incluye la posibilidad de expandirse a celdas adyacentes si estas están vacías. La energía inicial de las plantas es baja, pero se pueden reproducir rápidamente si no están rodeadas por otras plantas​.

### Herbívoros
Los herbívoros son organismos móviles que buscan plantas para alimentarse y reproducirse. Su comportamiento es más complejo que el de las plantas, ya que además de buscar comida, intentan escapar de los carnívoros que se encuentran en celdas adyacentes. Los herbívoros tienen una vida limitada, determinada por su edad, y también pueden reproducirse si tienen suficiente energía​.

### Carnívoros
Los carnívoros representan el nivel más alto en la cadena alimenticia del ecosistema. Se alimentan de herbívoros y también tienen la capacidad de reproducirse cuando su energía es suficiente. Similar a los herbívoros, los carnívoros también envejecen y eventualmente mueren si no encuentran suficiente comida​.

#### Funciones de Comportamiento
Cada tipo de entidad tiene funciones asociadas que definen su comportamiento dentro del ecosistema. Estas funciones incluyen la inicialización, movimiento, alimentación, reproducción, y envejecimiento. Se emplean técnicas de paralelización usando OpenMP para manejar múltiples entidades simultáneamente, optimizando así la simulación.
