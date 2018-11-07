#include <fstream>
#include <iostream>

using namespace std;

#include <TFile.h>
#include <TTree.h>

#include <stdio.h>
#include <stdlib.h>

#include "dataTree.h"


void RootImport(char inputFilePath[40]) {
	
	TFile* file = new TFile("tempData.root", "RECREATE");
	TTree* tree = new TTree("tree", "Output tree");
	
	FILE *readFile;
	
	Char_t stream[40];
	char* DateStr;
	char* TimeStr;
	char* TempStr;
	char* QCodeStr;
	
	// char dummyTemp[8];
	
	char *dummyPtr;
	
	MyEvent* event = new MyEvent();
	
	tree->Branch("event", &event);
	
	readFile = fopen(inputFilePath,"r");
	
	
	while(fgets(stream, 40, readFile)) {
		
		if(stream[10] == ';') {
			// event = new MyEvent();
			
			DateStr = strtok(stream, ";");
			TimeStr = strtok(NULL, ";");
			TempStr = strtok(NULL, ";");
			QCodeStr = strtok(NULL, ";");
			
			event->SetDate(DateStr);
			event->SetTime(TimeStr);
			
			event->SetTemp(strtod(TempStr, &dummyPtr));
			event->SetQCode(*QCodeStr);
			
			tree->Fill();
		}
	}
	
	fclose(readFile);
	file->Close();
}
