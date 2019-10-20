/**********************************
Author: 		Michelle Magpuyo

**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include <string>

#include "GlobalFunctions.h"
#include "Display.h"
#include "DisplayAdmin.h"
#include "Public.h"
#include "CheckingFunctions.h"
#include "ATMFunctions.h"

ATMPublic plc;

int dispInitialize() {
	int actNo,   /* INPUT*/
		flag = 0,  /* 0 -> ACCT VALID ; 1 -> INVALID  */
		transNo, /* CHOICE */
		adminAcct = 0;
	
	system("cls");
	
	char *actNoChr = (char *)calloc(20, sizeof(char));
	
	char *temp = (char *)calloc(5, sizeof(char)); strcpy(temp, "");
	char *temp2 = (char *)calloc(25, sizeof(char)); strcpy(temp2, "Input account number:");
	inputAcctPinNO(temp2, temp);
	
	gotoxy(40, 8);
	scanf("%d", &actNo);
	itoa(actNo, actNoChr, 10);
	
	while((flag = isAccountInvalid(actNoChr)) && actNo != adminAcct) {		
		/* print sa message box */
		gotoxy(10, 20); printf("The account number inputted is incorrect.");
		gotoxy(10, 21); printf("Please try again. (Press any key).");
		getch();
		
		clearErrorMessage();
		gotoxy(40, 8); printf("			");
		gotoxy(40, 8); scanf("%d", &actNo);
		itoa(actNo, actNoChr, 10);
	}
	
	if(actNo == adminAcct) {
		flag=1; adminMenu();
		
		strcpy(temp2, "Please input the transaction number here:"); dispErrorMessageLine2(temp2);
		gotoxy(55, 21); scanf("%d", &transNo);
		
		while(transNo!=1 && transNo!=2 && transNo!=3 && transNo!=4) {
			gotoxy(10, 20); printf("Please choose 1-4 only!		              ");
			gotoxy(10, 21); printf("Please choose again from the given choices above.");
			gotoxy(10, 22); printf("(Press any key).");
			getch();
			
			clearErrorMessage();
			
			strcpy(temp2, "Please input the transaction number here:"); dispErrorMessageLine2(temp2);
			gotoxy(55, 21); scanf("%d", &transNo);
		}
		
		switch(transNo) {
			case 1: displayReloadMoney(); break;
			case 2: displayCheckATMBills(); break;
			case 3: borders(); displayAllTransactions(); exitMessage(); break;
			case 4: exitMessage(); break;
		}
	}
	
	if(flag == 0) {
		mainMenu();
	
		/* print sa message box */
		gotoxy(10, 21); printf("Please input the transaction number here:");
		gotoxy(55, 21); scanf("%d", &transNo);
	
		while(transNo!=1 && transNo!=2 && transNo!=3 && transNo!=4 && transNo!=5 && transNo!=6) {
			/* print sa message box */
			gotoxy(10, 20); printf("Please choose 1-6 only!		              ");
			gotoxy(10, 21); printf("Please choose again from the given choices above.");
			gotoxy(10, 22); printf("(Press any key).");
			getch();
			
			/* erase msg in the msg box */
			clearErrorMessage();
			
			/* print sa message box */
			gotoxy(10, 21); printf("Please input the transaction number here:");
			gotoxy(55, 21); scanf("%d", &transNo);
		}
					
		switch(transNo) {
			case 1: dispWithdraw(actNo); break;
			case 2: dispInquire(actNo); break;
			case 3: dispTransfer(actNo); break;
			case 4: dispDeposit(actNo); break;
			case 5: dispHistory(actNo); break;
			case 6: exitMessage(); break;
		} getch();
	}
	
	return 0;
}

void dispErrorMessage(char *errorMessage) {
	gotoxy(10, 20);
	printf(errorMessage);
}

void dispErrorMessageLine2(char *errorMessage) {
	gotoxy(10, 21);
	printf(errorMessage);
}

void clearErrorMessage() {
	gotoxy(10, 20); printf("                                                     ");
	gotoxy(10, 21); printf("                                                  ");
	gotoxy(10, 22); printf("                                                     ");
}

void clearATMScreen() {
	for(int i = 4; i <= 15; i++) { for(int j = 7; j < 73; j++) { gotoxy(j, i); printf(" "); } }
}

void dispWithdraw(int acctNo) {
	int PIN;
	borders();
	
	char *temp = (char *)calloc(70, sizeof(char)); strcpy(temp, "________________________ W I T H D R A W _________________________");
	
	PIN = inputPIN(temp, acctNo);
	if(PIN == 1) { withdrawProcess(acctNo); }
}

