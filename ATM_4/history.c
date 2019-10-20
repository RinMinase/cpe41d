#include <stdio.h>
#include <conio.h>
#include "atm.h"

void history(){
	FILE *hist = fopen("history.txt","r");
	int acR;
	float deb,cre,total;
	char hdate[25],htime[25],dis[2],sdate[25],edate[25],ch;
	printf("====HISTORY====\n");
	printf("Date: %s\n",currdate);
	printf("Time: %s\n",currtime);
	printf("Name: %s,%s\n",c.lastn,c.firstn);
	printf("Account Number: %d\n",c.acnR);
	printf("Current Balance:Php%10.2f\n\n",c.curBal);
	printf("=====OPTION===\n[1]CURRENT MONTH\n[2]INCLUSIVE DATES");
	ch = getch();
	system("cls");
	if(ch=='1'){
			printf("CURRENT MONTH:%s\n",currdate);
			printf("===============================================\nDATE\t\tTIME\t\tDEBIT\tCREDIT\n");
		do{
		fscanf(hist,"%d %s %s %s %f %f",&acR,hdate,htime,dis,&deb,&cre);
		if(acR==c.acnR){
			if(strcmp(hdate,currdate)==0){
				printf("%s\t%s\t%.2f\t%.2f\n",hdate,htime,deb,cre);
				total+=deb;
				total+=cre;
			}
		}
		}while(!feof(hist));	
			printf("===============================================\n\t\t\t\tTOTAL:%.2f",total);
		
	}else if(ch=='2'){
		printf("START DATE?mm/dd/yyyy:");
		fflush(stdin);
		gets(sdate);
		printf("END DATE?mm/dd/yyyy:");
		fflush(stdin);
		gets(edate);
		printf("INCLUSIVE DATES:%s to %s\n",sdate,edate);
		printf("===============================================\nDATE\t\tTIME\t\tDEBIT\tCREDIT\n");
			do{
		fscanf(hist,"%d %s %s %s %f %f",&acR,hdate,htime,dis,&deb,&cre);
		if(acR==c.acnR){
			if(strcmp(hdate,sdate)==0){
				printf("%s\t%s\t%.2f\t%.2f\n",hdate,htime,deb,cre);
				total+=deb;
				total+=cre;
			}else if(strcmp(hdate,edate)==0){
				printf("%s\t%s\t%.2f\t%.2f\n",hdate,htime,deb,cre);
				total+=deb;
				total+=cre;
			}
		}
		}while(!feof(hist));	
			printf("===============================================\n\t\t\t\tTOTAL:%.2f",total);
	}
	
}
