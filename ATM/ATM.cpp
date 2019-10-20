#include <iostream>

#include "ATM.h"

using namespace std;

void displayMenu() {
	double balance = 10250.50f;
	int choice;
	
	while (choice != 4) {
		system("cls");
		cout << "Menu\n";
		cout << "[1] Inquire\n";
		cout << "[2] Deposit\n";
		cout << "[3] Withdraw\n";
		cout << "[4] Exit\n";
		cout << "Choice: ";
		fflush(stdin); cin >> choice;
		
		switch (choice) {
			case 1:
				if(inquire(balance) != -1) cout << "\nBalance: " << balance;
				break;
			case 2: balance = deposit(balance); break;
			case 3: balance = withdraw(balance); break;
			default: break;
		}
		getchar(); getchar();
	}
}

int checkPIN() {
	int input;
	
	cout << "Enter PIN: ";
	fflush(stdin); cin >> input;
	
	if (input != 1234) return 1;
	else return 0;
}

double withdraw(double balance) {
	double amount;
	
	if (checkPIN() == 0) {
		cout << "Enter amount to withdraw: ";
		fflush(stdin); cin >> amount;
		
		if (amount > balance) {
			cout << "Invalid amount";
			return balance;
		} else {
			cout << "Transaction successful";
			return (balance - amount);
		}
	} else {
		cout << "Invalid PIN";
		return balance;
	}
}

double deposit(double balance) {
	double amount;
	
	if (checkPIN() == 0) {
		cout << "Enter amount to deposit: ";
		fflush(stdin); cin >> amount;
		
		cout << "Transaction successful";
		return (balance + amount);
	} else {
		cout << "Invalid PIN";
		return balance;
	}
}

double inquire(double balance) {
	double amount;
	
	if (checkPIN() == 0) {
		cout << "Transaction successful";
		return (balance);
	} else {
		cout << "Invalid PIN";
		return -1;
	}
}