void withdrawProcess(int acctNo) {
	using namespace std;
	float amount = 0.0f;
	char *temp1 = (char *)calloc(30, sizeof(char));
	
	borders();
	
	gotoxy(17,8);
	strcpy(temp1, "Enter amount: ");
	printf("%s", temp1);
	
	gotoxy(35, 7);
	printf("-----------------------------");
	gotoxy(35, 9);
	printf("-----------------------------");
	
	gotoxy(40, 8);
	scanf("%f", &amount);
	
	while(isAmountInvalid(amount)) {
		strcpy(temp1, "Amount is invalid"); dispErrorMessage(temp1);
		strcpy(temp1, "Please enter the amount again"); dispErrorMessageLine2(temp1);
		
		gotoxy(40, 8); printf("                     ");
		gotoxy(40, 8); scanf("%f", &amount);
	}
	
	itoa(acctNo, temp1, 10);
	if(dispenseMoney(amount) == 0) {
		if(plc.withdraw(amount, temp1) == 0) {
			borders();
			gotoxy(30,8); strcpy(temp1, "Withdrawal Successful"); printf("%s", temp1);
			gotoxy(29,9); strcpy(temp1, "  Please remove card "); printf("%s", temp1);
			getch(); exitMessage();
		}
	} else {
		//PRINT INSUFFICIENT AMOUNT --->  AND CLEAR PrintF in else's of ATMFunctions.cpp
	}
}

void dispInquire(int acctNo) {
	int PIN;
	borders();
	
	char *temp = (char *)calloc(70, sizeof(char)); strcpy(temp, "__________________________ I N Q U I R E _________________________");
	PIN = inputPIN(temp, acctNo);
	
	if(PIN == 1) { 
		itoa(acctNo, temp, 10);
		plc.browse(temp); getch();
		
		borders();
		gotoxy(32,8); strcpy(temp, "Inquiry Successful"); printf("%s", temp);
		gotoxy(32,9); strcpy(temp, "Please remove card"); printf("%s", temp);
		getch(); exitMessage();
	}
}

void dispTransfer(int acctNo) {
	int PIN;
	borders();
	
	char *temp = (char *)calloc(70, sizeof(char)); strcpy(temp, "________________________ T R A N S F E R _________________________");
	PIN = inputPIN(temp, acctNo);
	
	if(PIN == 1) { transferProcess(acctNo);	}
}

void transferProcess(int acctNo) {
	using namespace std;
	float amount = 0.0f;
	int acctNo2;
	char *temp = (char *)calloc(30, sizeof(char));
	char *actNo2 = (char *)calloc(30, sizeof(char));
	
	borders();
	
	gotoxy(17,8);
	strcpy(temp, "Account no. : ");
	printf("%s", temp);
	
	gotoxy(35, 7);
	printf("-----------------------------");
	gotoxy(35, 9);
	printf("-----------------------------");
	
	gotoxy(40, 8);
	scanf("%d", &acctNo2);
	itoa(acctNo2, actNo2, 10);
	
	while(isAccountInvalid(actNo2)) {
		strcpy(temp, "Account Number not found"); dispErrorMessage(temp);
		strcpy(temp, "Please enter the account number again"); dispErrorMessageLine2(temp);
		
		gotoxy(40, 8); printf("                      ");
		gotoxy(40, 8); scanf("%d", &acctNo2);
		itoa(acctNo2, actNo2, 10);
	}
	
	borders();
	
	gotoxy(17,8);
	strcpy(temp, "Enter amount: ");
	printf("%s", temp);
	
	gotoxy(35, 7);
	printf("-----------------------------");
	gotoxy(35, 9);
	printf("-----------------------------");
	
	gotoxy(40, 8);
	scanf("%f", &amount);
	
	while(isAmountInvalid(amount)) {
		strcpy(temp, "Amount is invalid"); dispErrorMessage(temp);
		strcpy(temp, "Please enter the amount again"); dispErrorMessageLine2(temp);
		
		gotoxy(40, 8); printf("                     ");
		gotoxy(40, 8); scanf("%f", &amount);
	}
	
	itoa(acctNo, temp, 10);
	if(plc.transfer(temp, actNo2, amount) == 0) {
		borders();
		gotoxy(31,8); strcpy(temp, "Transfer Successful"); printf("%s", temp);
		gotoxy(31,9); strcpy(temp, " Please remove card"); printf("%s", temp);
		getch(); exitMessage();
	}
}

