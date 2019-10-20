#ifndef __ATM_H
#define __ATM_H

void displayMenu();
int checkPIN();

double withdraw(double balance);
double deposit(double balance);
double inquire(double balance);

#endif
