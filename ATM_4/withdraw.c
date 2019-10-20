#include <stdio.h>
#include <conio.h>
#include "atm.h"

void withMenu(){
	float withdrawal;
	printf("====WITHDRAW====\n");
	printf("Date: %s\n",currdate);
	printf("Time: %s\n",currtime);
	printf("Name: %s,%s\n",c.lastn,c.firstn);
	printf("Account Number: %d\n",c.acnR);
	printf("Current Balance: %10.2f\n",c.curBal);
	printf("Withdrawal Amount: Php ");
	scanf("%f",&withdrawal);
	updateWith(withdrawal);
}

void updateWith(float cash){	
	
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




