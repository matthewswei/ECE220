/*
    This code contains functions used in main.c. The goal of this program is create a sparse matrix for a given
    input. Sparse matricies are matricies with more 0s than values so memory wise, it is more efficient to create
    a linked list instead of an array. The code in this file essentially just creates a linked list with each
    node containing a value, its spot in the matrix, and the address to the next node. The list of functions is
    presented below:
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
            Simple file read is used. Reads file and transfers content into variables for initialization. For
            node initializations, it reads the file and initializes each node as each line goes on.
        gv_tuples
            Goes through the linked list and returns the value at a specific node. If no node is found, returns
            false.
        set_tuples
            Creates node only if value is determined to be able to be inserted. First it makes sure the base case
            is initialized with the first node. Then it checks for individual cases afterwards. First is if the value
            is 0. If it is and no node is present, then it just leaves the function. If a node is present, then it goes
            through the list, finds the node, and deletes it. The other case is if there is a non-zero value. First it checks
            if the node is already present. If it is, it replaces the node value. The last case is if it is a new node. It
            will go through the list and insert the node in where it is needed. If it goes through the list and isn't inserted,
            the node will be inserted at the very end of the node.
        save_tuples
            Uses C file output to write linked list file. Used while loop to loop through every node as long as
            it is present.
        add_tuples
            Creates a matricies for return and initializes values. Then it copies the value of A onto the return
            matrix. After that it goes through the second matrix and adds its values onto the return matrix, adding
            nodes where needed.
        mult_tuples
            Not needed for class.
        destroy_tuples
            Frees memory of every node. First goes through each node and frees each node individually. Then it
            frees the linked list itself.
    
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
    //Checks base case with first node inserted
    if (mat_t->tuples_head==NULL && value!=0) {
        sp_tuples_node* node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
        node->row = row;
        node->col = col;
        node->value = value;
        node->next = NULL;
        mat_t->tuples_head = node;
        mat_t->nz++;
        return;
    }
    //Checks if value is 0 and deletes said node
    if (value==0) {
        if (gv_tuples(mat_t,row,col)!=0) {
            sp_tuples_node* node = mat_t->tuples_head;
            sp_tuples_node* prev_node = NULL;
            while (node!=NULL) {
                if (node->row==row && node->col==col) {
                    if (prev_node==NULL) {
                        mat_t->tuples_head = node->next;
                    }
                    prev_node->next = node->next;
                    free(node);
                    mat_t->nz--;
                    return;
                }
                prev_node = node;
                node = node->next;
            }
        }
        return;
    } else {  //Checks if value is an actual insertable value and finds its location
        if (gv_tuples(mat_t, row, col)!=0) {
            //This area of code replaces value if the node being inserted is already present
            sp_tuples_node* node = mat_t->tuples_head;
            while (node!=NULL) {
                if (node->row==row && node->col==col) {
                    node->value = value;
                    return;
                }
                node = node->next;
            }
        } else {
            //This section of the code inserts a new node that hasn't been inserted yet
            sp_tuples_node* node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
            sp_tuples_node* prev_node = NULL;
            sp_tuples_node* next_node = mat_t->tuples_head;
            node->row = row;
            node->col = col;
            node->value = value;
            node->next = NULL;
            while (next_node!=NULL) {
                //Loop checks for when node being inserted has reached a point where it is no longer smaller than the next node
                if (next_node->row>node->row || (node->row==next_node->row && next_node->col>node->col)) {
                    if (prev_node==NULL) {
                        mat_t->tuples_head = node;
                        node->next = next_node;
                    } else {
                        prev_node->next = node;
                        node->next = next_node;
                    }
                    return;
                }
                prev_node = next_node;
                next_node = next_node->next;
            }
            prev_node->next = node;
            mat_t->nz++;
            return;
        }
    }
    return;
}

void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE* file = fopen(file_name, "w");
    sp_tuples_node* node = mat_t->tuples_head;
    fprintf(file, "%d %d\n", mat_t->m, mat_t->n);
    while (node!=NULL) {
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
    sp_tuples_node* nodeA = matA->tuples_head;
    sp_tuples_node* nodeB = matB->tuples_head;
    while (nodeA!=NULL) {
        set_tuples(retmat, nodeA->row, nodeA->col, nodeA->value);
        nodeA = nodeA->next;
    }
    while (nodeB!=NULL) {
        double retval = gv_tuples(retmat, nodeB->row, nodeB->col);
        set_tuples(retmat, nodeB->row, nodeB->col, nodeB->value + retval);
        nodeB = nodeB->next;
    }
	return retmat;
}

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