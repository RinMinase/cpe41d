/**********************************
Author: 		Jondric Zafra
contact info:	jondric_zafra@yahoo.com or megatoncupcake@gmail.com
**********************************/

#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>

#include "Admin.h"
#include "ATM.h"

using namespace std;

void Admin::reloadMoney() {
	int thousands,fivehundreds,/*twohundreds,*/hundreds;
	ATM machine; //the "database" is a whole Atm object that is saved and loaded from/to the "atm.dat" file
	
	system("cls");
	
	cout<<"Reload Money"<<endl;						//get inputs
	cout<<"Insert how many thousands: ";
	cin>>thousands;
	cout<<"Input how many fivehundreds: ";
	cin>>fivehundreds;
//	cout<<"Input how many twohundreds: ";
//	cin>>twohundreds;
	cout<<"Input how many hundreds: ";
	cin>>hundreds;						
	
	ifstream infile;
	infile.open("ATM_MACHINE.txt",ios::binary);
	if(!infile) { machine.init(); }
	
	infile.read((char*)&machine,sizeof(ATM));
	infile.close();
	machine.setThousands(machine.getThousands() + thousands);			//adds the inputs to the already existing values in the atm
	machine.setFiveHundreds(machine.getFiveHundreds() + fivehundreds);
//	machine.setTwoHundreds(machine.getTwoHundreds() + twohundreds);
	machine.setHundreds(machine.getHundreds() + hundreds);
	
	ofstream outfile;								//overwrites the old values with the new ones
	outfile.open("ATM_MACHINE.txt",ios::binary|ios::trunc);
	outfile.write((char*)&machine,sizeof(ATM));
	outfile.close();
}


//void Admin::historyTransaction() {		//double plus needs to be updated later
//	Record transaction;					//assuming the "database" is made of multiple Record objects
//	tm timedate;
//	
//	ifstream infile;
//	infile.open("HISTORY.dat",ios::binary);
//	
//	while(	infile.read((char*)&transaction,sizeof(Record))) {	//read through the history/database one at a time
//		cout<<"Account Num: "<<transaction.getAcctnum()<<endl;	//print out information
//		cout<<"Activity: "<<transaction.getActivity()<<endl;
//		cout<<"Amount: "<<transaction.getAmount()<<endl;
//		timedate = transaction.getDaytime();
//		cout<<"Date&Time: "<<timedate.tm_mon+1<<"/"<<timedate.tm_mday<<"/"<<timedate.tm_year-100<<" "<< timedate.tm_hour<<":"<<timedate.tm_min<<":"<<timedate.tm_sec<<endl;	//assuming date&time is saved as tm structure;assuming #include<ctime>
//		system("pause");
//	}
//}
//assuming something like
//class Record{
//	public:
//		int	acctnum;
//		char* activity;
//		int amount;
//		tm	daytime;
//};


