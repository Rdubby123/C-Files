#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "llist.h"

struct node {
  int data;
  struct node *next;
};

static void removeNodes(llist l) {
  if(l!=NULL) {
    removeNodes(l->next);
    free(l);
  }
}

llist createList(void) { return NULL; }
void destroyList(llist* l) { removeNodes(*l); *l = NULL; }

int getItem(llist l,int n) {
  int size = listSize(l);
  if((n < 0) || (n >= size)) return NULL_ITEM;
  else {
    llist ptr = l;
    for (int i = 0; i < n; i++) ptr=ptr->next;
    return ptr->data;
  }
}

int addItem(llist* l,int n) {
  llist tp = malloc(sizeof(struct node));
  tp->data = n; tp->next = NULL;
  int newIndex = 0;
  if(listEmpty(*l)) *l = tp;
  else {
    llist ptr = *l; int index=0;
    while(ptr->next != NULL) {
      ptr = ptr->next; index++;
    }
    ptr->next = tp; newIndex = index+1;
  }
  return newIndex;
}

int insertItem(llist *l,int i,int n) {
  int size = listSize(*l);
  if(i<0 || i>size) return -1;
  if (i==size)      return (addItem(l,n));
  llist tp = malloc(sizeof(struct node));
  tp->data = n; tp->next = NULL;
  if(i == 0) {
    tp->next = *l; *l = tp; 
  } else {
    llist ptr = *l;
    for(int j = 0; j < i-1; j++) ptr = ptr->next;
    tp->next = ptr->next; ptr->next = tp;
  }
  return i;
}

bool removeItem(llist* l,int n) {
  int size = listSize(*l);
  if(size==0 || n<0 || n>=size) return false;
  llist ptr = *l;
  if(n==0) {
    *l = (*l)->next; free(ptr); 
  } else {
    for(int i = 0; i < n-1; i++) ptr = ptr->next;
    llist tp = ptr->next;
    ptr->next = ptr->next->next;
    free(tp);
  }
  return true;
}

bool setItem(llist l,int n,int val) {
  int size = listSize(l);
  if(size==0 || n<0 || n>=size) return false;
  llist ptr = l;
  for(int i = 0; i < n; i++) ptr = ptr->next;
  ptr->data = val;
  return true;
}

int findItem(llist l, int item) {
  llist ptr = l;
  for(int i = 0; ptr != NULL; i++) {
    if(ptr->data == item) return i;
    ptr=ptr->next;
  }
  return -1;
}

int listSize(llist l) {
  int count = 0;
  llist ptr = l;
  while(ptr != NULL) {
    ptr = ptr->next; count++;
  }
  return count;
}

bool listEmpty(llist l) { return l==NULL; }
bool listFull(llist l) { return false; }

bool contains(llist l,int n) {
  llist ptr = l;
  while(ptr != NULL) {
    if(ptr->data == n) return true;
    ptr = ptr->next;
  }
  return false;
}