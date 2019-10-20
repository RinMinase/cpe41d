#include <fstream>
#include <string>
#include <iostream>

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "ATM.h"
#include "GlobalFunctions.h"
#include "ATMFunctions.h"

int thousands, fivehundreds, hundreds;

int dispenseMoney(float val) {
	using namespace std;
	
	ATM bills;
	int value = (int)val, flag = 0;
	
	ifstream infile;							
	infile.open("ATM_MACHINE.txt",ios::binary);
	if(!infile) { bills.init(); }
	
	infile.read((char*)&bills,sizeof(ATM));
	infile.close();
	
	thousands = bills.getThousands();
	fivehundreds = bills.getFiveHundreds();
	hundreds = bills.getHundreds();
	
	int newThousands = thousands, 
		newFivehundreds = fivehundreds, 
		newHundreds = hundreds,
		newValue = value;
	
//	printf("INITAL: %d, %d, %d\n\n", thousands, fivehundreds, hundreds);
	
	while(newValue >= 1000) {
		if(newThousands > 0) { newValue -= 1000; newThousands--; } 
		else if(newFivehundreds >= 2) { newValue -= 1000; newFivehundreds -= 2; } 
		else if(newHundreds >= 10) { newValue -= 1000; newHundreds -= 10; } 
		else { printf("insufficient bills"); flag=1; break; }
	}
	
	while(newValue >= 500 && flag !=1) {
		if(newFivehundreds > 0) { newValue -= 500; newFivehundreds--; } 
		else if(newHundreds >= 5) { newValue -= 500; newHundreds -= 5; } 
		else { printf("insufficient bills"); flag=1; break; }
	}
	
	while(newValue >= 100 && flag !=1) {
		if(newHundreds > 0) { newValue -= 100; newHundreds -= 1; } 
		else { printf("insufficient bills"); flag=1; break; }
	}
	
	if(flag == 0) {
		value = newValue;
		thousands = newThousands;
		fivehundreds = newFivehundreds;
		hundreds = newHundreds;
	}
	
//	printf("\n\nFINAL: %d, %d, %d", thousands, fivehundreds, hundreds);

	updateATM(); // printf("ATM Updated...");
	getch();
	
	return flag;
}

int updateATM() {
	using namespace std;
	ATM machine;
	
	ifstream infile;
	infile.open("ATM_MACHINE.txt",ios::binary);
	if(!infile) { machine.init(); }
	
	infile.read((char*)&machine,sizeof(ATM));
	infile.close();
	
	machine.setThousands(thousands);
	machine.setFiveHundreds(fivehundreds);
	machine.setHundreds(hundreds);
	
	ofstream outfile;
	outfile.open("ATM_MACHINE.txt",ios::binary|ios::trunc);
	outfile.write((char*)&machine,sizeof(ATM));
	outfile.close();
	
	return 0;
}

int displayAllTransactions() {
	using namespace std;
	
	string acnum,fname,lname,bal,action,day,month,nday,time,year;
	ifstream file;
	file.open("HISTORY.txt",ios::in);
	
	if(file) {
		while(file>>acnum>>fname>>lname>>bal>>action>>day>>month>>nday>>time>>year) {
			gotoxy(12, 8); cout << "                      ";
			for(int i = 7; i <= 13; i++) { gotoxy(25, i); cout << "                                       "; }
				
			gotoxy(25, 9);
			cout << acnum << "  " << lname << ", " << fname;
			gotoxy(25, 10);
			cout << "Balance : PHP" << bal;
			gotoxy(25, 11);
			cout << "Action : " << action;		
			gotoxy(25, 12);
			cout << "Date : " << day << " " << month << " " << nday << " " << time << " " << year;
			
			getch();
		}
	} else { cout<<"ERROR"; } file.close();
}
