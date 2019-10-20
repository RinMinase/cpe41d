#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NODE{
	   char jobid;
	   int bursttime;
	   int arrtime;
	   int prioritynum;
	   int tt;
	   int wt;
	   struct NODE *next;
};

struct NODE *front = NULL,
			*rear = NULL,
			*head = NULL,
			*tail = NULL;

char jobid[20];

int bursttime[20],
	arrtime[20],
	prioritynum[20],
	choice, num=0, time, qt;

float allwt[4],
	  alltt[4];

void enqueue(char w,int x,int y,int z) {
	struct NODE *temp = (struct NODE *)calloc(1, sizeof(struct NODE));
	temp->jobid=w;
	temp->bursttime=x;
	temp->arrtime=y;
	temp->prioritynum=z;
	temp->next=NULL;

	if(front==NULL) {
		rear=temp;
		front=rear;
	} else {
		rear->next=temp;
		rear=temp;
	}
}

int del(char id) {
	struct NODE *temp = (struct NODE *)calloc(1, sizeof(struct NODE));
	struct NODE* prev=(struct NODE *)calloc(1, sizeof(struct NODE));

	temp=front;
	while(temp!=NULL) {
		if(temp->jobid==id) {
			if(temp==front) { front=temp->next; free(temp); return 1; }
			else { prev->next=temp->next; free(temp); return 1; }
		} else { prev=temp; temp= temp->next; }
	} return 0;
}

void insert() {
	int i=0;
	printf("Enter Number of Jobs: ");
	scanf("%d",&num);

	do {
		fflush(stdin);

		printf("\nJob_ID: "); scanf("%c",&jobid[i]);
		printf("Burst_TIME: "); scanf("%d",&bursttime[i]);
		printf("Arr_TIME: "); scanf("%d",&arrtime[i]);
		printf("Priority_NUM: "); scanf("%d",&prioritynum[i]);

		enqueue(jobid[i],bursttime[i],arrtime[i],prioritynum[i]);
		i++;
	} while(i<num);
}

void dequeue() {
	struct NODE *temp = (struct NODE *)calloc(1, sizeof(struct NODE));
	temp=front;

	if(front==NULL) { printf("Empty Queue!\n"); }
	if(front == rear) { front = rear = NULL; } else { front = front->next; } free(temp);
}

void requeue() {
	struct NODE *temp = (struct NODE *)calloc(1, sizeof(struct NODE));
	int i;

	for(i=0;i<num;i++) { enqueue(jobid[i],bursttime[i],arrtime[i],prioritynum[i]); }
}

char shortest() {
	struct NODE *temp = (struct NODE *)calloc(1, sizeof(struct NODE));
	char small;
	int smallest=100000;

	temp=front;
	do {
		if(temp->bursttime<smallest) {
			smallest=temp->bursttime;
			small=temp->jobid;
		} temp=temp->next;
	} while(temp!=NULL); return small;
}

char priority() {
	struct NODE *temp = (struct NODE *)calloc(1, sizeof(struct NODE));
	char priority;
	int smallest=100000;

	temp=front;
	do {
		if(temp->prioritynum<smallest) {
			smallest=temp->prioritynum;
			priority=temp->jobid;
		} temp=temp->next;
	} while(temp!=NULL); return priority;
}

void printTable(int process) {
	char *processName = (char *)calloc(30, sizeof(char));
	struct NODE *temp = (struct NODE *)calloc(1, sizeof(struct NODE));
	int i=0; temp = front;

	switch(process) {
		case 1: strcpy(processName, "FIRST COME - FIRST SERVED"); break;
		case 2: strcpy(processName, "SHORTEST JOB NEXT"); break;
		case 3: strcpy(processName, "PRIORITY SCHEDULING"); break;
		case 4: strcpy(processName, "SHORTEST REMAINING TIME"); break;
		case 5: strcpy(processName, "ROUND ROBIN"); break;
		default: break;
	}

	system("cls");
	printf("%s\n\n", processName);
	printf("ELAPSED TIME: %d\n\n",time);
	printf("JOB_ID	 BURST_TIME	 ARR_TIME	 PRIORITY_NUM\n");

	if(temp!=NULL) {
		do {
	 		printf(" %c %10d %14d %12d \t\n",temp->jobid,temp->bursttime,temp->arrtime,temp->prioritynum);
			temp=temp->next;
		} while(temp!=NULL);
	}
}

