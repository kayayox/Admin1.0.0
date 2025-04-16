#ifndef PENSAMIENTO_PROFUNDO_H_INCLUDED
#define PENSAMIENTO_PROFUNDO_H_INCLUDED

#include "aistring_w.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

/**Identifica el tipo de patron para coincidir
con la oracion de ingreso*/
typedef enum Tipo_patron{
    AFIRMACION_SIMP,
    AFIRMACION_COMP,
    NEGACION_SIMP,
    NEGACION_COMP,
    PREGUNTA_SIMP,
    PREGUNTA_COMP,
    MIXTO,
    SENTENCIAS
}Tipo_patron;
///estructura que guarda cada patron
///estos seran algunos precargados y otros
///se estableceran por analisis
typedef struct Patron{
    int p[MAX_VARIANTES];
    Tipo_patron patern;
}Patron;
///lista para guardadr y cargar los patrones desde archivo
typedef struct Patrones{
    Patron actual;
    struct Patrones* sig;
}Patrones;
///generaran las listas de palabras a usar en el pensamiento
///obtenidas desde BDT de manera aleatoria
void genera_lista_Rand(Frace* fraceRand);
///genera un array con varias fraces con ekl mismo sustantivo
///con diferentes patrones
void genera_lista_Fraces(Frace* fraces,char arr_Fraces[MAX_VARIANTES][MAX_TOKEN]);
///crea un nodo del tipo Patron
Patrones* crear_Nodo(Patron p);
///carga una lista de patrones desde archivo
void cargar_patron(Patrones* p);
///guarda la lista de patrones en archivo
void guardar_patron(Patrones* actual);
///inserta un nuevo patron en la lista
void insertar_patron(Patrones** lista,Patron* actual);
///selecciona un patron a usar
void seleccionar_patron(Patron* actual);

#endif // PENSAMIENTO_PROFUNDO_H_INCLUDED
