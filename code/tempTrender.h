#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>

#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TH1.h>
#include <TGraph.h>
#include <dataTree.h>



class tempTrender {
	public:
	tempTrender(std::string filePath); //Construct using the specified file
	~tempTrender() {} //Destructor
	
	//void tempOnDay(int monthToCalculate, int dayToCalculate); //Make a histogram of the temperature on this day
	//void tempOnDay(int dateToCalculate); //Make a histogram of the temperature on this date
	//void tempPerDay(); //Make a histogram of the average temperature of each day of the year
	//void hotCold(); //Make a histogram of the hottest and coldest day of the year
	//void tempPerYear(int yearToExtrapolate); //Make a histogram of average temperature per year, then fit and extrapolate to the given year
	
	void dailyTempDiff() {
		
		TFile f(filePath);
		
		Int_t nDays = 23380;
		// TH1F *hist = new TH1F("hist", "Temperature difference between morning and evening", 
		
		MyClass* event = new MyClass();
		TBranch *branch  = T.GetBranch("event");
		branch->SetAddress(&event);
		
		Int_t nEvents = T.GetEntries();
		
		for(Int_t i = 0; i < nEvents; i++) {
			
			cout << branch->GetTime() << endl;
			
			if(i > 100) { break; }
		}
		
		f->Close();
	}

	private:
	
};

#endif