void dispDeposit(int acctNo) {
	int PIN;
	borders();
	
	char *temp = (char *)calloc(70, sizeof(char)); strcpy(temp, "_________________________ D E P O S I T __________________________");
	PIN = inputPIN(temp, acctNo);
	
	if(PIN == 1) { depositProcess(acctNo); }
}

void depositProcess(int acctNo) {
	using namespace std;
	float amount = 0.0f;
	char *temp = (char *)calloc(30, sizeof(char));
	
	borders();
	
	gotoxy(17,8);
	strcpy(temp, "Enter amount: ");
	printf("%s", temp);
	
	gotoxy(35, 7);
	printf("-----------------------------");
	gotoxy(35, 9);
	printf("-----------------------------");
	
	gotoxy(40, 8);
	scanf("%f", &amount);
	
	while(isAmountInvalid(amount)) {
		strcpy(temp, "Amount is invalid"); dispErrorMessage(temp);
		strcpy(temp, "Please enter the amount again"); dispErrorMessageLine2(temp);
		
		gotoxy(40, 8); printf("                     ");
		gotoxy(40, 8); scanf("%f", &amount);
	}
	
	itoa(acctNo, temp, 10);
	if(plc.deposit(amount, temp) == 0) {
		borders();
		gotoxy(32,8); strcpy(temp, "Deposit Successful"); printf("%s", temp);
		gotoxy(32,9); strcpy(temp, "Please remove card"); printf("%s", temp);
		getch(); exitMessage();
	}
}

void dispHistory(int acctNo) {
	int PIN;
	borders();
	
	char *temp = (char *)calloc(70, sizeof(char)); strcpy(temp, "_________________________ H I S T O R Y __________________________");
	PIN = inputPIN(temp, acctNo);
	
	if(PIN == 1) {
		itoa(acctNo, temp, 10);
		plc.accHistory(temp);
		
		borders();
		gotoxy(30,8); strcpy(temp, "History View Successful"); printf("%s", temp);
		gotoxy(29,9); strcpy(temp, "  Please remove card"); printf("%s", temp);
		getch(); exitMessage();
	}
}

void exitMessage() {
	borders();
	gotoxy(7,4);
	printf("__________________________________________________________________");
	gotoxy(7,5);
	printf("__________________________________________________________________");
	gotoxy(7,6);
	printf("__________________________________________________________________");
	gotoxy(7,7);
	printf("__________________________________________________________________");
	gotoxy(7,8);
	printf("______________ A T M  C A R D  H A S  E J E C T E D ______________");
	gotoxy(7,10);
	printf("______ T h a n k  y o u  f o r  b a n k i n g  w i t h  u s! _____");
	gotoxy(7,11);
	printf("__________________________________________________________________");
	gotoxy(7,12);
	printf("__________________________________________________________________");
	gotoxy(7,13);
	printf("__________________________________________________________________");
	gotoxy(7,14);
	printf("__________________________________________________________________");
	gotoxy(7,15);
	printf("__________________________________________________________________");
	
	/* print sa message box */
	gotoxy(10, 21);
	printf("Press any key to exit.");
	getch();
	
	gotoxy(0,24);
	exit(0);
}

int inputPIN(char *strng, int acctNum) {
	int actNo;
	char *temp = (char *)calloc(20, sizeof(char));
	 
	itoa(acctNum, temp, 10);
	int acctNo = getAccountPIN(temp);
	
	strcpy(temp, "Input PIN number:"); inputAcctPinNO(temp, strng);
	
	gotoxy(40, 8);
	scanf("%d", &actNo);
		
	while(actNo != acctNo) {
		/* print sa message box */
		gotoxy(10, 20);
		printf("The PIN number inputted is incorrect.");
		gotoxy(10, 21);
		printf("Please try again. (Press any key).");
		getch();
		
		/* erase msg in the msg box */
		gotoxy(10, 20);
		printf("	 					");
		gotoxy(10, 21);
		printf("						");

		gotoxy(40, 8);
		printf("			");
		gotoxy(40, 8);
		scanf("%d", &actNo);
	}
	
	if(actNo == acctNo) return 1;
}

void inputAcctPinNO(char *strng1, char *strng2) {
	borders();
	
	gotoxy(12,8);
	printf("%s", strng1);
	
	gotoxy(7,4);
	printf("%s", strng2);
	
	gotoxy(35, 7);
	printf("-----------------------------");
	gotoxy(35, 9);
	printf("-----------------------------");
}

