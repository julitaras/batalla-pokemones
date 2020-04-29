#include <stdio.h>
#include "batallas.h"

// %[^;]; todo lo que sea distinto al punto y coma
// void main(){

//     printf("Hello World!");
// }

// torneo_t *torneo_crear(char *ruta_archivo) {
void main(){




    //Debo leer el archivo txt y pasar los datos a la estructura creada en el HEAP
    FILE *entrenadores_f = fopen("archivo.txt", "r");
    if (entrenadores_f == NULL) {
        return;
    }
    //Sabemos  que la estructura del archivo txt, es la de siguiente manera: nombre_entrenador ;nombre_p1;fuerza_p1;agilidad_p1;inteligencia_p1

    //vOY LEYENDO DE A UN POKEMON, SABIENDO QUE HAY 3 POKEMONS.DEBO CHEQUEAR QUE ENTONCES HAYA 3 POKEMOSN SINO HAY TRES POKEMONS POR ENTRENADOR ENTONCES CIERRO EL ARCHIVO
    char nombre_entrenador[50];
    char nombre_pokemon1[50];
    int fuerza;
    int agilidad;
    int inteligencia;

    char nombre_pokemon2[50];
    int fuerza2;
    int agilidad2;
    int inteligencia2;

    char nombre_pokemon3[50];
    int fuerza3;
    int agilidad3;
    int inteligencia3;



/////////////////////////////////////////////////////
    int cantidad_entrenadores = 0;

    entrenador_t *entrenadores = NULL;
    entrenadores = malloc(sizeof(entrenador_t));


    pokemon_t *pokemons = NULL;
    pokemons = malloc(3 * sizeof(pokemon_t));

        int leidos = fscanf(entrenadores_f, "%[^;];%[^;];%i;%i;%i;%[^;];%i;%i;%i;%[^;];%i;%i;%i\n", entrenadores->nombre, pokemons[0].nombre, pokemons[0].fuerza, pokemons[0].agilidad, pokemons[0].inteligencia, pokemons[1].nombre, pokemons[1].fuerza, pokemons[1].agilidad, pokemons[1].inteligencia, pokemons[2].nombre, pokemons[2].fuerza, pokemons[2].agilidad, pokemons[2].inteligencia);

        while (leidos == 13){
            entrenadores = realloc(entrenadores, (cantidad_entrenadores + 1) * sizeof(entrenador_t));

            if (entrenadores == NULL) {
                return;
            }

            cantidad_entrenadores++;
        }
    
//////////////////////////////////////////////////











    int leidos = fscanf(entrenadores_f, "%[^;];%[^;];%i;%i;%i;%[^;];%i;%i;%i;%[^;];%i;%i;%i\n", nombre_entrenador, nombre_pokemon1, &fuerza, &agilidad, &inteligencia, nombre_pokemon2, &fuerza2, &agilidad2, &inteligencia2, nombre_pokemon3, &fuerza3, &agilidad3, &inteligencia3);
    while (leidos == 13){
        cantidad_entrenadores++;

        // printf("Nombre del entrenador: %s\n", nombre_entrenador);
        // printf("Nombre del pokemon: %s\n", nombre_pokemon1);
        // printf("Fuerza del pokemon: %i\n", fuerza);
        // printf("Ageilidad del pokemon: %i\n", agilidad);
        // printf("Inteligencia del pokemon: %i\n\n", inteligencia);
        leidos = fscanf(entrenadores_f, "%[^;];%[^;];%i;%i;%i;%[^;];%i;%i;%i;%[^;];%i;%i;%i\n", nombre_entrenador, nombre_pokemon1, &fuerza, &agilidad, &inteligencia, nombre_pokemon2, &fuerza2, &agilidad2, &inteligencia2, nombre_pokemon3, &fuerza3, &agilidad3, &inteligencia3);
    }
        printf("Hay %i entrenadores anotados", cantidad_entrenadores);


    fclose(entrenadores_f);

    // pedir memoria en el HEAP con la estructura de torneo

     torneo_t *torneo = NULL;
     torneo = malloc(sizeof(torneo_t));

     if (torneo == NULL) {
         return NULL;
     }
    // // Como la estructura del torneo tiene entrenadores que es un puntero a la estructura
    // //Deberia hacer un realloc por cada vez que hay
    // entrenador_t *entrenadores = NULL;
    // entrenadores = malloc(torneo->cantidad_entrenadores * sizeof(entrenador_t));
    // if (entrenadores == NULL) {
    //     return NULL;
    // }
    // // Como la estructura del entrenador tiene pokemones que es un puntero a la estructura
    // pokemon_t *pokemones = NULL;
    // pokemones = malloc(3 * sizeof(pokemon_t));
    // if (pokemones == NULL) {
    //     return NULL;
    // }
}

// void torneo_destruir(torneo_t *torneo) {
//     //Deberia liberar a los pokemones, luego entrenadores y luego torneo
//     free(torneo);
// }


void mostrar_torneo(torneo_t * torneo){
    printf("El torneo tiene:", torneo->cantidad_entrenadores);
    for (int i = 0; i < torneo->cantidad_entrenadores; i++)
    {
        printf("Entrenadores son: ", torneo->entrenadores[i]);
        printf("Con sus pokemones:", torneo->entrenadores[i].pokemones[i]);
    }

}

void agregar_entrenador(torneo_t *torneo){
    
    FILE *entrenadores_f = fopen("archivo.txt", "r");
    
    if (entrenadores_f == NULL) {
        return;
    }
    
    void* auxiliar = realloc(torneo->entrenadores, (torneo->cantidad_entrenadores+1)*sizeof(entrenador_t));

    if (auxiliar == NULL ){
        return;
    }

    torneo->entrenadores = auxiliar;

    pokemon_t *pokemons = NULL;
    pokemons = malloc(3 * sizeof(pokemon_t));
    
    if (pokemons == NULL){
        return;
    }

    torneo->entrenadores->pokemones = pokemons;
    
    int leidos = fscanf(entrenadores_f, "%[^;];%[^;];%i;%i;%i;%[^;];%i;%i;%i;%[^;];%i;%i;%i\n", torneo->entrenadores->nombre, torneo->entrenadores->pokemones[0].nombre, torneo->entrenadores->pokemones[0].fuerza, torneo->entrenadores->pokemones[0].agilidad, torneo->entrenadores->pokemones[0].inteligencia, torneo->entrenadores->pokemones[1].nombre, torneo->entrenadores->pokemones[1].fuerza, torneo->entrenadores->pokemones[1].agilidad, torneo->entrenadores->pokemones[1].inteligencia, torneo->entrenadores->pokemones[2].nombre, torneo->entrenadores->pokemones[2].fuerza, torneo->entrenadores->pokemones[2].agilidad, torneo->entrenadores->pokemones[2].inteligencia);
        while (leidos == 13 )
        {
            mostrar_torneo(&torneo);
        }       
}
    