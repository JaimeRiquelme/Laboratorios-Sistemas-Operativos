#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "Particle.h"

// Entradas : recibe un arreglo de particulas y el numero de particulas
// Salidas : retorna el indice de la particula con mayor energia
// Descripcion : busca la particula con mayor energia dentro de un arreglo de particulas
int maxima_energia(double *energia_celdas, int cantidad_celdas);

// Entradas : recibe un arreglo de particulas, la cantidad de celdas, un arreglo de energia de celdas, la energia minima y el numero de particulas.
// Salidas : no retorna nada ya que modifica el arreglo de energia de celdas
// Descripcion : calcula la energia de cada celda y la almacena en el arreglo de energia de celdas.
void calcular_energia_celdas(Particle *particles, int cantidad_celdas, double *energia_celdas, double MIN_ENERGY, int num_particles);

// Entradas : recibe el nombre del archivo de salida, el numero de celda con mayor energia, la energia de la celda con mayor energia, el arreglo de energia de celdas y el numero de celdas.
// Salidas : no retorna nada ya que escribe en un archivo de salida.
// Descripcion : escribe en un archivo de salida, en la cabeza del archivo, el numero de celda con mayor energia y la energia de la celda con mayor energia. 
//              Luego escribe en el archivo de salida el numero de celda y la energia de cada celda.
void escribir_archivo(char *nombresalida, int numerocelda, double mayor, double *energia_celdas, int cantidad_celdas);

// Entradas : recibe el arreglo de energia de celdas, el numero de celdas y la energia de la celda con mayor energia.
// Salidas : no retorna nada ya que imprime en pantalla el numero de celda y la energia de cada celda en forma de 'o'.
// Descripcion : imprime en pantalla el numero de celda y la energia de cada celda.
void imprimir_energia_celdasD(double *energia_celdas, int cantidad_celdas, double mayor);
