/**********************************
Author: 		Jondric Zafra
contact info:	jondric_zafra@yahoo.com or megatoncupcake@gmail.com
**********************************/

#include <iostream>
#include <fstream>
#include "ATM.h"

void ATM::setThousands(int val)		{m_thousands_n = val;}//getters and setters
int ATM::getThousands()				{return m_thousands_n;}
void ATM::setFiveHundreds(int val)	{m_fivehundreds_n = val;}
int ATM::getFiveHundreds()			{return m_fivehundreds_n;}
//void ATM::setTwoHundreds(int val)	{m_twohundreds_n = val;}
//int ATM::getTwoHundreds()			{return m_twohundreds_n;}
void ATM::setHundreds(int val)		{m_hundreds_n = val;}
int ATM::getHundreds()				{return m_hundreds_n;}

void ATM::init()//initialize atm bills database to zero; saves the whole atm object rather than individual integers
{
	using namespace std;
	
	this->setThousands(0);
	this->setFiveHundreds(0);
//	this->setTwoHundreds(0);
	this->setHundreds(0);
	
	ofstream outfile;
	outfile.open("ATM_MACHINE.txt",ios::binary|ios::trunc);//atm.dat is the name of the file. saved in binary form; replaces "atm.dat" if it already exists
	outfile.write((char*)this,sizeof(ATM));
	outfile.close();
}

void ATM::initialize_main()
{
	/*
	Atm example;	
	example.init();	//initialize database(erases any changes you've done, so comment this out after running the program once)
	
	using namespace std;

	Admin zafra;
	zafra.reloadMoney();
		
	//code below is just checking if the amount changed; use example.init() to reset the database
	ifstream infile;							
	infile.open("atm.dat",ios::binary);
	infile.read((char*)&example,sizeof(Atm));
	infile.close();
	cout<<example.getThousands()<<";"<<example.getFiveHundreds()<<";"<<example.getTwoHundreds()<<";"<<example.getHundreds()<<";";
*/
	/*Record first;
	first.setAcctnum(1);
	first.setActivity("yahallo");
	first.setAmount(1000);
	first.setDaytime();
	first.updateToDB();
	
	Record second;
	second.setAcctnum(2);
	second.setActivity("deposit");
	second.setAmount(-500);
	second.setDaytime();
	second.updateToDB();*/
	
//	Admin zafra;
//	zafra.historyTransaction();
}

