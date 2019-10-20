#include <stdio.h>
#include <conio.h>
#include "atm.h"


void inquire(){
	printf("====BALANCE====\n");
	printf("Date: %s\n",currdate);
	printf("Time: %s\n",currtime);
	printf("Name: %s,%s\n",c.lastn,c.firstn);
	printf("Account Number: %d\n",c.acnR);
	printf("Current Balance:Php%10.2f\n\n",c.curBal);
	printf("Press any key to return to Main Menu. \n");
	getch();
}
