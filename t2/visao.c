/**
 * @file visao.c
 * @author GRR20173559 Camile Nunes dos Anjos (cna17@inf.ufpr.br)
 * @author GRR20190378 Eduardo Rosso Barbosa (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-04
**/

#include "visao.h"

transacao_t **original;


void troca(transacao_t **e, int l, int i ) { 
    transacao_t* temp = e[l];
    e[l] = e[i];
    e[i] = temp;
}

// retorna o id da ultima transacao que tem o ultimo write
// retorna -1 caso não encontre escrita
int seleciona_ultima_escrita(transacao_t** e, int n){
    for(int i = n-1; i >=0; i--) {
        for (int j = e[i]->num_ops-1; j >= 0; j--) {
            if(e[i]->ops[j]->operation == WRITE){
                return e[i]->transation_id;
            }   
        }
    }
    return -1;
}

int valida_ultimo(transacao_t **a, int n){

    int id_last_w_original = seleciona_ultima_escrita(original, n);
    int id_last_w_a = seleciona_ultima_escrita(a, n);

    fprintf(stderr, "<-original: %d a: %d\n", id_last_w_original, id_last_w_a);

    if(id_last_w_original == -1){ return 0;}    
    if(id_last_w_a != id_last_w_original){ return 0; }
    fprintf(stderr, "<-GAYYY: %d a: %d\n", id_last_w_original, id_last_w_a);


    return 1;
}

int compara(transacao_t **a, int n){
    if(!valida_ultimo(a, n)) return -1;

    for(int i = 0; i < n; i++){

    }


    return 0;
}


void printa(transacao_t **a, int n){
    fprintf(stderr, "<----- ");

    for (int i = 0; i < n; i++) {
        fprintf(stderr, "%d ", a[i]->transation_id);
    }

    fprintf(stderr, "------>\n");
}



int permuta (transacao_t** e, int l, int r){
    //fprintf(stderr, "P %d %d\n", l, r);

    if(l == r){
        // printa(e, r);
        // printa(original, r);
        if(compara(e, r) == -1) return -1;
    }

    for(int i = l; i < r; i++){
        troca(e, l, i);
        if(permuta(e, l+1, r) == -1) return -1;
        troca(e, l, i);
    }
    return 0;
}


int check_view(transacao_t **escalation, int n){
    original = escalation;
    
    transacao_t ** permutada = malloc(n*sizeof(transacao_t*));
    for(int i = 0; i < n; i++){
        permutada[i] = original[i];
    }

    int p = permuta(permutada, 0, n);

    free(permutada);

    if(p == -1)
        return 0;
    return 1;
}