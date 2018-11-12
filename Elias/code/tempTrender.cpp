#include <iostream>
#include <TGraphErrors.h>
#include "dataTree.h"
#include "tempTrender.h"
#include <TLatex.h>


tempTrender::tempTrender(std::string filePath) {

	cout << "Filepath: " << filePath << endl;
	dataFilePath = filePath;
}

void tempTrender::dailyTempDiff(Int_t excludeBadData) {

	// Open TTree from .root file.
	TFile *f = TFile::Open("/home/courseuser/Downloads/MNXB01-project-master/datasets/tempDataKarlstad.root");
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

void tempTrender::tempPerDay(Int_t excludeBadData) {

	// Open TTree from .root file.
	TFile *f = TFile::Open("/home/courseuser/Downloads/MNXB01-project-master/datasets/tempDataKarlstad.root");
	TTree *dataTree = (TTree *) f->Get("tree");
	TBranch *eventBranch  = dataTree->GetBranch("event");

	// Create event object to import tree data to
	MyClass* event = new MyClass();
	eventBranch->SetAddress(&event);

	Int_t n = 366;
	Double_t tSum[n];
	Double_t tCount[n];
	Double_t tAvg[n];
	Double_t tErr[n];
	Double_t tDay[n];
	Double_t t0[n];

	// Set the contents of arrays to zeroes
	memset(tSum, 0, sizeof(tSum));
	memset(tCount, 0, sizeof(tCount));
	memset(tAvg, 0, sizeof(tAvg));
	memset(tErr, 0, sizeof(tErr));
	memset(tDay, 0, sizeof(tDay));
	memset(t0, 0, sizeof(t0));

	Int_t nEvents = eventBranch->GetEntries();

	Int_t currentDayOfYear;

	// Iterate through all events in TTree branch
	for(Int_t i = 0; i < nEvents; i++) {

		// Update event object
		eventBranch->GetEntry(i);

		// If excludeBadData = 1, then exclude deviating data points
		if(excludeBadData && !(event->GetQCode())) { continue; }

		currentDayOfYear = event->GetDayOfYear();
		tSum[currentDayOfYear - 1] += event->GetTemp();
		tCount[currentDayOfYear - 1] += 1;

	}

	// For each day of the year, calculate the arithmetic mean over all years
	for(Int_t i = 0; i < n; i++) {
		tAvg[i] = tSum[i] / tCount[i];
		tDay[i]=i+1;
	}

	// For each day of the year, calculate standard deviation

	for(Int_t i = 0; i < nEvents; i++) {
		// Update event object
		eventBranch->GetEntry(i);
		// If excludeBadData = 1, then exclude deviating data points
		if(excludeBadData && !(event->GetQCode())) { continue; }

		currentDayOfYear = event->GetDayOfYear();
		tErr[currentDayOfYear-1] += pow((event->GetTemp()-tAvg[currentDayOfYear-1]),2);
	}

	for(Int_t i = 0; i < n; i++) {
		tErr[i] = sqrt(tErr[i]/ tCount[i]);
	}

	// Graph the result
	TGraphErrors *gr  = new TGraphErrors(n,tDay,tAvg,t0,tErr);


	TCanvas *c2 = new TCanvas("c2","Temperature per Day");

	gr->SetLineColor(40);
	gr->SetTitle("Temperature per Day");
	gr->GetHistogram()->GetXaxis()->SetTitle("Day of Year");
	gr->GetHistogram()->GetYaxis()->SetTitle("Temperature [#circ C]");
	gr->GetXaxis()->SetLimits(0,n);

	gr->Draw();

	f->Close();

}
