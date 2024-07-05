// Ryan DuBrueler

// For scientific notation or stoichiometry

#include <stdio.h>

int main (void) {

	double num;
	int factor;
	printf(" ____________________________\n");
	printf("|Table of Conversions:       |\n");
	printf("| pico = 10^-12 tera = 10^12 |\n");
	printf("| nano = 10^-9  giga = 10^9  |\n");
	printf("| micro = 10^-6 mega = 10^5  |\n");
	printf("| milli = 10^-3 kilo = 10^3  |\n");
	printf("| centi = 10^-2 hecta = 10^2 |\n");
	printf("| deci = 10^-1  deca = 10^1  |\n");
	printf("|____________________________|\n");
	printf("Enter number to be converted: ");
	scanf("%lf",&num);
	printf("Times 10 to the: ");
	scanf("%d",&factor);
	printf("Equals : ");
	if(factor>0){
		while(factor!=0){
			num=num*10; factor--;
		}
		printf("%-0.0lf",num);
	}
	else if(factor<0){
		while(factor!=0){
			num=num/10; factor++;
		}
		printf("%-0.12lf",num);
	}	
	else printf("%-0.4lf",num);
}