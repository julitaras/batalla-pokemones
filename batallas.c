#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batallas.h"

void achicar_vector(torneo_t* torneo, int posicion){
    //Probar y acomodar codigo
    if(torneo->cantidad_entrenadores == 0){
        return;
    }
    
    int ultimo = torneo->cantidad_entrenadores-1;
    
    torneo->cantidad_entrenadores--;
    
    entrenador_t aux = torneo->entrenadores[posicion]; 

    torneo->entrenadores[posicion] = torneo->entrenadores[ultimo];

    torneo->entrenadores[ultimo] = aux;
    
    free(torneo->entrenadores[torneo->cantidad_entrenadores].pokemones);
    
    entrenador_t* auxiliar = realloc(torneo->entrenadores, ((unsigned)torneo->cantidad_entrenadores)*sizeof(entrenador_t));
    
    if(auxiliar == NULL){
        return;
    }
    
    torneo->entrenadores = auxiliar;
}

int ganador_inteligencia(entrenador_t* entrenador1 ,entrenador_t* entrenador2){

    int suma_inteligencias_entrenador1 = entrenador1->pokemones[0].inteligencia + entrenador1->pokemones[1].inteligencia + entrenador1->pokemones[2].inteligencia;
    int suma_inteligencias_entrenador2 = entrenador2->pokemones[0].inteligencia + entrenador2->pokemones[1].inteligencia + entrenador2->pokemones[2].inteligencia;
    
    if(suma_inteligencias_entrenador1 >= suma_inteligencias_entrenador2){
        return 0;
    }
    else{
        return 1;
    }
}

int torneo_jugar_ronda(torneo_t* torneo, int (*ganador_batalla)(entrenador_t* ,entrenador_t*)){
    if(ganador_batalla == NULL){
        return -1;
    }
    if(torneo->cantidad_entrenadores == 1){
        return -1;
    }

    if(torneo->cantidad_entrenadores %2 != 0){
        for (int i = 0; i < torneo->cantidad_entrenadores - 1; i++){
            int gandor = ganador_batalla(&torneo->entrenadores[i], &torneo->entrenadores[i] + 1);
            if (gandor == 0){
                achicar_vector(torneo, i+1);
            }else{
                achicar_vector(torneo, i);
            }
        }
    }else{
        for (int i = 0; i < torneo->cantidad_entrenadores; i++){
            int gandor = ganador_batalla(&torneo->entrenadores[i], &torneo->entrenadores[i] + 1);
            
             if (gandor == 0){
                achicar_vector(torneo, i+1);
            }else{
                achicar_vector(torneo, i);
            }
        }
    }   

    return 0;
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

    //fijarse si el archivo esta vacio
    FILE *entrenadores_f = fopen(ruta_archivo, "r");
        
    if (entrenadores_f == NULL) {
        return NULL;
    }

    torneo_t* torneo = NULL;
    torneo = malloc(1 * sizeof(torneo_t));
    torneo->cantidad_entrenadores = 0;
    torneo->entrenadores = NULL;
    torneo->ronda = 0;

    if (torneo == NULL) {
        return NULL;
    }

    agregar_entrenador(torneo, entrenadores_f);
    fclose(entrenadores_f);

    return torneo;
}

void pedir_memoria(torneo_t* torneo){
    entrenador_t* auxiliar = NULL;
    auxiliar = realloc(torneo->entrenadores, ((unsigned)torneo->cantidad_entrenadores+1)*sizeof(entrenador_t));

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

        torneo->cantidad_entrenadores--;
        free(torneo->entrenadores[torneo->cantidad_entrenadores].pokemones);

        entrenador_t* auxiliar = realloc(torneo->entrenadores, ((unsigned)torneo->cantidad_entrenadores)*sizeof(entrenador_t));

        if (auxiliar == NULL){
            return;
        }

        torneo->entrenadores = auxiliar;
    }
}

void torneo_listar(torneo_t* torneo, void (*formatear_entrenador)(entrenador_t*)){
    for (int i = 0; i < torneo->cantidad_entrenadores; i++){
        formatear_entrenador(&torneo->entrenadores[i]);
    }  
}

