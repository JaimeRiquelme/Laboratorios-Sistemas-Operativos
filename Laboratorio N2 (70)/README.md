# Sistemas Operativos: Laboratorio 2 
Procesos hijos y comunicación entre procesos implementando uso de fork(), execv(), dup2, pipe() 

## Autor: Jaime Riquelme & Byron Caices

## Fecha: 2023-11-09

### Cómo ejecutar este proyecto

0. Se requiere un sistema operativo linux-based
1. Compilar mediante el comando `make`
2. Para ejecutar debes estar conciente de las siguientes definiciones para los flags:

```
 -N: es el número de celdas
 
 -P: es el número de procesos (workers)
 
 -i: es el archivo con el bombardeo (archivo de entrada)
 
 -o: es el archivo de salida
 
 -c: es el número de chuck, es decir, cantidad de líneas a leer por chunk.
 
 -D: bandera o flag que permite indicar si se quiere ver por consola la cantidad de celdas de
material.
```

3. Ejemplo de comando para ejecutar:

```{c}
./lab2 -N 35 -P 5 -c 2 -i test1_35.txt -o output.txt -D
```

_| obs: El programa está preparado para valores erróneos que puedan ser ingresados y tampoco importa el orden en que ingreses los flags_

---

### Descripción

Se tiene un archivo de texto que contiene particulas, en la forma `"posicion energia"` por ejemplo:

```
5
4 80
8 10
10 100
15 20
27 10
```

- Es un archivo que indica que hay 5 particulas, la primera particula `j = 0` impacta en la posicion `i = 4` de un arreglo unidimensional con una $E_j = E_0 = 80$
- Cada partícula que impacta una celda tiene una funcion de disipación asociada a la formula $Eji$

$$ E_{ji} = \frac{1000 \times E_j}{\text{N} \times (\sqrt{|j - i| + 1})} $$

La salida final del programa es un archivo, que en primer lugar muestra la celda con mayor energía recibida y luego muestra la energía recibida por cada celda

A continuacion un ejemplo para `N = 35`
```
10 4186.647113
0 2175.753651
1 2349.908263
2 2588.782451
3 2958.667612
...
33 1295.642004
34 1265.731283
```

### Para efectos de este proyecto existen mínimo 3 procesos: 1 lab2, 1 broker y P workers. 

- La tarea de lab2 es recibir y validar las flags y luego enviarlas al broker.

- La tarea de broker es crear los P procesos hijos.

- Luego broker lee el archivo linea a linea hasta enviar `c` líneas a un worker seleccionado al azar, luego selecciona otro y le envia `c` líneas hasta que se haya leído todo el archivo de entrada.

- el worker con la información recibida calculará la energía disipada por las particulas y la enviara al broker.

- el broker se encarga de combinar estas soluciones por los workers y finalmente escribe el archivo con la salida.



### Contacto

Para más información o dudas, por favor contacta a jaime.riquelme@usach.cl o byron.caices@usach.cl

---
