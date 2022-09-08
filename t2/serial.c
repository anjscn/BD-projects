/**
 * @file serial.c
 * @author GRR20173559 Camile Nunes dos Anjos (cna17@inf.ufpr.br)
 * @author GRR20190378 Eduardo Rosso Barbosa (erb19@inf.ufpr.br)
 * @brief 
 * @version 0.1
 * @date 2022-09-04
**/

#include "header.h"
#include "serial.h"
#include "transacao.h"

vertice_t** vertices;
int max_num_vertices, num_vertices;


vertice_t* new_vertice(int id){
    vertice_t* v = malloc(sizeof(vertice_t));

    vertice_t** reachables = malloc(num_vertices * sizeof(vertice_t*));
    for(int i = 0; i < num_vertices; i++){
        reachables[i] = NULL;
    }

    v->id = id;
    v->reachables = reachables;

    vertices[num_vertices] = v;

    num_vertices++;

    return v;
}

vertice_t* find_vertice(int id){
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i]->id == id)
            return vertices[i];
    }

    return new_vertice(id);
}

// return if a can reach  b
int is_reachable(vertice_t* a, vertice_t* b){

    if(a == b)
        return SUCCESS_RETURN;

    for (int i = 0; i < max_num_vertices; i++)
    {
        if(a->reachables[i] == b)
            return SUCCESS_RETURN;
        if(a->reachables[i] == NULL)
            return FAIL_RETURN;
    }

    return FAIL_RETURN;
}

// add edge from a to b
int add_edge(vertice_t *a, vertice_t *b){
    if(a == b)
        return -1;  // ENCONTRADO CICLO

    for(int i = 0; i < num_vertices; i++){
        if(a->reachables[i] == NULL){
            a->reachables[i] = b;
            return SUCCESS_RETURN;
        }
    }
    return FAIL_RETURN;
}

int update_reachables(vertice_t* a, vertice_t* b){
    for(int i = 0; i < num_vertices; i++){
        if(is_reachable(vertices[i], a)){
            if(add_edge(vertices[i], b) == -1){ // ENCONTRADO CICLO
                return -1;
            }
        } 
    }
    return SUCCESS_RETURN;
}



int new_edge(transacao_t *t1, transacao_t *t2){
    vertice_t *v1 = find_vertice(t1->transation_id);
    vertice_t *v2 = find_vertice(t2->transation_id);

    add_edge(v1, v2);

    if(update_reachables(v1, v2) == -1){    // ENCONTRADO CICLO
        return -1;
    }

    
    //fprintf(stderr, "cria aresta %d-%d\n", t1->transation_id, t2->transation_id);
    return SUCCESS_RETURN;
}

// dá free em tudo o que precisa
void destroy_serial(){
    for (int i = 0; i < num_vertices; i++)
    {
        free(vertices[i]->reachables);
        free(vertices[i]);
    }
    
    free(vertices);
}   

int check_serial(transacao_t **escalation, int n){
    num_vertices = 0;

    max_num_vertices = n;

    vertices = malloc(max_num_vertices* sizeof(vertice_t*));


    transacao_t *t1, *t2;
    for (int i = 0; i < n; i++) {
        t1 = escalation[i];
        for(int j = 0; j < t1->num_ops; j++){

            if(t1->ops[j]->operation == WRITE){ // Acomoda todos os casos
                for(int k = 0; k < n; k++){
                    if(k != i){
                        t2 = escalation[k];
                        for(int r = 0; r < t2->num_ops; r++){
                            if(t2->ops[r]->operation != COMMIT){
                                if(t2->ops[r]->time < t1->ops[j]->time){
                                    if (new_edge(t2, t1) == -1){
                                        destroy_serial();
                                        return FAIL_RETURN;
                                    }
                                }else{
                                    if(t2->ops[r]->operation == READ){
                                        if (new_edge(t1, t2) == -1){
                                            destroy_serial();    
                                            return FAIL_RETURN;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        
        }
    }
    destroy_serial();
    return SUCCESS_RETURN;
}

