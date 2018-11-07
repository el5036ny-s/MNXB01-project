
#include <TObject.h>

class MyEvent : public TObject {
	private:
	
		Int_t year;
		Int_t month;
		Int_t day;
		
		Int_t time;
		
		Double_t temp;
		
		char qCode;
	
	public:
		
		MyEvent();

		ClassDef(MyEvent, 5); // Help class	
		
	
		void SetDate(Char_t Date[10]) {
			char* dummyStr;
			
			dummyStr = strtok(Date, "-");
			year = atoi(dummyStr);
			
			dummyStr = strtok(NULL, "-");
			month = atoi(dummyStr);
			
			dummyStr = strtok(NULL, "-");
			day = atoi(dummyStr);
		
		}
		void SetTime(Char_t Time[8]) {
			char* dummyStr;
			dummyStr = strtok(Time, ":");
			time = atoi(dummyStr);
		}
		void SetTemp(Double_t newTemp) {
			temp = newTemp;
		}
		void SetQCode(char newQCode) {
			qCode = newQCode;
		}
		
		Int_t GetYear() { return year; }
		Int_t GetMonth() { return month; }
		Int_t GetDay() { return day; }
		Int_t GetTime() { return time; }
		Double_t GetTemp() { return temp; }
		char GetQCode() { return qCode; }
	};

ClassImp(MyEvent)

MyEvent::MyEvent():
TObject(),
	year(-1),
	month(-1),
	day(-1),
	time(-1),
	temp(-1000),
	qCode('1')
{

// default constructor

};




/*
class MyTrack : public TObject {
	public:
	
		Double_t fPhi;
		MyTrack();
		
		ClassDef(MyTrack, 1);
		
		void SetfPhi(Double_t newfPhi) {
			
			fPhi = newfPhi;
			
		}
		
		Double_t GetfPhi() {
			
			return fPhi;
			
		}
};

ClassImp(MyTrack)

MyTrack::MyTrack():
TObject(),
	fPhi(-1)
{
	// Constructor
};
*/
