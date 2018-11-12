#include <iostream>
#include "dataTree.h"
#include "tempTrender.h"


tempTrender::tempTrender(std::string filePath) {

	cout << "Filepath: " << filePath << endl;
	dataFilePath = filePath;
}

void tempTrender::dailyTempDiff(Int_t excludeBadData) {
	
	// Open TTree from .root file.
	TFile *f = TFile::Open("/home/courseuser/git/eliasnyh/MNXB01-project/datasets/tempDataKarlstad.root");
	TTree *dataTree = (TTree *) f->Get("tree");
	TBranch *eventBranch  = dataTree->GetBranch("event");
	
	// Create event object to import tree data to
	MyClass* event = new MyClass();
	eventBranch->SetAddress(&event);
	
	Double_t midnightSum[366];
	Double_t noonSum[366];
	
	Double_t midnightCount[366];
	Double_t noonCount[366];
	
	// Set the contents of arrays to zeroes
	memset(noonSum, 0, sizeof(noonSum));
	memset(midnightSum, 0, sizeof(midnightSum));
	memset(noonCount, 0, sizeof(noonCount));
	memset(midnightCount, 0, sizeof(midnightCount));
	
	Int_t nEvents = eventBranch->GetEntries();
	
	Int_t currentDayOfYear;
	
	// Iterate through all events in TTree branch
	for(Int_t i = 0; i < nEvents; i++) {
		
		// Update event object
		eventBranch->GetEntry(i);
		
		// If excludeBadData = 1, then exclude deviating data points
		if(excludeBadData && !(event->GetQCode())) { continue; }
		
		currentDayOfYear = event->GetDayOfYear();
		
		// If event is from midnight
		if(event->GetTime() == 0) {
			midnightSum[currentDayOfYear - 1] += event->GetTemp();
			midnightCount[currentDayOfYear - 1] += 1; 
		}
		
		// If event is from noon
		if(event->GetTime() == 12) {
			noonSum[currentDayOfYear - 1] += event->GetTemp();
			noonCount[currentDayOfYear - 1] += 1;
		}
	
	
	}
	
	// Graph the result
	TGraph *gr  = new TGraph();
	
	// For each day of the year, calculate the arithmetic mean over all years
	for(Int_t i = 0; i < 366; i++) {
		Double_t aveNoon = noonSum[i] / noonCount[i];
		Double_t aveMidnight = midnightSum[i] / midnightCount[i];
		
		gr->SetPoint(i, i + 1, aveNoon - aveMidnight);
	}
	
	
	TCanvas *c1 = new TCanvas("c1","Daily Temp Diff");

	gr->SetFillColor(40);
	gr->SetTitle("Temp difference between noon and midnight");
	gr->GetHistogram()->GetXaxis()->SetTitle("Day of Year");
	gr->GetHistogram()->GetYaxis()->SetTitle("DeltaT(Noon, Midnight)");
	
	gr->Draw("AB");
	
	f->Close();
	
}