//Hacer mas lindos los mostrar
void mostrar_nombre_entrenador(entrenador_t* entrenador){
    printf("Nombre del entrenador: %s\n", entrenador->nombre);
}
void mostrar_nombres_pokemones_entrenador(entrenador_t* entrenador){
    printf("Nombre entrenador: %s, nombre del primer pokemon: %s\n", entrenador->nombre, entrenador->pokemones[0].nombre);
    printf("Nombre entrenador: %s, nombre del segundo pokemon: %s\n", entrenador->nombre, entrenador->pokemones[1].nombre);
    printf("Nombre entrenador: %s, nombre del tercer pokemon: %s\n", entrenador->nombre,entrenador->pokemones[2].nombre);
}
void mostrar_fuerza_pokemones_entrenador(entrenador_t* entrenador){
    printf("Nombre entrenador: %s, fuerza del primer pokemon: %i\n", entrenador->nombre,entrenador->pokemones[0].fuerza);
    printf("Nombre entrenador: %s, fuerza del segundo pokemon: %i\n", entrenador->nombre,entrenador->pokemones[1].fuerza);
    printf("Nombre entrenador: %s, fuerza del tercer pokemon: %i\n", entrenador->nombre,entrenador->pokemones[2].fuerza);
}
void mostrar_agilidad_pokemones_entrenador(entrenador_t* entrenador){
    printf("Nombre entrenador: %s, agilidad del primer pokemon: %i\n", entrenador->nombre,entrenador->pokemones[0].agilidad);
    printf("Nombre entrenador: %s, agilidad del segundo pokemon: %i\n", entrenador->nombre,entrenador->pokemones[1].agilidad);
    printf("Nombre entrenador: %s, agilidad del tercer pokemon: %i\n", entrenador->nombre,entrenador->pokemones[2].agilidad);
}
void mostrar_inteligencia_pokemones_entrenador(entrenador_t* entrenador){
    printf("Nombre entrenador: %s, inteligencia del primer pokemon: %i\n", entrenador->nombre,entrenador->pokemones[0].inteligencia);
    printf("Nombre entrenador: %s, inteligencia del segundo pokemon: %i\n", entrenador->nombre,entrenador->pokemones[1].inteligencia);
    printf("Nombre entrenador: %s, inteligencia del tercer pokemon: %i\n", entrenador->nombre,entrenador->pokemones[2].inteligencia);
}
void mostrar_torneo(entrenador_t* entrenador){

    printf("Entrenador: %s\n", entrenador->nombre);
    printf("\tPokemon 1 Nombre: %s\n", entrenador->pokemones[0].nombre);
    printf("\tPokemon 1 Fuerza: %i\n", entrenador->pokemones[0].fuerza);
    printf("\tPokemon 1 Agilidad: %i\n", entrenador->pokemones[0].agilidad);
    printf("\tPokemon 1 Inteligencia: %i\n\n", entrenador->pokemones[0].inteligencia);
    printf("\tPokemon 2 Nombre: %s\n", entrenador->pokemones[1].nombre);
    printf("\tPokemon 2 Fuerza: %i\n", entrenador->pokemones[1].fuerza);
    printf("\tPokemon 2 Agilidad: %i\n", entrenador->pokemones[1].agilidad);
    printf("\tPokemon 2 Inteligencia: %i\n\n", entrenador->pokemones[1].inteligencia);
    printf("\tPokemon 3 Nombre: %s\n", entrenador->pokemones[2].nombre);
    printf("\tPokemon 3 Fuerza: %i\n", entrenador->pokemones[2].fuerza);
    printf("\tPokemon 3 Agilidad: %i\n", entrenador->pokemones[2].agilidad);
    printf("\tPokemon 3 Inteligencia: %i\n\n", entrenador->pokemones[2].inteligencia);
}

int main(){
    char* ruta = "archivo.txt";
    torneo_t* torneo = torneo_crear(ruta);
    torneo_listar(torneo, mostrar_torneo);
    torneo_jugar_ronda(torneo, ganador_inteligencia);
    torneo_listar(torneo, mostrar_torneo);
    torneo_destruir(torneo);
    return 0;
}


