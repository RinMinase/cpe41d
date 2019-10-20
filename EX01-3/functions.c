#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

void display() {
	int choice;
	int poly1[10];
	int poly2[10];
	
	printf("Enter First Polynomial: ");
	fflush(stdin);
	scanf("%d %d %d %d %d %d %d %d %d %d", &poly1[0], &poly1[1], &poly1[2], &poly1[3], &poly1[4], &poly1[5], &poly1[6], &poly1[7], &poly1[8], &poly1[9]);
	printPolynomial(poly1);
	
	printf("\n\nEnter Second Polynomial: ");
	fflush(stdin);
	scanf("%d %d %d %d %d %d %d %d %d %d", &poly2[0], &poly2[1], &poly2[2], &poly2[3], &poly2[4], &poly2[5], &poly2[6], &poly2[7], &poly2[8], &poly2[9]);
	printPolynomial(poly2);
	
	printf("\n\n****************************");
	printf("\n*      [1] Addition        *");
	printf("\n*      [2] Subtraction     *");
	printf("\n*      [3] Derivative      *");
	printf("\n****************************");
	printf("\nChoice: ");
	fflush(stdin);
	scanf("%d", &choice);
	
	switch(choice) {
		case 1: add(poly1, poly2); break;
		case 2: subtract(poly1, poly2); break;
		case 3: derive(poly1, poly2);  break;
		default:  break;
	}
	
}

void printPolynomial(int poly[]) {
	int i, j;
	
	for(i=0, j=9; i<10; i++, j--) {
		if(poly[i] !=0) {
			if(i == 9) {
				printf("%d", poly[i]);
				break;
			} else {
				if(poly[i+1] > 0) {
					printf("%dx^%d + ", poly[i], j);
				} else {
					printf("%dx^%d ", poly[i], j);
				}
			}
		}
	}
}

void add(int poly1[], int poly2[]) {
	int i;
	int total[10];
	
	for(i=0; i<10; i++) {
		total[i] = poly1[i] + poly2[i];
	}
	
	printf("\nThe sum of the polynomials is :\n");
	printPolynomial(total);
}

void subtract(int poly1[], int poly2[]) {
	int i;
	int total[10];
	
	for(i=0; i<10; i++) {
		total[i] = poly1[i] - poly2[i];
	}
	
	printf("\nThe difference of the polynomials is :\n");
	printPolynomial(total);
}

void derive(int poly1[], int poly2[]) {
	int i, j;
	int derive1[10];
	int derive2[10];
	
	derive1[0] = 0;
	for(i=1, j=9; i<10; i++, j--) {
		derive1[i] = poly1[i-1] * j;	
	}
	
	derive2[0] = 0;
	for(i=1, j=9; i<10; i++, j--) {
		derive2[i] = poly2[i-1] * j;	
	}
	
	printf("\nThe derivative of the polynomials is :\n");
	printPolynomial(derive1);
	printPolynomial(derive2);
}
