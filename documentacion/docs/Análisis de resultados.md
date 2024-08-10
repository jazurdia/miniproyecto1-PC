---
sidebar_position: 3
---

# Análisis de resultados

## Resultados de la Simulación

### Inicialización del Ambiente
- **Plantas**: 30
- **Herbívoros**: 25
- **Carnívoros**: 15
- **Tamaño del ecosistema**: 60x60

**Análisis:** 
La simulación comenzó con una distribución controlada de 30 plantas, 25 herbívoros y 15 carnívoros. Esta configuración inicial proporciona un punto de partida para observar cómo las especies interactúan y cómo sus poblaciones cambian a lo largo del tiempo en un entorno dinámico.

### Ciclo 0
- **Plantas**: 63
- **Herbívoros**: 44
- **Carnívoros**: 28

**Análisis:** 
Al inicio de la simulación, el número de entidades se incrementa rápidamente. Esto se debe a que las plantas tienen una alta probabilidad de reproducirse (30%), lo que permite un crecimiento rápido. Los herbívoros y carnívoros también comienzan a reproducirse y consumir recursos, lo que explica el aumento inicial en sus poblaciones.

### Ciclo 1000
- **Plantas**: 1303
- **Herbívoros**: 348
- **Carnívoros**: 532

**Análisis:** 
En este punto, las plantas han experimentado un crecimiento exponencial debido a la abundancia de espacio. Sin embargo, el número de herbívoros y carnívoros también ha aumentado significativamente, con los carnívoros superando en número a los herbívoros. Esto sugiere que los carnívoros están cazando efectivamente a los herbívoros, manteniendo bajo control su población. La alta cantidad de carnívoros puede comenzar a presionar a los herbívoros, lo que podría impactar su capacidad para sobrevivir en ciclos futuros.

### Ciclo 2000
- **Plantas**: 1591
- **Herbívoros**: 330
- **Carnívoros**: 455

**Análisis:** 
El crecimiento de las plantas continúa, pero se ha desacelerado ligeramente, probablemente debido a la competencia por espacio y recursos. La población de herbívoros ha disminuido un poco, lo que podría ser un indicio de que la presión de los carnívoros está comenzando a afectar su capacidad para reproducirse y sobrevivir. Los carnívoros, por otro lado, han disminuido su número, lo que podría estar relacionado con la reducción de presas disponibles o la competencia entre ellos.

### Ciclo 3000
- **Plantas**: 1606
- **Herbívoros**: 210
- **Carnívoros**: 508

**Análisis:** 
En este ciclo, las plantas se han estabilizado en número, lo que sugiere que han alcanzado un equilibrio en el ecosistema. Sin embargo, los herbívoros han experimentado una caída notable, lo que podría ser un resultado directo de la alta población de carnívoros. Esta disminución en los herbívoros podría tener un impacto a largo plazo en la población de carnívoros, ya que su fuente de alimento principal está disminuyendo.

### Ciclo 4000
- **Plantas**: 1629
- **Herbívoros**: 328
- **Carnívoros**: 427

**Análisis:** 
Hacia el final de la simulación, las plantas siguen siendo abundantes, aunque su crecimiento se ha estabilizado. Curiosamente, la población de herbívoros ha vuelto a aumentar, lo que podría ser un signo de que los carnívoros han alcanzado un equilibrio en su caza, permitiendo que los herbívoros sobrevivan y se reproduzcan. La reducción en el número de carnívoros también puede haber aliviado la presión sobre los herbívoros, permitiendo esta recuperación parcial. 

**Conclusión:** 
La simulación muestra cómo las dinámicas entre depredadores y presas, junto con la disponibilidad de recursos, pueden influir significativamente en las poblaciones de un ecosistema. La competencia y la depredación crean fluctuaciones en las poblaciones, que eventualmente parecen alcanzar un equilibrio.


>**Nota:** Es importante destacar que estos resultados varían en cada ejecución de la simulación debido a ciertos factores aleatorios en el comportamiento de las entidades, como la reproducción y el movimiento. Estas variaciones son inherentes a la naturaleza estocástica del modelo y añaden realismo a la simulación, representando la imprevisibilidad presente en los ecosistemas reales.