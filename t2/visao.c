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

/* Function to swap values at 
   two pointers */
void troca(transacao_t *a , transacao_t *b ) 
{ 
    //fprintf(stderr, "> trocando %d com %d\n", a->transation_id, b->transation_id);
    transacao_t temp = *a;
    *a = *b;
    *b = temp;

} 

void compara(transacao_t **a, transacao_t **b, int n){
    for(int i = 0; i < n; i++){

    }



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
        printa(e, r);
        compara(e, original, r);
    }


    for(int i = l; i < r; i++){
        troca(e[l], e[i]);
        permuta(e, l+1, r);
        troca(e[l], e[i]);
    }
    return 0;
}


int check_view(transacao_t **escalation, int n){
    original = escalation;
    
    transacao_t ** permutada = malloc(n*sizeof(transacao_t*));
    for(int i = 0; i < n; i++){
        permutada[i] = original[i];
    }

    permuta(permutada, 0, n);
    return 1;
}