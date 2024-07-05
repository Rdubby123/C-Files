
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pqueue.h"

// Function to convert an integer pointer to a string
char *itos(const void *p) {
    char buff[40];
    snprintf(buff, sizeof(buff), "%d", *(int*)p);
    char *s = malloc(strlen(buff) + 1);
    if (s != NULL) {
        strcpy(s, buff);
    }
    return s;
}

// Function to print the contents of a priority queue
void printQueue(pq q) {
    printf("Priority Queue Contents: %s\n", pqToString(q, itos));
}

int main(void) {
    // Creating a priority queue
    pq q = createpq();

    // Testing enq and pqSize functions
    printf("Enqueuing items...\n");
    for (int i = 1; i <= 10; i++) {
        int *ptr = malloc(sizeof(int));
        if (ptr != NULL) {
            *ptr = i * 100;
            enq(q, ptr, i);
            printf("Enqueued item with priority %d\n", i);
            printf("Queue size: %d\n", pqSize(q));
        } else {
            fprintf(stderr, "Memory allocation failed\n");
        }
    }

    // Testing pqEmpty and pqFull functions
    printf("\nIs queue empty? %s\n", pqEmpty(q) ? "Yes" : "No");
    printf("Is queue full? %s\n", pqFull(q) ? "Yes" : "No");

    // Testing pqToString function
    printf("\n");
    printQueue(q);

    // Testing front, frontP, rear, and rearP functions
    printf("\nFront item: %d\n", *(int*)front(q));
    printf("Front priority: %d\n", frontP(q));
    printf("Rear item: %d\n", *(int*)rear(q));
    printf("Rear priority: %d\n", rearP(q));

    // Testing countP function
    printf("\nNumber of items with priority 3: %d\n", countP(q, 3));

    // Testing dequeue functionality
    printf("\nDequeuing items...\n");
    while (!pqEmpty(q)) {
        void *item = front(q);
        deq(q);
        printf("Dequeued item with value %d\n", *(int*)item);
        printf("Queue size: %d\n", pqSize(q));
        free(item);
    }

    // Freeing the priority queue
    freepq(q);

    // Testing copy function
    pq original = createpq();
    for (int i = 1; i <= 3; i++) {
        int *ptr = malloc(sizeof(int));
        if (ptr != NULL) {
            *ptr = i * 10;
            enq(original, ptr, i);
        } else {
            fprintf(stderr, "Memory allocation failed\n");
        }
    }

    printf("\nOriginal queue contents:\n");
    printQueue(original);

    pq copied = copy(original);
    printf("Copied queue contents:\n");
    printQueue(copied);

    // Modifying the original queue
    int *ptr = malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = 999;
        enq(original, ptr, 4);
        printf("\nModified original queue contents:\n");
        printQueue(original);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    // Verifying the copied queue remains unchanged
    printf("Copied queue contents (should be unchanged):\n");
    printQueue(copied);

    // Freeing the copied queue
    freepq(copied);

    // Freeing the original queue
    freepq(original);

    // Testing edge cases
    printf("\nTesting edge cases...\n");
    pq empty = createpq();
    printf("Front item of empty queue: %p\n", front(empty));
    printf("Front priority of empty queue: %d\n", frontP(empty));
    printf("Rear item of empty queue: %p\n", rear(empty));
    printf("Rear priority of empty queue: %d\n", rearP(empty));
    freepq(empty);

    return 0;
}



/*

#include <stdlib.h>
#include "unity.h"
#include "pqueue.h"
#include "unity_internals.h"
#include <string.h>
*/
 /*Notes:
-This unity test set relies on pqToString() to work as intended to verify the correct outcome(s) of a function call for 
 several of the test sets. If pqToString() isn't working feel free to change the file to primarily use frontP(), front(), 
 rearP(), and rear() instead. It's also possible to split the test cases into smaller test cases if needed.
-The string returned by pqToString assumes the form '(value, priority) ' in order of descending priority.
-If a test case calls a function that is incomplete, or is coded incorrectly, it can result in a program crash. In that 
 case comment out the test case function call(s) in main() that where the crash oocurred until the code is fixed.
-Passing a NULL pq is undefined in all functions apart from freepq(); NULL pq is only tested in test_createFreepq().
 This does not mean that passing a pq pointing to a NULL gllist (an empty queue) is undefined and this WILL be tested.
 Passing an empty queue returns "", 0, or a boolean. It's undefined in frontP(), front(), rearP(), and rear().
-pqFull() should always return false.
-freepq() frees the queues only. The memory management of data (the int* s) is left to the user.
-The functionality of a shallow copy of a queue is explained in test_copypq().
*/

