// Ryan DuBrueler & Shreyas Harish

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.h"
#include "gllist.h"
struct pqueueType{
    gllist data;
    gllist priority;
};

pq createpq(){ // creates a pqueue
    pq queue = malloc(sizeof(struct pqueueType));
    queue->data = createList();
    queue->priority = createList();
    return queue;
}   
void freepq(pq queue){ // deallocates a pqueue; 
    if(queue==NULL){return;}
    free(queue);
}  

pq copy(pq queue){
    pq copy = createpq();
    if(!pqEmpty(queue)){
    int qsize = pqSize(queue);
    for(int i=0; i<qsize; i++) addItem(&(copy->data),getItem(queue->data,i));
    // above will add the data items to the data list
    for(int i=0; i<qsize; i++) addItem(&(copy->priority),getItem(queue->priority,i));
    // above will add the priority items to the priority list
    }
    return copy;
}// returns an exact (shallow) copy of p

// priorityOrder = 100, 99, 98
void enq(pq q, void *item, int p) {
    int *priority = malloc(sizeof(int));
    *priority = p;
    int index = 0;
    if(!pqEmpty(q))while (index < pqSize(q) && *priority <= *(int *)getItem(q->priority, index)) {index++;} 
    // above finds where to insert item in queue by incrementing index
    insertItem(&(q->data), index, item);
    insertItem(&(q->priority), index, priority);
}
void deq(pq q){ // removes item at front of q
    if(!pqEmpty(q)){removeItem(&q->data,0);removeItem(&q->priority,0);}
    else return; // "undefined"
}   

void *front(pq q){ // returns item at front of q without removing it
    if(!pqEmpty(q))return (int*)getItem(q->data,0); 
    else return (void*)0; // "undefined"
} 
        
int frontP(pq q){ // returns priority of item at front without removing it
    if(!pqEmpty(q))return *(int*)getItem(q->priority,0); 
    else return 0; // "undefined"
}  
        
void *rear(pq q){ // returns item at rear without removing it
    if(!pqEmpty(q))return (int*)getItem(q->data,listSize(q->data)-1);
    else return (void*)0; // "undefined"
}  

int rearP(pq q){ // returns priority of item at rear without removing it
    if(!pqEmpty(q))return *(int*)getItem(q->priority,listSize(q->priority)-1);
    else return 0; // "undefined"
}   

int countP(pq q, int p) {
    if (pqEmpty(q)) return 0;
    int count = 0,i = 0;
    while (i < pqSize(q)) {
        if (*(int*)getItem(q->priority, i) == p) count++;
        i++;
    }
    return count;
}       

int pqSize(pq q){ return listSize(q->data);}  // current queue size 
bool pqEmpty(pq q){ return pqSize(q)==0; } // list empty?
bool pqFull(pq q){ return listFull(q->priority); } // list full?

char *pqToString(pq q, char *(*f)(const void*)) {
    char *str = malloc(pqSize(q)*sizeof(int)*2+3);
    strcpy(str, ""); // blank string to print to or null pointer case
    if(!pqEmpty(q)){
        char *container[100];
        for(int i = 0; i<listSize(q->data); i++){
            container[i] = malloc(sizeof(int)*2+1);
            sprintf(container[i], "(%s, %s) ",f((int*)getItem(q->data,i)),f((int*)getItem(q->priority,i)));
            strcat(str,container[i]);
        }
    }
    return str;
    }












   
