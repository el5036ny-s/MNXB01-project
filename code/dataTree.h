
#include <TObject.h>

class MyClass : public TObject {
	private:
	
		Int_t year;
		Int_t month;
		Int_t day;
		
		Int_t time;
		
		Double_t temp;
		
		Int_t qCode;
	
	public:
		
		MyClass();

		ClassDef(MyClass, 6); // Help class	
		
	
		void SetDate(Int_t newYear, Int_t newMonth, Int_t newDay) {
			year = newYear;
			month = newMonth;
			day = newDay;
		
		}
		void SetTime(Int_t newTime) {
			time = newTime;
		}
		void SetTemp(Double_t newTemp) {
			temp = newTemp;
		}
		void SetQCode(Int_t newQCode) { // 1 = G (OK), 0 = Y (Suspicious)
			qCode = newQCode;
		}
		
		Int_t GetYear() { return year; }
		Int_t GetMonth() { return month; }
		Int_t GetDay() { return day; }
		Int_t GetTime() { return time; }
		Double_t GetTemp() { return temp; }
		Int_t GetQCode() { return qCode; }
	};

ClassImp(MyClass)

MyClass::MyClass():
TObject(),
	year(-1),
	month(-1),
	day(-1),
	time(-1),
	temp(-1000),
	qCode(-1)
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
