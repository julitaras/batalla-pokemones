#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "batallas.h"

/*Achicara el vector de entrenadores.
* Debe recibir el torneo y la posicion que se quiere sacar del vector. 
*/
void achicar_vector(torneo_t* torneo, int posicion){

    if(torneo->cantidad_entrenadores == 0){
        return;
    }

    for(int j = posicion; j < torneo->cantidad_entrenadores - 1; j++){
            
        entrenador_t aux = torneo->entrenadores[j+1];
        torneo->entrenadores[j+1] = torneo->entrenadores[j];
        torneo->entrenadores[j] = aux;
            
    }
    
    int ultimo = torneo->cantidad_entrenadores-1;
    
    torneo->cantidad_entrenadores--;

    free(torneo->entrenadores[ultimo].pokemones);
    
    entrenador_t* auxiliar = realloc(torneo->entrenadores, ((unsigned)torneo->cantidad_entrenadores)*sizeof(entrenador_t));
    
    if(auxiliar == NULL){
        return;
    }
    
    torneo->entrenadores = auxiliar;
}

/* Se pasa por parametro dos entrenadores.
*Ganara aquel que la sumatoria de inteligencia de sus pokemones sea mayor
* Devolvera 0 en caso de que gane el primer entrenador, 1 en caso del segundo.
*/
int ganador_inteligencia(entrenador_t* entrenador1, entrenador_t* entrenador2){

    int suma_inteligencias_entrenador1 = entrenador1->pokemones[0].inteligencia + entrenador1->pokemones[1].inteligencia + entrenador1->pokemones[2].inteligencia;
    int suma_inteligencias_entrenador2 = entrenador2->pokemones[0].inteligencia + entrenador2->pokemones[1].inteligencia + entrenador2->pokemones[2].inteligencia;
    
    if(suma_inteligencias_entrenador1 >= suma_inteligencias_entrenador2){
        return 0;
    }
    else{
        return 1;
    }
}


/*Devuelve el maximo de 3 numeros que se le pasen*/
int numero_mayor(int n1, int n2, int n3){
    if ( n1 >= n2 && n1 >= n3 ){
        return n1;
    }
    else{
        if ( n2 > n3 ){
            return n2;
        }
        else{
            return n3;
        }
    }
}

/*Se le pasa por parametros a dos entrenadores
* Ganara aquel que elija su pokemon con mayor fuerza
*Devolvera 0 en caso de que gane el primer entrenador, 1 en caso del segundo.
*/
int ganador_fuerza(entrenador_t* entrenador1, entrenador_t* entrenador2){

    int fuerza_entrenador1 = numero_mayor(entrenador1->pokemones[0].fuerza, entrenador1->pokemones[1].fuerza, entrenador1->pokemones[2].fuerza);
    int fuerza_entrenador2 = numero_mayor(entrenador2->pokemones[0].fuerza, entrenador2->pokemones[1].fuerza, entrenador2->pokemones[2].fuerza);
    
    if(fuerza_entrenador1 >= fuerza_entrenador2){
        return 0;
    }
    else{
        return 1;
    }
}

