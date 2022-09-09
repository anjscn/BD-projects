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
char attribute;

void troca(transacao_t **e, int l, int i ) { 
    transacao_t* temp = e[l];
    e[l] = e[i];
    e[i] = temp;
}

operacoes_t* seleciona_ultima_op_em_t(transacao_t* t, char op){
    
    for (int i = t->num_ops-1;  i >= 0; i--) {
        fprintf(stderr, " %d : att %c %c contra %c %c\n", i, t->ops[i]->operation, t->ops[i]->attribute, op, attribute);
        if((t->ops[i]->operation == op)){
            if(t->ops[i]->attribute == attribute){
                fprintf(stderr, "Retorna esse msmaaaaaaaaaaaaa\n");
                
                return t->ops[i];
            }
        }
    }
    fprintf(stderr, "Nulo ultimo\n");
    return NULL;
}

operacoes_t* seleciona_primeira_op_em_t(transacao_t* t, char op){
    
    for (int i = 0; i < t->num_ops; i++) {
        fprintf(stderr, " %d : att %c %c contra %c %c\n", i, t->ops[i]->operation, t->ops[i]->attribute, op, attribute);
        if((t->ops[i]->operation == op)){
            if(t->ops[i]->attribute == attribute){
                fprintf(stderr, "Retorna esse msmaaaaaaaaaaaaa\n");
                
                return t->ops[i];
            }
        }
    }
    fprintf(stderr, "Nulo primeiro\n");
    
    return NULL;
}


// retorna o tempo da ultima transacao que tem o ultimo write
// retorna -1 caso não encontre escrita
int seleciona_ultima_op(transacao_t** e, int n, char op, int take_time_in_account){
    int last_time = -1;

    for(int i = n-1; i >=0; i--) {
        operacoes_t* ultimo_w = seleciona_ultima_op_em_t(e[i], op);
        if( (ultimo_w) && ultimo_w->time > last_time){
            last_time = ultimo_w->time;
        
            if(!take_time_in_account){
                return last_time;
            }
        }
    }

    return last_time;
}

int valida_ultimo(transacao_t **a, int n){
    int time_last_w_original = seleciona_ultima_op(original, n, WRITE, 1);
    int time_last_w_a = seleciona_ultima_op(a, n, WRITE, 0);

    fprintf(stderr, "original:%d, a:%d \n", time_last_w_original, time_last_w_a);

    if(time_last_w_original == -1){ return SUCCESS_RETURN;} // Caso não tenha w no original, retorne SUCESSO

    if(time_last_w_a == time_last_w_original){ return SUCCESS_RETURN; } // Caso tenha w e é igual ao permutado, retorne SUCESSO

    return FAIL_RETURN;
}


int seleciona_w_previos (transacao_t ** antecessoras, int time, int n) {
    int qnt = 0;
    fprintf(stderr, "%d precisa ter : ", time);
    for (int i = 0; i < n; i++) {
        operacoes_t* primeiro_r = seleciona_primeira_op_em_t(original[i], WRITE);
        if( (primeiro_r) && (primeiro_r->time < time) ) {
            fprintf(stderr, "<%d> ", original[i]->transation_id);
            antecessoras[qnt] = original[i];
            qnt++;
        }
    }
    fprintf(stderr, "ocorrendo antes. No total %d\n", qnt);
    return qnt;
}

int remove_da_lista (int id, transacao_t** lista, int tam_lista) {
    for(int i = 0; i < tam_lista; i++){
        if(lista[i]->transation_id == id){
            lista[i] = NULL;
            return 1;
        }
    }
    return 0;
}

int verifica_previos (transacao_t** lista, int tam_lista, transacao_t** a, int id, int tam_a) {
    if(tam_lista == 0) return  SUCCESS_RETURN;
    

    fprintf(stderr, "%d: Ocorrem: ", tam_lista);
    int faltam = tam_lista;
    for(int i = 0; i < tam_a; i++) {
        if(a[i]->transation_id == id){
            fprintf(stderr, ". Vish, cabou\n");
            return FAIL_RETURN;
        }

        if(remove_da_lista(a[i]->transation_id, lista, tam_lista) == 1){
            fprintf(stderr, "%d ", a[i]->transation_id);
            faltam --;
        }

        if(faltam <= 1){
            fprintf(stderr, "! Todos\n");
            return SUCCESS_RETURN;
        }
    }
    fprintf(stderr, ". E só, faltaram %d\n", faltam);

    return FAIL_RETURN;
}

int valida_w_antes_de_r(transacao_t **a, int n){

    // encontra ultimo r em Ti de tempo t
    // percorre antecessores e anota quem possui write com tempo < t
    // verifica se de fato vem antes
    // 

    transacao_t** antecessoras = malloc( (n-1) * sizeof(transacao_t*)); // lista de transações que devem preceder a atual

    operacoes_t* last_r_original;
    int qnt = 0;
    for(int i = 0; i < n; i ++){
        last_r_original = seleciona_ultima_op_em_t(original[i], READ);
        if(last_r_original){
            qnt = seleciona_w_previos(antecessoras, last_r_original->time, n);

            if(qnt == 0){ // Caso especial, vamos garantir que no permutado também não tem write antes
                for(int j = 0; j < n; j++){
                    if(a[j] == original[i]) j = n;
                    else {
                        if(seleciona_primeira_op_em_t(a[j], WRITE) != NULL)
                            return FAIL_RETURN;
                    }
                }
            } else if(verifica_previos(antecessoras, qnt, a, original[i]->transation_id, n) == FAIL_RETURN){
                return FAIL_RETURN;
            }
        }
    }

    return SUCCESS_RETURN;
}


int compara(transacao_t **a, int n){
    if(!valida_ultimo(a, n)) return FAIL_RETURN;
fprintf(stderr, "É valido 1\n");
    if(!valida_w_antes_de_r(a, n)) return FAIL_RETURN;
fprintf(stderr, "É valido 2\n");


    return SUCCESS_RETURN;
}


void printa(transacao_t **a, int n){
    fprintf(stderr, "<----- ");

    for (int i = 0; i < n; i++) {
        fprintf(stderr, "%d ", a[i]->transation_id);
    }

    fprintf(stderr, "------>\n");
}



int permuta (transacao_t** e, int l, int r){
    fprintf(stderr, "P %d %d\n", l, r);

    if(l == r){
        printa(e, r);
        printa(original, r);
        if(compara(e, r) == SUCCESS_RETURN) return SUCCESS_RETURN;  // Se um dos permutados der certo, é equivalente por visão
    }

    for(int i = l; i < r; i++){
        troca(e, l, i);
        if(permuta(e, l+1, r) == SUCCESS_RETURN) return SUCCESS_RETURN;
        troca(e, l, i);
    }
    return FAIL_RETURN; // Se nenhum dos permutados der certo, não é equivalente por visão
}


int check_view(transacao_t **escalation, int n, char att){
    original = escalation;
    attribute = att;

    fprintf(stderr, "!!!!!!!!!!!!!1 Fazendo para %c\n", attribute);

    transacao_t ** permutada = malloc(n*sizeof(transacao_t*));
    for(int i = 0; i < n; i++){
        permutada[i] = original[i];
    }

    int answer = permuta(permutada, 0, n);

    free(permutada);

    return answer;
}