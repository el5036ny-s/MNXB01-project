#include <iostream>
#include <TGraphErrors.h>
#include "dataTree.h"
#include "tempTrender.h"
#include <TLatex.h>


tempTrender::tempTrender(std::string filePath) {

	//cout << "Filepath: " << filePath << endl;
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

void tempTrender::tempPerDay(Int_t excludeBadData) {

	// Open TTree from .root file.
	TFile *f = TFile::Open("/home/courseuser/git/eliasnyh/MNXB01-project/datasets/tempDataKarlstad.root");
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


void tempTrender::tempDev(Int_t type) {

	// Open TTree from .root file.
	TFile *f = TFile::Open("/home/courseuser/git/eliasnyh/MNXB01-project/datasets/tempDataKarlstad.root");
	TTree *dataTree = (TTree *) f->Get("tree");
	TBranch *eventBranch  = dataTree->GetBranch("event");

	// Create event object to import tree data to
	MyClass* event = new MyClass();
	eventBranch->SetAddress(&event);

	Int_t currentYear;

	//Determine the numbero of years
	Int_t nEvents = eventBranch->GetEntries();
	eventBranch->GetEntry(0);
	Int_t y1 = event->GetYear();
	eventBranch->GetEntry(nEvents-2);
	Int_t y2 = event->GetYear();
	Int_t totyears = y2 - y1;

	Double_t tSum[totyears];
	Double_t tCount[totyears];
	Double_t tAvg[totyears];
	Double_t wAvg[totyears];
	Double_t lAvg[totyears];

	// Set the contents of arrays to zeroes
	memset(tSum, 0, sizeof(tSum));
	memset(tCount, 0, sizeof(tCount));
	memset(tAvg, 0, sizeof(tAvg));
	memset(wAvg, 0, sizeof(wAvg));
	memset(lAvg, 0, sizeof(lAvg));

	// Iterate through all events in TTree branch
	for(Int_t i = 0; i < nEvents; i++) {
		// Update event object
		eventBranch->GetEntry(i);
		currentYear = event->GetYear();


		// If excludeBadData = 1, then exclude deviating data points
		//if(excludeBadData && !(event->GetQCode())) { continue; }
		if(currentYear<y1) { continue; }
		if(currentYear>y2) { continue; }

		if(type==0) {
			tSum[currentYear-y1]+=event->GetTemp();
			tCount[currentYear-y1]+=1;
		}

		if(type<0 && tSum[currentYear-y1]>event->GetTemp()) {
			tSum[currentYear-y1]=event->GetTemp();
			tCount[currentYear-y1]=1;
		}

		if(type>0 && tSum[currentYear-y1]<event->GetTemp()) {
			tSum[currentYear-y1]=event->GetTemp();
			tCount[currentYear-y1]=1;
		}

	}

	// create a red, blue and white graph
	TGraph *rgr  = new TGraph();
	TGraph *bgr  = new TGraph();
	TGraph *wgr  = new TGraph();
	TGraph *lgr  = new TGraph();
	//TMultiGraph *hs  = new TMultiGraph();

	// Calculate the arithmetic mean over the the days and then all years
	Double_t sum = 0;
	Double_t count = 0;
	for(Int_t i = 0; i < totyears; i++) {
		tAvg[i] = tSum[i] / tCount[i];
		sum += tSum[i];
		count += tCount[i];
		rgr->SetPoint(y1+i, y1+i, tAvg[i]);
	}
	Double_t avg = sum/count;

	//Find greatest and smallest value in plot, crop the overlaying graphs
	Double_t min = 100;
	Double_t max = -100;
	for(Int_t i = 0; i < totyears; i++) {
		bgr->SetPoint(y1+i, y1+i, avg);
		wAvg[i]=tAvg[i];
		if(min>tAvg[i]){min=tAvg[i];}
		if(max<tAvg[i]){max=tAvg[i];}
		if(type>=0){
			if(tAvg[i]>avg) {wAvg[i]=avg;}
		}
		else{
			if(tAvg[i]<avg) {wAvg[i]=avg;}
		}
		wgr->SetPoint(y1+i, y1+i, wAvg[i]);
		//cout<<(tAvg[i]+tAvg[i+1])/2<<endl<<tAvg[i]<<endl<<tAvg[i+1]<<endl;
		if(i==0){ lAvg[i] = (tAvg[i]+tAvg[i+1]+tAvg[i+2])/3; }                                     //horrible code for moving average
		else if(i==1){ lAvg[i] = (tAvg[i-1]+tAvg[i]+tAvg[i+1]+tAvg[i+2])/4; }
		else if(i==(totyears-2)){ lAvg[i] = (tAvg[i]+tAvg[i-1]+tAvg[i-2]+tAvg[i+1])/4; }
		else if(i==(totyears-1)){ lAvg[i] = (tAvg[i]+tAvg[i-1]+tAvg[i-2])/3; }
		else{lAvg[i] = ( tAvg[i-2]+tAvg[i-1]+tAvg[i]+tAvg[i+1]+tAvg[i+2])/5; }
		lgr->SetPoint(y1+i, y1+i, lAvg[i]);
	}

	//choose colors for the histograms
	TCanvas *c1 = new TCanvas ("c1","temperature developement",1200,800);
	if(type>=0){
		rgr->SetFillColor(kRed);
		bgr->SetFillColor(kBlue);
	}
	else{
		rgr->SetFillColor(kBlue);
		bgr->SetFillColor(kRed);
	}

		wgr->SetFillColor(kWhite);
		//hs->Add(rgr);
		//hs->Add(bgr);
		//hs->Add(wgr);
	lgr->SetLineWidth(2);
	rgr->Draw("AB");	bgr->Draw("B");		wgr->Draw("B");		lgr->Draw("L");
	//rgr->Draw("AC");	bgr->Draw("C");		wgr->Draw("C");		lgr->Draw("C");



	if(type>0){ rgr->GetHistogram()->GetYaxis()->SetTitle("maximal temperature [#circC]"); }
	if(type==0){ rgr->GetHistogram()->GetYaxis()->SetTitle("average temperature [#circC]"); }
	if(type<0){ rgr->GetHistogram()->GetYaxis()->SetTitle("minimal temperature [#circC]"); }

	//Set axis limits
	rgr->GetXaxis()->SetLimits(y1-.5,y2-.5);
	if(type>=0){
	rgr->GetHistogram()->SetMinimum(min-1);
	rgr->GetHistogram()->SetMaximum(max+1);
	}
	gPad->RedrawAxis("g");
	gPad->Modified();	//tell root, the canvas has changed

	f->Close();

}
