// Ryan DuBrueler and Shreyas Harish

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "rat.h"

// Function to create a rational number
rat createRat (int numerator, int denominator)
{
  if (denominator == 0)
	{
	  printf ("Error: Denominator cannot be zero\n");
	  exit (EXIT_FAILURE);
	}
//allocates size of rtype to new rat
  rat newRat = (rat) malloc (sizeof (struct rtype));
//double-check malloc
  if (newRat == NULL)
	{
	  printf ("Memory allocation failed\n");
	  exit (EXIT_FAILURE);
	}
// Store numerator and denominator
  newRat->n = numerator;
  newRat->d = denominator;

  return newRat;
}

// Function to normalize a rational number
rat norm (const rat r)
{
  rat normal = createRat (r->n, r->d);
// If the numerator is 0, make denominator 1
  if (r->n == 0)
	{
	  r->d = 1;
	}
// If the denominator is negative, swap signs
  else if (normal->d < 0)
	{
	  normal->n = -(normal->n);
	  normal->d = -(normal->d);
	}

  return normal;
}

// Function to reduce a rational number using GCF
rat reduce (const rat r)
{
// If numerator(nummy) is 0, then denominator(dummy) is 1
  if (r->n == 0)
	{
	  r->d = 1;
	}
	// Temporary variables
  int nummy = abs (r->n), dummy = r->d;
  while (dummy != 0)
	{
	  int temp = nummy % dummy;
	  nummy = dummy;            // Euclid's algorithm for gcf
	  dummy = temp; 
	}
  int gcf = nummy;
  return createRat (r->n / gcf, r->d / gcf);
}

// Function to compare two rational numbers
int cmp (const rat r1, const rat r2)
{

// Temporary variables
  rat cmpReduce1 = reduce (r1);
  rat cmpReduce2 = reduce (r2);

// Cross multiply and compare
  int crossProduct1 = cmpReduce1->n * cmpReduce2->d;
  int crossProduct2 = cmpReduce2->n * cmpReduce1->d;
  if (crossProduct1 < crossProduct2)
	{
	  return -1;
	}
  else if (crossProduct1 > crossProduct2)
	{
	  return 1;
	}
  else
	{
	  return 0;
	}

}

// Function to add two rational numbers
rat add (const rat r1, const rat r2)
{
  int num = (r1->n * r2->d) + (r2->n * r1->d);
  int den = r1->d * r2->d;
  return reduce (norm (createRat (num, den)));
  //when we figured out this worked it blew our minds a little
}

// Function to subtract two rational numbers
rat sub (const rat r1, const rat r2)
{
  int num = (r1->n * r2->d) - (r2->n * r1->d);
  int den = r1->d * r2->d;
  return reduce (norm (createRat (num, den)));
}

// Function to multiply two rational numbers
rat mul (const rat r1, const rat r2)
{
  int num = r1->n * r2->n;
  int den = r1->d * r2->d;
  return reduce (norm (createRat (num, den)));
}

// Function to divide two rational numbers
rat divide (const rat r1, const rat r2)
{
  if (r2->n == 0)
	{
	  printf ("Error: Division by zero\n");
	  exit (EXIT_FAILURE);
	}
  int num = r1->n * r2->d;
  int den = r1->d * r2->n;
  return reduce (norm (createRat (num, den)));
}

// Function to get the inverse of a rational number
rat inverse (const rat r)
{
  if (r->n == 0)
	{
	  printf ("Error: Cannot invert zero\n");
	  exit (EXIT_FAILURE);
	}
  return createRat (r->d, r->n);
}

// Function to check if a rational number is well-formed
bool wellFormed (const rat r)
{
  return (r->d != 0);
}

// Function to convert a rational number to a string
char *toString (const rat r)
{
    // 32 for 4*signed int(8)
  char *str = (char *) malloc (32 * sizeof (char));	// Allocate memory for the string
  if (str == NULL)
	{
	  printf ("Memory allocation failed\n");
	  exit (EXIT_FAILURE);
	}
  snprintf (str, 32, "%d/%d", r->n, r->d);	// Writes n and d to str (string variable)
  return str;
}
