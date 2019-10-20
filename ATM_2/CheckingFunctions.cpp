#include <stdlib.h>
#include <string.h>
#include <string>
//#include <iostream>
#include <fstream>
#include "CheckingFunctions.h"

int isAmountInvalid(float amount) {
	if(amount < 100 || ((int)amount % 100) != 0 || amount > 10000) {
		return 1;
	} else {
		return 0;
	}
}

int isAccountInvalid(char *acctNo) {
	using namespace std;
	string acnum, unused;
//	float bal;
	
	ifstream file1;
	file1.open("ACCOUNTS.txt",ios::in);
	
	if(file1) {
		while(file1 >> acnum >> unused >> unused >> unused >> unused) {
			if(acnum.compare(acctNo) == 0) {
				file1.close();
				return 0;
			}
		}
	}
	file1.close();	
	return 1;
}

int getAccountPIN(char *acctNo) {
	using namespace std;
	string acnum, unused;
	char *pin = (char *)calloc(20, sizeof(char));
	int pinVal;
	
	ifstream file1;
	file1.open("ACCOUNTS.txt",ios::in);
	
	if(file1) {
		while(file1 >> acnum >> pin >> unused >> unused >> unused) {
			if(acnum.compare(acctNo) == 0) {
				file1.close();
				pinVal = atoi(pin);
				return pinVal;
			}
		}
	}
	file1.close();	
	return 0;
}
