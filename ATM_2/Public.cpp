/**********************************
Author: 		Elizer Absin,
				James Rodriguez
**********************************/

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <conio.h>
#include "GlobalFunctions.h"
#include "Public.h"

using namespace std;

int ATMPublic::sample_main() {
	string acct="1234567891";
	string acct2="1234567892";
//	browse(acct);
//	withDraw(500,acct);
//  deposit(3000,acct);
//	accHistory(acct);
	transfer(acct,acct2,5000);

//	system("pause");
	return 0;
}

void ATMPublic::browse(string accNum) { //BALANCE INQUIRY
	string acnum,pin,fname,lname;
	float bal;
	ifstream file;
	file.open("ACCOUNTS.txt",ios::in);
	
	if(file) {
		while(file>>acnum>>pin>>fname>>lname>>bal) {
			if(acnum.compare(accNum)==0) {
				gotoxy(12, 8); cout << "                      ";
				for(int i = 7; i <= 13; i++) { gotoxy(25, i); cout << "                                       "; }
				
				gotoxy(25, 11);
				cout << "Current Balance : PHP " << bal;
				
//				cout<<"ACCOUNT NUMBER: "<<acnum<<"\nNAME: "<<fname<<" "<<lname<<"\nBALANCE: "<<bal;
                history(1,acnum,fname,lname,bal);
				break;
			}
		}
	} else { cout<<"file not found"; } file.close();
}

int ATMPublic::withdraw(float amount, string accNum) { //WITHDRAW USER
	string acnum,pin,fname,lname;
	float bal;
	ifstream file1;
	ofstream file2;
	
	if(amount<=10000) {
		file1.open("ACCOUNTS.txt",ios::in);
		file2.open("TEMP.txt",ios::out);
		
		if(file1) {
			while(file1>>acnum>>pin>>fname>>lname>>bal) {
				if(acnum.compare(accNum)==0) {
					if(bal>=amount) {
						file2<<acnum<<" "<<pin<<" "<<fname<<" "<<lname<<" "<<(bal-amount)<<"\n";
						history(2,acnum,fname,lname,bal);
					} else { return 1; }
				} else { file2<<acnum<<" "<<pin<<" "<<fname<<" "<<lname<<" "<<bal<<"\n"; }
			}
		}
		
		file1.close();
		file2.close();
		
		remove("ACCOUNTS.TXT");
		if(rename("TEMP.TXT","ACCOUNTS.TXT")==0) { return 0; } else { return 1; }
	}
}

int ATMPublic::deposit(float amount, string accNum) { //DEPOSIT USER
	string acnum,pin,fname,lname;
	float bal;
	ifstream file1;
	ofstream file2;
	
	if(amount<=10000) {
		file1.open("ACCOUNTS.txt",ios::in);
		file2.open("TEMP.txt",ios::out);
		
		if(file1) {
			while(file1>>acnum>>pin>>fname>>lname>>bal) {
				if(acnum.compare(accNum)==0) {
					if(bal>=amount) {
						file2<<acnum<<" "<<pin<<" "<<fname<<" "<<lname<<" "<<(bal+amount)<<"\n";
						history(3,acnum,fname,lname,bal);
					} else { return 1; }
				} else { file2<<acnum<<" "<<pin<<" "<<fname<<" "<<lname<<" "<<bal<<"\n"; }
			}
		}
		
		file1.close();
		file2.close();
		
		remove("ACCOUNTS.TXT");
		if(rename("TEMP.TXT","ACCOUNTS.TXT")==0) { return 0; } else { return 1; }
	}
}

void ATMPublic::history(int flag,string accNum,string fname,string lname,float bal) { //UPDATE HISTORY
	string temp;
	ofstream file;
	file.open("HISTORY.txt",std::ios_base::app);
	
	time_t now = time(0);
	char* dt=ctime(&now);

	if(file) {
		if(flag==1) { temp="CHECK-BALANCE"; file<<accNum<<" "<<fname<<" "<<lname<<" "<<bal<<" "<<temp<<" "<<dt; }
		if(flag==2) { temp="WITHDRAW"; file<<accNum<<" "<<fname<<" "<<lname<<" "<<bal<<" "<<temp<<" "<<dt; }
		if(flag==3) { temp="DEPOSIT"; file<<accNum<<" "<<fname<<" "<<lname<<" "<<bal<<" "<<temp<<" "<<dt; }
		if(flag==4) { temp="TRANSFER"; file<<accNum<<" "<<fname<<" "<<lname<<" "<<bal<<" "<<temp<<" "<<dt; }
		file.close();
	}
	
	cleanHistory();
}

