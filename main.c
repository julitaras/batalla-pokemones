#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batallas.h"

void mostrar_torneo(torneo_t *torneo);

void agregar_entrenador(torneo_t* torneo);

int main(){

    torneo_t* torneo = NULL;
    torneo->cantidad_entrenadores = 0;
    torneo = malloc(sizeof(torneo_t));

    if (torneo == NULL){
        return 1;
    }

    agregar_entrenador(torneo);
    mostrar_torneo(torneo);
    free(torneo->entrenadores);
}

void agregar_entrenador(torneo_t *torneo){
    FILE *entrenadores_f = NULL;
    if (torneo->cantidad_entrenadores == 0){
        entrenador_t* entrenadores = NULL;
        entrenadores = malloc(sizeof(entrenador_t));

        if (entrenadores == NULL){
            return;
        }

        torneo->entrenadores = entrenadores;
    
        entrenadores_f = fopen("archivo.txt", "r");
        
        if (entrenadores_f == NULL) {
            return;
        }
    }
    else{
        void* aux = realloc(torneo->entrenadores, torneo->cantidad_entrenadores * sizeof(entrenador_t));

        if (aux == NULL){
            return;
        }

        torneo->entrenadores = aux;
    }
    
    pokemon_t* pokemones = NULL;
    pokemones = malloc(3 * sizeof(pokemon_t));

    if (pokemones == NULL){
        return;
    }

    torneo->entrenadores[torneo->cantidad_entrenadores].pokemones = pokemones;

    int leidos = fscanf(entrenadores_f, "%[^;];%[^;];%i;%i;%i;%[^;];%i;%i;%i;%[^;];%i;%i;%i\n", torneo->entrenadores[torneo->cantidad_entrenadores].nombre, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].inteligencia, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].inteligencia, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].inteligencia);
    torneo->cantidad_entrenadores++;

    while(leidos == 13){
        void* aux = realloc(torneo->entrenadores, torneo->cantidad_entrenadores * sizeof(entrenador_t));

        if (aux == NULL){
            return;
        }

        torneo->entrenadores = aux;
        pokemon_t* pokemones = NULL;
       pokemones = malloc(3 * sizeof(pokemon_t));

        if (pokemones == NULL){
            return;
        }

        torneo->entrenadores[torneo->cantidad_entrenadores].pokemones = pokemones;
        int leidos = fscanf(entrenadores_f, "%[^;];%[^;];%i;%i;%i;%[^;];%i;%i;%i;%[^;];%i;%i;%i\n", torneo->entrenadores[torneo->cantidad_entrenadores].nombre, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].inteligencia, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].inteligencia, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].inteligencia);
        torneo->cantidad_entrenadores++;
    }

    fclose(entrenadores_f);
}












void mostrar_torneo(torneo_t *torneo){
    printf("El torneo tiene: %i ", torneo->cantidad_entrenadores);

    for (int i = 0; i < torneo->cantidad_entrenadores; i++)
    {
        printf("Entrenador: %s\n", torneo->entrenadores[i].nombre);
        printf("Pokemon 1 Nombre: %s\n", torneo->entrenadores[i].pokemones[0].nombre);
        printf("Pokemon 1 Fuerza: %i\n", torneo->entrenadores[i].pokemones[0].fuerza);
        printf("Pokemon 1 Agilidad: %i\n", torneo->entrenadores[i].pokemones[0].agilidad);
        printf("Pokemon 1 Inteligencia: %i\n\n", torneo->entrenadores[i].pokemones[0].inteligencia);
        printf("Pokemon 2 Nombre: %s\n", torneo->entrenadores[i].pokemones[1].nombre);
        printf("Pokemon 2 Fuerza: %i\n", torneo->entrenadores[i].pokemones[1].fuerza);
        printf("Pokemon 2 Agilidad: %i\n", torneo->entrenadores[i].pokemones[1].agilidad);
        printf("Pokemon 2 Inteligencia: %i\n\n", torneo->entrenadores[i].pokemones[1].inteligencia);
        printf("Pokemon 3 Nombre: %s\n", torneo->entrenadores[i].pokemones[2].nombre);
        printf("Pokemon 3 Fuerza: %i\n", torneo->entrenadores[i].pokemones[2].fuerza);
        printf("Pokemon 3 Agilidad: %i\n", torneo->entrenadores[i].pokemones[2].agilidad);
        printf("Pokemon 3 Inteligencia: %i\n\n", torneo->entrenadores[i].pokemones[2].inteligencia);
    }  
}

