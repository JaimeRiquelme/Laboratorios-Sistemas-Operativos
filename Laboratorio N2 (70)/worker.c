#include "fworker.h"

#define READ 0
#define WRITE 1
#define FIN "FIN"
#define MAX_LINES 100
#define MAX_LENGTH 100


int main(int argc, char* argv[])
{
    int cantidad_celdas = atoi(argv[2]); // cantidad de celdas
    Particle **particulas = (Particle**)malloc(sizeof(Particle*) * cantidad_celdas); // arreglo de particulas
    double *energia_celdas = (double *)malloc(cantidad_celdas * sizeof(double)); // arreglo de energias de las celdas
    char buffer[MAX_LENGTH]; // buffer para recibir el mensaje de confirmación del worker
    int lineas_procesadas = 0; // cantidad de lineas procesadas por cada worker
    double MIN_ENERGY = pow(10, -3);  // Energía mínima para ser considerada en una celda

    while (1)
    {
        memset(buffer, 0, sizeof(buffer)); // Limpiar el buffer
        // Leer el mensaje desde el pipe
        int bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
        buffer[bytes_read] = '\0'; // Asegurar que el buffer sea una cadena válida
        // Si se recibe "FIN", finalizar el bucle
        if (strcmp(buffer, FIN) == 0)
        {
            break;
        }
        // Almacenar la línea leída
        particulas[lineas_procesadas] = convertir_particula(buffer);
        write(STDOUT_FILENO,buffer,strlen(buffer)+1);

        lineas_procesadas++; // Aumentar la cantidad de líneas procesadas
    }

    //calcular la energia de las celdas
    calcular_energia_celdas(particulas, cantidad_celdas, energia_celdas, MIN_ENERGY, lineas_procesadas);


    //envio la cantidad de lineas procesadas
    write(STDOUT_FILENO, &lineas_procesadas, sizeof(lineas_procesadas));
    
    //bucle para enviar una por una la energia de cada celda
    for(int i = 0; i<cantidad_celdas; i++){
        write(STDOUT_FILENO, &energia_celdas[i], sizeof(energia_celdas[i]));
    }
    
    return 0;
}
