#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batallas.c"

int main(){
    char* ruta = "archivo.txt";
    torneo_t* torneo = torneo_crear(ruta);

    if (torneo != NULL){
        printf("Presentamos a los participantes del torneo:\n");
        torneo_listar(torneo, mostrar_torneo);
        int exito = torneo_jugar_ronda(torneo, ganador_inteligencia);
        printf("\nLos participantes que quedan despues de la ronda de inteligencia:\n");
        torneo_listar(torneo, mostrar_nombres_pokemones_entrenador);
        printf("\nMostramos la agilidad de los pokemones de los entrenadores:\n");
        torneo_listar(torneo, mostrar_agilidad_pokemones_entrenador);
        exito = torneo_jugar_ronda(torneo, ganador_agilidad);
        printf("\nMostramos la fuerza de los pokemones de los entrenadores:\n");
        torneo_listar(torneo, mostrar_fuerza_pokemones_entrenador);
        exito = torneo_jugar_ronda(torneo, ganador_fuerza);
        if(exito == -1){
            printf("\nTenemos el ganador del torneo:\t");
            torneo_listar(torneo, mostrar_nombre_entrenador);
        }
        torneo_destruir(torneo);
    }
    return 0;
}