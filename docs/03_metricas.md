# Simulación de contagio en hospitales

## Objetivo

Dada a la complejidad de Repast HPC y al tiempo disponible de la materia para
llevar a cabo el proyecto, se optó por priorizar el paralelismo en la
simulación, realizando mediciones de rendimiento y buscando posibles mejoras.
Por este motivo en la simulación solo se mantuvo una lógica de transmisión entre
los agentes, desplazándose de manera aleatoria sobre un mapa trivial con paredes
en los bordes, solo con el objetivo de verificar que el modelo funciona
correctamente y que los mapas y agentes son generados de forma correcta.

## Rendimiento 
 
Para realizar comparaciones de rendimiento, se ejecuta reiteradas veces la
simulación combinando distintos parámetros como el tamaño del mapa, la cantidad
de agentes y la distribución del mapa en cantidad de procesos. 

De cada combinación se mide el tiempo de ejecución para la simulación con esas
características. 

<!-- TODO agregar gráficos de rendimiento para cada mapa y agentes  -->

Cuando el espacio se trata de un mapa de tamaño reducido con poca o mediana
cantidad de agentes (como el caso de los dos primeros gráficos), el rendimiento
no se ve favorecido al aumentar la cantidad de procesos, sino al contrario, el
tiempo de ejecución aumenta, debido al incremento de comunicación; reduciendo el
rendimiento del sistema.  

En los siguientes casos, cuando el mapa espacial aumenta a 500x500, sí se puede
observar una notable mejora de rendimiento cuando ejecutamos la simulación en 1
y en 4 procesos, reduciendo el tiempo de ejecución a aproximadamente la mitad en
las simulaciones respectivamente.

Los resultados obtenidos se deben a que cuando el nivel de procesamiento es
reducido, la comunicación entre procesos es excesivamente alta, por lo que
tratándose de simulaciones que no demandan un gran procesamiento no se justifica
la paralelización de la misma ya que el rendimiento se verá afectado. 
Por el contrario, cuando se trata de simulaciones con una cantidad de agentes
mayor, en un espacio extenso, las mejoras en tiempo de ejecución son muy
significativas, reduciendo el mismo, en algunos casos, a casi el 50%.

También, es necesario destacar otro factor que influye directamente en el
rendimiento de la simulación que es el balance de procesamiento para cada
proceso. Es decir, si la simulación se ejecuta, por ejemplo, en 4 procesos, el
escenario perfecto sería que cada proceso ejecute el 25% del procesamiento
total, ya que de otra manera los procesos tendrían que esperarse entre sí,
simulando una barrera, hasta que todos terminen su ejecución para que el
scheduler pueda realizar la sincronización entre los mismos antes del siguiente
tick de manera que todos los procesos comiencen la ejecución en el mismo
instante.
