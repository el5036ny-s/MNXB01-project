
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

		ClassDef(MyClass, 7); // Help class	
		
		Int_t GetDayOfYear() {
			if(month == '\0' | day == '\0') { return -1; } // If date not set, return -1
			
			Int_t N = (month - 1)*30;
			N += day;
			
			// Take into account the different number of days in each month
			if(month == 1 | month == 3){ return N; }
			if(month == 2 | month == 4 | month == 5) { return N + 1; }
			if(month == 6 | month == 7){ return N + 2; }
			if(month == 8){ return N + 3; }
			if(month == 9 | month == 10){ return N + 4; }
			
			return N + 5;
		}
	
	
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

