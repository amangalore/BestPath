#include <stdio.h>
#include <stdlib.h>

#ifndef Lex_List_h
#define Lex_List_h

// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty Queue object.
List newList(void);

// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------
int length(List L);
int getIndex(List L);
int front(List L);
int back(List L);
int getElement(List L);
int equals(List A, List B);

// Manipulation procedures ----------------------------------------------------
void clear1(List L);
void moveTo(List L, int i);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L);
List copyList(List L);

#endif