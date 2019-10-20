#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "atm.h"

void gotoxy(short x, short y) {
COORD pos = {x, y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void accessView(){
		int accNum,flag=0;
		char acc[4];
		FILE *fp;
		fp = fopen("accounts.txt","r");
	
	while(flag!=1){
		gotoxy(80/2-15,25/2);	
		printf("=====USC BANKING SERVICE======\n");
		
		gotoxy(80/2-15,(25/2)+1);	
		printf("Input Account Number:");
		
		gotoxy(80/2-15,25/2+2);	
		printf("Input Access Code:");
		
		gotoxy(80/2-15,25/2+3);
		printf("==============================");
		
		gotoxy(80/2+6,(25/2)+1);
		scanf("%d",&accNum);
		
		gotoxy(80/2+6,(25/2)+2);
		acc[0]=getch();
		printf("*");
		acc[1]=getch();
		printf("*");
		acc[2]=getch();
		printf("*");
		acc[3]=getch();
		printf("*");
		getch();
		rewind(fp);
	do{
		fscanf(fp,"%d %s %s %s %f",&c.acnR,c.acR,c.lastn,c.firstn,&c.curBal);
		if(accNum==c.acnR){
			if(strcmp(acc,c.acR)==0){
				flag=1;
				fclose(fp);
				system("cls");
				break;
				
			}else{
				flag=2;
				gotoxy(80/2-15,25/2+4);
				printf("Sorry, invalid password.");
				
				gotoxy(80/2-15,25/2+5);
				printf("Press a key to try again...");
			
				getch();
				system("cls");
				break;	
			}
		}else{
			flag=3;
		}
	}while(!feof(fp));		
		
		if(flag==3){
			gotoxy(80/2-15,25/2+4);
			printf("Sorry, account # %d is not existing.",accNum);
			
			gotoxy(80/2-15,25/2+5);
			printf("Press a key to try again...");
			
			getch();
			system("cls");		
		}
		
		system("cls");
	
	}
}

void mainMenu(){
	char choice;
	do{
	system("cls");
	gotoxy(80/2-10,25/2-5);
	printf("=====MAIN MENU=====");
	gotoxy(80/2-10,25/2-4);
	printf("[1]Inquire");
	gotoxy(80/2-10,25/2-3);
	printf("[2]Withdraw");
	gotoxy(80/2-10,25/2-2);
	printf("[3]Deposit");
	gotoxy(80/2-10,25/2-1);
	printf("[4]Fast Cash");
	gotoxy(80/2-10,25/2);
	printf("[5]History");
	gotoxy(80/2-10,25/2+1);
	printf("[6]Exit");
	gotoxy(80/2-10,25/2+2);
	printf("choice?");
	gotoxy(80/2-10,25/2+3);
	printf("===================");
	gotoxy(80/2-3,25/2+2);
	choice=getch();
	system("cls");
	
	switch(choice){
		case '1':	gotoxy(0,0);
					inquire();
					getch();
					break;
		case '2':	gotoxy(0,0);
					withMenu();
					getch();
					break;
		case '3':	gotoxy(0,0);
					depMenu();
					getch();
					break;
		case '4':	gotoxy(0,0);
					fastMenu();
					getch();
					break;
		case '5':	gotoxy(0,0);
					history();
					getch();
					break;
		}
					
}while(choice!='6');
}

int main(){
	
	accessView();
	time_t timer;
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);
    
    strftime(currdate, 30, "%m/%d/%Y", tm_info);
    strftime(currtime, 30, "%I:%M:%S %p", tm_info);
    strftime(hisdate, 30, "%m/%d/%Y", tm_info);
	mainMenu();
		
	getch();
	return 0;
	
}
