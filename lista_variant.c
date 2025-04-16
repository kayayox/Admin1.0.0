#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lista_variant.h"

/**modulo para la creacion y el manejo de listas
de datos mixtas o por tipo, doblemente enlazadas,
y las diferentes funciones para su manipulacion*/

Var* crear_Var(Variant variable){
    Var* nuevoVar=(Var*)malloc(sizeof(Var));
    if(nuevoVar==NULL){
        printf("ERROR: no se pudo asignar memoria\n");
        return NULL;
    }
    nuevoVar->variable=variable;
    nuevoVar->sig=NULL;
    nuevoVar->prev=NULL;
    return nuevoVar;
}
/// Función para inicializar la lista
void inic_Lista_Doble(Lista_Var* lista_D){
    lista_D->cabeza=NULL;
    lista_D->cola=NULL;
    lista_D->contador=0;
}
/// Función para insertar un usuario al final de la lista
void insertar_append_Doble(Lista_Var* lista_D,Variant variable){
    Var* nuevoVar=crear_Var(variable);
    if(!nuevoVar)return;
    if(lista_D->cola){
        lista_D->cola->sig=nuevoVar;
    }else{
        lista_D->cabeza=nuevoVar;
    }
    lista_D->cola=nuevoVar;
    lista_D->contador++;
}
///funcion para buscar en lista y evitar duplicados de ser necesario
_bool buscar_en_lista_Doble(Lista_Var* listaActual,Variant* variable){
    if(!listaActual || !variable)return _duda;
    Var* actual=listaActual->cabeza;
    listaActual->contador=0;
    while(actual!=NULL){
        if(Variant_Comparator(&actual->variable,variable)==_true){
            return _true;
        }
        actual=actual->sig;
    }
    return _false;
}
/// Función para eliminar un usuario por nombre
void eliminar_Variant(Lista_Var* lista_D,Variant* temp){
    if(lista_D->cabeza==NULL || !temp || lista_D->contador==0){
        printf("La lista está vacía.\n");
        return;
    }
    Var* actual=lista_D->cabeza;
    while(actual!=NULL){
        if(Variant_Comparator(&actual->variable,temp)==_true){
            if(actual->prev!=NULL){
                actual->prev->sig=actual->sig;
            }else{
                lista_D->cabeza=actual->sig;
            }
            if(actual->sig!=NULL){
                actual->sig->prev=actual->prev;
            }else{
                lista_D->cola=actual->prev;
            }
            free(actual);
            printf("valor eliminado.\n");
            temp=NULL;
            lista_D->contador--;
            return;
        }
        actual=actual->sig;
    }
    printf("valor no encontrado.\n");
}
///Función para imprimir la lista desde el inicio al final
void imprimirLista_D_Adelante(Lista_Var* lista_D) {
    if(lista_D->cabeza==NULL){
        printf("La lista está vacía.\n");
        return;
    }
    Var* actual=lista_D->cabeza;
    while(actual!=NULL){
        imprime(&actual->variable);
        actual=actual->sig;
    }
}
///guarda una lista corrida de los ingresos del usuario
void guardar_Datos_variant(Lista_Var* datos){
    FILE* fp=fopen(".-data.dat","wb");
    if(fp==NULL){
        printf("ERROR...al abrir el Archivo\n");
        return;
    }
    Var* actual=datos->cabeza;
    while(actual!=NULL){
        fwrite(&actual->variable,sizeof(Variant),1,fp);
        actual=actual->sig;
    }
    fclose(fp);
}
///recupera la lista de entrada de datos del usuario
void cargar_Datos_variant(Lista_Var* datos){
    FILE* fp=fopen(".-data.dat","rb");
    if(fp==NULL){
        printf("ERROR...al abrir el Archivo\n");
        return;
    }
    Variant variable;
    while(fread(&variable,sizeof(Variant),1,fp)){
        insertar_append_Doble(datos,variable);
    }
    fclose(fp);
}
