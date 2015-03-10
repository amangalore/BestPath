// Aman Mangalore
// aamangal
// List.c
// List ADT

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "List.h"

int exit_status = EXIT_SUCCESS;
size_t nitems = 1;

// Node Struct
typedef struct Node Node;
struct Node{
    int data;
    Node *next;
    Node *prev;
};

// List Object Struct
struct ListObj{
    Node *head;
    Node *tail;
    Node *cursor;
    int index;
};

// Constructors-Destructors
List newList(void){
    List this = malloc(sizeof(struct ListObj));
    assert (this != NULL);
    this->head = this->tail = this->cursor = NULL;
    this->index = -1;
    return this;
}

void freeList(List* pL){
    if(pL != NULL && *pL != NULL){
        while(length(*pL) > 0){
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}
// Access Functions
int length(List L){
    int count = 0;
    Node *curr = NULL;
    for(curr = L->head; curr != NULL; curr = curr->next){
        count++;}
    return count;
}

int getIndex(List L){
    int count = 0;
    if(L->index == -1){
        return L->index;}
    Node *curr;
    for(curr = L->head; curr != NULL; curr = curr->next){
        if(curr == L->cursor){break;}
        count++;}
    return count;
}

int front(List L){
    if(length(L) == 0){
        fprintf(stderr, "%s\n", "Empty List.");
        exit_status = EXIT_FAILURE;
        exit(EXIT_FAILURE);
    }else{
        return L->head->data;}
}

int back(List L){
    if(length(L) == 0){
        fprintf(stderr, "%s\n", "Empty List.");
        exit_status = EXIT_FAILURE;
        exit(EXIT_FAILURE);
    }else{
        return L->tail->data;}
}

int getElement(List L){
    if(length(L) == 0){
        fprintf(stderr, "%s\n", "Empty List.");
        exit_status = EXIT_FAILURE;
        exit(EXIT_FAILURE);}
    else if(getIndex(L) < 0){
        fprintf(stderr, "%s\n", "Cursor is not defined.");
        exit_status = EXIT_FAILURE;
        exit(EXIT_FAILURE);}
    else{
        return L->cursor->data;}
}

int equals(List A, List B){
    if(length(A) != length(B)){
        return 0;}
    Node *current = NULL;
    Node *current2 = A->head;
    for(current = B->head; current != NULL; current = current->next){
        if(current->data != current2->data){return 0;}
        current2 = current->next;}
    return 1;
}

// Manipulation Procedures
void clear1(List L){
    L->head = L->tail = L->cursor = NULL;
    L->index = -1;
}

void moveTo(List L, int i){
    if(i < 0 || i > length(L) - 1){
        L->index = -1;
        L->cursor = NULL;
        return;}
    L->cursor = L->head;
    int n = 0;
    while(n != i){
        L->cursor = L->cursor->next;
        ++n;}
    L->index = i;
    return;
}

void movePrev(List L){
    if(getIndex(L) <= 0){
        L->cursor = NULL;
        L->index = -1;
        return;}
    else if(getIndex(L) <= length(L) - 1){
        L->cursor = L->cursor->prev;
        --L->index;
        return;}
    else{
        return;}
}

void moveNext(List L){
    if(getIndex(L) == -1){
        return;}
    else if(getIndex(L) == length(L) - 1){
        L->cursor = NULL;
        L->index = -1;
        return;}
    else{
        L->cursor = L->cursor->next;
        ++L->index;
        return;}
}

void prepend(List L, int data){
    Node *temp = calloc(nitems, sizeof(struct Node));
    assert(temp != NULL);
    temp->data = data;
    if(L->head == NULL){
        L->head = temp;
        L->tail = temp;
        L->head->prev = NULL;
        L->head->next = NULL;
        L->cursor = L->head;
        L->index = 0;}
    else{
        temp->next = L->head;
        temp->prev = NULL;
        L->head->prev = temp;
        L->head = temp;}
    if(L->index != -1){
        ++L->index;}
    return;
}

void append(List L, int data){
    Node *temp = calloc(nitems, sizeof(struct Node));
    assert(temp != NULL);
    temp->data = data;
    if(L->head == NULL){
        temp->next = NULL;
        temp->prev = NULL;
        L->head = temp;
        L->tail = temp;
        L->cursor = L->head;
        L->index = 0;}
    else if(L->head->next == NULL){
        temp->prev = L->head;
        temp->next = NULL;
        L->head->next = temp;
        L->tail = temp;}
    else{
        temp->prev = L->tail;
        L->tail->next = temp;
        temp->next = NULL;
        L->tail = temp;}
    return;
}

void insertBefore(List L, int data){
    if(length(L) == 0){
        fprintf(stderr, "%s\n", "Empty List.");
        exit_status = EXIT_FAILURE;
        exit(EXIT_FAILURE);}
    if(getIndex(L) < 0){
        fprintf(stderr, "%s\n", "Cursor is not defined.");
        exit_status = EXIT_FAILURE;
        exit(EXIT_FAILURE);}
    Node *temp = malloc(sizeof(Node));
    assert(temp != NULL);
    temp->data = data;
    if(L->cursor == L->head){
        temp->next = L->head;
        L->head->prev = temp;
        temp->prev = NULL;
        L->head = temp;}
    else if(L->cursor == L->tail){
        temp->next = L->tail;
        temp->prev = L->tail->prev;
        L->tail->prev->next = temp;
        L->tail->prev = temp;}
    else{
        temp->next = L->cursor;
        temp->prev = L->cursor->prev;
        L->cursor->prev->next = temp;
        L->cursor->prev = temp;}
    ++L->index;
}

void insertAfter(List L, int data){
    if(length(L) == 0){
        fprintf(stderr, "%s\n", "Empty List.");
        exit_status = EXIT_FAILURE;
        exit(EXIT_FAILURE);}
    if(getIndex(L) < 0){
        fprintf(stderr, "%s\n", "Cursor is not defined.");
        exit_status = EXIT_FAILURE;
        exit(EXIT_FAILURE);}
    Node *temp = malloc(sizeof(Node));
    assert(temp != NULL);
    temp->data = data;
    if(L->cursor == L->head){
        temp->prev = L->head;
        temp->next = L->head->next;
        L->head->next = temp;}
    else if(L->cursor == L->tail){
        temp->prev = L->tail;
        L->tail->next = temp;
        temp->next = NULL;
        L->tail = temp;}
    else{
        temp->next = L->cursor->next;
        temp->prev = L->cursor;
        L->cursor->next->prev = temp;
        L->cursor->next = temp;}
    return;
}

void deleteFront(List L){
    if(length(L) == 0){
        fprintf(stderr, "%s\n", "Empty List.");
        exit_status = EXIT_FAILURE;
        exit(EXIT_FAILURE);}
    Node *tmp = L->head;
    if(L->head->next == NULL){
        L->head->next = L->head->prev = NULL;
        L->tail->next = L->tail->prev = NULL;
        L->head = L->tail = NULL;}
    else{
        L->head = L->head->next;
        L->head->prev = NULL;}
    if((L->index) > 0){
        --L->index;}
    if(L->index == 0){
        L->cursor = NULL;
        L->index = -1;}
    free(tmp);
    return;
}

void deleteBack(List L){
    if(length(L) == 0){
        fprintf(stderr, "%s\n", "Empty List.");
        exit_status = EXIT_FAILURE;
        exit(EXIT_FAILURE);}
    Node *tmp = L->tail;
    if(L->tail->prev == NULL){
        L->tail->next = L->tail->prev = NULL;
        L->head->next = L->head->prev = NULL;
        L->tail = L->head = NULL;}
    else{
        L->tail = L->tail->prev;
        L->tail->next = NULL;}
    if(L->index == length(L) - 1){
        L->cursor = NULL;
        L->index = -1;}
    free(tmp);
    return;
}

void deleteAll(List L){
    Node *tmp = NULL;
    if(length(L) == 0){
        fprintf(stderr, "%s\n", "Empty List.");
        exit_status = EXIT_FAILURE;
        exit(EXIT_FAILURE);}
    if(getIndex(L) < 0){
        fprintf(stderr, "%s\n", "Cursor is not defined.");
        exit_status = EXIT_FAILURE;
        exit(EXIT_FAILURE);}
    if(getIndex(L) == 0){
        deleteFront(L);}
    else if(getIndex(L) == length(L) - 1){
        deleteBack(L);}
    else{
        tmp = L->cursor;
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        L->cursor = NULL;
        L->index = -1;}
    free(tmp);
    return;
}

// Other operations
void printList(FILE *out, List L){
    char str[16];
    Node *curr;
    for(curr = L->head; curr != NULL; curr = curr->next){
        sprintf(str, "%d ", curr->data);
        fputs(str, out);}
    return;
}

List copyList(List L){
    List listCopy = newList();
    Node *current = L->head;
    Node *temp2 = NULL;
    while(current != NULL){
        Node *temp = malloc(sizeof(struct Node));
        assert(temp != NULL);
        temp->data = current->data;
        if(listCopy->head == NULL){
            listCopy->head = temp;
            listCopy->tail = temp;
            temp->prev = NULL;
            temp->next = NULL;}
        else if(listCopy->head->next == NULL){
            temp->prev = listCopy->head;
            temp->next = NULL;
            listCopy->head->next = temp;
            temp2 = temp;}
        else{
            temp->prev = temp2;
            temp->next = NULL;
            temp2->next = temp;
            temp2 = temp;
            listCopy->tail = temp;}
        current = current->next;
    }
    return listCopy;
}
