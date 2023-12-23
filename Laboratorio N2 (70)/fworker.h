#ifndef FWORKER_H
#define FWORKER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/wait.h>
#include "Particle.h"


// Funciones comentadas en archivo .c

Particle* convertir_particula(char* buffer);
void calcular_energia_celdas(Particle **particles, int cantidad_celdas, double *energia_celdas, double MIN_ENERGY, int num_particles);

#endif