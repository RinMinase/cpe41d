#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "atm.h"

void updateFile(float balance){
	FILE *original = fopen("accounts.txt", "r");
	FILE *newfile;
	char buf[200];
	int i=0,j=0,x=0;
	
//	while (fgets(buf,sizeof buf,original)!=NULL){
//		sscanf(buf,"%d %s %f %s %s",&client[i].acnR,client[i].acR,&client[i].curBal,client[i].lastn,client[i].firstn);
		//printf("%d %s %.2f %s %s\n",client[i].acnR,client[i].acR,client[i].curBal,client[i].lastn,client[i].firstn);
  //    	i++;
   // }
   
   do{
   	fscanf(original,"%d %s %s %s %f",&client[i].acnR,client[i].acR,client[i].lastn,client[i].firstn,&client[i].curBal);
   	i++;
   }while(!feof(original));
    
    do{
      	if(c.acnR=client[x].acnR){
      	client[x].curBal=balance;
      	break;
      	}
      	x++;
    }while(x<5);
    
    newfile = fopen ("client_temp.txt", "w");
	
      for(j=0;j<5;j++){
      	fprintf(newfile,"%d %s %s %s %f\n",client[j].acnR,client[j].acR,client[j].lastn,client[j].firstn,client[j].curBal);
      }
      
      fclose(original);
      fclose(newfile);
      
      remove("accounts.txt");
      rename("client_temp.txt","accounts.txt");
}

