/**********************************
Author: 		Michelle Magpuyo

**********************************/

#ifndef __DISPLAY_H
#define __DISPLAY_H

void borders();
void inputAcctPinNO(char *strng1, char *strng2);

void adminMenu();
void mainMenu();

int dispInitialize();

void dispWithdraw(int acctNo);
void withdrawProcess(int acctNo);

void dispDeposit(int acctNo);
void depositProcess(int acctNo);

void dispTransfer(int acctNo);
void transferProcess(int acctNo);

void dispHistory(int acctNo);

void dispInquire(int acctNo);
void exitMessage();
int inputPIN(char *strng, int acctNum);

void dispErrorMessage(char *errorMessage);
void dispErrorMessageLine2(char *errorMessage);
void clearErrorMessage();
void clearATMScreen();

#endif
