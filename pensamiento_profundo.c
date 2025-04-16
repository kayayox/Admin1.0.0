#include "pensamiento_profundo.h"

///Genera una lista de 100 palabras al azar de BDT
void genera_lista_Rand(Frace* fraceRand){
    srand(time(NULL));
    _bool activador;
    Word* temp=fraceRand->inicio;
    FILE* fp;
    DIR* dir;
    int i=0;
    struct dirent* env;
    if((dir=opendir("BDT"))!=NULL){
        while((env=readdir(dir))!=NULL){
            if(i>100){
                break;
            }
            activador=(random()%3+1)-1;
            if(activador==_true){
                fp=fopen(env->d_name,"rb");
                if(!fp)continue;
                fread(&temp->palabra,sizeof(Wd),1,fp);
                i++;
                fclose(fp);
            }
        }
        closedir(dir)
    }
}
///genera un array de fraces obtenido a partir de fraceRand y un patron selectivo
void genera_lista_Fraces(Frace* fraces,char arr_Fraces[MAX_VARIANTES][MAX_TOKEN]){
    genera_lista_Rand(fraces);
    Word* temp=fraces->inicio;
    while(temp!=NULL){

    }
}
Patrones* crear_Nodo(Patron p){
    Patrones* nuevo_Nodo=(Patrones*)malloc(sizeof(Patrones));
    if(nuevo_Nodo==NULL){///verificacion importante
        fprintf(stderr,"ERROR: no se pudo asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    nuevo_Nodo->actual=p;///se carga el valor en la variable del Nodo
    nuevo_Nodo->sig=NULL;///importante para evitar fugas
    return nuevo_Nodo;
}
void cargar_patron(Patrones* p){
    FILE* fp=fopen("BDTT/.Patrones","rb");
    if(!fp)return;
    Patron* temp=(Patron*)malloc(sizeof(Patron));
    while(fread(temp,sizeof(Patron),1,fp)){
        insertar_patron(&p,temp);
    }
    free(temp);
    fclose(fp);
}
void guardar_patron(Patrones* actual){
    FILE* fp=fopen("BDTT/.Patrones","wb");
    if(!fp)return;
    while(fwrite(&actual->actual,sizeof(Patron),1,fp)){
        actual=actual->sig;
    }
    fclose(fp);
}
void insertar_patron(Patrones** lista,Patron* actual){
    Patrones* nuevo_Nodo=crear_Nodo(*actual);
    if(*lista==NULL){
        *lista=nuevo_Nodo;
    }else{
        nuevo_Nodo->sig=*lista;
        *lista=nuevo_Nodo;
    }
}
///selecciona el patron a usar en generar_lista_fraces
///para la conversacion interna y la creacion de nuevas fraces
///de manera autonoma
void seleccionar_patron(Patron* patron){
    Patrones* ps=(Patrones*)malloc(sizeof(Patrones));
    cargar_patron(ps);
    srand(time(NULL));
    _bool activador;
    while(ps!=NULL){
        activador=(random()%5+1)-1;
        if(activador==_true){
            *patron=ps->actual;
            break;
        }
        else if(activador==_duda){
            patron->p[0]=PREG;
            patron->p[1]=ART;
            patron->p[2]=SUST;
            patron->p[3]=VERB;
            patron->patern=PREGUNTA_SIMP;
            break;
        }
        ps=ps->sig;
    }
}
