#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdio.h>
#include <stdlib.h>

// Estructura para almacenar una partícula
typedef struct {
    int position;  // Posición de la partícula
    double energy;  // Energía de la partícula
} Particle;

// Función para leer el archivo de entrada
Particle* read_input_file(char* filename, int* num_particles) ;

#endif