/**
 * @file escalona.c
 * @author GRR20173559 Camile Nunes dos Anjos (cna17@inf.ufpr.br)
 * @author GRR20190378 Eduardo Rosso Barbosa (erb19@inf.ufpr.br)
 * @brief 
 * @version 0.1
 * @date 2022-09-04
**/

#include <stdio.h>
#include "serial.h"
#include "transacao.h"


int main(int argc, char *argv[])
{

    int time;
    int transation_id;
    char operation;
    char attribute; 


    init_transactions();

    while (scanf ("%d %d %c %c", &time, &transation_id,
                         &operation, &attribute) != EOF) {

        new_ops(transation_id, time, operation, attribute);

        if(num_active_transactions == 0){
            check_serial_equivalent();
            clear_transactions();
        }
    }

    end_transactions();


    return 0;
}
