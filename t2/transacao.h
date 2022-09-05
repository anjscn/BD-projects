#ifndef __TRANSACAO__
#define __TRANSACAO__

    #include <stdlib.h>
    #include <stdio.h>

    #define SUCCESS_RETURN 1
    #define FAIL_RETURN 0

    #define MAX_TRANSACOES 10
    #define MAX_OPS 50

    #define COMMIT 'C'
    #define READ 'R'
    #define WRITE 'W'

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


    extern int num_active_transactions;

    int init_transactions();
    
    int print_transactions();

    // Encontra transação de id transation_id em tss
    transacao_t* find_transation(int transation_id);

    int new_ops(int transaction_id, int time, char operation, char attribute);

    transacao_t* new_transaction(int transation_id);

    int check_serial_equivalent();

    int clear_transactions();

    int end_transactions();

#endif