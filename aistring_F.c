#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aistring_F.h"

///Laestructura Oracion dependera de los sustantivos
Oracion* cargar_Oracion_de_Frace(Frace* fraceActual){
    if(!fraceActual)return NULL;
    Oracion* nueva=(Oracion*)malloc(sizeof(Oracion));
    if(!nueva)return NULL;
    nueva->num_bloques=0;
    nueva->tim=INDETERMINADO;
    Word* temp=fraceActual->inicio;
    while(temp!=NULL && nueva->num_bloques<MAX_BLOQUES){
        strncpy(nueva->b[nueva->num_bloques].block,temp->palabra.palabra,WORD_LENGTH-1);
        nueva->b[nueva->num_bloques].block[WORD_LENGTH-1]='\0';
        nueva->b[nueva->num_bloques].typo_b=temp->palabra.Tipo;
        nueva->Typos.A[nueva->num_bloques]=temp->palabra.Tipo;
        if(temp->palabra.Tipo==VERB){
            nueva->tim=temp->palabra.Verb;
        }
        if(temp->palabra.Tipo==SUST){
            strcpy(nueva->clave.block,temp->palabra.palabra);
            nueva->clave.typo_b=temp->palabra.Tipo;
            nueva->frecuencia=1.0f;
        }
        nueva->num_bloques++;
        temp=temp->sig;
    }
    if(nueva->clave.typo_b==SUST){
        return nueva;
    }else{
        for(int i=0;i<nueva->num_bloques;i++){
            if(nueva->b[i].typo_b==VERB){
                strcpy(nueva->clave.block,nueva->b[i].block);
                nueva->clave.typo_b=nueva->b[i].typo_b;
                nueva->frecuencia=1.2f;
                return nueva;
            }
        }
    }
    return nueva;
}

Sentencia* inic_vinculo_oracion(Oracion* oracionActual){
    if(!oracionActual)return NULL;
    Sentencia* nueva=(Sentencia*)malloc(sizeof(Sentencia));
    if(!nueva)return NULL;
    nueva->idea=*oracionActual;
    nueva->der=NULL;
    nueva->izq=NULL;
    nueva->bro=NULL;
    nueva->raiz_orig=nueva;
    nueva->raiz_pri=nueva;
    return nueva;
}
Sentencia* crear_vinculo_oracion(Oracion* oracionActual,Sentencia* anterior){
    if(!oracionActual || !anterior)return NULL;
    Sentencia* nueva=(Sentencia*)malloc(sizeof(Sentencia));
    if(!nueva)return NULL;
    nueva->idea=*oracionActual;
    nueva->der=NULL;
    nueva->izq=NULL;
    nueva->bro=NULL;
    nueva->raiz_orig=anterior;
    nueva->raiz_pri=anterior->raiz_pri;

    _bool sustantivo=_false;
    for(int i=0;i<oracionActual->num_bloques;i++){
        if(oracionActual->b[i].typo_b==SUST){
            sustantivo=_true;
            break;
        }
    }
    if(sustantivo==_true){
        for(int i=0;i<anterior->idea.num_bloques;i++){
            if(anterior->idea.b[i].typo_b==SUST){
                for(int j=0;j<oracionActual->num_bloques;j++){
                    if(oracionActual->b[j].typo_b==SUST && strcmp(oracionActual->b[j].block,anterior->idea.b[i].block)==0){
                        anterior->bro=nueva;
                        return nueva;
                    }
                }
            }
        }
        anterior->der=nueva;
    }else{
        anterior->izq=nueva;
    }
    return nueva;
}
void imprime_texto(Sentencia* raiz){
    if(!raiz)return;
    for(int i=0;i<raiz->idea.num_bloques;i++){
        printf("%s ",raiz->idea.b[i].block);
    }printf("\n");
    imprime_texto(raiz->izq);
    imprime_texto(raiz->der);
    if(raiz->bro && raiz->bro!=raiz){
        imprime_texto(raiz->bro);
    }
}
void guardar_Oracion(Oracion* actual){
    if(!actual)return;
    FILE* fp;
    char filename[MAX_FILENAME];
    mkdir("BDTT",0755);
    sprintf(filename,"BDTT/%s_%s",actual->clave.block,tipo_a_texto(actual->clave.typo_b));
    fp=fopen(filename,"ab");
    fwrite(&actual->num_bloques,sizeof(int),1,fp);
    fwrite(&actual->frecuencia,sizeof(float),1,fp);
    fwrite(&actual->tim,sizeof(Tiempo_oracion),1,fp);
    for(int i=0;i<actual->num_bloques;i++){
        fwrite(&actual->b[i],sizeof(Bloque),1,fp);
    }fclose(fp);
}
Oracion* obtener_Oracion(Wd* palabraclave){
    if(!palabraclave)return NULL;
    Oracion* tempo=(Oracion*)malloc(sizeof(Oracion));
    FILE* fp;
    char filename[MAX_FILENAME];
    sprintf(filename,"BDTT/%s_%s",palabraclave->palabra,tipo_a_texto(palabraclave->Tipo));
    fp=fopen(filename,"rb");
    if(!fp)return NULL;
    fread(&tempo->num_bloques,sizeof(int),1,fp);
    fread(&tempo->frecuencia,sizeof(float),1,fp);
    fread(&tempo->tim,sizeof(Tiempo_oracion),1,fp);
    for(int i=0;i<tempo->num_bloques;i++){
        fread(&tempo->b[i],sizeof(Bloque),1,fp);
    }fclose(fp);
    for(int i=0;i<tempo->num_bloques;i++){
        tempo->Typos.A[i]=tempo->b[i].typo_b;
        if(tempo->b[i].typo_b==3){
            strcpy(tempo->clave.block,tempo->b[i].block);
            tempo->clave.typo_b=tempo->b[i].typo_b;
        }
    }
    if(tempo->clave.typo_b==3)return tempo;
    for(int i=0;i<tempo->num_bloques;i++){
        if(tempo->b[i].typo_b==4){
            strcpy(tempo->clave.block,tempo->b[i].block);
            tempo->clave.typo_b=tempo->b[i].typo_b;
        }
    }
    return tempo;
}
///Guarda cada oracion dependiendo de su sustantivo
void guardar_Sentencia(Sentencia* raiz){
    if(!raiz)return;
    guardar_Oracion(&raiz->idea);
    guardar_Sentencia(raiz->izq);
    guardar_Sentencia(raiz->der);
}
///Carga una oracion dependiendo de un sustantivo clave
void cargar_Sentencia(Sentencia** actual,Wd* clave){
    Sentencia* temp=(Sentencia*)malloc(sizeof(Sentencia));
    if(actual==NULL){
        temp=inic_vinculo_oracion(obtener_Oracion(clave));
    }
    Oracion* corriente=obtener_Oracion(clave);
    temp=crear_vinculo_oracion(corriente,*actual);
    *actual=temp;
}
void generar_respuesta_autonoma(Frace* frace){
    Oracion* oracion=cargar_Oracion_de_Frace(frace);
    if(oracion==NULL)return;

    Sentencia* sentencia=inic_vinculo_oracion(oracion);

    DecisionState decision=eleccion_primaria();
    switch(decision){
        case DECISION_SI:
            break;
        case DECISION_NO:
            break;
        case DECISION_DUDA:
            break;
        case DECISION_RAND:
            break;
        case DECISION_LEARN:
            break;
    }
    free(oracion);
    free(sentencia);
}
