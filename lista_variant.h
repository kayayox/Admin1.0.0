#ifndef LISTA_VARIANT_H_INCLUDED
#define LISTA_VARIANT_H_INCLUDED

/**
*@struct Var
*@brief Nodo de lista doble que almacena un Variant y punteros al siguiente/anterior*/

#include "variant.h"

typedef struct Var{
    Variant variable;
    struct Var* sig;
    struct Var* prev;
}Var;
typedef struct{
    Var* cabeza;
    Var* cola;
    size_t contador;
}Lista_Var;

///crea una variable clasificada
Var* crear_Var(Variant variable);
///inicializa la lista vacia de Variant
void inic_Lista_Doble(Lista_Var* lista_D);
///inserta una nueva variable en la lista
void insertar_append_Doble(Lista_Var* lista_D,Variant variable);
///busca una variable especifica en la lista
_bool buscar_en_lista_Doble(Lista_Var* listaActual,Variant* variable);
///elimina una variable de la lista
void eliminar_Variant(Lista_Var* lista_D,Variant* temp);
///guarda la lista en un archivo binario
///se usara luego para contexto
void guardar_Datos_variant(Lista_Var* datos);
///carga la lista desde el archivo binario
///tambien servira para contexto
void cargar_Datos_variant(Lista_Var* datos);

#endif // LISTA_VARIANT_H_INCLUDED
