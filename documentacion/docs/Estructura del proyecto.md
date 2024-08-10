---
sidebar_position: 2
---

## Estructura del Proyecto

- **main.c**: Punto de entrada del programa. Aquí se inicializan las entidades y se controla el ciclo de simulación.
- **ecosystem.c / ecosystem.h**: Define la estructura del ecosistema y funciones para inicializar y mostrar el estado del ecosistema.
- **entities.c / entities.h**: Contiene la implementación de las plantas, herbívoros y carnívoros, así como su comportamiento.
- **configs.h**: Archivo de configuración que define los parámetros de la simulación como el tamaño de la matriz, probabilidades de expansión, número de ciclos, entre otros.
- **CMakeLists.txt**: Archivo para la configuración de la compilación del proyecto con CMake.

## Decisiones Tomadas
Para este proyecto se estableció que la simulación se ejecutará en una cuadrícula de 60 por 60, con una instaciación de 30 plantas, 25 herbívoros y 15 carnívoros.

También se colocaron las siguientes reglas:

### Reproducción
#### Plantas
Las plantas se pueden reproducir siempre y cuando haya espacio suficiente alrededor de ellas y estas nacen con un 30% de probabilidad.

#### Herbívoros
Los herbívoros se pueden reproducir siempre y cuando haya espacio suficiente y tengan un nivel de energía mayor a 2, así mismo al hacer este acto, estos pierden 2 puntos de energía.

#### Carnívoros
Los carnívoros se pueden reproducir siempre y cuando haya espacio suficiente y tengan un nivel de energía mayor a 3, así mismo al hacer este acto, estos pierden 2 puntos de energía.

### Consumo de recursos
#### Plantas
Las plantas no pueden consumir recursos.

#### Herbívoros
Los herbívoros consumen plantas y estas les otorgan un punto de energía siempre y cuando posean menos de 8 puntos de energía. Los herbívoros prefieren comer antes de hacer cualquier otro movimiento.

#### Carnívoros
Los carnívors consumen herbívoros y estos les otorgan un punto de energía siempre y cuando posean menos de 8 puntos de energía. Los carnívors prefieren comer antes de hacer cualquier otro movimiento.

### Movimiento
#### Plantas
Estas entidades no pueden moverse.

#### Herbívoros
Los herbívoros se mueven 1 celda por tick en busca de comida, y cuando detectan un depredador cercano, cambian su configuración para poder escapar de estos antes que cualquier otro movimiento.

#### Carnívoros
Los carnívoros se mueven 1 celda por tick en busca de comida, y cuando detectan un herbívor cercano, cambian su configuración para poder cazar a estos antes que cualquier otro movimiento.

### Muerte
#### Plantas
Las plantas mueren cuando son rodeadas por otras entidades y no poseen espacio suficiente para crecer o cuando son comidas por un herbívoro.

#### Herbívoros
Los herbívoros mueren cuando llegan a una edad mayor a 10, cada tick es una unidad de edad, se quedan sin energía o cuando son consumidos por un depredador.

#### Carnívoros
Los carnívoros mueren cuando llegan a una edad mayor a 15, cada tick es una unidad de edad, o se quedan sin energía.

## Uso de OpenMP

En el proyecto de simulación del ecosistema, se utilizó la computación paralela a través de OpenMP para mejorar la eficiencia de las operaciones que involucran iteraciones sobre la cuadrícula que representa el ecosistema. A continuación, se describen las secciones específicas del código donde se implementó OpenMP y las razones detrás de estas decisiones.

### Inicialización del Ecosistema

Durante la inicialización del ecosistema, cada celda de la cuadrícula se establece con valores predeterminados, lo que incluye la configuración de las coordenadas, la entidad (si la hay), y la etiqueta correspondiente. Esta operación de inicialización es realizada en paralelo utilizando la directiva `#pragma omp parallel for collapse(2)` para recorrer las dos dimensiones de la cuadrícula (matriz). Esto permite que múltiples iteraciones se ejecuten simultáneamente, reduciendo significativamente el tiempo requerido para inicializar una cuadrícula de gran tamaño.

### Reseteo del Estado de Movimiento

Cada ciclo de la simulación comienza con un reseteo del estado de movimiento (`hasMovedInThisTurn`) de todas las entidades dentro del ecosistema. Esto también se realiza en paralelo usando `#pragma omp parallel for collapse(2)` para recorrer eficientemente todas las celdas de la matriz. Dado que cada celda se puede procesar de forma independiente, esta operación es ideal para paralelizarla, permitiendo una reducción en el tiempo de ejecución de este proceso.

### Comportamiento de las Entidades

Las funciones que manejan el comportamiento de plantas, herbívoros, y carnívoros también se ejecutan en paralelo durante cada ciclo de la simulación. Esto se logra a través de un bucle anidado paralelo con `#pragma omp parallel for collapse(2)`, que recorre cada celda de la matriz para ejecutar el comportamiento específico de la entidad correspondiente. La paralelización aquí es crucial debido a que cada entidad realiza operaciones complejas, como buscar comida, moverse, o reproducirse, y el procesamiento en paralelo de estas operaciones permite que la simulación se ejecute más rápidamente, especialmente en ciclos donde la cantidad de entidades es alta.

### Sincronización y Secciones Críticas

Para manejar correctamente la concurrencia, se emplean secciones críticas (`#pragma omp critical`) en lugares donde varias entidades podrían acceder o modificar simultáneamente los mismos recursos, como al inicializar una nueva entidad en una celda específica. Estas secciones críticas aseguran que solo una entidad a la vez pueda realizar operaciones críticas, evitando condiciones de carrera y garantizando la integridad de los datos en el ecosistema.