/* Se pasa por parametro dos entrenadores.
*Ganara aquel que la sumatoria de agilidades de sus pokemones sea mayor
* Devolvera 0 en caso de que gane el primer entrenador, 1 en caso del segundo.
*/
int ganador_agilidad(entrenador_t* entrenador1, entrenador_t* entrenador2){

    int suma_agilidades_entrenador1 = entrenador1->pokemones[0].agilidad + entrenador1->pokemones[1].agilidad + entrenador1->pokemones[2].agilidad;
    int suma_agilidades_entrenador2 = entrenador2->pokemones[0].agilidad + entrenador2->pokemones[1].agilidad + entrenador2->pokemones[2].agilidad;
    
    if(suma_agilidades_entrenador1 >= suma_agilidades_entrenador2){
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

    if(torneo == NULL){
        return -1;
    }

    if(torneo->cantidad_entrenadores == 1){
        return -1;
    }

    if(torneo->cantidad_entrenadores %2 != 0){
        for (int i = 0; i < torneo->cantidad_entrenadores - 1; i++){
            int ganador = ganador_batalla(&torneo->entrenadores[i], &torneo->entrenadores[i] + 1);
        
            if (ganador == 0){
                achicar_vector(torneo, i+1);
            }
            else{
                achicar_vector(torneo, i);
            }
        }
    }
    else{
        for (int i = 0; i < torneo->cantidad_entrenadores; i++){
            int ganador = ganador_batalla(&torneo->entrenadores[i], &torneo->entrenadores[i] + 1);
            
             if (ganador == 0){
                achicar_vector(torneo, i+1);
            }
            else{
                achicar_vector(torneo, i);
            }
        }
    }   
    torneo->ronda++;
    return 0;
}

void torneo_destruir(torneo_t* torneo){
    if(torneo == NULL){
        return;
    }

    for (int i = 0; i < torneo->cantidad_entrenadores; i++){
        free(torneo->entrenadores[i].pokemones);
    }
    free(torneo->entrenadores);
    free(torneo);
}

/* Se encarga de reservar espacio en el HEAP de la estructura de entrenador y pokemon
* En caso de no poder reservala, sale de la funcion
*/
void pedir_memoria(torneo_t* torneo){

    entrenador_t* auxiliar = NULL;
    auxiliar = realloc(torneo->entrenadores, ((unsigned)torneo->cantidad_entrenadores+1) * sizeof(entrenador_t));

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

/* Chequea que hay una segunda linea que leer, es decir, que haya un entrenador
* Si hay una linea que leer, devuelve true,  sino false
*/
bool hay_entrenador(FILE* entrenadores_f){
    entrenador_t entrenador;
    pokemon_t pokemones[3];
    entrenador.pokemones = pokemones;

    int leidos = fscanf(entrenadores_f, "%[^;];%[^;];%i;%i;%i;%[^;];%i;%i;%i;%[^;];%i;%i;%i\n", entrenador.nombre, entrenador.pokemones[0].nombre, &entrenador.pokemones[0].fuerza, &entrenador.pokemones[0].agilidad, &entrenador.pokemones[0].inteligencia, entrenador.pokemones[1].nombre, &entrenador.pokemones[1].fuerza, &entrenador.pokemones[1].agilidad, &entrenador.pokemones[1].inteligencia, entrenador.pokemones[2].nombre, &entrenador.pokemones[2].fuerza, &entrenador.pokemones[2].agilidad, &entrenador.pokemones[2].inteligencia);

    if (leidos == 13){
        return true;
    }

    return false;
}

/* Leera el archivo y copiara los datos a la estructura entrenador_t
* Devolvera la cantidad de caracteres leidos
*/
int parsear_archivo(FILE* entrenadores_f, entrenador_t* entrenador){
    int leidos = fscanf(entrenadores_f, "%[^;];%[^;];%i;%i;%i;%[^;];%i;%i;%i;%[^;];%i;%i;%i\n", entrenador->nombre, entrenador->pokemones[0].nombre, &entrenador->pokemones[0].fuerza, &entrenador->pokemones[0].agilidad, &entrenador->pokemones[0].inteligencia, entrenador->pokemones[1].nombre, &entrenador->pokemones[1].fuerza, &entrenador->pokemones[1].agilidad, &entrenador->pokemones[1].inteligencia, entrenador->pokemones[2].nombre, &entrenador->pokemones[2].fuerza, &entrenador->pokemones[2].agilidad, &entrenador->pokemones[2].inteligencia);

    return leidos;
}

/* Se encarga de copiar los datos que se encuentran en la estructura de entrenador auxiliar, 
* para pasar todo a la estructura de torneo que se encuentra en el HEAP
*/
void mapear_datos(torneo_t* torneo, entrenador_t entrenador){
    strcpy(torneo->entrenadores[torneo->cantidad_entrenadores].nombre, entrenador.nombre);
    strcpy(torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].nombre, entrenador.pokemones[0].nombre);
    strcpy(torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].nombre, entrenador.pokemones[1].nombre);
    strcpy(torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].nombre, entrenador.pokemones[2].nombre);
    torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].fuerza = entrenador.pokemones[0].fuerza;
    torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].fuerza = entrenador.pokemones[1].fuerza;
    torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].fuerza = entrenador.pokemones[2].fuerza;
    torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].agilidad = entrenador.pokemones[0].agilidad;
    torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].agilidad = entrenador.pokemones[1].agilidad;
    torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].agilidad = entrenador.pokemones[2].agilidad;
    torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[0].inteligencia = entrenador.pokemones[0].inteligencia;
    torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[1].inteligencia = entrenador.pokemones[1].inteligencia;
    torneo->entrenadores[torneo->cantidad_entrenadores].pokemones[2].inteligencia = entrenador.pokemones[2].inteligencia;
    torneo->cantidad_entrenadores++;
}


/* Se encarga de crear una estructura auxiliar en el stack, llama a la funcion
* parsear_archivo, si la misma nos devuleve 13 reservaremos la memoria con la funcion pedir_memoria
* y luego copiaremos los datos a la estructura en el HEAP con mapear_datos
*/
void agregar_entrenadores(FILE* entrenadores_f, torneo_t* torneo){

    entrenador_t entrenador;
    pokemon_t pokemones[3];
    entrenador.pokemones = pokemones;

    rewind(entrenadores_f);
    int leidos = parsear_archivo(entrenadores_f, &entrenador);

    while(leidos == 13){
        pedir_memoria(torneo);

        mapear_datos(torneo, entrenador);

        leidos = parsear_archivo(entrenadores_f, &entrenador);
    }
}

torneo_t* torneo_crear(char *ruta_archivo){

    FILE *entrenadores_f = fopen(ruta_archivo, "r");
        
    if (entrenadores_f == NULL) {
        return NULL;
    }

    if(!hay_entrenador(entrenadores_f)){
        fclose(entrenadores_f);
        return NULL;
    }

    torneo_t* torneo = NULL;
    torneo = malloc(1 * sizeof(torneo_t));

    if (torneo == NULL) {
        return NULL;
    }
    
    torneo->cantidad_entrenadores = 0;
    torneo->entrenadores = NULL;
    torneo->ronda = 0;

    agregar_entrenadores(entrenadores_f, torneo);

    fclose(entrenadores_f);

    return torneo;
}

