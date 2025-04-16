#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "variant.h"

/**recepcion de datos por teclado (texto plano)*/
size_t recibe_Dato(Word_couter* cp,const char* archivo){
    int i,j=0,k=0,aux=0;
    char argv1[1024];
    cp->num_caracteres=strlen(archivo);
///tokenizasion del texto ingrezado
    for(i=0;i<cp->num_caracteres;i++){
        if(isalpha(archivo[i]) || isalnum(archivo[i]) || archivo[i]=='.' || archivo[i]==','){
            argv1[cp->num_letras]=archivo[i];
            cp->num_letras++;
        }
        else {
            cp->num_palabras++;
        }cp->letras_por_palabra_x[cp->num_palabras]=cp->num_letras;
    }
///calcula el tamaño de cada bloque
    for(i=1;i<=cp->num_palabras;i++){
        aux+=cp->letras_por_palabra_x[i-1];
        cp->letras_por_palabra_x[i]=cp->letras_por_palabra_x[i]-aux;
    }
    for(i=0;i<=cp->num_palabras;i++){
        if(cp->letras_por_palabra_x[i]==0){
            cp->letras_por_palabra_x[i];
        }else{
            cp->letras_por_palabra_y[j]=cp->letras_por_palabra_x[i];
            j++;
        }
    }
///ingresa cada caracter en su respectivo bloque
    for(i=0;i<cp->num_palabras+1;i++){
        for(int j=0;j<cp->letras_por_palabra_y[i];j++){
            cp->arr_string[i][j]=argv1[k];
            k++;
        }
    }
    for(i=0;i<cp->num_palabras+1;i++){
        for(int j=0;j<cp->letras_por_palabra_y[i];j++){///para verificar en pruebas
            ///printf("%c",arr_string[i][j]);
        }///printf("\n");
    }
    return cp->num_palabras+1;
}
///tokeniza por conjunto separado por ",.:;="
size_t tokenizar(Word_couter* cp,const char* input){
    int i,j=0,k=0,aux=0;
    char argv1[1024];
    cp->num_caracteres=strlen(input);
    for(i=0;i<cp->num_caracteres;i++){
        if((isalpha(input[i]) || isalnum(input[i])) || input[i]==' ' || ((isalnum(input[i+1]) && isalnum(input[i-1])) && (input[i]=='.'))){
            argv1[cp->num_letras]=input[i];
            cp->num_letras++;
        }
        else {
            cp->num_palabras++;
        }cp->letras_por_palabra_x[cp->num_palabras]=cp->num_letras;
    }
///calcula el tamaño de cada bloque
    for(i=1;i<=cp->num_palabras;i++){
        aux+=cp->letras_por_palabra_x[i-1];
        cp->letras_por_palabra_x[i]=cp->letras_por_palabra_x[i]-aux;
    }
    for(i=0;i<=cp->num_palabras;i++){
        if(cp->letras_por_palabra_x[i]==0){
            cp->letras_por_palabra_x[i];
        }else{
            cp->letras_por_palabra_y[j]=cp->letras_por_palabra_x[i];
            j++;
        }
    }
///ingresa cada caracter en su respectivo bloque
    for(i=0;i<cp->num_palabras+1;i++){
        for(int j=0;j<cp->letras_por_palabra_y[i];j++){
            cp->arr_string[i][j]=argv1[k];
            k++;
        }
    }
    for(i=0;i<cp->num_palabras+1;i++){
        for(int j=0;j<cp->letras_por_palabra_y[i];j++){///para verificar en pruebas
            ///printf("%c",arr_string[i][j]);
        }///printf("\n");
    }
    return cp->num_palabras+1;
}
///Etapa de clasificacion de datos int,float,double,char,string
///seran mas en el futuro(long,long long,etc)->listo
void reconocer(Variant* variant,const char* ptinput){
    if(!variant || !ptinput)return;
    char* endPtr;
    size_t j=0;
    char input[MAX_DATA+1];
    strncpy(input,ptinput,MAX_DATA);
    input[MAX_DATA]='\0';
    size_t n=strlen(input);
    ///verifica si todos los caracteres del bloque son letras
    for(size_t i=0;i<n;i++){
        if(isalpha(input[i])){
            j+=0;
        }
        else{
            j+=1;
        }
    }
    ///si es asi lo guarda como palabra
    if(j==0){
        variant->type=TYPE_STRING;
        strncpy(variant->value.stringValue,input,MAX_DATA-1);
        variant->value.stringValue[MAX_DATA-1]='\0';
    }else{///de lo contrario se empieza a clasificar en los diferentes formatos de numeros
        long long longLongValue=strtoll(input,&endPtr,10);
        if(*endPtr=='\0'){
            if(longLongValue>=INT_MIN && longLongValue<=INT_MAX){
                variant->type=TYPE_INT;
                variant->value.intValue=(int)longLongValue;
            }else if(longLongValue>=LONG_MIN && longLongValue<=LONG_MAX){
                variant->type=TYPE_LONG;
                variant->value.longValue=(long)longLongValue;
            }else{
                variant->type=TYPE_LONG_LONG;
                variant->value.longLongValue=longLongValue;
            }
            return;
        }
        float floatValue=strtof(input,&endPtr);
        if(*endPtr=='\0'){
            variant->type=TYPE_FLOAT;
            variant->value.floatValue=floatValue;
            return;
        }
        double doubleValue=strtod(input,&endPtr);
        if(*endPtr=='\0'){
            variant->type=TYPE_DOUBLE;
            variant->value.doubleValue=doubleValue;
            return;
        }
        if(strlen(input)==1){
            variant->type=TYPE_CHAR;
            variant->value.charValue=input[0];
            return;
        }
    }
    return;
}
///imprecion individual del dato reconocido
void imprime(Variant* variant){
    if(!variant){
        printf("ERROR: variable es NULL\n");
        return;
    }
    switch(variant->type){
        case TYPE_INT:
            printf("Entero: %d\n",variant->value.intValue);
            break;
        case TYPE_FLOAT:
            printf("Fraccion: %f\n",variant->value.floatValue);
            break;
        case TYPE_DOUBLE:
            printf("Doble precision: %lf\n",variant->value.doubleValue);
            break;
        case TYPE_LONG:
            printf("Entero long%ld\n",variant->value.longValue);
            break;
        case TYPE_LONG_LONG:
            printf("Entero long long%lld\n",variant->value.longLongValue);
            break;
        case TYPE_CHAR:
            printf("Caracter: %c\n",variant->value.charValue);
            break;
        case TYPE_STRING:
            printf("Palabra: %s\n",variant->value.stringValue);
            break;
        default:
            printf("No Data\n");
            break;
    }
}
///comparador de variable nueva typo "Variant"
_bool Variant_Comparator(Variant* var1,Variant* var2){
    if(var1->type!=var2->type)return _false;
    switch(var1->type){
        case TYPE_INT:
            return (var1->value.intValue==var2->value.intValue) ? _true : _false;
            break;
        case TYPE_FLOAT:
            return fabs(var1->value.floatValue-var2->value.floatValue)<1e-6 ? _true : _false;
            break;
        case TYPE_DOUBLE:
            return fabs(var1->value.doubleValue-var2->value.doubleValue)<1e-9 ? _true : _false;
            break;
        case TYPE_LONG:
            return (var1->value.longValue==var2->value.longValue) ? _true : _false;
            break;
        case TYPE_LONG_LONG:
            return (var1->value.longLongValue==var2->value.longLongValue) ? _true : _false;
            break;
        case TYPE_CHAR:
            return (strcmp(&var1->value.charValue,&var2->value.charValue)==0)? _true : _false;
            break;
        case TYPE_STRING:
            return (strcmp(var1->value.stringValue,var2->value.stringValue)==0) ? _true : _false;
            break;
        default:
            break;
    }
    return _false;
}
