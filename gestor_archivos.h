#ifndef GESTOR_ARCHIVOS_H_INCLUDED
#define GESTOR_ARCHIVOS_H_INCLUDED

#include "variant.h"

#ifndef MAX_FILENAME
#define MAX_FILENAME 128
#endif /// MAX_FILENAME

void guardar(Variant* variant);
void guardar_tokens(char arr_tokens[MAX_DATA][MAX_TOKEN],size_t len);
size_t cargar_int(int* arr_int);
size_t cargar_float(float* arr_float);
size_t cargar_double(double* arr_double);
size_t cargar_char(char* arr_char);
size_t cargar_string(char arr_string[MAX_DATA][WORD_LENGTH]);
void free_archivo_variant(int flag);


#endif // GESTOR_ARCHIVOS_H_INCLUDED
