#include <stdio.h>
#include <conio.h>
#include "atm.h"

void fastMenu(){
	char choice;
	printf("====FAST CASH====\n");
	printf("Date: %s\n",currdate);
	printf("Time: %s\n",currtime);
	printf("Name: %s,%s\n",c.lastn,c.firstn);
	printf("Account Number: %d\n",c.acnR);
	printf("Current Balance: %10.2f\n",c.curBal);
	printf("====OPTION====\n");
	printf("[1] Php 500\n");
	printf("[2] Php 1000\n");
	printf("[3] Php 2000\n");
	printf("[4] Php 5000\n");
	printf("[5] Php 10000\n");
	choice=getch();
	switch(choice){
		case '1': updateFast(500); break;
		case '2': updateFast(1000); break;
		case '3': updateFast(2000); break;
		case '4': updateFast(5000); break;
		case '5': updateFast(10000); break;
		default: system("cls"); printf("\n\nInvalid Input\n\n"); break;
	}
}

void updateFast(float cash){ 
	
	FILE *fps2;
	float debit=0;
	
   	if((c.curBal-cash)<0){
   		system("cls");	
   		printf("Transaction Failed.\n\n");	
   		printf("Insufficient Funds!!!\n\n");	
   		getch();
   	}else{
   		c.curBal=c.curBal-cash;
   		system("cls");
    	updateFile(c.curBal);
    	fps2 = fopen("history.txt", "a+");											
    	fprintf(fps2,"%d %s %s %.2f %.2f\n",c.acnR,hisdate,currtime,debit,cash);	// <---updated the hist.
    	fclose(fps2);
    	printf("Transaction Completed.\n\n");
    	printf("Php %5.2f was deducted.\n\n",cash);
    	printf("Remaining Balance: Php %5.2f\n\n\n",c.curBal);
    	getch();
   	}
	
}



