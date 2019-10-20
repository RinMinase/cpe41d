#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "structs.h"

void gotoxy(short x, short y);
void printMemoryList(PARTITION *array);
void printJobList(JOB **queue);
void printMenu();
void initializePartitions(PARTITION **array);
int addJob(JOB **queue,int name,int size,int pendingTime);

int spanTimePending(PARTITION **array);
int spanTimeFirstFit(PARTITION **array,JOB **queue);
int spanTimeBestFit(PARTITION **array,JOB **queue);
int spanTimeNextFit(PARTITION **array,JOB **queue);
int spanTimeWorstFit(PARTITION **array,JOB **queue);
int checkPending(JOB **queue);
int checkProcessing(PARTITION *array);

void activateAllJobs(JOB **queue);
void initializeReports(REPORT **rep);
void printReports(REPORT *rep);
int countDrops(JOB **queue);
int countTotalJobSize(JOB **queue);

PARTITION *array;
JOB *queue;
REPORT *rep;

int main(int argc, char *argv[]) {
	int running, jbcnt, tempTime, tempSize;
    char chc, span; 

    array = (PARTITION *)malloc(sizeof(PARTITION)*10);
    rep = (REPORT *)malloc(sizeof(REPORT)*4);
    
    initializePartitions(&array);
    initializeReports(&rep);
    queue=NULL;
    
    running=1;
    jbcnt=0;
    
    while(running) {
        printMemoryList(array); printJobList(&queue); printMenu();

        chc=getch();
        if((chc=='i')||(chc=='I')) {
        	if(jbcnt < MAXJOBS) {
				gotoxy(54,21); printf("                    ");
				gotoxy(54,22); printf("                    ");
				gotoxy(54,23); printf("                    ");

				gotoxy(54,21);
				printf("Enter time: ");
				scanf("%d",&tempTime);

				gotoxy(54,22);
				printf("Enter size: ");
				scanf("%d",&tempSize);

				jbcnt++; 
				addJob(&queue,jbcnt,tempSize,tempTime);      
			} else {
				printf("Job queue is full...");
				getch();    
			}
		}
		
		if((chc=='s')||(chc=='S')) {
			gotoxy(54,20); printf("[1]First Fit        ");
        	gotoxy(54,21); printf("[2]Best Fit         ");
        	gotoxy(54,22); printf("[3]Next Fit         ");
        	gotoxy(54,23); printf("[4]Worst Fit        ");
			chc=getch(); span=0;

			switch(chc) {
				case '1':
					while(checkPending(&queue) || checkProcessing(array)) {
						printMemoryList(array); 
						printJobList(&queue);

						gotoxy(54,21); printf("Press Spacebar to   ");
			        	gotoxy(54,22); printf("Decrement Unit Time ");
						chc=getch();

						if(chc==' ') {
							spanTimePending(&array);
							spanTimeFirstFit(&array,&queue);
							span++;  
						} else if(chc=='x') { break; }
					}
					rep[0].finished=1;
					rep[0].timeTaken=span;
					rep[0].droppedJobs=countDrops(&queue);
					rep[0].totalThroughput=countTotalJobSize(&queue);
					chc = '1';
					break;
					
				case '2':
					while(checkPending(&queue)||checkProcessing(array)) {
						printMemoryList(array); 
						printJobList(&queue);
						
						gotoxy(54,21); printf("Press Spacebar to   ");
			        	gotoxy(54,22); printf("Decrement Unit Time ");
						chc=getch();

						if(chc==' ') {
							spanTimePending(&array);
							spanTimeBestFit(&array,&queue); 
							span++;  
						} else if(chc=='x') { break; }
					}
					rep[1].finished=1;
					rep[1].timeTaken=span;
					rep[1].droppedJobs=countDrops(&queue);
					rep[1].totalThroughput=countTotalJobSize(&queue);
					chc = '2';
					break;
					
				case '3':
					while(checkPending(&queue)||checkProcessing(array)) {
						printMemoryList(array); 
						printJobList(&queue); 
						
						gotoxy(54,21); printf("Press Spacebar to   ");
			        	gotoxy(54,22); printf("Decrement Unit Time ");
						chc=getch();
						
						if(chc==' ') {
							spanTimePending(&array);
							spanTimeNextFit(&array,&queue); 
							span++;  
						} else if(chc=='x') { break; }
					}

					rep[2].finished=1;
					rep[2].timeTaken=span;
					rep[2].droppedJobs=countDrops(&queue);
					rep[2].totalThroughput=countTotalJobSize(&queue);
					chc = '3';
					break;

				case '4':
					while(checkPending(&queue)||checkProcessing(array)) {
						printMemoryList(array); 
						printJobList(&queue);
						
						gotoxy(54,21); printf("Press Spacebar to   ");
			        	gotoxy(54,22); printf("Decrement Unit Time ");
						chc=getch();
						
						if(chc==' ') {
							spanTimePending(&array);
							spanTimeWorstFit(&array,&queue);  
							span++;  
						} else if(chc=='x') { break; }
					}

					rep[3].finished = 1;
					rep[3].timeTaken = span;
					rep[3].droppedJobs = countDrops(&queue);
					rep[3].totalThroughput = countTotalJobSize(&queue);
					chc = '4';
					break;
				
				default: break;                                   
            } 

            activateAllJobs(&queue);
            
            if(chc == '1' || chc == '2' || chc == '3' || chc == '4') {
				printMemoryList(array); printJobList(&queue);
	            
				gotoxy(54,20); printf("                    ");
	        	gotoxy(54,21); printf("                    ");
	        	gotoxy(54,22); printf("                    ");
	        	gotoxy(54,23); printf("                    ");

	        	gotoxy(54,20); printf("%-12s", rep[(int)chc - 49].name);
	        	gotoxy(54,21); printf("Total Time: %-8d", rep[(int)chc - 49].timeTaken);
	        	gotoxy(54,22); printf("Dropped: %-11d", rep[(int)chc - 49].droppedJobs);
	        	gotoxy(54,23); printf("Thruput: %-9.2f", rep[(int)chc - 49].totalThroughput);
	        	getch();
        	}
        }
        
		if((chc=='r')||(chc=='R')) { printReports(rep); getch(); }
		if((chc=='x')||(chc=='X')) { running=0; }
    } getch(); return 0;
}


