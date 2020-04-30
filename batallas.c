#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batallas.h"

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

void torneo_destruir(torneo_t* torneo){

    for (int i = 0; i < torneo->cantidad_entrenadores; i++){
        free(torneo->entrenadores[i].pokemones);
        //free(&torneo->entrenadores[i]);
    //free(torneo->entrenadores);
    }
    free(torneo);
}

void agregar_entrenador(torneo_t *torneo, FILE* entrenadores_f);

torneo_t* torneo_crear(char *ruta_archivo){
    FILE *entrenadores_f = fopen(ruta_archivo, "r");
        
    if (entrenadores_f == NULL) {
        return NULL;
    }
    torneo_t* torneo = NULL;
    torneo = malloc(1 * sizeof(torneo_t));

    if (torneo == NULL) {
        return NULL;
    }
    agregar_entrenador(torneo, entrenadores_f);
    fclose(entrenadores_f);
    return torneo;
}


void agregar_entrenador(torneo_t *torneo, FILE* entrenadores_f){

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
            
    while (leidos == 13 ){
        //agregar_entrenador(torneo, entrenadores_f);
       // agregar_entrenador(torneo, entrenadores_f);
        auxiliar = realloc(torneo->entrenadores, (torneo->cantidad_entrenadores+1)*sizeof(entrenador_t));

        if (auxiliar == NULL ){
            return;
        }

        torneo->entrenadores = auxiliar;
        torneo->entrenadores[torneo->cantidad_entrenadores].pokemones = NULL;
        torneo->entrenadores[torneo->cantidad_entrenadores].pokemones = malloc(3 * sizeof(pokemon_t));
            
        if (torneo->entrenadores[torneo->cantidad_entrenadores].pokemones == NULL){
            return;
        }

        leidos = fscanf(entrenadores_f, "%[^;];%[^;];%i;%i;%i;%[^;];%i;%i;%i;%[^;];%i;%i;%i\n", torneo->entrenadores[torneo->cantidad_entrenadores].nombre, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].inteligencia, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].inteligencia, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].inteligencia);
        torneo->cantidad_entrenadores++;

        if (leidos != 13){

            auxiliar = realloc(torneo->entrenadores, (torneo->cantidad_entrenadores-1)*sizeof(entrenador_t));

            if (auxiliar == NULL){
                return;
            }
            free(torneo->entrenadores[torneo->cantidad_entrenadores].pokemones);
            free(torneo->entrenadores);
            torneo->entrenadores = auxiliar;
            torneo->cantidad_entrenadores--;
        }
    }
}

int main(){
    char* ruta = "archivo.txt";

   torneo_t* torneo = torneo_crear(ruta);
    mostrar_torneo(torneo);
  // torneo_destruir(torneo);
    return 0;
}