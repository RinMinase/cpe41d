#include <stdio.h>
#include <conio.h>
#include "def_func.h"

void displaySplash() {
	gotoxy(80/2-15,21/2);	
	printf("=====USC BANKING SERVICE======\n");
	
	gotoxy(80/2-15,(21/2)+1);	
	printf("Input Account Number:");
	
	gotoxy(80/2-15,21/2+2);	
	printf("Input Access Code:");
	
	gotoxy(80/2-15,21/2+3);
	printf("==============================");
}

int dispInputAccountNumber() {
	gotoxy(80/2+6,(25/2)+1);
	
	int AccountNumber;
	scanf("%d",&AccountNumber);
	
	return AccountNumber;
}

int * dispInputPIN() {
	int * pinValue;
	
	gotoxy(80/2+6,(25/2)+2);
	pinValue[0]=getch();
	printf("*");
	pinValue[1]=getch();
	printf("*");
	pinValue[2]=getch();
	printf("*");
	pinValue[3]=getch();
	printf("*");
	getch();
	
	return pinValue;
}
