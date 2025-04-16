#include "aistring_w.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

///metodo de eleccion primaria de BDT
_bool eleccion_primaria(){
    srand(time(NULL));
    _bool eleccion=(random()%3+1)-1;
    return eleccion;
}
///eleccion aleatoria,caotica,para compensar "_duda"
DecisionState eleccion_secundaria(_bool eleccion,Wd* palabra_clave){
    if(eleccion==_true && (palabra_clave->Tipo==SUST || palabra_clave->Tipo==VERB) && palabra_clave->num_relasionadas==0){
        return DECISION_SI;
    }
    else if(eleccion==_true && (palabra_clave->Tipo==SUST || palabra_clave->Tipo==VERB) && palabra_clave->num_relasionadas>0){
        return DECISION_NO;
    }
    else if((eleccion==_duda && (palabra_clave->Tipo==SUST || palabra_clave->Tipo==VERB) || palabra_clave->num_relasionadas>0)){
        return DECISION_DUDA;
    }
    else if(eleccion==_duda || palabra_clave->Tipo==SUST || palabra_clave->Tipo==VERB || palabra_clave->num_relasionadas==0){
        return eleccion_primaria();
    }
    else{
        return DECISION_LEARN;
    }
}
///Definicion de alternativa para switch de opciones
///de procesamiento BDT
Alternativa definicion_primaria(DecisionState* desicion){
    srand(time(NULL));
    Alternativa opcion;
    if(desicion==DECISION_SI)return ALTERNATIVA_1;
    else if(desicion==DECISION_NO)return ALTERNATIVA_2;
    else if(desicion==DECISION_DUDA){
        opcion=(random()%5+1)-1;
        return opcion;
    }
    else if(desicion==DECISION_RAND){
        opcion=(random()%3+1)-1;
        return opcion;
    }
    else{
        return ALTERNATIVA_5;
    }
}
DecisionState tomar_decision_aprendizaje(Wd* palabra){
    _bool eleccion=eleccion_primaria();
    return eleccion_secundaria(eleccion,palabra);
}
