/**
 * @file header.h
 * @author GRR20173559 Camile Nunes dos Anjos (cna17@inf.ufpr.br)
 * @author GRR20190378 Eduardo Rosso Barbosa (you@domain.com)
 * @brief Arquivo com o cabeçalho das funções desenvolvidas nos arquivos ... e as structs.
 * @version 0.1
 * @date 2022-09-04
**/

#ifndef _HEADER_H
#define _HEADER_H

/**
 * @brief 
 * 
 */
    #define COMMIT 'C'
    #define READ 'R'
    #define WRITE 'W'

    #define MAX_TRANSACOES 10
    #define MAX_OPS 50


    typedef struct operacoes_t{
        int time;
        char operation;
        char attribute;
    } operacoes_t;

    typedef struct transacao_t{
        int transation_id;
        int num_ops;
        operacoes_t* ops[MAX_OPS * sizeof(operacoes_t*)];
    } transacao_t;


#endif
