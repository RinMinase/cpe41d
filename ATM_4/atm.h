void fastMenu();
void withMenu();
void depMenu();
void inquire();
void history();
void updateFile(float balance);
void updateFast(float cash);
void updateWith(float cash);
void updateDepo(float cash);
char currtime[30],currdate[30],hisdate[30]; ;

struct client{
	char firstn[15],lastn[15],acR[4];
	int acnR;
	float curBal;
}c,client[5];

