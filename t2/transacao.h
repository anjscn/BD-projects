#ifndef __TRANSACAO__
#define __TRANSACAO__

    #include <stdlib.h>
    #include <stdio.h>
    #include "serial.h"
    #include "visao.h"
    #include "header.h"



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