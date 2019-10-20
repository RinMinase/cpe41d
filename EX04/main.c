#include <stdio.h>
#include <stdlib.h>

int pro,res,flag=0;

void initAlgo(int block[pro+1][res+1]) {
	int newblock[pro+1][res+1],
		diff[pro+1][res+1],
		available[res],
		totalreq[res],
		count=0,check,input,i,j;
	char choice;

	for(i=0;i<res;i++) { available[i]=0; totalreq[i]=0; }

	/*copy block to new block - reset to 0*/
	for(i=0;i<pro+1;i++){	
		for(j=0;j<res+1;j++){
			if(j!=0&&i!=0) { newblock[i][j]=0; diff[i][j]=0; }
			else { newblock[i][j]=block[i][j]; diff[i][j]=block[i][j]; }
		}
	}

	/*request sequence*/
	system("cls");
	for(i=0;i<pro+1;i++){
		for(j=0;j<res+1;j++) {
			check=0; // system("cls");
			if(j!=0&&i!=0) {
				do {
					printf("Enter Request for Resource #%d under Process #%d: ",j,i); scanf("%d",&input);
					if(input>block[i][j]) { printf("Request Denied! Decrease the Input."); }
					else { newblock[i][j]=input; check++; }
				} while(check!=1);
			}
		}
	} display(newblock); getch();

	/*check available*/
	for(j=0;j<res+1;j++) {
		for(i=0;i<pro+1;i++){ if(i!=0&&j!=0){ totalreq[j-1]+=newblock[i][j]; } }
		if(j!=0){ available[j-1]=newblock[0][j]-totalreq[j-1]; }
	}

	/*count safe*/
	for(j=0;j<res+1;j++) { for(i=0;i<pro+1;i++){ if(i!=0&&j!=0){ if(available[j-1]>=diff[i][j]){ count++; } } } }

	if(count!=0){ printf("\n\nStatus: SAFE"); } else { printf("\n\nStatus: UNSAFE"); }
	fflush(stdin); printf("\n\nContinue[Y/N]? "); scanf("%c",&choice); getch();

	switch(choice){
		case 'n': flag=1; system("cls"); break;
		default: system("cls"); printf("Refresh..."); break;
	} getch();
}

void initBlock(){
	int block[pro+1][res+1],i,j,input;

	/* input max for resources & processes */
	for(i=0;i<pro+1;i++){	
		for(j=0;j<res+1;j++){
			//system("cls");
			if(j==0&&i==0){ block[i][j]=0; }
			if(j==0&&i!=0){ block[i][j]=9; }
			if(j!=0&&i==0){ printf("Enter Max for Resource #%d: ",j); scanf("%d",&input); block[i][j]=input; }
			if(j!=0&&i!=0){ printf("Enter Max for Process #%d under Resource #%d: ",i,j); scanf("%d",&input); block[i][j]=input; }
		}
	} display(block); getch(); do{ initAlgo(block); } while(flag!=1);
}

void display(int block[pro+1][res+1]){
	int i,j;
	system("cls");
	for(i=0;i<pro+1;i++){
		for(j=0;j<res+1;j++){
			if(j==0&&i==0) { printf("\t"); }
			else if(j!=0&&i==0) { printf("Res%d\t",j); }
			else if(j==0&&i!=0) { printf("Proc%d\t",i); }
			else { printf("%d\t",block[i][j]); }
		} printf("\n");
	}
}

void input(){
	printf("Enter Number of Resources: "); scanf("%d",&res);
	printf("Enter Number of Processes: "); scanf("%d",&pro);
	printf("\n"); initBlock();
}


int main(int argc, char *argv[]) {
	input();
	printf("Terminating Program.");
	return 0;
}
