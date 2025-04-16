#ifndef AISTRING_F_H_INCLUDED
#define AISTRING_F_H_INCLUDED

#include "aistring_w.h"
#define MAX_BLOQUES 15

/**Estructuras para el manejo de oraciones, patrones,
relaciones entre oraciones dentro de una misma idea,
creacion de ideas BDTT y BDLP*/

///patron tipo en la sentencia(oracion)
typedef struct SENS_T{
    Tipo_palabra A[MAX_BLOQUES];
}SENS_T;
///bloque fundamental de analisis
typedef struct Bloque{
    char block[WORD_LENGTH];
    Tipo_palabra typo_b;
}Bloque;
///contiene la oracion, el tiempo verbal y el patron
typedef struct Oracion{
    Bloque b[MAX_BLOQUES];///tamaño maximo de oracion 15 palabras
    Tiempo_oracion tim;
    Bloque clave;
    SENS_T Typos;
    float frecuencia;///veces que se usa este patron
    int num_bloques;///cantidad de palabras en la oracion
}Oracion;
///estructura relacional en el texto(parrafo)
typedef struct Sentencia{
    Oracion idea;
    struct Sentencia* izq;///no contiene sustantivo
    struct Sentencia* der;///contiene sustantivo
    struct Sentencia* bro;///contiene el mismo sustantivo de origen
    struct Sentencia* raiz_orig;///origende la oracion actual
    struct Sentencia* raiz_pri;///origen del parrafo
}Sentencia;
///cadena que une indistintamente el parrafo oracion por oracion
typedef struct{
    Sentencia oracion_actual;
    Sentencia* sig;
}Texto;
///Genera una oracion para estructura sentencia
Oracion* cargar_Oracion_de_Frace(Frace* fraceActual);
///Inicializa una Sentencia con una oOracion
Sentencia* inic_vinculo_oracion(Oracion* oracionActual);
///Crea los siguientes vinculos(insercion de nodos)
Sentencia* crea_vinculo_oracion(Oracion* oracionActual,Sentencia* anterior);
///imprime arbol
void imprime_texto(Sentencia* raiz);
///guarda una oracion
void guardar_Oracion(Oracion* actual);
///Guarda cada oracion dependiendo de su sustantivo
void guardar_Sentencia(Sentencia* actual);
///Guarda cada oracion dependiendo de su sustantivo
void guardar_Sentencia(Sentencia* raiz);
///Carga una oracion dependiendo de un sustantivo clave
void cargar_Sentencia(Sentencia** actual,Wd* clave);
///prototipo de generacion de respuesta para prueba preliminar
///sera sustituida por funciones mas complejas al terminar los modulos de pensamiento profundo
void generar_respuesta_autonoma(Frace* frace);

#endif // AISTRING_F_H_INCLUDED
