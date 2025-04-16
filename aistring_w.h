#ifndef AISTRING_W_H_INCLUDED
#define AISTRING_W_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include "variant.h"
#include "my_bool.h"

#ifndef MAX_FILENAME
#define MAX_FILENAME 128
#endif /// MAX_FILENAME
#define MAX_VARIANTES 16
#define WORD_LENGTH 22
/**calificador de tipo para analisis comparativo*/
///define los articulos
typedef enum Tipo_cant{
    SING,
    PLUR,
    NONE
}Tipo_cant;
///define los verbos
typedef enum Tipo_tiempo{
    PASS,
    PRES,
    FUTR,
    INDETERMINADO
}Tipo_tiempo;
///califica el grado de la palabra o la oracion
typedef enum Tipo_grado{
    COMPARA,
    SUPERLA,
    POSIT,
    INTENS,
    INTERRG,
    NEGAT,
    RELAT,
    CUANTI,
    NON
}Tipo_grado;
///califica el tipo de persona de la que se habla
typedef enum Tipo_persona{
    PRIM,
    SEGU,
    TERC,
    NIN
}Tipo_persona;
///califica el genero de la palabra si lo tiene
typedef enum Tipo_genero{
    MASC,
    FEME,
    NEUT
}Tipo_genero;
///clasifica las palabras
typedef enum Tipo_palabra{
    PRON,
    ART,
    ADJT,
    SUST,
    VERB,
    PREG,
    ADV,
    SENS,
    PREP,
    POSE,
    RELT,
    NUM,
    CONJ,
    CONT,
    CUANT,
    DEMS,
    INDEFINIDO
}Tipo_palabra;
///calificador de tiempo verbal para analisis comparativo
typedef enum Tiempo_oracion{
    PASADO,
    PRESENTE,
    FUTURO,
    INFINITIVO
}Tiempo_oracion;
///estructura de datos ampliable para analisis de cada palabra
typedef struct Wd{
    char palabra[WORD_LENGTH];
    char significado[256];
    int num_relasionadas;
    int num_variantes;
    char variantes[MAX_VARIANTES][WORD_LENGTH];
    char relasionadas[MAX_VARIANTES][WORD_LENGTH];
    double valor_relasion[MAX_VARIANTES];
    Tipo_palabra Tipo;
    Tipo_cant Cant;
    Tipo_tiempo Tiempo;
    Tipo_genero Gen;
    Tipo_grado Grado;
    Tipo_persona Per;
}Wd;
///nodo para fraces
typedef struct Word{
    Wd palabra;
    struct Word* sig;
    struct Word* pre;
}Word;
///lista doble para contener fraces
typedef struct{
    Word* inicio;
    Word* cola;
}Frace;
///crea una nueva palabra para su analisis
Wd* crea_palabra(char* pala);
///asigna los elementos relevantes de dicha palabra
void inic_Wd(Wd* nuevaPalabra);
void asigna_palabra(Wd* nuevaPalabra);
void asignar_Tipo_A(Wd* nueva,const char* significado);
void asignar_Tipo_B(Wd* nueva,const char* significado);
_bool tiene_terminacion(const char* palabra,const char* terminacion[],int num_terminacion);
_bool es_sustantivo(const char* palabra);
_bool es_verbo(const char* palabra);
_bool es_adjetivo(const char* palabra);
_bool es_adverbio(const char* palabra);
_bool es_plural(const char* palabra);
_bool es_genero_femenino(const char* palabra);
_bool es_genero_masculino(const char* palabra);
Tipo_tiempo es_tiempo(const char* palabra);
void asignar_Tipo(Wd* nueva);
const char* tipo_a_texto(Tipo_palabra tipo);
const char* tiempo_a_texto(Tipo_tiempo tiempo);
const char* genero_a_texto(Tipo_genero genero);
const char* grado_a_texto(Tipo_grado grado);
///busca el archivo individual de cada palabra en BDLP
_bool buscar_palabra(Wd* nuevaPalabra);
///asigna variantes relacionales por contexto
void asignar_variante_relacional(Wd* nuevaPalabra,Word* temp);
void mostrar_detalle_Wd(Wd* palabra);
///crea un nodo de la lista doble Frace
Word* crear_Word(Wd nuevaPalabra);
///inicializa la lista (lista vacia)
void inic_Frace_Word(Frace* frace);
///agrega nodos al final de la lista
void insertar_append_Frace(Frace* frace,Wd nuevaPalabra);
///guarda la frace en un archivo unico de BDT
void guardar_Frace_respuesta(Frace* frace,const char* filename);
///carga el archivo para su analisis y posterior incersion en BDLP
void cargar_Frace_respuesta(Frace* frace,const char* filename);
///imprime una lista completa, uso en respuestas
void imprimir_Frace_completa(Frace* frace);
///metodo de eleccion primaria de BDT
_bool eleccion_primaria();
///eleccion aleatoria,caotica,para compensar "_duda"
DecisionState eleccion_secundaria(_bool eleccion,Wd* palabra_clave);
///Definicion de alternativa para switch de opciones
///de procesamiento BDT
Alternativa definicion_primaria(DecisionState* desicion);

DecisionState tomar_decision_aprendizaje(Wd* palabra);

void analizar_relacionar(Frace* frace);

void mostrar_estadistica(Frace* frace);

#endif // AISTRING_W_H_INCLUDED
