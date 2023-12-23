#include "fbroker.h"

#define READ 0
#define WRITE 1
#define FIN "FIN"

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
    char* BanderaArchivo = argv[11]; // bandera para saber si se ingresó el archivo de salida
    char* nombresalida = argv[8]; // nombre del archivo de salida
    int cant_celdas = atoi(argv[2]); // cantidad de celdas
    int cant_workers = atoi(argv[4]); // cantidad de workers
    int chunk_size = atoi(argv[10]); // tamaño del chunk
    char *filename_in = argv[6]; // nombre del archivo de entrada
    char buffer3[100]; // buffer para recibir el mensaje de confirmación del worker

    int bandera = -1; // bandera para saber que posición está asociada a cada hijo
    int pid;      // pid del proceso
    int pids[cant_workers]; // arreglo de pids de los procesos hijos

    double *energia_total = (double *)malloc(sizeof(double) * cant_celdas);
    int lineas_procesadas; // cantidad de lineas procesadas por cada worker
    int *lineasProcesadas = (int *)malloc(sizeof(int) * cant_workers); // arreglo de lineas procesadas por cada worker
    double prueba; // variable para recibir la energia de cada celda

    int fd[cant_workers][2];  // crear pipe para los hijos
    int fd2[cant_workers][2]; // crear pipe para padre

    for (int i = 0; i < cant_workers; i++) //cerrar los pipes
    {
        pipe(fd[i]);
        pipe(fd2[i]);
    }

    for (int i = 0; i < cant_workers; i++)
    { // crear hijos

        pid = fork();
        if (pid == 0)
        {                // si corresponden a los procesos hijos, se les asociará banderas
            bandera = i; // solo los hijos tendrán esa bandera en positivo (indice)
            break; // el padre conservará su bandera en -1
        }
        else if (pid > 0)
        {
            pids[i] = pid; // guardar los pids de los hijos
            
        }
    }
    if (pid == -1)
    {
        printf("Error");
        exit(1);
    }

    else if (pid == 0)
    { // si es el proceso hijo
        for (int i = 0; i < cant_workers; i++)
        {

            if (bandera == i)
            { // si es el proceso hijo i
                // Cerrar escritura de pipe hijos
                close(fd[i][WRITE]);
                // Cerrar lectura de pipe padre
                close(fd2[i][READ]);

                // Redirigir lectura del pipe hijo a STDIN
                dup2(fd[i][READ], STDIN_FILENO);
                close(fd[i][READ]); // Cerrar lectura del hijo (buena practica)

                // Redigir escritura del pipe padre a STDOUT
                dup2(fd2[i][WRITE], STDOUT_FILENO);
                close(fd2[i][WRITE]); // Cerrar escritura del padre (buena practica)

                // Ejecutar el programa worker en donde procesos hijos leeran
                execv("./worker", argv);
                printf("Error"); // si hay error en el execv
                exit(1);
            }
        }
    }
    else
    { // si es el proceso padre

        // Abrir archivo de entrada
        FILE *archivo = fopen(filename_in, "r");
        if (archivo == NULL)
        { // si hay problemas al abrir el archivo
            printf("Error al abrir el archivo de entrada");
            exit(1);
        }

        // Cerrar los extremos no utilizados del primer y segundo pipe
        for (int i = 0; i < cant_workers; i++)
        {
            close(fd[i][READ]);   // Extremo de lectura del primer pipe
            close(fd2[i][WRITE]); // Extremo de escritura del segundo pipe
        }

        char buffer[100];
        int lineaActual = 0;
        int LineasEnviadas = 0;
        int workerID = rand() % cant_workers; // seleccionar un worker aleatorio inicial

        // Leer la primera línea para obtener el número total de líneas
        int total_lineas;
        if (fscanf(archivo, "%d", &total_lineas) != 1)
        {
            printf("Error al leer el número total de líneas.\n");
            exit(1);
        }

        fscanf(archivo, "\n"); // Leer el salto de línea

        while (fgets(buffer, 100, archivo) != NULL)
        {

            lineaActual++;
            if (LineasEnviadas == chunk_size) // si se envió el chunk_size de lineas al worker seleccionado se cambia de worker
            {
                LineasEnviadas = 0;
                workerID = rand() % cant_workers;
                //printf("Worker seleccionado: %d\n", workerID);
            }
            LineasEnviadas++;
            write(fd[workerID][WRITE], &buffer, strlen(buffer) + 1);
            read(fd2[workerID][READ], &buffer3, sizeof(buffer3));
        }
        for (int i = 0; i < cant_workers; i++)
        {
            // escribo FIN en el pipe para que el worker termine
            write(fd[i][WRITE], &FIN, strlen(FIN) + 1);
            close(fd[i][WRITE]);
            // leo la cantidad de lineas procesadas
            read(fd2[i][READ], &lineas_procesadas, sizeof(lineas_procesadas));
            lineasProcesadas[i] = lineas_procesadas; // guardo la cantidad de lineas procesadas por cada worker

            // printf("esperando a que el worker %d termine\n", i);

            // bucle para recibir una por una la energia de cada celda
            for (int j = 0; j < cant_celdas; j++)
            {
                read(fd2[i][READ], &prueba, sizeof(prueba)); // recibo la energia de cada celda
                energia_total[j] += prueba; // sumo la energia de cada celda
            }
        }

        // Esperar a que terminen los procesos hijos
        for (size_t i = 0; i < cant_workers; i++)
        {
            // int status;
            waitpid(pids[i], NULL, 0);
        }


        // Escribir el archivo de salida
        escribir_archivo(energia_total, cant_celdas,nombresalida);
        
        // Imprimir la energía de cada celda en stderr por consola si la bandera se ingresó

        if(strcmp(BanderaArchivo,"0")==1){
            imprimir_energia_celdasD(energia_total, cant_celdas);
            imprimir_lineas_procesadas(lineasProcesadas, cant_workers, pids);
        }
        fclose(archivo); // cerrar archivo de entrada

    }

    return 0;
}