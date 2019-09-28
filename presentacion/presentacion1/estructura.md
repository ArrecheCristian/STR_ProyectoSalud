# Presentación 1

## Ideas principales
* Introducir el objetivo de la simulación en el proyecto: Determinar la probabilidad de ir sano a un hospital y volver enfermo, en temporada de gripe. 
* Entidades (con sus respectivas máquinas de estado y lógica):
    * Pacientes: Tienen una probabilidad de llegar enfermos (más probabilidad para la guardia). Siguen la siguiente rutina:
        1. Entran
        1. Van a recepción 
        1. Esperan a ser atendidos
        1. Se atienden
        1. Se van
        * Los pacientes de guardia tienen una probabilidad de ir a los consultorios comunes y luego irse.
    * Médicos: Fijos en los distintos consultorios. Se pueden enfermar de manera leve, si aumenta la enfermedad se van.
    * Objetos infectables: 
        * No tienen colisión
        * Las personas infectadas tienen una probabilidad de infectar el objeto
        * La infección del objeto puede ir en aumento al entrar en contacto con más enfermos
        * Cada cierto periodo, se limpia (no modelamos el personal de limpieza, ya que no lo consideramos relevante) 
* Presentación del mapa inicial (mencionar que la idea de los mapas es tener separado una zona de guardia y una zona de turnos presolicitados). Que sea realista la distribución de las zonas    
* Solo la última filmina de Respast con las ideas principales, C++, concurrente, alto rendimiento, etc.