void FCFS() {
	float tt=0, wt=0;
	int burst,check=0;
	struct NODE *temp = (struct NODE *)calloc(1, sizeof(struct NODE));

	temp=front;
	printTable(1);
	printf("\n\npress <SPACEBAR> to continue... "); getch();
	time=0;

	do {
		if(check==0) { burst=temp->bursttime; check++; }

		if (temp->bursttime==0) {
			temp->tt = time-temp->arrtime;
			temp->wt = temp->tt-burst;
			if (temp->wt<0) { temp->wt=0; }
			tt+=temp->tt;
			wt+=temp->wt;
			temp=temp->next;
			dequeue();
			check--;
		} else {
			temp->bursttime=temp->bursttime-1;
			printTable(1);
			time++;
			printf("\n\npress <SPACEBAR> to continue... ");
			getch();
		}
	} while(temp!=NULL);

	printTable(1);
	printf("\n\nSIMULATION COMPLETE...\n");
	printf("Average Turnaround Time is: %2.1f\n",(tt/num));
	printf("Average Waiting Time is: %2.1f\n",(wt/num));
	printf("\n\npress any key to continue... ");
	alltt[0]=tt/num;
	allwt[0]=wt/num;
	getch();
}

void SJN() {
	float tt=0,wt=0;
	int burst,check=0;
	struct NODE *temp = (struct NODE *)calloc(1, sizeof(struct NODE));
	struct NODE *temp1 = (struct NODE *)calloc(1, sizeof(struct NODE));

	char id;
	printTable(2);
	printf("\n\npress <SPACEBAR> to continue... ");
	getch();
	temp=front;
	time=0;
	do {
		if(check==0) { burst=temp->bursttime; check++; }

		id=shortest();
		if(temp->jobid==id) {
			do {
				temp1=temp;
				temp1->bursttime=temp1->bursttime-1;
				printTable(2);
				time++;
				printf("\n\npress <SPACEBAR> to continue... ");
				getch();
			}while(temp1->bursttime!=0);
			temp->tt = time-temp->arrtime;
			temp->wt = temp->tt-burst;
			if(temp->wt<0) { temp->wt=0; }
			tt+=temp->tt;
			wt+=temp->wt;
			check--;
			del(id);
			temp=front;
		} else { temp=temp->next; }
	} while(temp!=NULL);

	printTable(2);
  	printf("\n\nSIMULATION COMPLETE...\n\n");
	printf("Average Turnaround Time is: %2.1f\n",(tt/num));
	printf("Average Waiting Time is: %2.1f\n",(wt/num));
	printf("\n\npress any key to continue... ");
	alltt[1]=tt/num;
	allwt[1]=wt/num;
	getch();

}

void PS() {

	float tt=0,wt=0;
	int burst,check=0;
	struct NODE *temp = (struct NODE *)calloc(1, sizeof(struct NODE));
	struct NODE *temp1 = (struct NODE *)calloc(1, sizeof(struct NODE));

	char id;
	printTable(3);
	printf("\n\npress <SPACEBAR> to continue... ");
	getch();
	temp=front;
	time=0;

	do {
		if(check==0) { burst=temp->bursttime; check++; }

		id=priority();
		if(temp->jobid==id) {
			do {
				temp1=temp;
				temp1->bursttime=temp1->bursttime-1;
				printTable(3);
				time++;
				printf("\n\npress <SPACEBAR> to continue... ");
				getch();
			} while(temp1->bursttime!=0);

			temp->tt = time-temp->arrtime;
			temp->wt = temp->tt-burst;
			if(temp->wt<0) { temp->wt=0; }
			tt+=temp->tt;
			wt+=temp->wt;
			check--;
			del(id);
			temp=front;
		} else{ temp=temp->next; }
	} while(temp!=NULL);

	printTable(3);
  	printf("\n\nSIMULATION COMPLETE...\n\n");
	printf("Average Turnaround Time is: %2.1f\n",(tt/num));
	printf("Average Waiting Time is: %2.1f\n",(wt/num));
	printf("\n\npress any key to continue... ");
	alltt[2]=tt/num;
	allwt[2]=wt/num;
	getch();
}