void gotoxy(short x, short y) {
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	
}

void printMemoryList(PARTITION *array) {
	int cnt;
	system("cls");
	printf("                    MEMORY LIST                    \n");
	printf("---------------------------------------------------\n");
	printf("| %6s  | %6s | %4s  | %4s | %3s |\n","Block","Size","Job","Job Size","Time Left");
	printf("---------------------------------------------------\n");
	for(cnt=0;cnt<10;cnt++) {
		printf("| %6s | %6d  |",(array[cnt].name),(array[cnt].size));
		if((array[cnt].busy)==1) {
			printf(" %4d  |   %5d  |",(array[cnt].pendingName),(array[cnt].pendingSize));
			printf("    %-5d  |\n", (array[cnt].pendingTime));
		} else {
			printf(" %4s  |   %5s  |","","");
			printf("    %-5s  |\n", "");
		}
		printf("---------------------------------------------------\n");
	}
}

void printJobList(JOB **queue) {
	short x,y;
	JOB *rem;
	rem=*queue;
	gotoxy(59,0);
	printf("JOB LIST");
	
	x=54; y=2; gotoxy(x,y);
	printf("%-8s %-5s %s","Job No.","Time","Job Size");

	y++;
	while((*queue)!=NULL) {
		if(((*queue) -> status) == PENDING) {
			gotoxy(x,y++); 
			printf("%-8d %-5d %d",(*queue)->name,(*queue)->pendingTime,(*queue)->size); 
		} (*queue)=((*queue)->next);
	} (*queue)=rem;
}

void printMenu() {
	gotoxy(54,20); printf("                    ");
	gotoxy(54,21); printf("[I] Insert          ");
	gotoxy(54,22); printf("[S] Start           ");
	gotoxy(54,23); printf("[R] Report          ");
}

void initializePartitions(PARTITION **array) {
	strcpy(((*array)->name),"01"); 
	((*array) -> size) = 9500;
	((*array) -> busy) = 0;
	
	strcpy(((*array+1)->name),"02"); 
	((*array + 1) -> size) = 7000;
	((*array + 1) -> busy) = 0; 
	
	strcpy(((*array+2)->name),"03"); 
	((*array + 2) -> size) = 4500;
	((*array + 2) -> busy) = 0;   
	
	strcpy(((*array+3)->name),"04"); 
	((*array + 3) -> size) = 8500;
	((*array + 3) -> busy) = 0;   
	
	strcpy(((*array+4)->name),"05"); 
	((*array + 4) -> size) = 3000;
	((*array + 4) -> busy) = 0;   
	
	strcpy(((*array+5)->name),"06"); 
	((*array + 5) -> size) = 9000;
	((*array + 5) -> busy) = 0;   
	
	strcpy(((*array+6)->name),"07"); 
	((*array + 6) -> size) = 1000;
	((*array + 6) -> busy) = 0;
	
	strcpy(((*array+7)->name),"08"); 
	((*array + 7) -> size) = 5500;
	((*array + 7) -> busy) = 0;   
	
	strcpy(((*array+8)->name),"09"); 
	((*array + 8) -> size) = 1500;
	((*array + 8) -> busy) = 0;   
	
	strcpy(((*array+9)->name),"10"); 
	((*array + 9) -> size) = 500;
	((*array + 9) -> busy) = 0;
}

