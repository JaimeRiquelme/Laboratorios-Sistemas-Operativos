#include "funciones.h"

// Entradas : recibe un arreglo de particulas y el numero de particulas
// Salidas : retorna el indice de la particula con mayor energia
// Descripcion : busca la particula con mayor energia dentro de un arreglo de particulas
int maxima_energia(double *energia_celdas, int cantidad_celdas){
    int numerocelda = 0;
    double mayor = 0;
    for (int celda = 0; celda < cantidad_celdas; celda++)
    {
        if (energia_celdas[celda] > mayor)
        {
            numerocelda = celda;
            mayor = energia_celdas[celda];
        }
    }
    return numerocelda;
}

// Entradas : recibe un arreglo de particulas, la cantidad de celdas, un arreglo de energia de celdas, la energia minima y el numero de particulas.
// Salidas : no retorna nada ya que modifica el arreglo de energia de celdas
// Descripcion : calcula la energia de cada celda y la almacena en el arreglo de energia de celdas.
void calcular_energia_celdas(Particle *particles, int cantidad_celdas, double *energia_celdas, double MIN_ENERGY, int num_particles){
    for (int i = 0; i < num_particles; i++)
    {
        Particle p = particles[i]; // Obtener la partícula actual
        for (int celda = 0; celda < cantidad_celdas; celda++)
        {   //Iterar sobre cada celda del material
            // Calcular la energía depositada en la celda por la partícula p
            double E_ji = (1000 * p.energy) / (cantidad_celdas * (sqrt(abs(p.position - celda) + 1)));
            // Si E_ji es mayor al umbral (MIN_ENERGY), sumarla a la energía existente en la celda
            if (E_ji >= MIN_ENERGY)
            {
                energia_celdas[celda] += E_ji;
            }
        }
    }
}

// Entradas : recibe el nombre del archivo de salida, el numero de celda con mayor energia, la energia de la celda con mayor energia, el arreglo de energia de celdas y el numero de celdas.
// Salidas : no retorna nada ya que escribe en un archivo de salida.
// Descripcion : escribe en un archivo de salida, en la cabeza del archivo, el numero de celda con mayor energia y la energia de la celda con mayor energia. 
//              Luego escribe en el archivo de salida el numero de celda y la energia de cada celda.
void escribir_archivo(char *nombresalida, int numerocelda, double mayor, double *energia_celdas, int cantidad_celdas){
    FILE *fp;
    fp = fopen(nombresalida, "w");
    if (fp == NULL)
    {
        printf("Error al ingresar parametro flag -o. \nVerifique que lo haya ingresado o si el archivo existe \n");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "%d %lf\n", numerocelda, mayor); // Escribir la celda con mayor energía y su energía
    for (int celda = 0; celda < cantidad_celdas; celda++)
    {
        fprintf(fp, "%d %lf\n", celda, energia_celdas[celda]);
    }
    fclose(fp);
}

// Entradas : recibe el arreglo de energia de celdas, el numero de celdas y la energia de la celda con mayor energia.
// Salidas : no retorna nada ya que imprime en pantalla el numero de celda y la energia de cada celda en forma de 'o'.
// Descripcion : imprime en pantalla el numero de celda y la energia de cada celda.
void imprimir_energia_celdasD(double *energia_celdas, int cantidad_celdas, double mayor){
    // Calcular el factor de normalizacion
    // asumiendo que 60 'o' representan la energia max
    double norm_factor = 60.0 / mayor;
    // Graficar las energias
    for (int celda = 0; celda < cantidad_celdas; celda++)
    {
        int num_os = (int)(energia_celdas[celda] * norm_factor); // Número de 'o' a imprimir
        // Imprimir el número de celda y la energía
        printf("%d %.4f |", celda, energia_celdas[celda]);
        // Imprimir la barra de 'o's
        for (int i = 0; i < num_os; i++)
        {
            printf("o");
        }
        printf("\n");
    }
}