int ATMPublic::cleanHistory() {
	using namespace std;
	
	string acnum,fname,lname,bal,action,day,month,nday,time,year;
    int ctr=0;
    
	ifstream file;
	ofstream file2;
	
	file.open("HISTORY.txt",ios::in);
	file2.open("HISTORY_TEMP.txt",std::ios_base::app);
	
	
	if(file) {
		while(file>>acnum>>fname>>lname>>bal>>action>>day>>month>>nday>>time>>year) { ctr++; };
		file.close();
	}
	
	if(ctr > 10) { ctr -= 10; }
	
	file.open("HISTORY.txt",ios::in);
	
	if(file) {
		while(file>>acnum>>fname>>lname>>bal>>action>>day>>month>>nday>>time>>year) {
			if(ctr > 0) { ctr--; }
			else { file2<<acnum<<" "<<fname<<" "<<lname<<" "<<bal<<" "<<action<<" "<<day<<" "<<month<<" "<<nday<<" "<<time<<" "<<year<<"\n"; }
		};
	}
	
	file.close();
	file2.close();
	
	remove("HISTORY.txt");
	if(rename("HISTORY_TEMP.txt","HISTORY.txt")==0) { return 0; } else { return 1; }
}

void ATMPublic::accHistory(string accNum) { //CHECK HISTORY USER
	string acnum,fname,lname,bal,action,day,month,nday,time,year;
	ifstream file;
	file.open("HISTORY.txt",ios::in);
	
	if(file) {
		while(file>>acnum>>fname>>lname>>bal>>action>>day>>month>>nday>>time>>year) {
			if(acnum.compare(accNum)==0) {
				gotoxy(12, 8); cout << "                      ";
				for(int i = 7; i <= 13; i++) { gotoxy(25, i); cout << "                                       "; }
				
				gotoxy(25, 10);
				cout << "Balance : PHP" << bal;
				gotoxy(25, 11);
				cout << "Action : " << action;		
				gotoxy(25, 12);
				cout << "Date : " << day << " " << month << " " << nday << " " << time << " " << year;
				
//				cout<<acnum<<" "<<fname<<" "<<lname<<" "<<bal<<" "<<action<<" "<<day<<" "<<month<<" "<<nday<<" "<<time<<" "<<year<<"\n";
				getch();
			}
		}
	} else { cout<<"ERROR"; } file.close();
}

int ATMPublic::transfer(string accNum, string t_accNum, float amount) { //TRANSFER accNum amount TO t_accNum amount
	string acnum,pin,fname,lname;
	float bal;
	int flag1=0,flag2=0;
	ifstream file1;
	ofstream file2;
	
	if(amount<=10000) {
		file1.open("ACCOUNTS.txt",ios::in);
		file2.open("TEMP.txt",ios::out);
		
		if(file1) {
			while(file1>>acnum>>pin>>fname>>lname>>bal) {
				if(acnum.compare(accNum)==0) {
					if(bal>=amount) {
						file2<<acnum<<" "<<pin<<" "<<fname<<" "<<lname<<" "<<(bal-amount)<<"\n";
						history(4,acnum,fname,lname,bal);
					} else { flag1=0; }
				} else { file2<<acnum<<" "<<pin<<" "<<fname<<" "<<lname<<" "<<bal<<"\n"; }
			}
			file1.close();
			file2.close();
		
			remove("ACCOUNTS.TXT");
			if(rename("TEMP.TXT","ACCOUNTS.TXT")==0) { flag1=1; } else { flag1=0; }
		}
		
		file1.open("ACCOUNTS.txt",ios::in);
		file2.open("TEMP.txt",ios::out);
		if(file1) {
			while(file1>>acnum>>pin>>fname>>lname>>bal) {
				if(acnum.compare(t_accNum)==0) {
					if(bal>=amount) { file2<<acnum<<" "<<pin<<" "<<fname<<" "<<lname<<" "<<(bal+amount)<<"\n"; } else { flag2=0; }
				} else {
					file2<<acnum<<" "<<pin<<" "<<fname<<" "<<lname<<" "<<bal<<"\n";
				}
			}
			file1.close();
			file2.close();
		
			remove("ACCOUNTS.TXT");
			if(rename("TEMP.TXT","ACCOUNTS.TXT")==0) { flag2=1; } else { flag2=0; }
		} if(flag1+flag2==2) { return 0; } else { return 1; }
	}
}
