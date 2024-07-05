#include <stdbool.h>
#include <limits.h>
#ifndef GLLIST_H
#define GLLIST_H

typedef struct node *gllist;

gllist createList(void);
 // returns a newly created empty list; must be called before
 // using list routines
void destroyList(gllist*);
 // deallocates list; operation undefined if list hasn't
 // been created with createList; sets list to NULL

void *getItem(gllist,int);
 // returns item at location if it exists, otherwise
 // returns NULL_ITEM

int addItem(gllist*,void *item);
 // adds item to end of list; returns index
 // of new item or -1 if add was unsuccesful
int insertItem(gllist *l,int i, void *);
 // inserts item into list at position; returns
 // index of new item or -1 if unsuccessful; operation is successful
 // when 0 <= i <= listSize(l) (0 is the first item in the list)  

bool removeItem(gllist*,int);
 // removes item at position, returns true if operation
 // successful, false otherwise
bool setItem(gllist,int i,void *item);
 // replaces item at location i, returns true if operation
 // is succesful, false otherwise

int findItem(gllist,void *n);
// returns index of item n, -1 if not found

int listSize(gllist);
 // returns current number of items in list 
bool listEmpty(gllist);
 // returns true if list is empty, false otherwise
bool listFull(gllist);
 // returns true if list is full, false otherwise
bool contains(gllist,void*);
// returns true if item in list, false otherwise
#endif