int addJob(JOB **queue,int name,int size,int pendingTime) {
	JOB *rem;
	JOB *temp;
	temp = (JOB *)malloc(sizeof(JOB));
	(temp->name) = name;
	(temp->size) = size;
	(temp->pendingTime)=pendingTime;
	(temp->status) = PENDING;
	(temp->next) = NULL;
	
	if((*queue)!=NULL) { 
		rem=(*queue);  
		while(((*queue)->next) != NULL) { (*queue) = ((*queue) -> next); } 
		((*queue)->next) = temp; 
		(*queue) = rem;
	} else { (*queue) = temp; }
	return 1;
}

int spanTimePending(PARTITION **array) {
	JOB *rem1;
	PARTITION *rem2;
	int cnt;
	
	rem2=*array;
	cnt=0;
	
	while(cnt<10) {
		if(((*array+cnt)->busy)==1) {
			((*array+cnt)->pendingTime)-=1;

			if(((*array+cnt)->pendingTime)<=0) { ((*array+cnt)->busy) = 0; }
		} cnt++;
	} *array=rem2; return 1;
}

int spanTimeFirstFit(PARTITION **array,JOB **queue) {
	JOB *rem1; PARTITION *rem2;
	int cnt; rem1 = *queue; rem2 = *array; cnt=0;
	
	while((*queue)!=NULL) {
		if(((*queue)->status) == PENDING) {     
			if(((*queue)->size) > MAXMEMORY) { (*queue)->status=DROPPED; return 0; } 
			cnt=0;
			while(cnt<10) {
				if((((*array + cnt) -> busy) == 0) && (((*array+cnt) -> size) >= ((*queue) -> size))) {
					((*array+cnt)->pendingName)=((*queue)->name);                                                                  
					((*array+cnt)->pendingSize)=((*queue)->size);
					((*array+cnt)->pendingTime)=((*queue)->pendingTime);
					((*array+cnt)->busy)=1;
					((*queue)->status)=ACCEPTED;
					(*queue)=rem1;
					(*array)=rem2;
					return 1;
				} cnt++;
			}
		} (*queue)=((*queue)->next);
	} *queue=rem1; *array=rem2; return 0;
}

int spanTimeBestFit(PARTITION **array,JOB **queue) {
	JOB *rem1; PARTITION *rem2;
	int min; int cnt;

	rem1=*queue; min=0;
	rem2=*array; cnt=0;
	
	while((*queue)!=NULL) {
		if(((*queue)->status)==PENDING) {     
			if(((*queue) -> size) > MAXMEMORY) { (*queue)->status=DROPPED; return 0; } 
			min=0; cnt=0;
			while(cnt<10) {     
				if((((*array+cnt)->size)>=((*queue)->size))) {
					if((((*array+cnt)->busy)==1)) { cnt++; }                                     
					else if((((*array+cnt)->size)-((*queue)->size))<(((*array+min)->size)-((*queue)->size))) {  min=cnt; }
				} cnt++;
			}

			if((((*array+min)->busy)==0) && (((*array+min)->size)>=((*queue)->size))) {
				((*array+min) -> pendingName) = ((*queue)->name);
				((*array+min) -> pendingSize) = ((*queue)->size);
				((*array+min) -> pendingTime) = ((*queue)->pendingTime);
				((*array+min) -> busy)=1;
				((*queue) -> status) = ACCEPTED;
				(*queue)=rem1;
				(*array)=rem2;
				return 1;
			}
		} (*queue) = ((*queue) -> next);
	} *queue=rem1; *array=rem2; return 0;
}

int spanTimeNextFit(PARTITION **array,JOB **queue) {
	JOB *rem1; PARTITION *rem2;
	int cnt; rem1=*queue; rem2=*array; cnt=9;
	
	while((*queue)!=NULL) {
		if(((*queue)->status)==PENDING) {     
			if(((*queue)->size)>MAXMEMORY) { (*queue)->status=DROPPED; return 0; } 
			cnt=9;
			while(cnt>=0) {
				if((((*array + cnt) -> busy) == 0) && (((*array+cnt) -> size) >= ((*queue) -> size))) {
					((*array+cnt)->pendingName)=((*queue)->name);
					((*array+cnt)->pendingSize)=((*queue)->size);
					((*array+cnt)->pendingTime)=((*queue)->pendingTime);
					((*array+cnt)->busy)=1;
					((*queue)->status)=ACCEPTED;
					(*queue)=rem1;
					(*array)=rem2;
					return 1;
				} cnt--;
			}
		} (*queue)=((*queue)->next);
	} *queue=rem1; *array=rem2; return 0;   
}

