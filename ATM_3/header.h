#ifndef __HDR_H
#define __HDR_H

class ATM {
	private:
		struct data{
			char * name;
			int pin;
			float balance;
		};
		
	public:
		void insertData(char * nameValue, float balanceValue);
		void editData(char * query, float newBalanceValue);
		void queryData(char * query);
		
		int isValidWithdrawal(char * query, float withdrawalValue);
		int isPinCorrect(char * query, int pinValue);
		
		float atmInquire(char * nameValue);
		void atmWithdraw(char * nameValue, float withdrawalValue);
		void atmDeposit(char * nameValue, float depositValue);
};


#endif
