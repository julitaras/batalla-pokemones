#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batallas.h"

// %[^;]; todo lo que sea distinto al punto y coma

// void torneo_destruir(torneo_t *torneo) {
//     //Deberia liberar a los pokemones, luego entrenadores y luego torneo
//     free(torneo);
// }


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

void agregar_entrenador(torneo_t *torneo){
if (torneo->cantidad_entrenadores == 0){

    entrenador_t* entrenadores = NULL;
    entrenadores = malloc(sizeof(entrenador_t));

    if (entrenadores == NULL) {
        return;
    }

    torneo->entrenadores = entrenadores;
}
else{
        void* auxiliar = realloc(torneo->entrenadores, (torneo->cantidad_entrenadores+1)*sizeof(entrenador_t));

        if (auxiliar == NULL ){
            return;
        }

        torneo->entrenadores = auxiliar;
        FILE *entrenadores_f = fopen("archivo.txt", "r");
        
        if (entrenadores_f == NULL) {
            return;
        }

        torneo->entrenadores[torneo->cantidad_entrenadores].pokemones = NULL;
        torneo->entrenadores[torneo->cantidad_entrenadores].pokemones = malloc(3 * sizeof(pokemon_t));
        
        if (torneo->entrenadores[torneo->cantidad_entrenadores].pokemones == NULL){
            return;
        }

        int leidos = fscanf(entrenadores_f, "%[^;];%[^;];%i;%i;%i;%[^;];%i;%i;%i;%[^;];%i;%i;%i\n", torneo->entrenadores[torneo->cantidad_entrenadores].nombre, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].inteligencia, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].inteligencia, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].inteligencia);
        int stop = 0;
        torneo->cantidad_entrenadores++;
        
         
      while (leidos == 13 && stop != 1){

        void* auxiliar = realloc(torneo->entrenadores, (torneo->cantidad_entrenadores+1)*sizeof(entrenador_t));

        if (auxiliar == NULL ){
            return;
        }

        torneo->entrenadores = auxiliar;
        torneo->entrenadores[torneo->cantidad_entrenadores].pokemones = NULL;
        torneo->entrenadores[torneo->cantidad_entrenadores].pokemones = malloc(3 * sizeof(pokemon_t));
        
        if (torneo->entrenadores[torneo->cantidad_entrenadores].pokemones == NULL){
            return;
        }

        int leidos = fscanf(entrenadores_f, "%[^;];%[^;];%i;%i;%i;%[^;];%i;%i;%i;%[^;];%i;%i;%i\n", torneo->entrenadores[torneo->cantidad_entrenadores].nombre, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].inteligencia, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].inteligencia, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].inteligencia);
        torneo->cantidad_entrenadores++;
        stop = 1;
      }

    fclose(entrenadores_f);
    
    // free(pokemons);
    // free(torneo->entrenadores);
}}

int main(){

    torneo_t* torneo = NULL;
    torneo = malloc(sizeof(torneo_t));

    if (torneo == NULL) {
        return 1;
    }


    agregar_entrenador(torneo);
    mostrar_torneo(torneo);
    
    // free(torneo);
    return 0;
}