/*
void setUp(void) { }
void tearDown(void) { }

char *itos(const void *p) {
    char buff[40];
    snprintf(buff, sizeof(buff), "%d", *(int*)p);
    char *s = malloc(strlen(buff) + 1);
    if (s != NULL) {
        strcpy(s, buff);
    }
    return s;
}

void test_createFreepq(){
    pq test= createpq();
    TEST_ASSERT_NOT_NULL_MESSAGE(test,"test_createAndDestroypq1-1");
    freepq(test); 
    test=NULL;
    freepq(test);//freepq shouldn't cause a program crash even if a NULL pq is passed into it
    freepq(test);
    TEST_ASSERT_NULL_MESSAGE(test,"test_createAndDestroypq1-2");
}
void test_copypq(){
    pq q= createpq();
    pq test=copy(q);
    char *s = pqToString(test, itos);

    TEST_ASSERT_NOT_NULL_MESSAGE(test,"test_copy1-0");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("", s,"test_copy1-1");

    int* num1= malloc(sizeof(int));
    int* num2= malloc(sizeof(int));
    int* num3= malloc(sizeof(int));
    int* num4= malloc(sizeof(int));
    int* num5= malloc(sizeof(int));
    int* num6= malloc(sizeof(int));
    int* num7= malloc(sizeof(int));
    int* num8= malloc(sizeof(int));
    
    *num1 = 543;
    enq(q, num1, 10);
    *num2 = 432;
    enq(q, num2, 1);
    *num3 = 43;
    enq(q, num3, 7);
    *num4 = 69;
    enq(q, num4, 70);
    *num5 = 420;
    enq(q, num5, 80);
    *num6 = 21;
    enq(q, num6, 21);
    *num7 = 9;
    enq(q, num7, 9);
    *num8 = 10;
    enq(q, num8, 10);
    
    test = copy(q);

    char *s1;
    char *s2;
   
    //since the queues are shallow copied, they share 'child' values, where if such a value is changed it alters
    //both queues, since both queues have a pointer to that data
    *num5 = 748;
    *num7 = 37;
    s1=pqToString(q, itos);
    s2=pqToString(test, itos);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(s2, s1,"test_copy1-2");
    free(s1);
    free(s2);

    *num5=420;
    *num7=21;
    s1=pqToString(q, itos);
    s2=pqToString(test, itos);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(s2, s1,"test_copy1-3");
    free(s1);
    free(s2);

  
    //It should be expected that the pqueues are different when elements are removed from the pqueue 'test'
    //(i.e pointers to the data of pqueue 'q' in 'test' were removed, but 'q' still has pointers to the original data)
    deq(test);
    deq(test);
    s1=pqToString(q, itos);
    s2=pqToString(test, itos);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("(420, 80) (69, 70) (21, 21) (543, 10) (10, 10) (21, 9) (43, 7) (432, 1) ", s1,"test_copy1-4");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("(21, 21) (543, 10) (10, 10) (21, 9) (43, 7) (432, 1) ", s2,"test_copy1-5");
    free(s1);
    free(s2);

    
  //^likewise when adding a new element to 'q', 'test' isn't changed, since the new element is not a 'child' value.
    int* num9 = malloc(sizeof(int));
    *num9=321;
    enq(q, num9, 52);
    s1=pqToString(q, itos);
    s2=pqToString(test, itos);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("(420, 80) (69, 70) (321, 52) (21, 21) (543, 10) (10, 10) (21, 9) (43, 7) (432, 1) ", s1,"test_copy1-6");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("(21, 21) (543, 10) (10, 10) (21, 9) (43, 7) (432, 1) ", s2,"test_copy1-7");

    //check shallow copy pt 2. since both queues have a pointer to what int* num6 points to 
    //(it was a 'child' value and wasn't dequeued in either queue) a change in *num6 will be reflected in both queues.
    *num6 = 91;
    s1=pqToString(q, itos);
    s2=pqToString(test, itos);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("(420, 80) (69, 70) (321, 52) (91, 21) (543, 10) (10, 10) (21, 9) (43, 7) (432, 1) ", s1,"test_copy1-8");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("(91, 21) (543, 10) (10, 10) (21, 9) (43, 7) (432, 1) ", s2,"test_copy1-9");
    
    freepq(q);
    freepq(test);
    free(s);
    free(s1);
    free(s2);
    free(num1);
    free(num2);
    free(num3);
    free(num4);
    free(num5);
    free(num6);
    free(num7);
    free(num8);
    free(num9);
}
void test_enqpq(){
    int* num1= malloc(sizeof(int));
    int* num2= malloc(sizeof(int));
    int* num3= malloc(sizeof(int));
    int* num5= malloc(sizeof(int));
    int* num7= malloc(sizeof(int));
    int* num8= malloc(sizeof(int));

    pq q= createpq();
    *num1 = 543;
    enq(q, num1, 10);

    TEST_ASSERT_EQUAL_INT_MESSAGE(543, *(int*)front(q),"test_enq1-1");

    *num2 = 432;
    enq(q, num2, 1);
    *num3 = 43;
    enq(q, num3, 7);
    *num5 = 420;
    enq(q, num5, 80);
    *num7 = 54;
    enq(q, num7, 9);
    *num8 = 43;
    enq(q, num8, 10);

    char *s = pqToString(q, itos);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("(420, 80) (543, 10) (43, 10) (54, 9) (43, 7) (432, 1) ", s,"test_enq1-2");

    free(s);
    freepq(q);
    TEST_ASSERT_EQUAL_INT_MESSAGE(543, *num1,"test_enq1-3");
    TEST_ASSERT_EQUAL_INT_MESSAGE(420, *num5,"test_enq1-4");
    TEST_ASSERT_EQUAL_INT_MESSAGE(54, *num7,"test_enq1-5");
    free(num1);
    free(num2);
    free(num3);
    free(num5);
    free(num7);
    free(num8);
}
void test_deqpq(){
    int* num1= malloc(sizeof(int));
    int* num2= malloc(sizeof(int));
    int* num3= malloc(sizeof(int));
    int* num5= malloc(sizeof(int));
    int* num7= malloc(sizeof(int));
    int* num8= malloc(sizeof(int));
    *num1 = 543;
    *num2 = 432;
    *num3 = 43;
    *num5 = 420;
    *num7 = 54;
    *num8 = 43;
    
    pq q= createpq();
    enq(q, num1, 10);
    enq(q, num2, 1);
    enq(q, num3, 7);
    enq(q, num5, 80);
    enq(q, num7, 9);
    enq(q, num8, 10);

    deq(q);
    char *s = pqToString(q, itos);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("(543, 10) (43, 10) (54, 9) (43, 7) (432, 1) ", s,"test_enq1-2");
    deq(q);
    deq(q);
    deq(q);
    deq(q);
    TEST_ASSERT_EQUAL_INT_MESSAGE(432, *(int*)front(q),"test_enq1-3");
    deq(q);
    deq(q);
    deq(q);

    free(s);
    freepq(q);
    free(num1);
    free(num2);
    free(num3);
    free(num5);
    free(num7);
    free(num8);
}
void test_front_back_pq(){
    int* num1= malloc(sizeof(int));
    int* num2= malloc(sizeof(int));
    int* num3= malloc(sizeof(int));
    int* num5= malloc(sizeof(int));
    int* num7= malloc(sizeof(int));
    int* num8= malloc(sizeof(int));
    *num1 = 543;
    *num2 = 432;
    *num3 = 43;
    *num5 = 420;
    *num7 = 54;
    *num8 = 43;
    
    pq q= createpq();
    enq(q, num1, 10);
    enq(q, num2, 1);
    enq(q, num3, 7);
    enq(q, num5, 80);
    enq(q, num7, 9);
    enq(q, num8, 10);

    TEST_ASSERT_EQUAL_INT_MESSAGE(420, *(int*)front(q),"test_fbpq1-1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(80, frontP(q),"test_fbpq1-2");
    TEST_ASSERT_EQUAL_INT_MESSAGE(432, *(int*)rear(q),"test_fbpq1-3");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, rearP(q),"test_fbpq1-4");

    deq(q);
    deq(q);
    deq(q);

    TEST_ASSERT_EQUAL_INT_MESSAGE(54, *(int*)front(q),"test_fbpq1-5");
    TEST_ASSERT_EQUAL_INT_MESSAGE(9, frontP(q),"test_fbpq1-6");
    TEST_ASSERT_EQUAL_INT_MESSAGE(432, *(int*)rear(q),"test_fbpq1-7");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, rearP(q),"test_fbpq1-8");
    
    int* num9= malloc(sizeof(int));
    *num9 = 202;
    enq(q, num9, 9);
    int* num10= malloc(sizeof(int));
    *num10 = 101;
    enq(q, num10, 1);

    TEST_ASSERT_EQUAL_INT_MESSAGE(54, *(int*)front(q),"test_fbpq1-9");
    TEST_ASSERT_EQUAL_INT_MESSAGE(9, frontP(q),"test_fbpq2-1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(101, *(int*)rear(q),"test_fbpq2-2");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, rearP(q),"test_fbpq2-3");

    deq(q);
    deq(q);
    deq(q);
    deq(q);

    TEST_ASSERT_EQUAL_INT_MESSAGE(101, *(int*)front(q),"test_fbpq2-4");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, frontP(q),"test_fbpq2-5");
    TEST_ASSERT_EQUAL_INT_MESSAGE(101, *(int*)rear(q),"test_fbpq2-6");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, rearP(q),"test_fbpq2-7");

    freepq(q);
    free(num1);
    free(num2);
    free(num3);
    free(num5);
    free(num7);
    free(num8);
    free(num9);
    free(num10);
}
void test_count_size_pq(){
    
    int* num1= malloc(sizeof(int));
    int* num2= malloc(sizeof(int));
    int* num3= malloc(sizeof(int));
    int* num5= malloc(sizeof(int));
    int* num7= malloc(sizeof(int));
    int* num8= malloc(sizeof(int));
    *num1 = 543;
    *num2 = 432;
    *num3 = 43;
    *num5 = 420;
    *num7 = 54;
    *num8 = 43;
    
    pq q= createpq();
    enq(q, num1, 10);
    enq(q, num2, 3);
    enq(q, num3, 7);
    enq(q, num5, 80);
    enq(q, num7, 9);
    enq(q, num8, 10);

    TEST_ASSERT_EQUAL_INT_MESSAGE(2, countP(q,10),"test_countsize_1-1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, countP(q, 3),"test_countsize_1-2");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, countP(q, 32),"test_countsize_1-3");
    TEST_ASSERT_EQUAL_INT_MESSAGE(6, pqSize(q),"test_countsize_1-4");

    deq(q);
    deq(q);
    deq(q);
    deq(q);

    TEST_ASSERT_EQUAL_INT_MESSAGE(0, countP(q, 10),"test_countsize_1-6");
    TEST_ASSERT_EQUAL_INT_MESSAGE(2, pqSize(q),"test_countsize_1-7");

    deq(q);
    deq(q);

    TEST_ASSERT_EQUAL_INT_MESSAGE(0, countP(q, 69),"test_countsize_1-8");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, pqSize(q),"test_countsize_1-9");

    int* num9 =malloc(sizeof(int));
    *num9=50;
    enq(q, num9, 50);

    TEST_ASSERT_EQUAL_INT_MESSAGE(1, countP(q, 50),"test_countsize_2-0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, pqSize(q),"test_countsize_2-1");

    freepq(q);
    free(num1);
    free(num2);
    free(num3);
    free(num5);
    free(num7);
    free(num8);
    free(num9);
}
void test_empty_full_pq(){
    
    pq q= createpq();
    int* num1= malloc(sizeof(int));
    int* num2= malloc(sizeof(int));
    *num1=543;
    *num2=432;

    enq(q, num1, 10);
    enq(q, num2, 1);

    TEST_ASSERT_EQUAL_MESSAGE(false, pqEmpty(q),"test_empty_full_1-1");
    TEST_ASSERT_EQUAL_MESSAGE(false, pqFull(q),"test_empty_full_1-2");

    deq(q);

    TEST_ASSERT_EQUAL_MESSAGE(false, pqEmpty(q),"test_empty_full_1-3");

    deq(q);

    TEST_ASSERT_EQUAL_MESSAGE(true, pqEmpty(q),"test_empty_full_1-4");

    freepq(q);
    free(num1);
    free(num2);

}
void test_stringpq(){
    
    pq q= createpq();
    int* num1= malloc(sizeof(int));
    int* num2= malloc(sizeof(int));
    int* num3= malloc(sizeof(int));
    int* num5= malloc(sizeof(int));
    int* num7= malloc(sizeof(int));
    int* num8= malloc(sizeof(int));
    *num1 = 543;
    *num2 = 432;
    *num3 = 43;
    *num5 = 420;
    *num7 = 54;
    *num8 = 43;
    
    char *s = pqToString(q, itos);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("", s,"test_stringpq1-1");
    
    enq(q, num1, 10);
    s = pqToString(q, itos);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("(543, 10) ", s,"test_stringpq1-2");
    free(s);

    enq(q, num2, 1);
    enq(q, num3, 7);
    enq(q, num5, 80);
    enq(q, num7, 9);
    enq(q, num8, 10);

    s = pqToString(q, itos);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("(420, 80) (543, 10) (43, 10) (54, 9) (43, 7) (432, 1) ", s,"test_stringpq1-3");
    free(s);

    deq(q);
    deq(q);
    deq(q);
    deq(q);

    s = pqToString(q, itos);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("(43, 7) (432, 1) ", s,"test_stringpq1-4");
    free(s);

    freepq(q);
    free(num1);
    free(num2);
    free(num3);
    free(num5);
    free(num7);
    free(num8);
    
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_createFreepq);
    RUN_TEST(test_copypq);
    RUN_TEST(test_enqpq);
    RUN_TEST(test_deqpq);
    RUN_TEST(test_front_back_pq);
    RUN_TEST(test_count_size_pq);
    RUN_TEST(test_empty_full_pq);
    RUN_TEST(test_stringpq);
    return UNITY_END();
}
*/