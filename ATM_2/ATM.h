/**********************************
Author: 		Jondric Zafra
contact info:	jondric_zafra@yahoo.com or megatoncupcake@gmail.com
**********************************/

#ifndef __ATM_H
#define __ATM_H

class ATM
{
	private:
		int m_thousands_n;
		int m_fivehundreds_n;
		int m_twohundreds_n;
		int m_hundreds_n;
	public:
		void setThousands(int val);
		int getThousands();
		void setFiveHundreds(int val);
		int getFiveHundreds();
		void setTwoHundreds(int val);
		int getTwoHundreds();
		void setHundreds(int val);
		int getHundreds();
		void init();
		void initialize_main();
};

#endif
