#include <stdbool.h>
#include <limits.h>
#ifndef LLIST_H
#define LLIST_H
typedef struct node *llist;
#define NULL_ITEM INT_MIN
llist createList(void);
// returns a newly created empty list; must be called before
// using list routines
void destroyList(llist*);
// deallocates list; operation undefined if list hasn't
// been created with createList; sets list to NULL
int getItem(llist,int);
// returns item at location if it exists, otherwise
// returns NULL_ITEM
int addItem(llist*,int);
// adds item to end of list; returns index
// of new item or -1 if add was unsuccesful
int insertItem(llist *l,int i,int);
// inserts item into list at position; returns
// index of new item or -1 if unsuccessful; operation is successful
// when 0 <= i <= listSize(l) (0 is the first item in the list)
bool removeItem(llist*,int);
// removes item at position, returns true if operation
// successful, false otherwise
bool setItem(llist,int i,int);
// replaces item at location i, returns true if operation
// is succesful, false otherwise
int findItem(llist,int n);
// returns index of item n, -1 if not found
int listSize(llist);
// returns current number of items in list
bool listEmpty(llist);
// returns true if list is empty, false otherwise
bool listFull(llist);
// returns true if list is full, false otherwise
bool contains(llist,int);
// returns true if item in list, false otherwise
#endif
