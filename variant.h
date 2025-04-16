#ifndef VARIANT_H_INCLUDED
#define VARIANT_H_INCLUDED

#include <stddef.h>
#include <limits.h>
#include <math.h>
#include "my_bool.h"


#define MAX_DATA 1024
#define MAX_TOKEN 512
#define WORD_LENGTH 22
#define VARIANT_INIT {.type=TYPE_UNKNOWN,.value={0},.certeza=1.0}

typedef enum{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_LONG,
    TYPE_LONG_LONG,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_UNKNOWN
}DataType;

typedef union{
    int intValue;
    float floatValue;
    double doubleValue;
    long longValue;
    long long longLongValue;
    char charValue;
    char stringValue[MAX_DATA+1];
}DataValue;
/**
    *@struct Variant
    *@brief Almacena un valor de tipo variable(int,float,string,etc)
    */
typedef struct{
    DataType type;  ///<Tipo del dato almacenado
    DataValue value;///<Valor del dato
}Variant;

typedef struct Word_couter{
    char arr_string[MAX_DATA][WORD_LENGTH];
    int num_caracteres;
    int num_letras;
    int num_palabras;
    int letras_por_palabra_x[MAX_TOKEN];
    int letras_por_palabra_y[MAX_TOKEN];
}Word_couter;

///funcion que recibe la entrada en texto plano
size_t recibe_Dato(Word_couter* cp,const char* archivo);
size_t tokenizar(Word_couter* cp,const char* input);
///funcion que reconoce cada token por separado y los clasifica
void reconocer(Variant* variant,const char* input);
///imprime el contenido de una variable Variant
void imprime(Variant* variant);
///comparador de variables del tipo Variant
_bool Variant_Comparator(Variant* var1,Variant* var2);

#endif // VARIANT_H_INCLUDED
