#include "aistring_w.h"


/**funcion para crear una variable del tipo palabra*/
///normalizar primero
void normalizar_palabra(char* palabra){
    int i=0,j=0;
    while(palabra[i]){
        if(isalpha(palabra[i]) || palabra[i]=='\''){
            palabra[j]=tolower(palabra[i]);
            j++;
        }
        i++;
    }
    palabra[j]='\0';
}
///crea una estructura de palabra sin iniciar valores
Wd* crea_palabra(char* palabra){
    if(!palabra)return NULL;
    Wd* nueva_palabra=(Wd*)malloc(sizeof(Wd));
    if(!nueva_palabra)return NULL;
    normalizar_palabra(palabra);
    strncpy(nueva_palabra->palabra,palabra,WORD_LENGTH-1);
    nueva_palabra->palabra[WORD_LENGTH-1]='\0';
    return nueva_palabra;
}
///funciones para inicializar elementos relevantes a dicha variable por defecto
void inic_Wd(Wd* nuevaPalabra){
    nuevaPalabra->Cant=NONE;
    nuevaPalabra->Gen=NEUT;
    nuevaPalabra->Grado=NON;
    nuevaPalabra->num_relasionadas=0;
    nuevaPalabra->Per=NIN;
    nuevaPalabra->Tiempo=INFINITIVO;
    nuevaPalabra->Tipo=INDEFINIDO;
}
///funcion generica para verificar terminaciones de palabras
_bool tiene_terminacion(const char* palabra,const char* terminacion[],int num_terminacion){
    size_t len_palabra=strlen(palabra);
    for(int i=0;i<num_terminacion;i++){
        size_t len_terminacion=strlen(terminacion[i]);

        if(len_palabra>len_terminacion){
            if(strcmp(palabra+len_palabra-len_terminacion,terminacion[i])==0){
                return _true;
            }
        }
    }
    return _false;
}
///verifica terminacion de sustantivo(ampliable y depurable aun)
_bool es_sustantivo(const char* palabra){
    const char* terminacion[]={"cion","dad","tad","sion","aje",
        "ente","ante","or","ora","umbre","ez","eza"};
    int num_terminacion=sizeof(terminacion)/sizeof(terminacion[0]);
    return tiene_terminacion(palabra,terminacion,num_terminacion);
}
///verifica terminacion de verbo (ampliable y depurable aun)
_bool es_verbo(const char* palabra){
    const char* terminacion[]={"ar","er","ir","ando","iendo",
        "aba","ia","are","ere","ire","aria","eria","iria","aste",
        "iste","io","amos","imos","aron","ieron"};
    int num_terminacion=sizeof(terminacion)/sizeof(terminacion[0]);
    return tiene_terminacion(palabra,terminacion,num_terminacion);
}
///verifica terminacion de adjetivo (ampliable y depurable aun)
_bool es_adjetivo(const char* palabra){
    const char* terminacion[]={"oso","osa","able","ible","ivo",
        "iva","al","il","ble","ar","or","ora","ante","ista",
        "ario","aria","ero","era"};
    int num_terminacion=sizeof(terminacion)/sizeof(terminacion[0]);
    return tiene_terminacion(palabra,terminacion,num_terminacion);
}
///verifica terminacion de adverbio (ampliable y depurable aun)
_bool es_adverbio(const char* palabra){
    const char* terminacion[]={"mente","ando","endo","amente"};
    int num_terminacion=sizeof(terminacion)/sizeof(terminacion[0]);
    return tiene_terminacion(palabra,terminacion,num_terminacion);
} ///verifica terminacion de plural (ampliable y depurable aun)
_bool es_plural(const char* palabra){
    const char* terminacion[]={"s","es","as","on","an"};
    int num_terminacion=sizeof(terminacion)/sizeof(terminacion[0]);
    return tiene_terminacion(palabra,terminacion,num_terminacion);
}
///verifica terminacion de genero (ampliable y depurable aun)
_bool es_genero_femenino(const char* palabra){
    const char* terminacion[]={"e","a","es","as"};
    int num_terminacion=sizeof(terminacion)/sizeof(terminacion[0]);
    return tiene_terminacion(palabra,terminacion,num_terminacion);
}
_bool es_genero_masculino(const char* palabra){
    const char* terminacion[]={"o","l","as","on","an"};
    int num_terminacion=sizeof(terminacion)/sizeof(terminacion[0]);
    return tiene_terminacion(palabra,terminacion,num_terminacion);
}
///verifica terminacion de verbo para tiempo (ampliable y depurable aun)
Tipo_tiempo es_tiempo(const char* palabra){
    const char* terminacion[]={"ra","ia"};
    if(strcmp(palabra+strlen(palabra)-2,terminacion[0])==0){
        return PASS;
    }
    else if(strcmp(palabra+strlen(palabra)-3,terminacion[1])==0){
        return FUTR;
    }
    return PRES;
}
///primera posibiledad de asignar tipo por verificacion terminal
void asignar_Tipo_A(Wd* nueva,const char* significado){
    if(es_sustantivo(nueva->palabra)==_true)nueva->Tipo=SUST;
    if(es_verbo(nueva->palabra)==_true)nueva->Tipo=VERB;
    if(es_adjetivo(nueva->palabra)==_true)nueva->Tipo=ADJT;
    if(es_adverbio(nueva->palabra)==_true)nueva->Tipo=ADV;
    switch(nueva->Tipo){
        case SUST:{
            nueva->Cant=(es_plural(nueva->palabra)==_true)? PLUR : SING;
            if(es_genero_femenino(nueva->palabra)==_true)nueva->Gen=FEME;
            else if(es_genero_masculino(nueva->palabra)==_true)nueva->Gen=MASC;
            else{nueva->Gen=NEUT;}
        }break;
        case VERB:{
            nueva->Tiempo=es_tiempo(nueva->palabra);
            nueva->Cant=(nueva->palabra[-1]=='n')?PLUR : SING;
        }break;
        case ADJT:{
            if(es_genero_femenino(nueva->palabra)==_true)nueva->Gen=FEME;
            else if(es_genero_masculino(nueva->palabra)==_true)nueva->Gen=MASC;
            else{nueva->Gen=NEUT;}
        }break;
        case ADV:
            break;
        case INDEFINIDO:
            asignar_typo_B(nueva,significado);
            break;
    }
}
///devuelve un string con el tipo de la palabra
const char* tipo_a_texto(Tipo_palabra tipo){
    static const char* tipos[]={
        "Pronombre","Articulo","Adjetivo","Sustantivo","Verbo",
        "Pregunta","Adverbio","Sentencia","Prepocision","Posesivo",
        "Relativo","Numeral","Conjuncion","Contraccion","Cuantitativo",
        "Determinante","Indefinido"
    };
    return tipos[tipo];
}
///devuelve un string con el tiempo de la palabra o oracion
const char* tiempo_a_texto(Tipo_tiempo tiempo){
    static const char* tiempos[]={
        "Pasado","Presente","Futuro","Indeterminado"
    };
    return tiempos[tiempo];
}
///devuelve un string con el genero de la palabra
const char* genero_a_texto(Tipo_genero genero){
    static const char* generos[]={"Masculino","Femenino","Neutral"};
    return generos[genero];
}
///devuelve un string con el grado de la palabra
const char* grado_a_texto(Tipo_grado grado){
    static const char* grados[]={"Comparativo","Superlativo","Positivo",
        "Intension","Interrogativo","Negativo","Relativo","Cuantitativo","None"};
        return grados[grado];
}
///segunda posibiledad de asignar tipo por verificacion terminal
void asignar_typo_B(Wd* nuevaPalabra,char* significado){
    char clave[][22]={"pronombre","articulo","adjetivo","sustantivo",
            "verbo","pregunta","adverbio","sentencia","prepocision",
            "Posesivo","Relativo","Numeral","Conjuncion","Contraccion",
            "Cuantitativo","Demostrativo","indefinido"};
    for(int i=0;i<9;i++){
        if(strstr(significado,clave[i])!=NULL){
            nuevaPalabra->Tipo=(Tipo_palabra)i;
            if(nuevaPalabra->Tipo==ART){
                size_t len=strlen(nuevaPalabra->palabra);
                if(nuevaPalabra->palabra[len-1]=='s'){
                    nuevaPalabra->Cant=(Tipo_cant)PLUR;
                }else{
                    nuevaPalabra->Cant=(Tipo_cant)SING;
                }
            }
            if(nuevaPalabra->Tipo==VERB){
                nuevaPalabra->Tiempo=es_tiempo(nuevaPalabra->palabra);
            }
            return;
        }
    }
    nuevaPalabra->Tipo=INDEFINIDO;
}
///asigna valores a los elementos de la palabra
void asigna_palabra(Wd* nueva_palabra){
    char* significado=NULL;
    size_t n=0;
    size_t len;
    printf("Que es o que significa %s\n",nueva_palabra->palabra);
    len=getline(&significado,&n,stdin);
    if(len>0 && significado[len-1]=='\n'){
        significado[len-1]='\0';
    }
    strncpy(nueva_palabra->significado,significado,len);
    asignar_Tipo_A(nueva_palabra,significado);
    free(significado);
}
///revisar contexto y corregir de ser necesario (cuando my_bool genera DUDA)
void asignar_palabra_revision_A(Wd* nuevaPalabra,const char* contexto){
    Word_couter* cp=(Word_couter*)malloc(sizeof(Word_couter));
    size_t len;
    if(nuevaPalabra->Tipo==INDEFINIDO){
        len=recibe_Dato(cp,contexto);
        for(size_t i=0;i<len;i++){
            if(strncmp(cp->arr_string[i],nuevaPalabra->palabra,strlen(nuevaPalabra->palabra)-2)==0){
                strcpy(nuevaPalabra->variantes[nuevaPalabra->num_variantes],cp->arr_string[i]);
                nuevaPalabra->num_variantes++;
            }
        }
    }

}
///funcion para guardar la informacion de la variable en un archivo unico temporal
///para analisis y depuracion en el proceso de aprendizaje
void guardarWd(Wd* nuevapalabra){
    char filename[MAX_FILENAME];
    snprintf(filename,MAX_FILENAME,"BDT/%s",nuevapalabra->palabra);
    mkdir("BDT",0755);
    FILE* fp=fopen(filename,"wb");
    fwrite(nuevapalabra,sizeof(Wd),1,fp);
    fclose(fp);
}
///funcion para determinar la existencia de una palabra en el proceso de aprendizaje
_bool buscar_palabra(Wd* nuevaPalabra){
    if(!nuevaPalabra)return _false;
    char filename[MAX_FILENAME];
    snprintf(filename,MAX_FILENAME,"BDT/%s",nuevaPalabra->palabra);
    FILE* fp;
    DIR* dir;
    struct dirent* ent;
    if((dir=opendir("BDT"))!=NULL){
        while((ent=readdir(dir))!=NULL ){
            if(strcmp(ent->d_name,nuevaPalabra->palabra)==0){
                fp=fopen(filename,"rb");
                if(!fp){
                    closedir(dir);
                    return _false;
                }
                fread(nuevaPalabra,sizeof(Wd),1,fp);
                fclose(fp);
                return _true;
            }
        }
        closedir(dir);
    }
    return _false;
}
///proceso experimental para relacionar palabras y valorar la relacion
void asignar_variante_relacional(Wd* nuevaPalabra,Word* temp){
    size_t j=0,k=1;
    size_t n=strlen(nuevaPalabra->palabra);
    size_t n1=strlen(temp->palabra.palabra);
    size_t n2;
    double valor=0;
    if(!temp->palabra.num_relasionadas)temp->palabra.num_relasionadas=0;
    if(n>n1){
        n2=n-n1;
        for(size_t i=0;i<n1;i++){
            if((int)nuevaPalabra->palabra[i]==(int)temp->palabra.palabra[i]){
                j++;
            }else{
                k++;
            }
        }
        valor=((double)n/k)-((double)n/j);
        if(valor>((double)n1/n) && j>n2){
            strncpy(temp->palabra.relasionadas[temp->palabra.num_relasionadas],nuevaPalabra->palabra,strlen(nuevaPalabra->palabra));
            temp->palabra.valor_relasion[temp->palabra.num_relasionadas]=valor;
            temp->palabra.num_relasionadas++;
        }
    }
    if(n<n1){
        n2=n1-n;
        for(size_t i=0;i<n;i++){
            if((int)temp->palabra.palabra[i]==(int)nuevaPalabra->palabra[i]){
                j++;
            }else{
                k++;
            }
        }
        valor=((double)n1/k)-((double)n1/j);
        if(valor>((double)n/n1) && j>n2){
            strncpy(temp->palabra.relasionadas[temp->palabra.num_relasionadas],nuevaPalabra->palabra,strlen(nuevaPalabra->palabra));
            temp->palabra.valor_relasion[temp->palabra.num_relasionadas]=valor;
            temp->palabra.num_relasionadas++;
        }
    }
    if(n==n1 && strcmp(temp->palabra.palabra,nuevaPalabra->palabra)!=0){
        for(size_t i=0;i<n;i++){
            if((int)temp->palabra.palabra[i]==(int)nuevaPalabra->palabra[i]){
                j++;
            }else{
                k++;
            }
        }
        valor=((double)n/k)-((double)n/j);
        if(valor>(double)(n/(n1*k))){
            strncpy(temp->palabra.relasionadas[temp->palabra.num_relasionadas],nuevaPalabra->palabra,strlen(nuevaPalabra->palabra));
            temp->palabra.valor_relasion[temp->palabra.num_relasionadas]=valor;
            temp->palabra.num_relasionadas++;
        }
    }
}
///muestra los elementos de la palabra(sera ampliado)
void mostrar_detalle_Wd(Wd* palabra){
    if(palabra==NULL){
        printf("No hay palabra para mostrar\n");
        return;
    }
    printf("\n=== DETALLE DE (%s)===\n",palabra->palabra);
    printf("Palabra: %s\n",palabra->palabra);
    printf("Significado: %s\n",palabra->significado);
    printf("Tipo: %s\n",tipo_a_texto(palabra->Tipo));
    for(int i=0;i<palabra->num_relasionadas;i++){
        printf("[%s]",palabra->relasionadas[i]);
    }printf("\n");
    if(palabra->Tipo==ART){
        if(palabra->Cant==0){
            printf("Singular\n");
        }else if(palabra->Cant==1){
            printf("Plural\n");
        }
    }else{
        printf("NONE\n");
    }
    if(palabra->Tipo==VERB){
        printf("Tiempo: %s\n",tiempo_a_texto(palabra->Tiempo));
    }else{
        printf("NONE\n");
    }
    printf("========================\n");
}
///funcion para crear un nodo en la lista frace
Word* crear_Word(Wd nuevaPalabra){
    Word* nuevoWord=(Word*)malloc(sizeof(Word));
    if(nuevoWord==NULL){
        printf("ERROR: no se pudo asignar memoria\n");
        return NULL;
    }
    nuevoWord->palabra=nuevaPalabra;
    nuevoWord->sig = NULL;
    nuevoWord->pre = NULL;
    return nuevoWord;
}
///inicializar la lista frace vacia
void inic_Frace_Word(Frace* frace){
    frace->inicio=NULL;
    frace->cola=NULL;
}
///insertar nodos al final de la lista frace
void insertar_append_Frace(Frace* frace,Wd nuevaPalabra){
    Word* nuevoWord=crear_Word(nuevaPalabra);
    if(frace->inicio==NULL){
        frace->inicio=nuevoWord;
        frace->cola=nuevoWord;
    } else {
        frace->cola->sig=nuevoWord;
        nuevoWord->pre=frace->cola;
        frace->cola=nuevoWord;
    }
}
///guardar la informacion de la lista frace en un archivo temporal
void guardar_Frace_respuesta(Frace* frace,const char* filename){
    FILE* fp=fopen(filename,"Wb");
    if(fp==NULL){
        printf("ERROR al abrir el archivo");
        return;
    }
    Word* actual=frace->inicio;
    while(actual!=NULL){
        fwrite(&actual->palabra,sizeof(Wd),1,fp);
        actual=actual->sig;
    }
    fclose(fp);
}
///cargar del archivo temporal la lista frace
void cargar_Frace_respuesta(Frace* frace,const char* filename){
    FILE* fp=fopen(filename,"rb");
    if(fp==NULL){
        printf("ERROR al abrir el archivo");
        return;
    }
    Wd* nuevapalabra=NULL;
    while(fread(&nuevapalabra,sizeof(Wd),1,fp)){
        insertar_append_Frace(frace,*nuevapalabra);
    }
    fclose(fp);
    free(nuevapalabra);
}
void imprimir_Frace_completa(Frace* frace){
    if(frace==NULL){
        printf("La frace esta vacia\n");
        return;
    }
    printf("\n=== FRACE COMPLETA ===\n");
    Word* actual=frace->inicio;
    while(actual!=NULL){
        printf("%s ",actual->palabra.palabra);
        actual=actual->sig;
    }
    printf("\n=================================\n");
}
///relaciona palabras en la lista
void analizar_relacionar(Frace* frace){
    Word* actual=frace->inicio;
    while(actual!=NULL){
        Word* comparar=frace->inicio;
        while(comparar!=NULL){
            if(actual!=comparar){
                asignar_variante_relacional(&actual->palabra,comparar);
            }
            comparar=comparar->sig;
        }
        mostrar_detalle_Wd(&actual->palabra);
        actual=actual->sig;
    }
}
///estadistica prelimionar
void mostrar_estadistica(Frace* frace){
    printf("\nEstadistica actual:\n");
    int num_palabras=0;
    int num_sustantivos=0;
    int num_verbos=0;
    int num_adjetivos=0;

    Word*actual=frace->inicio;
    while(actual!=NULL){
        num_palabras++;
        switch(actual->palabra.Tipo){
            case SUST:num_sustantivos++;break;
            case VERB:num_verbos++;break;
            case ADJT:num_adjetivos++;break;
            default:break;
        }
        mostrar_detalle_Wd(&actual->palabra);
        actual=actual->sig;
    }
    printf("Total palabras actuales: [%d]\n",num_palabras);
    printf("Sustantivos: [%d]\n",num_sustantivos);
    printf("Verbos: [%d]\n",num_verbos);
    printf("Adjetivos: [%d]\n",num_adjetivos);
}
