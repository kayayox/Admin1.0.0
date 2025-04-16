#include "manejador.h"

///menu principal de prueba
void mostrar_menu_principal(){
    printf("\nOpciones de aprendizaje\n");
    printf("1. Ingresar nueva frace\n");
    printf("2. Mostrar conocimiento actual\n");
    printf("3. Generar respuesta autonoma\n");
    printf("4. Analizar relaciones entre palabras\n");
    printf("5. Mostrar estadistica\n");
    printf("6. Salir\n");
    printf("Elija una opcion\n");
}
///recibe los datos del teclado y crea los archivos binarios temporales variant
void iniciar_recepcion(Lista_Var* lista_actual,Word_couter* cp){
    Variant* temp=(Variant*)malloc(sizeof(Variant));
    if(temp==NULL)return;

    char* recibe=NULL;
    size_t n=0;
    size_t len;
    size_t lens;
    len=getline(&recibe,&n,stdin);
    if(len>0 && recibe[len-1]=='\n'){
        recibe[len-1]='\0';
    }
    lens=recibe_Dato(cp,recibe);

    for(size_t i=0;i<lens;i++){
        reconocer(temp,cp->arr_string[i]);
        guardar(temp);
        insertar_append_Doble(lista_actual,*temp);
    }

    guardar_Datos_variant(lista_actual);
    free(temp);
    free(recibe);
}
///revisa entre la lista de string en binario temporal variant
///las palabras existentes en BDT,agrega las que no estan
void iniciar_revicion_word(Frace* frace_actual){
    if(!frace_actual)return;
    Wd* temporal=(Wd*)malloc(sizeof(Wd));
    if(temporal==NULL)return;
    _bool respuesta;
    char arr_string[MAX_DATA][WORD_LENGTH];
    size_t len=cargar_string(arr_string);
    for(size_t i=0;i<len;i++){
        temporal=crea_palabra(arr_string[i]);
        respuesta=buscar_palabra(temporal);
        if(respuesta==_false){
            inic_Wd(temporal);
            asigna_palabra(temporal);
            guardarWd(temporal);
        }
        guardarWd(temporal);
        insertar_append_Frace(frace_actual,*temporal);
    }
    free_archivo_variant(TYPE_STRING);
    free(temporal);
}
///realiza una segunda revision para las palabras nuevas
void iniciar_segunda_revicion_word(Frace* frace){
    Word* temp=frace->inicio;
    while(temp!=NULL){
        Wd nueva;
        char* contexto=NULL;
        size_t n=0;
        size_t len;
        strcpy(nueva.palabra,temp->palabra.palabra);
        if(buscar_palabra(&nueva)==_false){
            asigna_palabra(&nueva);
            guardarWd(&nueva);
        }else{
            if(nueva.Tipo==INDEFINIDO){
                printf("porfavor usa '%s' en un contexto\n",nueva.palabra);
                len=getline(&contexto,&n,stdin);
                if(contexto[len-1]=='\n')contexto[len-1]='\0';
                asignar_palabra_revision_A(&nueva,contexto);
                guardarWd(&nueva);
            }
        }
        free(contexto);
        temp=temp->sig;
    }
}
///verifica si una palabra es variable contextual de otra y la califica
void completa_variantes_contexto(Word* temp,Wd* nueva){
    strncpy(nueva->palabra,temp->palabra.palabra,strlen(temp->palabra.palabra));
    asignar_variante_relacional(nueva,temp);
    mostrar_detalle_Wd(&temp->palabra);
    guardarWd(&temp->palabra);
}
///procesamiento de aprendizaje de prueba
///sera sustituido por celula(neurona) al terminar pensamiento profundo
void proceso_aprendizaje(Frace* frace,Lista_Var* lista_actual){
    int opcion;
    scanf("%d",&opcion);
    getchar();
    Word_couter cp;
    for(int i=0;i<MAX_TOKEN;i++){
        cp.letras_por_palabra_x[i]='\0';
        cp.letras_por_palabra_y[i]='\0';
    }
    cp.num_caracteres=0;
    cp.num_letras=0;
    cp.num_palabras=0;
    for(int i=0;i<MAX_DATA;i++){
        for(int j=0;j<WORD_LENGTH;j++){
            cp.arr_string[i][j]='\0';
        }
    }

    switch(opcion){
        case 1:{
            printf("Ingrece la frace...\no 'salir' para terminar\n");
            iniciar_recepcion(lista_actual,&cp);
            iniciar_revicion_word(frace);
            iniciar_segunda_revicion_word(frace);

            Word* temp=frace->inicio;
            while(temp!=NULL){
                DecisionState decision=tomar_decision_aprendizaje(&temp->palabra);
                Alternativa alternativa=definicion_primaria(&decision);

                switch(alternativa){
                    case ALTERNATIVA_1:
                        asignar_variante_relacional(&temp->palabra,temp);
                        break;
                    case ALTERNATIVA_2:
                        break;
                    case ALTERNATIVA_3:
                        printf("¿es %s un %s correcto? (si/no): ",
                            temp->palabra.palabra,tipo_a_texto(temp->palabra.Tipo));
                        char confirmacion;
                        scanf("%c",&confirmacion);
                        getchar();
                        if(confirmacion=='n'){
                            char* contexto=NULL;
                            size_t n=0;
                            size_t len;
                            asigna_palabra(&temp->palabra);
                            printf("¿podrias usar '%s' en otra frace?\n",temp->palabra.palabra);
                            len=getline(&contexto,&n,stdin);
                            if(len>0 && contexto[len-1]=='\n'){
                                contexto[len-1]='\0';
                            }
                            asignar_palabra_revision_A(&temp->palabra,contexto);
                            guardarWd(&temp->palabra);
                            free(contexto);
                        }
                        break;
                    case ALTERNATIVA_4:
                        completa_variantes_contexto(temp,&temp->palabra);
                        break;
                    case ALTERNATIVA_5:
                        break;
                }
                temp=temp->sig;
            }
            printf("\nProceso completo.Resultados:\n");
            imprimir_Frace_completa(frace);
            break;
        }
        case 2:{
            printf("\nConocimiento actual:\n");
            Word* listo=frace->inicio;
            while(listo!=NULL){
                mostrar_detalle_Wd(&listo->palabra);
                listo=listo->sig;
            }
            break;
            }
        case 3:{
            generar_respuesta_autonoma(frace);
            break;
        }
        case 4:{
            analizar_relacionar(frace);
            break;
        }
        case 5:{
            mostrar_estadistica(frace);
            break;
        }
        case 6:{
            printf("\nGuardando conocimiento actual...\n");
            guardar_Datos_variant(lista_actual);

            Oracion* oracion=cargar_Oracion_de_Frace(frace);
            if(oracion!=NULL){
                guardar_Oracion(oracion);
                free(oracion);
            }
            printf("Hasta la proxima...\n");
            exit(0);
        }
        default:
            printf("\nOpcion no valida\n");
            break;
    }
}
