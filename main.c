#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batallas.c"
#include "batallas.h"

int main(){
    char* ruta = "archivo.txt";
    torneo_t* torneo = torneo_crear(ruta);

    if (torneo != NULL){
        torneo_listar(torneo, mostrar_torneo);
        int exito = torneo_jugar_ronda(torneo, ganador_inteligencia);
        printf("Numero de ronda: %i\n", exito);
        exito = torneo_jugar_ronda(torneo, ganador_fuerza);
        printf("Numero de ronda: %i\n", exito);
        exito = torneo_jugar_ronda(torneo, ganador_agilidad);
        printf("Numero de ronda: %i\n", exito);
        printf("Ganador:\n");
        torneo_listar(torneo, mostrar_nombre_entrenador);
        torneo_destruir(torneo);
    }
    return 0;
}