void torneo_listar(torneo_t* torneo, void (*formatear_entrenador)(entrenador_t*)){

    if(torneo == NULL){
        return;
    }

    if(formatear_entrenador == NULL){
        return;
    }

    for (int i = 0; i < torneo->cantidad_entrenadores; i++){
        formatear_entrenador(&torneo->entrenadores[i]);
    }  
}

/* Muestra el nombre del entrenador
*/
void mostrar_nombre_entrenador(entrenador_t* entrenador){
    printf("Nombre del entrenador: %s\n", entrenador->nombre);
}

/* Muestra el nombre del entrenador y de sus pokemones
*/
void mostrar_nombres_pokemones_entrenador(entrenador_t* entrenador){
    printf("Nombre entrenador: %s, nombre del primer pokemon: %s\n", entrenador->nombre, entrenador->pokemones[0].nombre);
    printf("Nombre entrenador: %s, nombre del segundo pokemon: %s\n", entrenador->nombre, entrenador->pokemones[1].nombre);
    printf("Nombre entrenador: %s, nombre del tercer pokemon: %s\n", entrenador->nombre, entrenador->pokemones[2].nombre);
}

/* Muestra el nombre del entrenador, el de sus pokemones y su fuerza
*/
void mostrar_fuerza_pokemones_entrenador(entrenador_t* entrenador){
    printf("Nombre entrenador: %s, fuerza de %s: %i\n", entrenador->nombre, entrenador->pokemones[0].nombre, entrenador->pokemones[0].fuerza);
    printf("Nombre entrenador: %s, fuerza de %s: %i\n", entrenador->nombre, entrenador->pokemones[1].nombre, entrenador->pokemones[1].fuerza);
    printf("Nombre entrenador: %s, fuerza de %s: %i\n", entrenador->nombre, entrenador->pokemones[2].nombre, entrenador->pokemones[2].fuerza);
}


/* Muestra el nombre del entrenador, el de sus pokemones y su agilidad
*/
void mostrar_agilidad_pokemones_entrenador(entrenador_t* entrenador){
    printf("Nombre entrenador: %s, agilidad de %s: %i\n", entrenador->nombre, entrenador->pokemones[0].nombre, entrenador->pokemones[0].agilidad);
    printf("Nombre entrenador: %s, agilidad de %s: %i\n", entrenador->nombre, entrenador->pokemones[1].nombre, entrenador->pokemones[1].agilidad);
    printf("Nombre entrenador: %s, agilidad de %s: %i\n", entrenador->nombre, entrenador->pokemones[2].nombre, entrenador->pokemones[2].agilidad);
}


/* Muestra el nombre del entrenador, el de sus pokemones y su inteligencia
*/
void mostrar_inteligencia_pokemones_entrenador(entrenador_t* entrenador){
    printf("Nombre entrenador: %s, inteligencia de %s: %i\n", entrenador->nombre, entrenador->pokemones[0].nombre, entrenador->pokemones[0].inteligencia);
    printf("Nombre entrenador: %s, inteligencia de %s: %i\n", entrenador->nombre, entrenador->pokemones[1].nombre, entrenador->pokemones[1].inteligencia);
    printf("Nombre entrenador: %s, inteligencia de %s: %i\n", entrenador->nombre, entrenador->pokemones[2].nombre, entrenador->pokemones[2].inteligencia);
}


/* Muestra a los entrenadores con sus respectivos pokemones y sus habilidades
*/
void mostrar_torneo(entrenador_t* entrenador){
    printf("Entrenador: %s\n", entrenador->nombre);
    printf("\tPokemon 1:\n");
    printf("\t\t Nombre: %s\n", entrenador->pokemones[0].nombre);
    printf("\t\t Fuerza: %i\n", entrenador->pokemones[0].fuerza);
    printf("\t\t Agilidad: %i\n", entrenador->pokemones[0].agilidad);
    printf("\t\t Inteligencia: %i\n\n", entrenador->pokemones[0].inteligencia);
    printf("\tPokemon 2:\n");
    printf("\t\t Nombre: %s\n", entrenador->pokemones[1].nombre);
    printf("\t\t Fuerza: %i\n", entrenador->pokemones[1].fuerza);
    printf("\t\t Agilidad: %i\n", entrenador->pokemones[1].agilidad);
    printf("\t\t Inteligencia: %i\n\n", entrenador->pokemones[1].inteligencia);
    printf("\tPokemon 3:\n");
    printf("\t\t Nombre: %s\n", entrenador->pokemones[2].nombre);
    printf("\t\t Fuerza: %i\n", entrenador->pokemones[2].fuerza);
    printf("\t\t Agilidad: %i\n", entrenador->pokemones[2].agilidad);
    printf("\t\t Inteligencia: %i\n\n", entrenador->pokemones[2].inteligencia);
}