void adminMenu() {
	int ctr;
	borders();
	
	gotoxy(59, 4);
	printf("Admin Account");
	gotoxy(45, 5);
	printf("Please select a transaction");
	
	/*upper border*/
	for(ctr=0; ctr<60; ctr++) {
		gotoxy(9, 7); printf("+");
		gotoxy(ctr+10, 7); printf("-");
		gotoxy(70, 7); printf("+");
	}
	
	/*left border*/
	for(ctr=0; ctr<7; ctr++) {
		gotoxy(9, ctr+8); printf("|");
	}
	
	/*right border*/
	for(ctr=0; ctr<7; ctr++) {
		gotoxy(70, ctr+8); printf("|");
	}
	
	/*lower border*/
	for(ctr=0; ctr<60; ctr++) {
		gotoxy(9, 15); printf("+");
		gotoxy(ctr+10, 15); printf("-");
		gotoxy(70, 15); printf("+");
	}
	
	gotoxy(12, 9); printf("<	[1] Reload Money");
	gotoxy(12, 11); printf("<	[2] Check ATM Bills");
	gotoxy(12, 13); printf("<   [3] User Transactions");	

	gotoxy(40, 9); printf("                           ");		
	gotoxy(40, 11); printf("                           ");
	gotoxy(40, 13); printf("               Exit [4]   >");
	
	/* print sa message box */
	gotoxy(10, 21); printf("Please input the transaction number here:");
	
}

void mainMenu() {
	int ctr;
	borders();
	
	gotoxy(45, 5);
	printf("Please select a transaction");
	
	/*upper border*/
	for(ctr=0; ctr<60; ctr++) {
		gotoxy(9, 7); printf("+");
		gotoxy(ctr+10, 7); printf("-");
		gotoxy(70, 7); printf("+");
	}
	
	/*left border*/
	for(ctr=0; ctr<7; ctr++) {
		gotoxy(9, ctr+8); printf("|");
	}
	
	/*right border*/
	for(ctr=0; ctr<7; ctr++) {
		gotoxy(70, ctr+8); printf("|");
	}
	
	/*lower border*/
	for(ctr=0; ctr<60; ctr++) {
		gotoxy(9, 15); printf("+");
		gotoxy(ctr+10, 15); printf("-");
		gotoxy(70, 15); printf("+");
	}
	
	gotoxy(12, 9); printf("<	[1] Withdraw");
	gotoxy(12, 11); printf("<	[2] Inquire Balance");
	gotoxy(12, 13); printf("<   [3] Transfer");	

	gotoxy(40, 9); printf("            Deposit [4]   >");		
	gotoxy(40, 11); printf("History Transaction [5]   >");
	gotoxy(40, 13); printf("               Exit [6]   >");
	
	/* print sa message box */
	gotoxy(10, 21); printf("Please input the transaction number here:");
	
}

void borders() {
	int ctr;
	
	system("cls");

	/*para ni sa upper border === */
	for(ctr=0; ctr<70; ctr++) { gotoxy(ctr+5, 1); printf("="); }
	
	/*para ni sa  left border || */
	for(ctr=0; ctr<21; ctr++) { gotoxy(5, ctr+2); printf("||"); }
		
	/*para ni sa  right border || */
	for(ctr=0; ctr<21; ctr++) { gotoxy(73, ctr+2); printf("||"); }
	
	gotoxy(7, 2); printf("	   U  S  C     B  A  N  K  I  N  G      S  E  R  V  I  C  E");
	
	/*para ni sa lower usc banking border === */
	for(ctr=0; ctr<70; ctr++) { gotoxy(ctr+5, 3); printf("="); }
	
	/*para ni sa upper msg border === */
	for(ctr=0; ctr<70; ctr++) { gotoxy(ctr+5, 17); printf("="); }
	
	gotoxy(7, 18);
	printf("\t\t       M  E  S  S  A  G  E       B  O  X ");
	
	/*para ni sa lower msg border === */
	for(ctr=0; ctr<70; ctr++) { gotoxy(ctr+5, 19); printf("="); }
	
	/*para ni sa lower border === */
	for(ctr=0; ctr<70; ctr++) { gotoxy(ctr+5, 23); printf("="); }			
}	

//void gotoxy(int x, int y) {
//  static HANDLE h = NULL;  
//  if(!h) h = GetStdHandle(STD_OUTPUT_HANDLE);
//  COORD c = { x, y }; SetConsoleCursorPosition(h,c);
//}

