/*
    This code contains functions used in main.c. 
        1. load_tuples
        2. gv_tuples
        3. set_tuples
        4. save_tuples
        5. add_tuples
        6. mult_tuples
        7. destroy_tuples
    
    Explanations for each function and their inputs, outputs, and effects are detailed with functions.

    Algorithms used for functions:
        load_tuples
        gv_tuples
        set_tuples
        save_tuples
        add_tuples
        mult_tuples
        destroy_tuples
    
    Matthew Wei
    partners: mswei2, bmaedge2
    April 14, 2022
*/

#include "sparsemat.h"
#include <stdio.h>
#include <stdlib.h>

sp_tuples * load_tuples(char* input_file)
{
    int m, n, row, col;
    double val;
    sp_tuples* tuples = (sp_tuples*)malloc(sizeof(sp_tuples));
    FILE* file = fopen(input_file, "r");
    fscanf(file, "%d %d\n", &m, &n);
    tuples->m = m;
    tuples->n = n;
    tuples->tuples_head = NULL;
    tuples->nz = 0;
    while (fscanf(file, "%d %d %lf\n", &row, &col, &val)==3) {
        set_tuples(tuples, row, col, val);
    }
    fclose(file);
    return tuples;
}

double gv_tuples(sp_tuples * mat_t,int row,int col)
{
    sp_tuples_node* node = mat_t->tuples_head;
    while (node!=NULL) {
        if (node->row==row && node->col==col) {
            return node->value;
        }
        node = node->next;
    }
    return 0;
}

void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    sp_tuples_node* node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    sp_tuples_node* next_node = mat_t->tuples_head;
    node->row = row;
    node->col = col;
    node->value = value;
    node->next = NULL;
    if (mat_t->tuples_head == NULL) {
        mat_t->tuples_head = node;
        mat_t->nz++;
        return;
    }
    sp_tuples_node* prev_node = mat_t->tuples_head;
    if (node->row==prev_node->row && node->col==prev_node->col && node->value==0) {
        sp_tuples_node* temp = next_node->next;
        mat_t->tuples_head = temp->next;
        free(node);
        mat_t->nz--;
        return;
    } else if (node->row<prev_node->row) {
        mat_t->tuples_head = node;
        node->next = next_node;
        mat_t->nz++;
        return;
    } else if (node->row==prev_node->row && node->col<prev_node->col) {
        mat_t->tuples_head = node;
        node->next = next_node;
        mat_t->nz++;
        return;
    }
    while (next_node!=NULL) {
        if (node->row==next_node->row && node->col==next_node->col) {
            if (node->value==0) {
                sp_tuples_node* temp = next_node->next;
                prev_node->next = temp->next;
                free(node);
                mat_t->nz--;
                return;
            }
            next_node->value = node->value;
            free(node);
            return;
        }
        if (node->row>next_node->row || (node->row==next_node->row && node->col>next_node->col)) {
            prev_node->next = next_node;
            next_node = next_node->next;
            continue;
        } else if (node->row<next_node->row) {
            node->next = next_node;
            prev_node->next = node;
            mat_t->nz++;
            return;
        } else if (node->row==next_node->row && node->col<next_node->col) {
            node->next = next_node;
            prev_node->next = node;
            mat_t->nz++;
            return;
        }
    }
    next_node->next = node;
    return;
}

void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE* file = fopen(file_name, "w");
    sp_tuples_node* node = mat_t->tuples_head;
    fprintf(file, "%d %d\n", mat_t->m, mat_t->n);
    while (node != NULL) {
        fprintf(file, "%d %d %lf\n", node->row, node->col, node->value);
        node = node->next;
    }
    fclose(file);
	return;
}

sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    sp_tuples* retmat = (sp_tuples*)malloc(sizeof(sp_tuples));
    retmat->m = matA->m;
    retmat->n = matA->n;
    retmat->nz = 0;
    retmat->tuples_head = NULL;
    sp_tuples_node* nodeA = retmat->tuples_head;
    sp_tuples_node* nodeB = retmat->tuples_head;
    while (nodeA!=NULL) {
        set_tuples(retmat, nodeA->row, nodeA->col, nodeA->value);
        nodeA = nodeA->next;
    }
    while (nodeB!=NULL) {
        double Aval = gv_tuples(retmat, nodeB->row, nodeB->col);
        set_tuples(retmat, nodeB->row, nodeB->col, nodeB->value + Aval);
        nodeB = nodeB->next;
    }
	return retmat;
}

/*
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return retmat;
}
*/
	
void destroy_tuples(sp_tuples * mat_t){
    sp_tuples_node* node = mat_t->tuples_head;
    sp_tuples_node* next = NULL;
    while (node!=NULL) {
        next = node->next;
        free(node);
        node = next;
    }
    free(mat_t);
    return;
}  