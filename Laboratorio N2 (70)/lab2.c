#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>

int main(int argc, char *argv[])
{
    /* RECORDATORIO

    argv[0]: ./lab2
    argv[1]: -N
    argv[2]: 35 (cant_celdas)
    argv[3]: -P
    argv[4]: 1 (cant_workers)
    argv[5]: -i
    argv[6]: test1_35.txt (filename_in)
    argv[7]: -o
    argv[8]: res.txt (filename_out)
    argv[9]: -c
    argv[10]: 2 (chunk_size_size)
    argv[11]: -D (bandera_D)

    */

    // Variables para getopt
    int option;
    int cantidad_celdas = -1;
    int cant_workers = 0;
    char* nombrearchivo = NULL;
    char* nombresalida = NULL;
    int flag_D = 0;
    int chunk = 0;

    // Variables para el execv broker
    char* N;
    char* P;
    char* f_in;
    char* f_out;
    char* c;
    char* D = "0";

    // Usar getopt para leer las opciones de la línea de comandos
    while ((option = getopt(argc, argv, "N:P:i:o:c:D")) != -1)
    {
        switch (option) // Obtener la opción
        {
        case 'N':
            // Usando strtol para permitir una mejor validación de la entrada
            char *endptr;
            N = optarg; // optarg contiene el argumento de la opción
            cantidad_celdas = strtol(optarg, &endptr, 10); // Convertir a entero
            // Verificar que se usó toda la cadena y que el número es positivo
            if (*endptr != '\0' || cantidad_celdas <= 0)
            {
                fprintf(stderr, "La opción -N requiere un número entero positivo.\n");
                return 0;
            }
            break;
        case 'i':
            f_in = optarg; // optarg contiene el argumento de la opción
            nombrearchivo = optarg; // optarg contiene el argumento de la opción
            break;
        case 'o':
            f_out = optarg; // optarg contiene el argumento de la opción
            nombresalida = optarg; // optarg contiene el argumento de la opción
            break;
        case 'D':
            //D = optarg; // optarg contiene el argumento de la opción
            flag_D = 1; // optarg contiene el argumento de la opción
            if (flag_D == 1){
                D = "1";
            }
            break;
        case 'P':

            // Usando strtol para permitir una mejor validación de la entrada
            P = optarg; // optarg contiene el argumento de la opción
            char *endptr2;
            cant_workers = strtol(optarg, &endptr2, 10); // Convertir a entero
            // Verificar que se usó toda la cadena y que el número es positivo
            if (*endptr2 != '\0' || cant_workers <= 0)
            {
                fprintf(stderr, "La opción -P requiere un número entero positivo.\n");
                return 0;
            }
            break;

        case 'c':
            // Usando strtol para permitir una mejor validación de la entrada
            char *endptr3;
            c = optarg; // optarg contiene el argumento de la opción
            chunk = strtol(optarg, &endptr3, 10); // Convertir a entero
            // Verificar que se usó toda la cadena y que el número es positivo
            if (*endptr3 != '\0' || chunk <= 0)
            {
                fprintf(stderr, "La opción -c requiere un número entero positivo.\n");
                return 0;
            }
            break;
        default:
            fprintf(stderr, "Uso: %s [-N num_celdas] [-i input_file] [-o output_file] [-D]\n", // Mensaje de ayuda
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
    if (cant_workers == 0)
    {
        printf("La opción -P es requerida.\n");
        return 0;
    }
    if (chunk == 0)
    {
        printf("La opción -c es requerida.\n");
        return 0;
    }

    // Crear el arreglo de argumentos para el execv
    char* argv2[] = {"./lab2","-N",N,"-P",P,"-i",f_in,"-o",f_out,"-c",c,D,NULL};

    // Crear el proceso hijo
    int pid = fork();

    if (pid == 0)
    {
        // Ejecutar el proceso hijo y entrar al broker los argumentos correspondientes 
        execv("./broker", argv2);
        printf("Error execv en broker");
        return 0;
    }
    else
    {   // Esperar a que el proceso hijo termine
        waitpid(pid, NULL, 0);
    }

    return 0;
    
}
