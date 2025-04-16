/**###############################################################
07 Abril 2025                                                    #
    proyecto prototipo "Admin" version 5.1.0                     #
    Autor: Soubhi Khayat Najjar                                  #
    E-mail: kayayox@gmail.com                                    #
    hasta la 5.0.1 SACPD(Sistema Automatizado                    #
    de Clasificacion y Procesamiento de Datos)                   #
    Ahora                                                        #
    prueba de concepto de SACPD con SADAA                        #
    (Sistema de Administracion de Datos y Aprendisaje Autonomo   #
##################################################################*/

#include "manejador.h"
#include "aistring_F.h"
#include "aistring_w.h"
#include <locale.h>
#include <time.h>

int main()
{
/**esto sera la base para la celula(neurona)
falda depurar algunas cosas,realizar revicion exaustiva
de cada funcion y realizar pruebas "hay segmentacion"*////listo!
///esto en adelante sera un threand de cuatro que se ejecutaran por entrada
    setlocale(LC_ALL,"es_ESUTF-8");
    srand(time(NULL));
    Frace* frace=(Frace*)malloc(sizeof(Frace));
    inic_Frace_Word(frace);
    Lista_Var* lista_actual=(Lista_Var*)malloc(sizeof(Lista_Var));
    if(lista_actual!=NULL){
        inic_Lista_Doble(lista_actual);
    }
    cargar_Datos_variant(lista_actual);

    printf("Sistema Autonomo de Aprendizaje\n");
    printf("--------------------------------\n");
    printf("Modo Aprendisaje Activado\n\n");

    while(_true){
        mostrar_menu_principal();
        proceso_aprendizaje(frace,lista_actual);
    }

    free(frace);
    free(lista_actual);
    return 0;
}
