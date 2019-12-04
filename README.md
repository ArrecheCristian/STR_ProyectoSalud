# Sistemas de Tiempo Real

## Ideas principales

* Presentar un hospital más realista donde la estructura siga alguna lógica.
* Por ejemplo, contar con una sala de espera, guardia y consultorios especializados. 
* Los pacientes tienen que seguir una lógica de llegar al hospital, esperar a ser atendido, atenderse e irse. La espera no debe ser con desplazamiento aleatorio.
* Dividir los pacientes por guardia y por turno presolicitado.
* Médicos fijos en los consultorios. 
* Objetos infectados y portadores (sillas, tachos de basura, baño, etc.). Agregarle peso de infección a diferentes objetos, por ejemplo las puertas con alto grado de infección.
* Agregarle porcentaje de infección a los pacientes (por ejemplo, más porcentaje de infectados a los que van por guardia).
* Hay dos probabilidades, probabilidad de contagiar **a** otro agente, y probabilidad de ser contagiado **por** otro agente.

## Notas

* **IMPORTANTE** Explicar como funcionan las dos probabilidades, como se combinan.

## Formato del mapa

El mapa se almacena con la siguiente estructura:

- La primer linea indica el tamaño del mapa, en formato AnchoxAlto
- Las coordenadas (0,0) se encuentra en la primer linea del archivo, en el primer caracter
- Cada linea representa una fila, las columnas se encuentran separadas por un espacio
- Los *objetos* se almacenan codificadas como números, de la siguiente manera:

| Codigo    | Entidad           |
| --------- | ----------------- |
| 0         | Vacío             |
| 1         | Pared             |
| 2         | Persona sana      |
| 3         | Persona enferma   |

A modo de ejemplo, el siguiente texto representa un mapa de 5x5, con una entrada a la izquierda
y una persona enferma en el centro, y una persona sana a la derecha.

```
5x5
1 1 1 1 1
1 0 0 0 1
0 0 3 2 1
1 0 0 0 1
1 1 1 1 1
```

## Rendimiento

### 1

real	0m3.416s
user	0m2.109s
sys	    0m5.510s

### 2

real	0m4.661s
user	0m2.300s
sys	    0m4.802s

real	0m4.946s
user	0m2.132s
sys	    0m5.381s

### 3

real	0m8.818s
user	0m2.726s
sys	    0m8.097s

real	0m9.064s
user	0m2.735s
sys	    0m8.200s

real	0m9.305s
user	0m2.720s
sys	    0m7.688s

### 4

real	0m12.645s
user	0m3.043s
sys	    0m8.642s

real	0m12.788s
user	0m2.774s
sys	    0m8.657s

real	0m13.075s
user	0m3.007s
sys	    0m8.665s

real	0m13.577s
user	0m2.924s
sys	    0m9.121s
 

## Anexo

### Documentación

- Repast HPC Manual, 2013, https://repast.github.io/docs/repast_hpc.pdf