#ifndef MANEJADOR_H_INCLUDED
#define MANEJADOR_H_INCLUDED

#include "my_bool.h"
#include "lista_variant.h"
#include "gestor_archivos.h"
#include "aistring_F.h"

///recibir datos desde el teclado y generar los temp de variant y la lista acumulativa
void iniciar_recepcion(Lista_Var* lista_actual,Word_couter* cp);
///primera revision de palabras recibidas,genera los binarios de palabras nuevas en crudo
void iniciar_revicion_word(Frace* frace_actual);
///segunda revision de palabras,limpieza y estilisacion de datos binarios en BDT
void iniciar_segunda_revicion_word(Frace* frace);
///asigna variantes por contexto
void completa_variantes_contexto(Word* temp,Wd* nueva);
///Define relaciones y valores por comparacion
void proceso_aprendizaje(Frace* frace,Lista_Var* lista_actual);

#endif // MANEJADOR_H_INCLUDED