void SRT() {
	float tt=0,wt=0;
	int burst,check=0,x,y;
	struct NODE *temp = (struct NODE *)calloc(1, sizeof(struct NODE));
	struct NODE *temp2 = (struct NODE *)calloc(1, sizeof(struct NODE));
	struct NODE *swap = (struct NODE *)calloc(1, sizeof(struct NODE));

	int n, c, d,small=1000,totaljob=0,jobproc=0;
	char smallest,id;
	temp=front;

	do { totaljob++; temp=temp->next; } while(temp!=NULL);

	printTable(4);
	printf("\n\npress <SPACEBAR> to continue... ");
	getch();


	for(time=0, jobproc=0; jobproc<totaljob; time++) {
		small=1000;

		temp=front;
		do {
			if(temp->arrtime<=time && temp->bursttime<small) {
				small=temp->bursttime;
				smallest=temp->jobid;
			} temp=temp->next;
		} while(temp!=NULL);

		temp=front;
		do {
			if(temp->jobid==smallest) {
				if(temp->bursttime==0) {
					id=temp->jobid;
					for(x=0;x<num;x++) { if(id==jobid[x]) { y=x; } }

					burst=bursttime[y];
					temp->tt = time-temp->arrtime;
					temp->wt = temp->tt-burst;
					if(temp->wt<0) { temp->wt=0; }
					tt+=temp->tt;
					wt+=temp->wt;

					del(smallest);
					jobproc++;
					time--;
					break;
				} else {
					temp->bursttime=temp->bursttime-1;
					printTable(4);
					printf("\n\npress <SPACEBAR> to continue... ");
					getch();
					break;
				}
			} temp=temp->next;
		} while(temp!=NULL);

		if(small==1000) { printTable(4); printf("\n\npress <SPACEBAR> to continue... "); getch(); }
	}

	printTable(4);
	printf("\n\nSIMULATION COMPLETE...");
	printf("Average Turnaround Time is: %2.1f\n",(tt/num));
	printf("Average Waiting Time is: %2.1f\n",(wt/num));
	printf("\n\npress any key to continue... ");
	alltt[3]=tt/num;
	allwt[3]=wt/num;
	getch();

}

void RR() {
	float tt=0,wt=0;
	int burst,check=0;
	char id;
	struct NODE *temp = (struct NODE *)calloc(1, sizeof(struct NODE));
	struct NODE *temp1 = (struct NODE *)calloc(1, sizeof(struct NODE));
	int i,x,y;
	temp=front;

	printTable(5);
	printf("\n\npress <SPACEBAR> to continue... ");

	getch();
	time=0;
	do {
		i=0; y=0;
		do {
			if(temp->bursttime==0) {
				id=temp->jobid;
				for(x=0;x<num;x++) { if(id==jobid[x]) { y=x; } }
				burst=bursttime[y];
				temp->tt = time-temp->arrtime;
				temp->wt = temp->tt-burst;
				if(temp->wt<0) { temp->wt=0; }
				tt+=temp->tt;
				wt+=temp->wt;
				i++;
				break;
			} else {
				temp->bursttime=temp->bursttime-1;
				printTable(5);
				time++;
				i++;
				printf("\n\npress <SPACEBAR> to continue... ");
				getch();
			}
		} while(i<qt);

		if(temp->bursttime!=0) { enqueue(temp->jobid,temp->bursttime,temp->arrtime,temp->prioritynum); }
		temp=temp->next; dequeue();
	} while(temp!=NULL);

	printTable(5);
	printf("\n\nSIMULATION COMPLETE...\n\n");
	printf("Average Turnaround Time is: %2.1f\n",(tt/num));
	printf("Average Waiting Time is: %2.1f\n",(wt/num));
	printf("\n\npress any key to continue... ");
	alltt[4]=tt/num;
	allwt[4]=wt/num;
	getch();
}