int spanTimeWorstFit(PARTITION **array,JOB **queue) {
	JOB *rem1; PARTITION *rem2;
	int min; int cnt;

	rem1=*queue; min=0;
	rem2=*array; cnt=0;
      
	while((*queue)!=NULL) {
		if(((*queue)->status)==PENDING) {     
			if(((*queue)->size)>MAXMEMORY) { (*queue)->status=DROPPED; return 0; } 
			min=9;  cnt=0;
			
			while(cnt<10) {     
				if((((*array+cnt)->size)>=((*queue)->size))) {
					if((((*array+cnt)->busy)==1)) { cnt++; }                                     
					else if((((*array+cnt) -> size) - ((*queue) -> size)) > (((*array+min) -> size) - ((*queue) -> size))) { min=cnt; }
				} cnt++;
			}
			
			if((((*array+min)->busy)==0)&&(((*array+min)->size)>=((*queue)->size))) {
				((*array + min) -> pendingName) = ((*queue) ->name);
				((*array + min) -> pendingSize) = ((*queue)->size);
				((*array + min) -> pendingTime) = ((*queue)->pendingTime);
				((*array + min) -> busy) =1;
				((*queue) -> status) = ACCEPTED;
				(*queue) = rem1; (*array) = rem2; return 1;
			}
		} (*queue)=((*queue)->next);
	} *queue = rem1; *array = rem2; return 0;
}

int checkPending(JOB **queue) {
	JOB *rem; rem = (*queue);
	
	while((*queue)!=NULL) {
		if(((*queue)->status)==PENDING) { (*queue)=rem; return 1; }
		(*queue)=(*queue)->next;            
	} (*queue)=rem; return 0; 
}

int checkProcessing(PARTITION *array) {
	for(int cnt=0;cnt<10;cnt++) { if((array[cnt].busy)==1) return 1; } return 0;  
}

void activateAllJobs(JOB **queue) {
	JOB *rem; rem=*queue;

	while((*queue)!=NULL) {
		((*queue)->status) = PENDING;
		(*queue) = (*queue)->next;
	} *queue = rem;
}

void initializeReports(REPORT **rep) {   
	((*rep)->finished)=0;
	strcpy((*rep)->name,"First Fit");
	((*rep)->timeTaken)=0;
	((*rep)->droppedJobs)=0;
	((*rep)->totalThroughput)=0;
	
	((*rep+1)->finished)=0;
	strcpy((*rep+1)->name,"Best Fit");
	((*rep+1)->timeTaken)=0;
	((*rep+1)->droppedJobs)=0;
	((*rep+1)->totalThroughput)=0;
	
	((*rep+2)->finished)=0;
	strcpy((*rep+2)->name,"Next Fit");
	((*rep+2)->timeTaken)=0;
	((*rep+2)->droppedJobs)=0;
	((*rep+2)->totalThroughput)=0;
	
	((*rep+3)->finished)=0;
	strcpy((*rep+3)->name,"Worst Fit");
	((*rep+3)->timeTaken)=0;
	((*rep+3)->droppedJobs)=0;
	((*rep+3)->totalThroughput)=0;
}

void printReports(REPORT *rep) {
	system("cls");
	printf(" Simulation Summary Report\n\n %-12s %-12s %-12s %-12s\n","Method","Time Taken","Dropped Jobs","Throughput");
	for(int cnt=0;cnt<4;cnt++) {
		if(rep[cnt].finished==1) { printf(" %-12s %-12d %-12d %-12.2f\n",rep[cnt].name,rep[cnt].timeTaken,rep[cnt].droppedJobs,rep[cnt].totalThroughput); } 
		else { printf(" %-12s %-12s %-12s %-12s\n",rep[cnt].name,"","",""); }                
	}   
}

int countDrops(JOB **queue) {
	JOB *rem; int ret = 0; rem = *queue;
      
	while((*queue)!=NULL) {
		if(((*queue)->status)==DROPPED) { ret++; }              
		(*queue)=(*queue)->next;
	} *queue=rem; return ret;    
}

int countTotalJobSize(JOB **queue) {
	JOB *rem; int ret = 0;
	rem=*queue;
      
	while((*queue)!=NULL) {
		if(((*queue)->status)==ACCEPTED) { ret+=((*queue)->size); }              
		(*queue)=(*queue)->next;
	} *queue=rem; return ret;     
}