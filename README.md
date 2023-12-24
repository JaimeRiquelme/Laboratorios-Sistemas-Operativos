
# Sistemas Operativos: Laboratorios 1 y 2

Este repositorio contiene dos laboratorios del curso de Sistemas Operativos, cada uno enfocado en diferentes aspectos del manejo de procesos en un sistema operativo Linux.

---

## Laboratorio 1: Programación Imperativa en C

Este laboratorio tiene como objetivo aplicar técnicas de programación imperativa mediante lenguaje C, como la recepción de parámetros mediante getopt y compilación mediante Makefile sobre sistema operativo Linux.

### Autor: Jaime Riquelme & Byron Caices

### Fecha: 2023-11-09

#### Cómo ejecutar este proyecto

0. Se requiere un sistema operativo linux-based.
1. Compilar mediante el comando `make`.
2. Para ejecutar debes estar conciente de las siguientes definiciones para los flags:

```
 -N: es el número de celdas
 
 -i: es el archivo con el bombardeo (archivo de entrada)
 
 -o: es el archivo de salida
 
 -D: bandera o flag que permite indicar si se quiere ver por consola la cantidad de celdas de
material.
```

3. Ejemplo de comando para ejecutar:
   ```
   ./lab1 -N 5 -i input.txt -o output.txt -D
   ```

Obs: El programa está preparado para valores erróneos que puedan ser ingresados y tampoco importa el orden en que ingreses los flags.

#### Descripción del Laboratorio 1

Este laboratorio se enfoca en la implementación de un programa en C que maneja un archivo de texto conteniendo partículas, cada una con una posición y energía específica. El objetivo es calcular la energía disipada en un arreglo unidimensional, utilizando la fórmula dada. El programa debe leer los parámetros de entrada y generar un archivo de salida con la energía recibida por cada celda.

---

## Laboratorio 2: Procesos Hijos y Comunicación entre Procesos

Procesos hijos y comunicación entre procesos implementando uso de fork(), execv(), dup2, pipe().

### Autor: Jaime Riquelme & Byron Caices

### Fecha: 2023-11-09

#### Cómo ejecutar este proyecto

0. Se requiere un sistema operativo linux-based.
1. Compilar mediante el comando `make`.
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

#### Descripción del Laboratorio 2

En este laboratorio, se exploran conceptos avanzados de programación en sistemas operativos, como la creación y manejo de procesos hijos y la comunicación entre procesos. Los estudiantes aprenderán a implementar estos conceptos utilizando las funciones de sistema fork(), execv(), dup2 y pipe(), creando un entorno de programación más complejo y cercano a situaciones reales en el desarrollo de software en sistemas operativos.

---

### Contacto

Para más información o dudas, por favor contacta a jaime.riquelme@usach.cl o byron.caices@usach.cl

---
