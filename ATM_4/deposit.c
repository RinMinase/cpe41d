#include <stdio.h>
#include <conio.h>
#include "atm.h"

void depMenu(){	
	float deposit;

	printf("====FAST CASH====\n");
	printf("Date: %s\n",currdate);
	printf("Time: %s\n",currtime);
	printf("Name: %s,%s\n",c.lastn,c.firstn);
	printf("Account Number: %d\n",c.acnR);
	printf("Current Balance: %10.2f\n",c.curBal);
	printf("Deposit Amount: Php ");
	scanf("%f",&deposit);
	updateDepo(deposit);
	
	return;
}

void updateDepo(float cash){
	
	FILE *fps2;
	float credit=0;
	
   	c.curBal=c.curBal+cash;
   	
    	system("cls");
    	printf("Transaction Completed.\n\n");
    	printf("Php %5.2f was deposited.\n\n",cash);
    	printf("Current Balance: Php %5.2f\n\n\n",c.curBal);
    	updateFile(c.curBal);
		fps2 = fopen("history.txt", "a+");											
    	fprintf(fps2,"%d %s %s %.2f %.2f\n",c.acnR,hisdate,currtime,cash,credit);	
    	fclose(fps2);
}


