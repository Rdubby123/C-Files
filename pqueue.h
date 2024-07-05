#ifndef PQUEUE_H
#define PQUEUE_H
#include <stdbool.h>

typedef struct pqueueType *pq;

// passing a NULL pq to any routine (except freepq) is undefined

pq createpq();   // creates a pqueue
void freepq(pq); // deallocates a pqueue; passing NULL ok. All memory
                 // management of the data should be left to the user

pq copy(pq q);  // returns an exact (shallow) copy of p

/* priority p is defined as 0 <= p <= 100 where 0 is the lowest, 100 the highest */

void enq(pq q,void *item,int p); // inserts item with priority p into
                                 // queue q; items added with the same
                                 // priority are added after previous 
                                 // items with that priority

void deq(pq);    // removes item at front of q
void *front(pq); // returns item at front of q without removing it;
                 // is undefined if q is empty
int frontP(pq);  // returns priority of item at front without removing it;
                 // is undefined if q is empty
void *rear(pq);  // returns item at rear without removing it;
                 // is undefined if q is empty
int rearP(pq);   // returns priority of item at rear without removing it;
                 // is undefined if q is empty

int countP(pq q,int p); // returns count of items in q at priority p        

int pqSize(pq);  // current queue size

bool pqEmpty(pq);
bool pqFull(pq);

char *pqToString(pq,char *f(const void*)); // returns a string representation of queue;
                                           // string must contain data item & priority
                                           // in priority order highest to lowest

#endif
