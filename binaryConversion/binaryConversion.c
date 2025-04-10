#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUMBITS (sizeof(unsigned)*8)

char *bitsToStr(unsigned x){ 
char *s = malloc(NUMBITS+1);

    for (int i = NUMBITS - 1; i >= 0; i--) {
        s[NUMBITS - 1 - i] = (x & (1u << i)) ? '1' : '0';
    }

    s[NUMBITS] = '\0';
    return s;
}
int main (void){
    unsigned int x;
    printf("size of unsigned int = %d bytes \n",(int)sizeof(x));
    printf("x? "); scanf("%u",&x);
    printf("x = %s\n",bitsToStr(x));
}
