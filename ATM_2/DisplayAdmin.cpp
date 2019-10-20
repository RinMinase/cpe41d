#include <iostream>
#include <fstream>

#include <conio.h>

#include "GlobalFunctions.h"
#include "ATM.h"
#include "ATMFunctions.h"
#include "Admin.h"
#include "Display.h"
#include "DisplayAdmin.h"

Admin adminAccount;

void displayReloadMoney() {
	adminAccount.reloadMoney();
}

void displayCheckATMBills() {
	using namespace std;
	ATM bills;
	
	system("cls");
	borders();
	
	ifstream infile;							
	infile.open("ATM_MACHINE.txt",ios::binary);
	if(!infile) { bills.init(); }
	
	infile.read((char*)&bills,sizeof(ATM));
	infile.close();
	
	gotoxy(25, 10); cout << "PHP 1000 Bills : " << bills.getThousands();
	gotoxy(25, 11); cout << "PHP 500 Bills : " << bills.getFiveHundreds();
	gotoxy(25, 12); cout << "PHP 100 Bills : " << bills.getHundreds();
	
	getch(); exitMessage();
}

