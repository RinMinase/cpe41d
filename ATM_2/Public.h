/**********************************
Author: 		Elizer Absin,
				James Rodriguez
**********************************/

#ifndef __PUBLIC_H
#define __PUBLIC_H

#include <string>

class ATMPublic {
	private:
		int sample_main();
		void history(int flag,std::string accNum,std::string fname,std::string lname,float bal);
				
	public:
		void browse(std::string accNum);
		int withdraw(float amount, std::string accNum);
		int deposit(float amount, std::string accNum);
		void accHistory(std::string accNum);
		int cleanHistory();
		int transfer(std::string accNum, std::string t_accNum, float amount);
};

#endif