void ProcessJob(char id) {
	struct NODE *temp = (struct NODE *)calloc(1, sizeof(struct NODE));
	do{ if(temp->jobid==id) { temp->bursttime=temp->bursttime-1; } temp->next; } while(temp!=NULL);
}

void displayAll() {
	int choice,best=0,i;

	system("cls");
	printf("\nPROCESS SCHEDULING ALGORITHM\n\n");
  	printf("ALGORITHM\tATT\tAWT\n");
 	printf("   FCFS\t%2.1f\t%2.1f\n",alltt[0],allwt[0]);
 	printf("   SJN\t%2.1f\t%2.1f\n",alltt[1],allwt[1]);
 	printf("   PS\t%2.1f\t%2.1f\n",alltt[2],allwt[2]);
 	printf("   SRT\t%2.1f\t%2.1f\n",alltt[3],allwt[3]);
 	printf("   RR\t%2.1f\t%2.1f\n",alltt[4],allwt[4]);

 	for(i=0;i<5;i++) { if((alltt[i] < alltt[best]) && (allwt[i] < allwt[best])) { best = i; } }

 	printf("\n\nBest Process Scheduling Algorithm: ");
	switch(best) {
		case 0:  printf("First Come First Served\n"); getch(); break;
		case 1:  printf("Shortest Job Next\n"); getch();	break;
		case 2:  printf("Priority Scheduling\n"); getch(); break;
		case 3:  printf("Shortest Remaining Time\n"); getch(); break;
		case 4:  printf("Round Robin\n"); getch(); break;
		default:  printf("--Error--"); getch(); break;
	}
}

void UI() {
	struct NODE *temp = (struct NODE *)calloc(1, sizeof(struct NODE));
	int i=0;

	temp=front;
	system("cls");
	printf("\n\t   PROCESS SCHEDULING ALGORITHM\n\n\n\n");
 	printf("JOB_ID	 BURST_TIME	 ARR_TIME	PRIORITY_NUM\n");
 	do { printf(" %c %10d %15d %15d \t\n",temp->jobid,temp->bursttime,temp->arrtime,temp->prioritynum); temp=temp->next; } while(temp!=NULL);
}

void MENU() {
	printf("\n\nPROCESS SCHEDULER\n");
  	printf("[1] First Come - First Served\n");
  	printf("[2] Shortest Job Next\n");
  	printf("[3] Priority Scheduling\n");
  	printf("[4] Shortest Time Remaining\n");
  	printf("[5] Round Robin\n");
  	printf("[6] ALL\n[7] EXIT\nChoice: "); scanf("%d",&choice);

  	switch(choice) {
  		case 1: FCFS(); requeue(); break;
  		case 2: SJN(); requeue(); break;
  		case 3: PS(); requeue(); break;
  		case 4: SRT(); requeue(); break;
  		case 5: printf("Enter Quantum Time: "); scanf("%d",&qt); RR(); requeue(); break;
  		case 6: FCFS(); requeue(); SJN(); requeue(); PS(); requeue(); SRT(); requeue(); system("cls"); printf("Enter Quantum Time: "); scanf("%d",&qt); RR(); requeue(); displayAll(); break;
		case 7: system("cls"); printf("Program Terminating..."); exit(0); break;
  		default: printf("Invalid Choice!"); break;
	}
}

int main(int argc, char *argv[]) {
	insert();
	while(1) { UI(); MENU(); }
	return 0;
}
