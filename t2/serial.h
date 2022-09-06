/**
 * @file serial.c
 * @author GRR20173559 Camile Nunes dos Anjos (cna17@inf.ufpr.br)
 * @author GRR20190378 Eduardo Rosso Barbosa (erb19@inf.ufpr.br)
 * @brief 
 * @version 0.1
 * @date 2022-09-04
**/

#ifndef __SERIAL__
#define __SERIAL__
    #include "header.h"


    typedef struct vertice_t {
        int id;
        struct vertice_t** reachables;
    } vertice_t;



    // Checa se as n primeiras transições são serializaveis
    int check_serial(transacao_t **escalation, int n);

#endif