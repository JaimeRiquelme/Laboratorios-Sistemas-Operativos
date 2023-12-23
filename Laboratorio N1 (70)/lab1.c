#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <getopt.h>
#include "Particle.h"
#include "funciones.h"
#include <math.h>

int main(int argc, char *argv[])
{
    // Leer los argumentos de la línea de comandos
    int option;
    int cantidad_celdas = -1;
    char *nombrearchivo = NULL;
    char *nombresalida = NULL;
    int flag_D = 0;
    double MIN_ENERGY = pow(10, -3);  // Energía mínima para ser considerada en una celda

    // Usar getopt para leer las opciones de la línea de comandos
    while ((option = getopt(argc, argv, "N:i:o:D")) != -1)
    {
        switch (option) // Obtener la opción
        {
        case 'N':
            // Usando strtol para permitir una mejor validación de la entrada
            char *endptr;
            cantidad_celdas = strtol(optarg, &endptr, 10); // Convertir a entero
            // Verificar que se usó toda la cadena y que el número es positivo
            if (*endptr != '\0' || cantidad_celdas <= 0)
            {
                fprintf(stderr, "La opción -N requiere un número entero positivo.\n");
                return 0;
            }
            break;
        case 'i':
            nombrearchivo = optarg; // optarg contiene el argumento de la opción
            break;
        case 'o':
            nombresalida = optarg; // optarg contiene el argumento de la opción
            break;
        case 'D':
            flag_D = 1;  // optarg contiene el argumento de la opción
            break;
        default:
            fprintf(stderr, "Uso: %s [-N num_celdas] [-i input_file] [-o output_file] [-D]\n",  // Mensaje de ayuda
                    argv[0]);
            return 0;
        }
    }

    // Verificar que las opciones requeridas han sido provistas
    if (cantidad_celdas == -1)
    {
        printf("La opción -N es requerida.\n");
        return 0;
    }
    if (nombrearchivo == NULL)
    {
        
        printf("La opción -i es requerida.\n");
        return 0;
    }
    if (nombresalida == NULL)
    {
        printf("La opción -o es requerida.\n");
        return 0;
    }


    // Leer el archivo de entrada
    int num_particles;
    Particle *particles = read_input_file(nombrearchivo, &num_particles);  


    // Verificar que se pudo leer el archivo
    if (particles == NULL)
    {
        return 0; // Si no se pudo leer el archivo, terminar el programa
    }
    

    // Asignar memoria para el arreglo de energías de las celdas
    double *energia_celdas = (double *)malloc(cantidad_celdas * sizeof(double));
    if (energia_celdas == NULL)
    {
        fprintf(stderr, "No se pudo reservar memoria para las particulas\\n");
        return 0;
    }

    // Calcular la energía depositada en cada celda
    calcular_energia_celdas(particles, cantidad_celdas, energia_celdas, MIN_ENERGY, num_particles);

    // encontrar la celda con mayor energia
    int numerocelda = maxima_energia(energia_celdas, cantidad_celdas);

    // encontrar la mayor energia
    double mayor = energia_celdas[numerocelda];
    

    // Si la flag -D esta activada, graficar las energias de las celdas, si no esta activada, no graficar
    if (flag_D == 1)
    {
        imprimir_energia_celdasD(energia_celdas, cantidad_celdas, mayor);
    }

    // Escribir el archivo de salida

    escribir_archivo(nombresalida, numerocelda, mayor, energia_celdas, cantidad_celdas);

    // Libera memoria
    free(energia_celdas);
    free(particles);
    return 0;
}
