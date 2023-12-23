#include "fbroker.h"

// Descripción: Función para escribir la energía de cada celda en un archivo de salida, colocando primero la celda con la mayor energía.
// Entrada:
//   - double *energia_celdas: arreglo con las energías de cada celda.
//   - int cantidad_celdas: número total de celdas.
// Salida:
//   - void: no retorna ningún valor, pero escribe la información en un archivo llamado "output.txt".

void escribir_archivo(double *energia_celdas, int cantidad_celdas, char* nombresalidaArchivo){
    FILE *fp;
    char *nombresalida = nombresalidaArchivo;
    fp = fopen(nombresalida, "w");
    if (fp == NULL)
    {
        printf("Error al abrir el archivo para escritura. \n");
        exit(EXIT_FAILURE);
    }

    int numerocelda = 0;
    double mayor = energia_celdas[0];

    // Encuentra la celda con mayor energía
    for (int celda = 1; celda < cantidad_celdas; celda++)
    {
        if (energia_celdas[celda] > mayor)
        {
            mayor = energia_celdas[celda];
            numerocelda = celda;
        }
    }

    fprintf(fp, "%d %lf\n", numerocelda, mayor); // Escribir la celda con mayor energía y su energía

    for (int celda = 0; celda < cantidad_celdas; celda++)
    {
        fprintf(fp, "%d %lf\n", celda, energia_celdas[celda]); // Escribir la energía de cada celda
    }
    fclose(fp);
}

// Descripción: Función para imprimir en stderr la energía de cada celda, con la celda de mayor energía en primer lugar.
// Entrada:
//   - double *energia_celdas: arreglo con las energías de cada celda.
//   - int cantidad_celdas: número total de celdas.
// Salida:
//   - void: no retorna ningún valor, pero imprime en stderr las energías de las celdas.

#include <stdio.h>

void imprimir_energia_celdasD(double *energia_celdas, int cantidad_celdas) {
    // Inicializar la variable para la mayor energía
    double mayor = 0.0;

    // Buscar la mayor energía en el arreglo
    for (int celda = 0; celda < cantidad_celdas; celda++) {
        if (energia_celdas[celda] > mayor) {
            mayor = energia_celdas[celda];
        }
    }

    // Asegurarse de que la mayor energía no sea cero para evitar división por cero
    if (mayor == 0.0) {
        mayor = 1.0; // Asignar un valor mínimo a mayor para evitar división por cero
    }

    // Calcular el factor de normalización
    double norm_factor = 60.0 / mayor;

    // Graficar las energías
    for (int celda = 0; celda < cantidad_celdas; celda++) {
        // Calcular el número de 'o' a imprimir
        int num_os = (int)(energia_celdas[celda] * norm_factor);
        // Imprimir el número de celda y la energía
        printf("%d %.4f |", celda, energia_celdas[celda]);
        // Imprimir la barra de 'o's
        for (int i = 0; i < num_os; i++) {
            printf("o");
        }
        printf("\n");
    }
}


// Descripción: Función para imprimir en stderr el número de líneas procesadas por cada worker.
// Entrada:
//   - double *lineasProcesadas: arreglo con el número de líneas procesadas por cada worker.
//   - int cant_workers: número de workers que han procesado datos.
// Salida:
//   - void: no retorna ningún valor, pero imprime en stderr el número de líneas procesadas por cada worker.
void imprimir_lineas_procesadas(int *lineasProcesadas, int cant_workers, int pids[]){
    for(int i = 0; i<cant_workers; i++){
        fprintf(stderr, "Worker %d (pid %d) procesó %d líneas\n", i, pids[i], lineasProcesadas[i]);
    }
}
