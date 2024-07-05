// Generic List (data == void pointer)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "gllist.h"

struct node {
  void *data;
  struct node *next;
};

static void removeNodes(gllist l) {
  if(l!=NULL) {
    removeNodes(l->next);
    free(l);
  }
}

gllist createList(void) { return NULL; }
void destroyList(gllist* l) { removeNodes(*l); *l = NULL; }

void *getItem(gllist l,int n) {
  int size = listSize(l);
  if((n < 0) || (n >= size)) return NULL;
  else {
    gllist ptr = l;
    for (int i = 0; i < n; i++) ptr=ptr->next;
    return ptr->data;
  }
}

int addItem(gllist* l,void *n) {
  gllist tp = malloc(sizeof(struct node));
  tp->data = n; tp->next = NULL;
  int newIndex = 0;
  if(listEmpty(*l)) *l = tp;
  else {
    gllist ptr = *l; int index=0;
    while(ptr->next != NULL) {
      ptr = ptr->next; index++;
    }
    ptr->next = tp; newIndex = index+1;
  }
  return newIndex;
}

int insertItem(gllist *l,int i,void *n) {
  int size = listSize(*l);
  if(i<0 || i>size) return -1;
  if (i==size)      return (addItem(l,n));
  gllist tp = malloc(sizeof(struct node));
  tp->data = n; tp->next = NULL;
  if(i == 0) {
    tp->next = *l; *l = tp; 
  } else {
    gllist ptr = *l;
    for(int j = 0; j < i-1; j++) ptr = ptr->next;
    tp->next = ptr->next; ptr->next = tp;
  }
  return i;
}

bool removeItem(gllist* l,int n) {
  int size = listSize(*l);
  if(size==0 || n<0 || n>=size) return false;
  gllist ptr = *l;
  if(n==0) {
    *l = (*l)->next; free(ptr); 
  } else {
    for(int i = 0; i < n-1; i++) ptr = ptr->next;
    gllist tp = ptr->next;
    ptr->next = ptr->next->next;
    free(tp);
  }
  return true;
}

bool setItem(gllist l,int n,void *val) {
  int size = listSize(l);
  if(size==0 || n<0 || n>=size) return false;
  gllist ptr = l;
  for(int i = 0; i < n; i++) ptr = ptr->next;
  ptr->data = val;
  return true;
}

int findItem(gllist l, void *item) {
  gllist ptr = l;
  for(int i = 0; ptr != NULL; i++) {
    if(ptr->data == item) return i;
    ptr=ptr->next;
  }
  return -1;
}

int listSize(gllist l) {
  int count = 0;
  gllist ptr = l;
  while(ptr != NULL) {
    ptr = ptr->next; count++;
  }
  return count;
}

bool listEmpty(gllist l) { return l==NULL; }
bool listFull(gllist l) { return false; }

bool contains(gllist l,void *n) {
  gllist ptr = l;
  while(ptr != NULL) {
    if(ptr->data == n) return true;
    ptr = ptr->next;
  }
  return false;
}
