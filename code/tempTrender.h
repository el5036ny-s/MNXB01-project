#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>

#include <iostream>

using namespace std;

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TH1.h>
#include <TGraph.h>

#include <dataTree.h>




class tempTrender {
	public:
	std::string dataFilePath;
	
	tempTrender(std::string filePath); //Construct using the specified file
	~tempTrender() {} //Destructor
	
	
	//void tempOnDay(int monthToCalculate, int dayToCalculate); //Make a histogram of the temperature on this day
	//void tempOnDay(int dateToCalculate); //Make a histogram of the temperature on this date
	//void tempPerDay(); //Make a histogram of the average temperature of each day of the year
	//void hotCold(); //Make a histogram of the hottest and coldest day of the year
	//void tempPerYear(int yearToExtrapolate); //Make a histogram of average temperature per year, then fit and extrapolate to the given year
	

	void dailyTempDiff();
	

	private:
	
};

tempTrender::tempTrender(std::string filePath) {

	cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	dataFilePath = filePath;
}

void tempTrender::dailyTempDiff() {
	
	TFile *f = TFile::Open("/home/courseuser/git/eliasnyh/MNXB01-project/datasets/tempDataKarlstad.root");
	TTree *dataTree = (TTree *) f->Get("tree");
	TBranch *eventBranch  = dataTree->GetBranch("event");
	
	MyClass* event = new MyClass();
	eventBranch->SetAddress(&event);
	
	Double_t midnightSum[31];
	Double_t noonSum[31];
	
	Int_t midnightCount[31];
	Int_t noonCount[31];
	
	Int_t nEvents = eventBranch->GetEntries();
	
	
	// cout << "nEvents = " << eventBranch->GetEntries() << endl;
	Int_t currentDay;
	
	for(Int_t i = 0; i < nEvents; i++) {
		
		eventBranch->GetEntry(i);
		
		currentDay = event->GetDay();
		
		if(event->GetTime() == 0) {
			
			midnightSum[currentDay - 1] += event->GetTemp();
			midnightCount[currentDay - 1] += 1; 
		}
		
		if(event->GetTime() == 12) { 
			noonSum[currentDay - 1] += event->GetTemp();
			midnightCount[currentDay - 1] += 1; 
		}
		
		//cout << event->GetDayOfYear() << endl;
		
		if(i > 400){ break; }
	}
	
	cout << "Temps on the 22nd: " << midnightSum[22] << " and " << midnightCount[22] << endl;
	

	f->Close();
	
}


#endif
