#ifndef __GETTERSSETTERS_H__
#define __GETTERSSETTERS_H__

class gettersSetters{
	
	public:
		
		int getCalorie();
		void setCalorie(int temp);
		
		int getWeight();
		void setWeight(int temp);
		
		float getPrice();
		void setPrice(float temp);
		
		char getFirstLetter();
		void setFirstLetter(char temp);	
		
		char getSecondLetter();
		void setSecondLetter(char temp);
		
		
	private:
		int calorie;
		int weight;
		float price;
		char firstLetter;
		char secondLetter;
		
			
};


#endif
