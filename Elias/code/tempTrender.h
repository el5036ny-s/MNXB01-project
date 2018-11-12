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
#include <TCanvas.h>

//#include <dataTree.h>




class tempTrender {
	public:
	std::string dataFilePath;

	tempTrender(std::string filePath); //Construct using the specified file
	~tempTrender() {} //Destructor

	void dailyTempDiff(Int_t excludeBadData);
	void tempPerDay(Int_t excludeBadData);

	private:

};


#endif
