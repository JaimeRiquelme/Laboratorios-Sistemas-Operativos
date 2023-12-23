#ifndef FBROKER_H
#define FBROKER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "Particle.h"

#define READ 0
#define WRITE 1
#define FIN "FIN"

// Funciones comentadas en archivo .c

void imprimir_info_lineas(int num_lineas);
void SumarTotalEnergias(double **energia_celdas, int cantidad_celdas, int cant_workers, double *energia_total);
void escribir_archivo(double *energia_celdas, int cantidad_celdas,char* nombresalida);
void imprimir_energia_celdasD(double *energia_celdas, int cantidad_celdas);
void imprimir_lineas_procesadas(int *lineasProcesadas, int cant_workers, int pids[]);

#endif