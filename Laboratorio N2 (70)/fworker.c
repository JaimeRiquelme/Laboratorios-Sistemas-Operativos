#include "fworker.h"

// Descripción: Funcion que recibe un posicion y una energia y retorna una particula.
// Entrada: Posicion y energia.
// Salida: Puntero a una particula.
Particle* convertir_particula(char* buffer){
    Particle* particula = malloc(sizeof(Particle));
    sscanf(buffer,"%d %lf",&particula->position,&particula->energy);
    return particula;
}

// Descripción: Funcion que recibe un arreglo de particulas y calcula
// la energia de recibida por cada celda segun la dispersion E_ji.
// Entrada: Arreglo de particulas, cantidad de celdas, arreglo de energia de celdas, energia minima y cantidad de particulas.
// Salida: Ninguna. Trabaja modificando el arreglo de energia de celdas.
void calcular_energia_celdas(Particle **particles, int cantidad_celdas, double *energia_celdas, double MIN_ENERGY, int num_particles) {

    for (int i = 0; i < num_particles; i++) {
        Particle *p = particles[i]; // Obtener el puntero a la partícula actual
        for (int celda = 0; celda < cantidad_celdas; celda++) {
            // Calcular la energía depositada en la celda por la partícula p
            double E_ji = (1000 * p->energy) / (cantidad_celdas * (sqrt(abs(p->position - celda) + 1)));
            // Si E_ji es mayor al umbral (MIN_ENERGY), sumarla a la energía existente en la celda
            if (E_ji >= MIN_ENERGY) {
                energia_celdas[celda] += E_ji;
            }
        }
    }

}
