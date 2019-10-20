#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "gettersSetters.h"

using namespace std;

int main(int argc, char** argv) {
	gettersSetters gettersSetters;
	
	int set, get;
	float val;
	char firstLet;
	char secondLet;
	cin>>set;
	gettersSetters.setCalorie(set);
	
	cin>>get;
	gettersSetters.setWeight(get);
	
	cin>>val;
	gettersSetters.setPrice(val);
	
	cin>>firstLet;
	gettersSetters.setFirstLetter(firstLet);
	
	cin>>secondLet;
	gettersSetters.setSecondLetter(secondLet);
	
	
	cout<<gettersSetters.getCalorie()<<"\n";

	cout<<gettersSetters.getWeight()<<"\n";
	cout<<gettersSetters.getPrice()<<"\n";
	cout<<gettersSetters.getFirstLetter()<<"\n";
	cout<<gettersSetters.getSecondLetter()<<"\n";
	
	return 0;
}
