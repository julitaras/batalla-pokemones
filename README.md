# Batalla de pokemones

## Introduccion
El programa se encarga de crear, cargar, listar y realizar batallas de pokemones.

Se generara un torneo en el cual se cargaran los participantes a traves de un ```archivo.txt```

En el mismo se encontraran los nombres de los participantes junto con los nombres de sus respectivos pokemones y sus habilidades (fuerza, agilidad, inteligencia).

Todos los participantes poseen 3 pokemones.

---
#### Acerca de listar
Se listara a los participantes, mostrando todos sus datos.

Ejemplo:
````c
Entrenador: Ash
        Pokemon 1:
                 Nombre: Pikachu
                 Fuerza: 40
                 Agilidad: 90
                 Inteligencia: 70

        Pokemon 2:
                 Nombre: Charizard
                 Fuerza: 76
                 Agilidad: 60
                 Inteligencia: 90

        Pokemon 3:
                 Nombre: Snorlax
                 Fuerza: 200
                 Agilidad: 10
                 Inteligencia: 10

Entrenador: Giovanni
        Pokemon 1:
                 Nombre: Nidoqueen
                 Fuerza: 100
                 Agilidad: 40
                 Inteligencia: 90

        Pokemon 2:
                 Nombre: Nidoking
                 Fuerza: 160
                 Agilidad: 62
                 Inteligencia: 76

        Pokemon 3:
                 Nombre: Rhydon
                 Fuerza: 180
                 Agilidad: 77
                 Inteligencia: 42
````

Tambien se podra listar:
- Mostrando solamente el nombre de los entrenadores
- Mostrando el nombre de los entrenadores junto con el nombre de sus pokemones
- Mostrando el nombre de los entranadores junto con el nombre de sus pokemones y su fuerza
- Mostrando el nombre de los entranadores junto con el nombre de sus pokemones y su agilidad
- Mostrando el nombre de los entranadores junto con el nombre de sus pokemones y su inteligencia

---

#### Acerca de las batallas
Los entrenadores se enfrentaran junto con sus pokemones los unos a los otros en diferentes batallas.

Iran pasando de ronda hasta que se obtenga el ganador del torneo.

Existen diferentes tipos de batallas:
- **La batalla de inteligencia**:

    Esta batalla la ganara el entrenador que posea la mayor sumatoria de la habilidad inteligencia de sus pokemones. 

- **La batalla de fuerza**:

    Los entrenadores eligiran el pokemon con mas fuerza, en el enfrentamiento ganara el que mayor fuerza tenga.

- **La batalla de agilidad**:

    Esta batalla la ganara el entrenador que posea la mayor sumatoria de la habilidad agilidad de sus pokemones. 

---

## ¿Cómo compilar ?

Compilamos haciendo:
````c
 gcc main.c -Wall -Werror -Wconversion -std=c99 -o torneo_pokemon
````

Ejecutamos el programa haciendo:

`````c
./torneo_pokemon
`````

---
## Explicacion de conceptos 

1. **Punteros:**

    - Lo utilizamos para apuntar a una variable o estructura que se encuentra en otra parte de la memoria.

    - En este caso lo utilice para apuntar a una estructura que cree en el ```heap``` .

        Ejemplo:

        ````c
        entrenador_t* auxiliar = NULL;
        ````

2. **Aritmética de punteros:**

    - Lo utilizamos para poder acceder a por ejemplo el siguiente valor del puntero

    - En este caso lo use para poder acceder a dos entrenadores a la vez, mientras iteraba.

        Ejemplo:

        `````c
        for (int i = 0; i < torneo->cantidad_entrenadores - 1; i++){
            int ganador = ganador_batalla(&torneo->entrenadores[i], &torneo->entrenadores[i] + 1);

            if (ganador == 0){
                achicar_vector(torneo, i+1);
            }
            else{
                achicar_vector(torneo, i);
            }
        }
        `````
3. **Punteros a funciones:**

    - Es la direccion de donde se encuentra una funcion en especifico. 
    
    - Nos permite ejecutar la funcion desde cualquier parte del programa.

    - Las funciones deben cumplir con la firma que se pasa por parametro.

    - En este caso, lo utilizo en ```torneo_jugar_ronda```y en ```torneo_listar```.
    
    - Esto nos permite "perzonalizar" la funcion de alguna manera, ya que respetanto la firma puedo por ejemplo elegir de que manera listar o de que manera se jugara la ronda.

        Ejemplo:

        `````c
        void torneo_listar(torneo_t* torneo, void (*formatear_entrenador)(entrenador_t*)){

            if(formatear_entrenador == NULL){
                return;
            }

            for (int i = 0; i < torneo->cantidad_entrenadores; i++){
                formatear_entrenador(&torneo->entrenadores[i]);
            }  
        }

        void mostrar_nombre_entrenador(entrenador_t* entrenador){
            printf("Nombre del entrenador: %s\n", entrenador->nombre);
        }
        `````

4. **Malloc y Realloc:**
    
    - Son funciones que utilizamos para pedir memoria dinamica, es decir para reservar un espacio de memoria en el ```heap```.

    - En este caso lo use para reservar en el heap las estructuras necesarias para poder crear el torneo.

    - Con realloc podemos agrandar o achicar el bloque de memoria que reservamos anteriormente. 

        Ejemplo ```malloc```:

        `````c
            torneo_t* torneo = NULL;
            torneo = malloc(1 * sizeof(torneo_t));

            if (torneo == NULL) {
                return NULL;
            }
        `````

        Ejemplo ```realloc```:

        ````c
        entrenador_t* auxiliar = NULL;
        auxiliar = realloc(torneo->entrenadores, ((unsigned)torneo->cantidad_entrenadores+1) * sizeof(entrenador_t));

        if (auxiliar == NULL ){
            return;
        }

        torneo->entrenadores = auxiliar;
        ````
