#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gestor_archivos.h"
#include "lista_variant.h"

/**modulo para la manipulasion de Archivos BDT
//Base de Datos Temporal
//guarda cada variable reconocida en su respectivo archivo*/
void guardar(Variant* variant){
    char filename[MAX_FILENAME];
    FILE* fp;
    switch(variant->type){
        case TYPE_INT:
            sprintf(filename,"._temp_int");
            fp=fopen(filename,"ab");
            fwrite(&variant->value.intValue,sizeof(int),1,fp);
            fclose(fp);
            break;
        case TYPE_FLOAT:
            sprintf(filename,"._temp_float");
            fp=fopen(filename,"ab");
            fwrite(&variant->value.floatValue,sizeof(float),1,fp);
            fclose(fp);
            break;
        case TYPE_DOUBLE:
            sprintf(filename,"._temp_double");
            fp=fopen(filename,"ab");
            fwrite(&variant->value.doubleValue,sizeof(double),1,fp);
            fclose(fp);
            break;
        case TYPE_LONG:
            sprintf(filename,"._temp_long");
            fp=fopen(filename,"ab");
            fwrite(&variant->value.longValue,sizeof(long),1,fp);
            fclose(fp);
        break;
            case TYPE_LONG_LONG:
            sprintf(filename,"._temp_long_long");
            fp=fopen(filename,"ab");
            fwrite(&variant->value.longLongValue,sizeof(long long),1,fp);
            fclose(fp);
            break;
        case TYPE_CHAR:
            sprintf(filename,"._temp_char");
            fp=fopen(filename,"ab");
            fwrite(&variant->value.charValue,sizeof(char),1,fp);
            fclose(fp);
            break;
        case TYPE_STRING:
            sprintf(filename,"._temp_string");
            fp=fopen(filename,"ab");
            if(variant->value.stringValue[strlen(variant->value.stringValue)-1]=='\n')variant->value.stringValue[strlen(variant->value.stringValue)-1]='\0';
            fwrite(&variant->value.stringValue,1024*sizeof(char),1,fp);
            fclose(fp);
            break;
        default:
            printf("No Data\n");
            break;
    }
}
///Guardar tokens de entrada
void guardar_tokens(char arr_tokens[MAX_DATA][MAX_TOKEN],size_t len){
    FILE* fp=fopen(".tokens_temp","a");
    if(!fp)return;
    for(size_t i=0;i<len;i++){
        fprintf(fp,"%s|",arr_tokens[i]);
    }
    fclose(fp);
}
///cargar tokens desde archivo
void cargar_tokens(char arr_tokens[MAX_DATA][MAX_TOKEN],size_t* len){
    FILE* fp=fopen(".tokens_temp","r");
    if(!fp)return;
    size_t cantidad=0;
    while(!feof(fp)){
        int contado=fgetc(fp);
        if(contado=='|')cantidad++;
    }
    fseek(fp,0,SEEK_SET);
    char leido[MAX_DATA*MAX_TOKEN];
    while(fgets(leido,MAX_DATA*MAX_TOKEN,fp)){
        char* token=strtok(leido,"|");
        strncpy(arr_tokens[(*len)++],token,strlen(token));
        arr_tokens[*len-1][strlen(arr_tokens[*len-1])+1]='\0';
        for(size_t i=0;i<(cantidad-1);i++){
            token=strtok(NULL,"|");
            strncpy(arr_tokens[(*len)++],token,strlen(token)+1);
            arr_tokens[*len-1][strlen(arr_tokens[*len-1])+1]='\0';
        }
    }
    fclose(fp);
}
///carga del archivo los dastos (int) en un array
size_t cargar_int(int* arr_int){
    char filename[MAX_FILENAME];
    sprintf(filename,"._temp_int");
    int arr_temp=0;
    size_t i=0;
    FILE* fp=fopen(filename,"rb");
    if(!fp){
        printf("ERROR No Data...\n");
    }
    else{
        while(fread(&arr_temp,sizeof(int),1,fp)){
            arr_int[i]=arr_temp;
            i++;
        }
        fclose(fp);
    }
    return i;
}
///carga del archivo los dastos (float) en un array
size_t cargar_float(float* arr_float){
    char filename[MAX_FILENAME];
    sprintf(filename,"._temp_float");
    float arr_temp=0;
    size_t i=0;
    FILE* fp=fopen(filename,"rb");
    if(!fp){
        printf("ERROR No Data...\n");
    }
    else{
        while(fread(&arr_temp,sizeof(float),1,fp)){
            arr_float[i]=arr_temp;
            i++;
        }
        fclose(fp);
    }
    return i;
}
///carga del archivo los dastos (double) en un array
size_t cargar_double(double* arr_double){
    char filename[MAX_FILENAME];
    sprintf(filename,"._temp_double");
    double arr_temp=0;
    size_t i=0;
    FILE* fp=fopen(filename,"rb");
    if(!fp){
        printf("ERROR No Data...\n");
    }
    else{
        while(fread(&arr_temp,sizeof(double),1,fp)){
            arr_double[i]=arr_temp;
            i++;
        }
        fclose(fp);
    }
    return i;
}
///carga del archivo los dastos (char) en un array
size_t cargar_char(char* arr_char){
    char filename[MAX_FILENAME];
    sprintf(filename,"._temp_char");
    char arr_temp=0;
    size_t i=0;
    FILE* fp=fopen(filename,"rb");
    if(!fp){
        printf("ERROR No Data...\n");
    }
    else{
        while(fread(&arr_temp,sizeof(char),1,fp)){
            arr_char[i]=arr_temp;
            i++;
        }
        fclose(fp);
    }
    return i;
}
size_t cargar_long(long* arr_long){
    char filename[MAX_FILENAME];
    sprintf(filename,"._temp_long");
    long arr_temp=0;
    size_t i=0;
    FILE* fp=fopen(filename,"rb");
    if(!fp){
        printf("ERROR No Data...\n");
    }
    else{
        while(fread(&arr_temp,sizeof(long),1,fp)){
            arr_long[i]=arr_temp;
            i++;
        }
        fclose(fp);
    }
    return i;
}
size_t cargar_long_long(long long* arr_long_long){
    char filename[MAX_FILENAME];
    sprintf(filename,"._temp_long_long");
    long long arr_temp=0;
    size_t i=0;
    FILE* fp=fopen(filename,"rb");
    if(!fp){
        printf("ERROR No Data...\n");
    }
    else{
        while(fread(&arr_temp,sizeof(long long),1,fp)){
            arr_long_long[i]=arr_temp;
            i++;
        }
        fclose(fp);
    }
    return i;
}
///carga del archivo los dastos (string) en un array
size_t cargar_string(char arr_string[MAX_DATA][WORD_LENGTH]){
    if(!arr_string)return 0;
    char filename[MAX_FILENAME+1];
    snprintf(filename,sizeof(filename),"._temp_string");
    size_t i=0;
    FILE* fp=fopen(filename,"rb");
    if(!fp){
        printf("ERROR No Data...\n");
        return 0;
    }
    else{
        Variant variable;
        variable.type=4;
        while(i<MAX_DATA && fread(&variable.value.stringValue,1024*sizeof(char),1,fp)==1){
            strncpy(arr_string[i],variable.value.stringValue,MAX_DATA);
            arr_string[i][MAX_DATA-1]='\0';
            i++;
        }fclose(fp);
    }
    return i;
}
void free_archivo_variant(int flag){
    char filename[MAX_FILENAME];
    FILE* fp;
    switch(flag){
        case TYPE_INT:
            sprintf(filename,"._temp_int");
            fp=fopen(filename,"wb");
            fclose(fp);
            break;
        case TYPE_FLOAT:
            sprintf(filename,"._temp_float");
            fp=fopen(filename,"wb");
            fclose(fp);
            break;
        case TYPE_DOUBLE:
            sprintf(filename,"._temp_double");
            fp=fopen(filename,"wb");
            fclose(fp);
            break;
        case TYPE_LONG:
            sprintf(filename,"._temp_long");
            fp=fopen(filename,"wb");
            fclose(fp);
        break;
            case TYPE_LONG_LONG:
            sprintf(filename,"._temp_long_long");
            fp=fopen(filename,"wb");
            fclose(fp);
            break;
        case TYPE_CHAR:
            sprintf(filename,"._temp_char");
            fp=fopen(filename,"wb");
            fclose(fp);
            break;
        case TYPE_STRING:
            sprintf(filename,"._temp_string");
            fp=fopen(filename,"w");
            fclose(fp);
            break;
        case TYPE_UNKNOWN:
            fp=fopen(".tokens_temp","wb");
            break;
        default:
            printf("No Data\n");
            break;
    }
}
///proximamente funciones que carguen de los archivos
///a listas de "Variant"
