#include "transacao.h"

int num_transicoes;
int num_active_transactions;

int num_escalonamento_finalizado;

transacao_t** transacao_list;

int init_transactions(){

    transacao_list = malloc(MAX_TRANSACOES * sizeof(transacao_t*));

    num_transicoes = 0;
    num_active_transactions = 0;
    num_escalonamento_finalizado = 0;

    // Limpa área de transacao_list
    for (int i = 0; i < MAX_TRANSACOES; i++) {
        transacao_list[i] = NULL;
    }

    return SUCCESS_RETURN;
}

// Encontra transação de id transation_id em tss
transacao_t* find_transation(int transation_id){
    for (int i = 0; i < num_transicoes; i++) {
        if(transacao_list[i] && transacao_list[i]->transation_id == transation_id)
            return transacao_list[i];    
    }
    return NULL;
}

int new_ops(int transaction_id, int time, char operation, char attribute){
    transacao_t* t = find_transation(transaction_id);
     
    if(!t){
        t = new_transaction(transaction_id);
        if(t == NULL)  { fprintf(stderr, "Erro ops1\n"); return FAIL_RETURN; }
    }

    if( !(t->num_ops < MAX_OPS) ) { fprintf(stderr, "Erro ops2\n"); return FAIL_RETURN; }
    
    if( t->num_ops > 0 && (t->ops[t->num_ops-1]->operation == COMMIT) ) { fprintf(stderr, "Erro ops3\n"); return FAIL_RETURN; } // Se já houve commit

    operacoes_t* ops = malloc(sizeof(operacoes_t));

    ops->time = time;
    ops->operation = operation;
    ops->attribute = attribute;
    
    t->ops[t->num_ops] = ops;

    fprintf(stderr, "Created new operation at Tr%d pos%d op%d - %p\n\n", transaction_id, t->num_ops, ops->time, ops);

    t->num_ops ++;


    if(ops->operation == COMMIT){
        num_active_transactions--;
        if(num_active_transactions == 0)
            num_escalonamento_finalizado++;
    }

    return SUCCESS_RETURN;
}

transacao_t* new_transaction(int transaction_id){
    if( !(num_transicoes < MAX_TRANSACOES) ) return NULL; // Alcançou o máximo de transicoes

    transacao_t* t = malloc(sizeof(transacao_t));
    
    t->transation_id = transaction_id;
    t->num_ops = 0;

    for (int i = 0; i < MAX_OPS; i++) {
        t->ops[i] = NULL;
    }
    

    transacao_list[num_transicoes] = t;


    fprintf(stderr, "Created new transaction at pos%d(id%d) - %p <<<<\n", num_transicoes, transaction_id, t);


    num_transicoes++;
    num_active_transactions++;

    return t;
}

int print_transactions(){
    fprintf(stderr, "<-----PRINT------>\n");

    transacao_t* t;
    operacoes_t* op;
    for (int i = 0; i < num_transicoes; i++) {
        t = transacao_list[i];
        fprintf(stderr, "> %d: 0 .. %d <\n", i, t->num_ops);
        for(int j = 0; j < t->num_ops; j++){
            fprintf(stderr, "> [i%d j%d] ", i, j);

            op = t->ops[j];
            fprintf(stderr, "%d:", t->transation_id);
            fprintf(stderr, "%c",op->operation);
            fprintf(stderr, "(%c)", op->attribute);
            fprintf(stderr, "at time %d\n", op->time);
        }
    }

    fprintf(stderr, "<----ENDPRINT------->\n");

    return SUCCESS_RETURN;
}


int is_serial(){
    return check_serial(transacao_list, num_transicoes);
}

int is_equivalent(){
    return check_view(transacao_list, num_transicoes);
}


int check_serial_equivalent(){



    fprintf(stdout, "%d ", num_escalonamento_finalizado);

    // Imprime lista de transações no escalonamento
    for (int i = 0; i < num_transicoes - 1; i++) {
        fprintf(stdout, "%d,", transacao_list[i]->transation_id);
    }
    fprintf(stdout, "%d ", transacao_list[num_transicoes-1]->transation_id);



    ( is_serial() ? fprintf(stdout, "SS ") : fprintf(stdout, "NS ") );
    ( is_equivalent() ? fprintf(stdout, "SV\n") : fprintf(stdout, "NV\n") );


    return FAIL_RETURN;
}

int clear_transactions(){
    transacao_t* t;
    for (int i = 0; i < num_transicoes; i++) {
        t = transacao_list[i];
        for(int j = 0; j < t->num_ops; j++){
            free(t->ops[j]);
        }
        free(t);
    }

    num_transicoes = 0;

    return SUCCESS_RETURN;
}


// Dar free em tudo o que precisa
int end_transactions(){
    clear_transactions();

    free(transacao_list);
    
    return FAIL_RETURN;
}
