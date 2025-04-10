#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* lista = (List*) malloc(sizeof(List));
    if (lista == NULL) exit(EXIT_FAILURE);

    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;

    return lista;
}

void * firstList(List * list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list == NULL || list->current == NULL || list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list == NULL || list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list == NULL || list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* nuevoNodo = createNode(data);
    if (list->head == NULL) {
        list->head = nuevoNodo;
        list->tail = nuevoNodo;
        list->current = nuevoNodo;
    } else {
        nuevoNodo->next = list->head;
        list->head->prev = nuevoNodo;
        list->head = nuevoNodo;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list == NULL || list->current == NULL) return;

    Node* nuevoNodo = createNode(data);
    if (list->current->next == NULL){
        list->current->next = nuevoNodo;
        nuevoNodo->prev = list->current;
        list->tail = nuevoNodo;
    } else {
        list->current->next->prev = nuevoNodo;
        nuevoNodo->next = list->current->next;
        nuevoNodo->prev = list->current;
        list->current->next = nuevoNodo;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list == NULL || list->current == NULL) return NULL;
    
    Node* currentTemp = list->current;
    void* datoTemp = list->current->data;

    if (currentTemp->prev == NULL){ // Si es head
        list->head = currentTemp->next;
    } else {
        currentTemp->prev->next = currentTemp->next;
    }

    if (currentTemp->next == NULL){ // Si es tail
        list->tail = currentTemp->prev;
    } else {
        currentTemp->next->prev = currentTemp->prev;
    }

    list->current = currentTemp->next;

    free(currentTemp);
    return datoTemp;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}