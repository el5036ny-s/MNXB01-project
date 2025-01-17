#include <iostream>
#include <fstream>

using namespace std;

#include <TFile.h>
#include <TTree.h>
#include <TString.h>

#include "dataTree.h"


void RootImport(char inputFilePath[40]) 
{	
  TFile* file = new TFile("tempData.root", "RECREATE");
  TTree* tree = new TTree("tree", "Output tree");
  
	
  
  char *dummyPtr;
  
  MyClass* event = new MyClass();
  
  tree->Branch("event", "MyClass", &event, 64000, 1)
;
	
  ifstream readFile(inputFilePath);
  
  // Walk through the first couple of lines (which does not include datapoints)

  Char_t stream[200];
  while(!readFile.eof()) {
    
    readFile.getline(stream, 200);
    TString helpString(stream);
    //    cout << helpString << endl;
    cout << helpString.Contains("Datum") << endl;
    if(helpString.Contains("Datum"))
      break;
  }

  char DateStr[40];
  char TimeStr[40];
  char TempStr[40];
  char QCodeStr[200];

	Int_t n = 0;
	
  while(!readFile.eof()) {

    readFile.getline(DateStr, 40, ';');
    readFile.getline(TimeStr, 40, ';');
    readFile.getline(TempStr, 40, ';');
    readFile.getline(QCodeStr, 200); 
    
    
    TString helpStr(DateStr);
    TString yearStr(helpStr(0, 4));
    Int_t year = yearStr.Atoi();
    
    TString monthStr(helpStr(5,7));
    Int_t month = monthStr.Atoi();
    
    TString dayStr(helpStr(8,10));
    Int_t day = dayStr.Atoi();
    
    
    helpStr= TimeStr;
    TString hourString(helpStr(0,2));
    Double_t hour = hourString.Atoi();
    
    helpStr = TempStr;
    Double_t temp = helpStr.Atof();
    
    event->SetDate(year, month, day);
    event->SetTime(hour);
    event->SetTemp(temp);
    if(QCodeStr[0] == 'G') { event->SetQCode(1); } else {event->SetQCode(0); }
    
      
    tree->Fill();
    
    n++;
  }
  
  tree->Write();
  readFile.close();
  file->Close();
}
