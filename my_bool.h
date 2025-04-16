#ifndef MY_BOOL_H_INCLUDED
#define MY_BOOL_H_INCLUDED

/**contendra todos los enum necesarios para la toma de decisiones*/
///en el analisis de datos desde y hacia la BDLP,BDT,BDTT,y BDD.

typedef enum _bool{
    _false, ///coinsidencia total
    _true,  ///coinsidencia nula
    _duda   ///coinsidencia parcial
}_bool;

typedef enum{
    DECISION_SI,    ///100% si
    DECISION_NO,    ///100% no
    DECISION_DUDA,  ///entre 50% y 70%
    DECISION_RAND,  ///solo si esta en el rango anterior
    DECISION_LEARN  ///desconocido o nuevo enfoque
}DecisionState;

typedef enum{
    ALTERNATIVA_1,    ///primera alternativa de la lista
    ALTERNATIVA_2,    ///segunda alternativa de la lista
    ALTERNATIVA_3,    ///tercera alternativa de la lista
    ALTERNATIVA_4,    ///cuarta alternativa de la lista
    ALTERNATIVA_5     ///quinta alternativa de la lista
}Alternativa;


#endif // MY_BOOL_H_INCLUDED
