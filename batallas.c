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
    }
    free(torneo->entrenadores);

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
    torneo->cantidad_entrenadores = 0;
    
    if (torneo == NULL) {
        return NULL;
    }

    agregar_entrenador(torneo, entrenadores_f);
    fclose(entrenadores_f);

    return torneo;
}

void pedir_memoria(torneo_t* torneo){
    entrenador_t* auxiliar = NULL;
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
}

int parsear_archivo(FILE* entrenadores_f, torneo_t* torneo){
    int leidos = fscanf(entrenadores_f, "%[^;];%[^;];%i;%i;%i;%[^;];%i;%i;%i;%[^;];%i;%i;%i\n", torneo->entrenadores[torneo->cantidad_entrenadores].nombre, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].inteligencia, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].inteligencia, torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].nombre, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].fuerza, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].agilidad, &torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].inteligencia);

    return leidos;
}

void agregar_entrenador(torneo_t *torneo, FILE* entrenadores_f){

    pedir_memoria(torneo);

    int leidos = parsear_archivo(entrenadores_f, torneo);
    
    torneo->cantidad_entrenadores++;
            
    while (leidos == 13 ){
        pedir_memoria(torneo);

        leidos = parsear_archivo(entrenadores_f, torneo);

        torneo->cantidad_entrenadores++;
        
    }
    if (leidos != 13){

        void* auxiliar = realloc(torneo->entrenadores, (torneo->cantidad_entrenadores-1)*sizeof(entrenador_t));

        if (auxiliar == NULL){
            return;
        }
            
        free(torneo->entrenadores[torneo->cantidad_entrenadores].pokemones);
        torneo->entrenadores = auxiliar;
        torneo->cantidad_entrenadores--;
    }
}



void torneo_listar(torneo_t* torneo, void (*formatear_entrenador)(entrenador_t*)){
    mostrar_torneo(torneo);
    //mostrar caracteristicas
    //mostrar fuerza
    //mostrar nombres
    //mostrar agilidad
    //mostrar inteligencia
}

int main(){
    char* ruta = "archivo.txt";
    torneo_t* torneo = torneo_crear(ruta);
    torneo_destruir(torneo);
    return 0;
}