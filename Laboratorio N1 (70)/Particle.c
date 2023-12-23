#include "Particle.h"


// Entradas : recibe un arreglo de particulas y el numero de particulas
Particle* read_input_file(char* filename, int* num_particles) {

    FILE* file = fopen(filename, "r");  // Abrir el archivo en modo lectura
    if (file == NULL) { // Verificar que el archivo se haya abierto correctamente
        printf("Error al ingresar parametro flag -i. \nVerifique que lo haya ingresado o si el archivo existe \n");
        return NULL;
    }
    
    // leemos el numero de particulas
    fscanf(file, "%d", num_particles);
    
    // Asignar memoria para el arreglo de particulas
    Particle* particles = (Particle*) malloc((*num_particles) * sizeof(Particle));
    if (particles == NULL) { // Verificar que se haya reservado memoria correctamente
        printf("No se pudo abrir el archivo o este no existe \n");
        fclose(file);
        return NULL;
    }
    
    // leemos las particulas del archivo
    for (int i = 0; i < *num_particles; i++) {
        fscanf(file, "%d %lf", &particles[i].position, &particles[i].energy);
    }
    
    // cerramos el archivo
    fclose(file);
    return particles;
}