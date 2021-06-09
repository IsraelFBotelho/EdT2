#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct nodeStruct{ 
    Info info;
    struct nodeStruct *next;
    struct nodeStruct *back;
} NodeStruct;

typedef struct listStruct{
    NodeStruct *head;
    NodeStruct *tail;
    int size;
    int visit;
} ListStruct;


typedef struct snodeStruct{
    Info info;
    struct snodeStruct *next;
} SNodeStruct;

typedef struct slistStruct{
    int nx;
    int size;
    int visit;
    SNodeStruct *head;
    SNodeStruct *tail;
    SNodeStruct *array;
} SListStruct;


/*
        Funções de Lista Dinamica Duplamente Encadeada
*/

void dRemoveNode(List list, Node node);


List createList(){
    ListStruct *new = (ListStruct *) malloc(sizeof(ListStruct));

    new->head = NULL;
    new->tail = NULL;
    new->size = 0;
    new->visit = 0;

    return new;
}

void endList(List list, int* numberVisits){
    ListStruct *list_aux = (ListStruct*) list;
    if(list_aux->size != 0){
        NodeStruct *aux;
        while(list_aux->head){
            aux = list_aux->head;
            list_aux->visit++;
            removeListNode(list, aux);
        }
    }
    if(numberVisits){
        *numberVisits = list_aux->visit;
    }
    free(list_aux);
}

void insertListElement(List list, Info info){
    ListStruct *list_aux = (ListStruct *) list;

    NodeStruct *new = (NodeStruct *) malloc(sizeof(NodeStruct));

    if(list_aux->size == 0){
        new->info = info;
        new->next = NULL;
        new->back = NULL;
        list_aux->head = new;
        list_aux->tail = new;
        list_aux->size++;
    }else{
        new->info = info;
        new->next = NULL;
        new->back = list_aux->tail;
        list_aux->tail->next = new;
        list_aux->tail = new;
        list_aux->size++;
    }
}

void removeListNode(List list, Node node){
    ListStruct *list_aux = (ListStruct *) list;
    NodeStruct *node_aux = (NodeStruct *) node;
    

    if(list_aux->size == 0)
        return;

    if(!node_aux){
        return;
    }
       
    NodeStruct *aux;

    if(node_aux->back){
        aux = node_aux->back;
        list_aux->visit++;
        aux->next = node_aux->next;
    }else{
        list_aux->head = node_aux->next;
    }

    if(node_aux->next){
        aux = node_aux->next;
        list_aux->visit++;
        aux->back = node_aux->back;
    }else{
        list_aux->tail = node_aux->back;
    }

    free(node_aux);
    list_aux->size--;
}

Info getListInfo(Node node){
    NodeStruct *node_aux = (NodeStruct *) node;

    return node_aux->info;
}

Node getListFirst(List list){
    ListStruct *list_aux = (ListStruct *) list;
    list_aux->visit++;

    return list_aux->head;
}

Node getListNext(List list, Node node){
    NodeStruct *node_aux = (NodeStruct *) node;
    ListStruct *list_aux = (ListStruct *) list;
    list_aux->visit++;

    return node_aux->next;
}

Node getListBack(List list, Node node){
    NodeStruct *node_aux = (NodeStruct *) node;
    ListStruct *list_aux = (ListStruct *) list;
    list_aux->visit++;

    return node_aux->back;
}

int getListSize(List list){
    ListStruct *list_aux = (ListStruct *) list;

    return list_aux->size;
}

int getListVisit(List list){
    ListStruct *list_aux = (ListStruct *) list;

    return list_aux->visit;
}
