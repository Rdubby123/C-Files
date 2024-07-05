#include <stdio.h>
#include <stdlib.h>
#include "rat.h"

int main(void) {
printf("infinite loop: 69 to escape\n");
while(17)
{
int r1n, r1d, r2n, r2d;
char action[10]="add";
printf("fraction 1 (n/d)?: ");
scanf("%d/%d",&r1n,&r1d);
if(r1n==69)
{
    printf("Manual Escape Performed");
    exit(69);
}
printf("Action To Fraction (plus, minus, times, divided by)?: ");
scanf("%s",action);
printf("fraction 2 (n/d)?: ");
scanf("%d/%d",&r2n,&r2d);
rat r1 = createRat(r1n,r1d), r2 = createRat(r2n,r2d);
if(action[0] == 'p')
{
printf("r1 + r2 = %s\n",toString((add(r1,r2))));
}
else if(action[0] == 'm')
{
printf("r1 - r2 = %s\n",toString((sub(r1,r2))));
}
else if(action[0] == 't')
{
printf("r1 * r2 = %s\n",toString((mul(r1,r2))));
}
else if(action[0] == 'd')
{
printf("r1 / r2 = %s\n",toString((divide(r1,r2))));
}
}
}

// unity tests below

/*

// gcc unity.c rat.c ratUnity.c
#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "rat.h"
void setUp(void){  }
void tearDown(void){  }

void createRat_1(void) {
rat r = createRat(5,10);
TEST_ASSERT_EQUAL_INT_MESSAGE(r->n,5,"createRat_1-1");
TEST_ASSERT_EQUAL_INT_MESSAGE(r->d,10,"createRat_1-2");
r = createRat(0,1);
TEST_ASSERT_EQUAL_INT_MESSAGE(r->n,0,"createRat_1-3");
free(r);
}
void toString_1(void) {
rat r = createRat(2,3);
TEST_ASSERT_EQUAL_STRING_MESSAGE("2/3",toString(r),"toString_1-1");
r->d = -5;
TEST_ASSERT_EQUAL_STRING_MESSAGE("2/-5",toString(r),"toString_1-1");
r->d = 0;
TEST_ASSERT_EQUAL_STRING_MESSAGE("2/0",toString(r),"toString_1-1");
free(r);
}
void norm_1(void) {
rat r = createRat(244,7777), r1 = norm(r);
TEST_ASSERT_EQUAL_INT_MESSAGE(244,norm(r)->n,"norm_1-1");
TEST_ASSERT_EQUAL_INT_MESSAGE(7777,norm(r)->d,"norm_1-2");
r1->d = 999;
TEST_ASSERT_EQUAL_INT_MESSAGE(7777,r->d,"norm_1-3");
r->d= -999;
TEST_ASSERT_EQUAL_INT_MESSAGE(-244,norm(r)->n,"norm_1-4");
TEST_ASSERT_EQUAL_INT_MESSAGE(999,norm(r)->d,"norm_1-5");
r->n = -3;
TEST_ASSERT_EQUAL_INT_MESSAGE(3,norm(r)->n,"norm_1-6");
TEST_ASSERT_EQUAL_INT_MESSAGE(999,norm(r)->d,"norm_1-7");
r->n = 0; r->d = 555;
TEST_ASSERT_EQUAL_INT_MESSAGE(0,norm(r)->n,"norm_1-8");
TEST_ASSERT_EQUAL_INT_MESSAGE(1,norm(r)->d,"norm_1-9");
r->n = 0; r->d = -555;
TEST_ASSERT_EQUAL_INT_MESSAGE(0,norm(r)->n,"norm_1-10");
TEST_ASSERT_EQUAL_INT_MESSAGE(1,norm(r)->d,"norm_1-11");
free(r);
}
void reduce_1(void) {
rat r = createRat(2,5);
TEST_ASSERT_EQUAL_INT_MESSAGE(2,reduce(r)->n,"reduce_1-1");
TEST_ASSERT_EQUAL_INT_MESSAGE(5,reduce(r)->d,"reduce_1-2");
r->n = 52; r->d = 64;
TEST_ASSERT_EQUAL_INT_MESSAGE(13,reduce(r)->n,"reduce_1-3");
TEST_ASSERT_EQUAL_INT_MESSAGE(16,reduce(r)->d,"reduce_1-4");
r->n = 0; r->d = 22;
TEST_ASSERT_EQUAL_INT_MESSAGE(0,reduce(r)->n,"reduce_1-5");
TEST_ASSERT_EQUAL_INT_MESSAGE(1,reduce(r)->d,"reduce_1-6");
r->n = 125; r->d = -1000;
TEST_ASSERT_EQUAL_INT_MESSAGE(1,reduce(r)->n,"reduce_1-6");
TEST_ASSERT_EQUAL_INT_MESSAGE(-8,reduce(r)->d,"reduce_1-7");
r->n = 59466; r->d = -1041;
TEST_ASSERT_EQUAL_INT_MESSAGE(19822,reduce(r)->n,"reduce_1-8");
TEST_ASSERT_EQUAL_INT_MESSAGE(-347,reduce(r)->d,"reduce_1-9");
free(r);
}
void inverse_1(void) {
rat r = createRat(2,5);
TEST_ASSERT_EQUAL_INT_MESSAGE(5,inverse(r)->n,"inverse_1-1");
TEST_ASSERT_EQUAL_INT_MESSAGE(2,inverse(r)->d,"inverse_1-2");
r->n = 46; r->d = 281;
TEST_ASSERT_EQUAL_INT_MESSAGE(281,inverse(r)->n,"inverse_1-3");
TEST_ASSERT_EQUAL_INT_MESSAGE(46,inverse(r)->d,"inverse_1-4");
free(r);
}
void wellFormed_1(void) {
rat r = createRat(2,5);
TEST_ASSERT_TRUE_MESSAGE(wellFormed(r),"wellFormed_1-1");
r->n = -34; r->d = -23;
TEST_ASSERT_TRUE_MESSAGE(wellFormed(r),"wellFormed_1-2");
r->n = 0; r->d = -928192;
TEST_ASSERT_TRUE_MESSAGE(wellFormed(r),"wellFormed_1-3");
r->n = 22; r->d = 0;
TEST_ASSERT_FALSE_MESSAGE(wellFormed(r),"wellFormed_1-4");
free(r);
}
void cmp_1(void) {
rat r1 = createRat(2,5), r2 = createRat(2,5);
TEST_ASSERT_EQUAL_INT_MESSAGE(0,cmp(r1,r2),"cmp_1-1");
TEST_ASSERT_EQUAL_INT_MESSAGE(0,cmp(r2,r1),"cmp_1-2");
r2->n = 9000; r2->d = 22500;
TEST_ASSERT_EQUAL_INT_MESSAGE(0,cmp(r1,r2),"cmp_1-3");
r1->n = 0; r1->d = 4299; r2->n = 0; r2->d = 27;
TEST_ASSERT_EQUAL_INT_MESSAGE(0,cmp(r1,r2),"cmp_1-4");
r1->n = -23; r1->d = -4299; r2->n = 23; r2->d = 4299;
TEST_ASSERT_EQUAL_INT_MESSAGE(0,cmp(r1,r2),"cmp_1-5");
r1->n = -23; r1->d = 4299; r2->n = 23; r2->d = -4299;
TEST_ASSERT_EQUAL_INT_MESSAGE(0,cmp(r1,r2),"cmp_1-6");
r1->n = 2; r1->d = 3; r2->n = 12; r2->d = 13;
TEST_ASSERT_EQUAL_INT_MESSAGE(-1,cmp(r1,r2),"cmp_1-7");
TEST_ASSERT_EQUAL_INT_MESSAGE(1,cmp(r2,r1),"cmp_1-8");
r1->n = 2; r1->d = -3; r2->n = 2; r2->d = 3;
TEST_ASSERT_EQUAL_INT_MESSAGE(-1,cmp(r1,r2),"cmp_1-9");
TEST_ASSERT_EQUAL_INT_MESSAGE(1,cmp(r2,r1),"cmp_1-10");
free(r1); free(r2);
}
void add_1(void) {
rat r1 = createRat(2,5), r2 = createRat(2,5);
TEST_ASSERT_EQUAL_INT_MESSAGE(4,add(r1,r2)->n,"add_1-1");
TEST_ASSERT_EQUAL_INT_MESSAGE(5,add(r1,r2)->d,"add_1-2");
r2->n = 62; r2->d = 23;
TEST_ASSERT_EQUAL_INT_MESSAGE(356,add(r1,r2)->n,"add_1-3");
TEST_ASSERT_EQUAL_INT_MESSAGE(115,add(r1,r2)->d,"add_1-4");
r2->d = -23;
TEST_ASSERT_EQUAL_INT_MESSAGE(-264,add(r1,r2)->n,"add_1-5");
TEST_ASSERT_EQUAL_INT_MESSAGE(115,add(r1,r2)->d,"add_1-6");
r1->n = -2; r1->d = 3; r2->n = -1; r2->d = 7;
TEST_ASSERT_EQUAL_INT_MESSAGE(-17,add(r1,r2)->n,"add_1-7");
TEST_ASSERT_EQUAL_INT_MESSAGE(21,add(r1,r2)->d,"add_1-8");
TEST_ASSERT_EQUAL_INT_MESSAGE(-17,add(r2,r1)->n,"add_1-9");
TEST_ASSERT_EQUAL_INT_MESSAGE(21,add(r2,r1)->d,"add_1-10");
r1->n = 0; r1->d = 3; r2->n = 0; r2->d = -199912;
TEST_ASSERT_EQUAL_INT_MESSAGE(0,add(r1,r2)->n,"add_1-11");
TEST_ASSERT_EQUAL_INT_MESSAGE(1,add(r1,r2)->d,"add_1-12");
r1->n = -1; r1->d = -25; r2->n = -1; r2->d = 25;
TEST_ASSERT_EQUAL_INT_MESSAGE(0,add(r1,r2)->n,"add_1-13");
TEST_ASSERT_EQUAL_INT_MESSAGE(1,add(r1,r2)->d,"add_1-14");
free(r1); free(r2);
}
void sub_1(void) {
rat r1 = createRat(2,5), r2 = createRat(2,5);
TEST_ASSERT_EQUAL_INT_MESSAGE(0,sub(r1,r2)->n,"sub_1-1");
TEST_ASSERT_EQUAL_INT_MESSAGE(1,sub(r1,r2)->d,"sub_1-2");
r2->n = 62; r2->d = 23;
TEST_ASSERT_EQUAL_INT_MESSAGE(-264,sub(r1,r2)->n,"sub_1-3");
TEST_ASSERT_EQUAL_INT_MESSAGE(115,sub(r1,r2)->d,"sub_1-4");
r2->d = -23;
TEST_ASSERT_EQUAL_INT_MESSAGE(356,sub(r1,r2)->n,"sub_1-5");
TEST_ASSERT_EQUAL_INT_MESSAGE(115,sub(r1,r2)->d,"sub_1-6");
r1->n = -2; r1->d = 3; r2->n = -1; r2->d = 7;
TEST_ASSERT_EQUAL_INT_MESSAGE(-11,sub(r1,r2)->n,"sub_1-7");
TEST_ASSERT_EQUAL_INT_MESSAGE(21,sub(r1,r2)->d,"sub_1-8");
TEST_ASSERT_EQUAL_INT_MESSAGE(11,sub(r2,r1)->n,"sub_1-9");
TEST_ASSERT_EQUAL_INT_MESSAGE(21,sub(r2,r1)->d,"sub_1-10");
r1->n = 0; r1->d = 3; r2->n = 0; r2->d = -199912;
TEST_ASSERT_EQUAL_INT_MESSAGE(0,sub(r1,r2)->n,"sub_1-11");
TEST_ASSERT_EQUAL_INT_MESSAGE(1,sub(r1,r2)->d,"sub_1-12");
r1->n = -1; r1->d = -25; r2->n = -1; r2->d = 25;
TEST_ASSERT_EQUAL_INT_MESSAGE(2,sub(r1,r2)->n,"sub_1-13");
TEST_ASSERT_EQUAL_INT_MESSAGE(25,sub(r1,r2)->d,"sub_1-14");
free(r1); free(r2);
}
void mul_1(void) {
rat r1 = createRat(2,5), r2 = createRat(2,5);
TEST_ASSERT_EQUAL_INT_MESSAGE(4,mul(r1,r2)->n,"mul_1-1");
TEST_ASSERT_EQUAL_INT_MESSAGE(25,mul(r1,r2)->d,"mul_1-2");
TEST_ASSERT_EQUAL_INT_MESSAGE(4,mul(r2,r1)->n,"mul_1-3");
TEST_ASSERT_EQUAL_INT_MESSAGE(25,mul(r2,r1)->d,"mul_1-4");
r1->n = 3; r1->d = 2; r2->n=3; r2->d=9;
TEST_ASSERT_EQUAL_INT_MESSAGE(1,mul(r1,r2)->n,"mul_1-5");
TEST_ASSERT_EQUAL_INT_MESSAGE(2,mul(r1,r2)->d,"mul_1-6");
r1->n = 3; r1->d = -2; r2->n=-3; r2->d=-9;
TEST_ASSERT_EQUAL_INT_MESSAGE(-1,mul(r1,r2)->n,"mul_1-7");
TEST_ASSERT_EQUAL_INT_MESSAGE(2,mul(r1,r2)->d,"mul_1-8");
r1->n = 3; r1->d = -2; r2->n=0; r2->d=-9;
TEST_ASSERT_EQUAL_INT_MESSAGE(0,mul(r1,r2)->n,"mul_1-9");
TEST_ASSERT_EQUAL_INT_MESSAGE(1,mul(r1,r2)->d,"mul_1-10");
r1->n = 0; r1->d = 1; r2->n=0; r2->d=1;
TEST_ASSERT_EQUAL_INT_MESSAGE(0,mul(r1,r2)->n,"mul_1-11");
TEST_ASSERT_EQUAL_INT_MESSAGE(1,mul(r1,r2)->d,"mul_1-12");
free(r1); free(r2);
}
void divide_1(void) {
rat r1 = createRat(2,5), r2 = createRat(2,5);
TEST_ASSERT_EQUAL_INT_MESSAGE(1,divide(r1,r2)->n,"divide_1-1");
TEST_ASSERT_EQUAL_INT_MESSAGE(1,divide(r1,r2)->d,"divide_1-2");
TEST_ASSERT_EQUAL_INT_MESSAGE(1,divide(r2,r1)->n,"divide_1-3");
TEST_ASSERT_EQUAL_INT_MESSAGE(1,divide(r2,r1)->d,"divide_1-4");
r1->n = 3; r1->d = 2; r2->n=3; r2->d=9;
TEST_ASSERT_EQUAL_INT_MESSAGE(9,divide(r1,r2)->n,"divide_1-5");
TEST_ASSERT_EQUAL_INT_MESSAGE(2,divide(r1,r2)->d,"divide_1-6");
r1->n = 3; r1->d = -2; r2->n=-3; r2->d=-9;
TEST_ASSERT_EQUAL_INT_MESSAGE(-9,divide(r1,r2)->n,"divide_1-7");
TEST_ASSERT_EQUAL_INT_MESSAGE(2,divide(r1,r2)->d,"divide_1-8");
r1->n = 3; r1->d = -2; r2->n=99; r2->d=1293;
TEST_ASSERT_EQUAL_INT_MESSAGE(-431,divide(r1,r2)->n,"divide_1-9");
TEST_ASSERT_EQUAL_INT_MESSAGE(22,divide(r1,r2)->d,"divide_1-10");
r1->n = 0; r1->d = 1; r2->n=44; r2->d=3;
TEST_ASSERT_EQUAL_INT_MESSAGE(0,divide(r1,r2)->n,"divide_1-11");
TEST_ASSERT_EQUAL_INT_MESSAGE(1,divide(r1,r2)->d,"divide_1-12");
r1->n = 1; r1->d = 1; r2->n=1; r2->d=1;
TEST_ASSERT_EQUAL_INT_MESSAGE(1,divide(r1,r2)->n,"divide_1-13");
TEST_ASSERT_EQUAL_INT_MESSAGE(1,divide(r1,r2)->d,"divide_1-14");
free(r1); free(r2);
}
int main ( void ){
UNITY_BEGIN();
RUN_TEST(createRat_1);
RUN_TEST(toString_1);
RUN_TEST(norm_1);
RUN_TEST(reduce_1);
RUN_TEST(inverse_1);
RUN_TEST(wellFormed_1);
RUN_TEST(cmp_1);
RUN_TEST(add_1);
RUN_TEST(sub_1);
RUN_TEST(mul_1);
RUN_TEST(divide_1);
return UNITY_END();
}

*/

