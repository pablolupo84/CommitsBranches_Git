#include <sstream>
#include <ctime>

#include "DateTime.h"

using std::string;
using std::endl;

using UDateTime::DateTime;
using UDateTime::DateTimeFormat;

void SetTimeNow(DateTime* dateTime);
string FormatToFormatMsg(const DateTime* dateTime,const char* toFormatMsg);
string ConvertCharToString(char* cadena);

bool IsDate(unsigned int year,unsigned int month,unsigned int day);
bool IsTime(unsigned int hour,unsigned int minutes,unsigned int second);
bool IsLeapYear(unsigned int year);

struct UDateTime::DateTime{
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minutes;
	unsigned int seconds;
};

UDateTime::DateTime* UDateTime::Now(){
	DateTime* timeNow=new DateTime;
	SetTimeNow(timeNow);
	return timeNow;
}

UDateTime::DateTime* UDateTime::CreateDateTime(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minutes, unsigned int seconds){
	DateTime* time=NULL;
	if(IsDate(year,month,day)==IsTime(hour,minutes,seconds)){
		time=new DateTime;
		time->year=year;
		time->month=month;
		time->day=day;
		time->hour=hour;
		time->minutes=minutes;
		time->seconds=seconds;
	}
	return time;
}

unsigned int UDateTime::GetYear(const DateTime* dateTime){
	return dateTime->year;
}

unsigned int UDateTime::GetMonth(const DateTime* dateTime){
	return dateTime->month;
}

unsigned int UDateTime::GetDay(const DateTime* dateTime){
	return dateTime->day;
}

unsigned int UDateTime::GetHour(const DateTime* dateTime){
	return dateTime->hour;
}

unsigned int UDateTime::GetMinutes(const DateTime* dateTime){
	return dateTime->minutes;
}

unsigned int UDateTime::GetSeconds(const DateTime* dateTime){
	return dateTime->seconds;
}

string UDateTime::ToFormat(const DateTime* dateTime,DateTimeFormat format){
	string toFormat="";
	int horaAux;

	switch(format){
		case DateTimeFormat::YYYYMMDD_HHmmss:
										//2019-04-27 19:01:10
										toFormat=FormatToFormatMsg(dateTime,"%Y-%m-%d %H:%M:%S");
										break;

		case DateTimeFormat::YYYYMMDD_hhmmss:
										//2019-04-27 07:01:10 p.m.
										toFormat=FormatToFormatMsg(dateTime,"%Y-%m-%d %I:%M:%S %p");
										break;

		case DateTimeFormat::DDMMYYYY_hhmmss:
										//27-04-2019 07:01:10 p.m.
										toFormat=FormatToFormatMsg(dateTime,"%d-%m-%Y %I:%M:%S %p");
										break;

		case DateTimeFormat::DDMMYYYY_HHmmss:
										//27-04-2019 19:01:10
										toFormat=FormatToFormatMsg(dateTime,"%d-%m-%Y %H:%M:%S");
										break;

		case DateTimeFormat::YYYYMMDDHHmmss:
										//20190427191410
										toFormat=FormatToFormatMsg(dateTime,"%Y%m%d%H%M%S");
										break;
		case DateTimeFormat::YYMD_Hms:
										//19-4-27 19:1:10
										toFormat=FormatToFormatMsg(dateTime,"%y")+"-"+std::to_string(UDateTime::GetMonth(dateTime))+"-" + std::to_string(UDateTime::GetDay(dateTime))+" ";
										toFormat+=std::to_string(UDateTime::GetHour(dateTime))+":"+std::to_string(UDateTime::GetMinutes(dateTime))+":"+std::to_string(UDateTime::GetSeconds(dateTime));
										break;

		case DateTimeFormat::YYMD_hms:
										//19-4-27 7:1:10 p.m.
										toFormat=FormatToFormatMsg(dateTime,"%y")+"-"+ std::to_string(UDateTime::GetMonth(dateTime))+"-"+std::to_string(UDateTime::GetDay(dateTime))+" ";

										horaAux=UDateTime::GetHour(dateTime);
										horaAux<12?toFormat+=std::to_string(horaAux):toFormat+=std::to_string(horaAux-12);

										toFormat+=":"+std::to_string(UDateTime::GetMinutes(dateTime))+":"+std::to_string(UDateTime::GetSeconds(dateTime))+ " "+ FormatToFormatMsg(dateTime,"%p");;
										break;
		case DateTimeFormat::DMYY_hms:
										//27-4-19 7:1:10 p.m.
										toFormat+=std::to_string(UDateTime::GetDay(dateTime))+"-" + std::to_string(UDateTime::GetMonth(dateTime))+"-"+FormatToFormatMsg(dateTime,"%y")+" ";

										horaAux=UDateTime::GetHour(dateTime);
										horaAux<12?toFormat+=std::to_string(horaAux):toFormat+=std::to_string(horaAux-12);

										toFormat+=":"+std::to_string(UDateTime::GetMinutes(dateTime))+":"+std::to_string(UDateTime::GetSeconds(dateTime))+ " "+ FormatToFormatMsg(dateTime,"%p");
										break;

		case DateTimeFormat::DMYY_Hms:
										//27-4-19 19:1:10
										toFormat+=std::to_string(UDateTime::GetDay(dateTime))+"-" + std::to_string(UDateTime::GetMonth(dateTime))+"-"+FormatToFormatMsg(dateTime,"%y")+" ";
										toFormat+=std::to_string(UDateTime::GetHour(dateTime))+":"+std::to_string(UDateTime::GetMinutes(dateTime))+":" + std::to_string(UDateTime::GetSeconds(dateTime))+ " "+ FormatToFormatMsg(dateTime,"%p");
										break;

		default:	toFormat=FormatToFormatMsg(dateTime,"%Y-%m-%d %H:%M:%S");
					break;
	}
	return toFormat;
}

void UDateTime::DestroyDateTime(DateTime* dateTime){
	delete(dateTime);
}

// Precondicion: @dateTime es una instancia v�lida
// Postcondicion: 	Inicializa con el tiempo Actual.
void SetTimeNow(DateTime* dateTime){
	time_t timeNow=time(&timeNow);
	tm* structTime=localtime( &timeNow );

	dateTime->year=structTime->tm_year+1900;
	dateTime->month=structTime->tm_mon+1;
	dateTime->day=structTime->tm_mday;
	dateTime->hour=structTime->tm_hour;
	dateTime->minutes=structTime->tm_min;
	dateTime->seconds=structTime->tm_sec;
}

// Precondicion: Ninguna.
// Postcondicion: 	Retorna TRUE si los datos ingresados forman un horario valido ->
//					(hour<24) and (minutes<60) and (second<60). Caso contrario FALSE.
bool IsTime(unsigned int hour,unsigned int minutes,unsigned int second){
	return (hour<24) and (minutes<60) and (second<60);
}

enum MonthsOfTheYear{January=1,February,March,April,May,June,July,August,September,October,November,December};
enum DaysOfTheMonths{JanuaryDays=31,FebruaryDays=28,FebruaryLeapYear=29,MarchDays=31,AprilDays=30,MayDays=31,JuneDays=30,JulyDays=31,AugustDays=31,SeptemberDays=30,OctoberDays=31,NovemberDays=30,DecemberDays=31};

// Precondicion: Ninguna.
// Postcondicion: 	Retorna True si la fecha es valida. Caso contrario retorna false
bool IsDate(unsigned int year,unsigned int month,unsigned int day){
	bool isDateValid=false;
	switch(month){
		case January: 	isDateValid=(day>=1 && day<JanuaryDays);
						break;
		case February: 	if (IsLeapYear(year)){
							isDateValid=(day>=1 && day<FebruaryLeapYear);
						}else{
							isDateValid=(day>=1 && day<FebruaryDays);
						}
						break;
		case March: 	isDateValid=(day>=1 && day<MarchDays);
						break;
		case April: 	isDateValid=(day>=1 && day<AprilDays);
						break;
		case May: 		isDateValid=(day>=1 && day<MayDays);
						break;
		case June: 		isDateValid=(day>=1 && day<JuneDays);
						break;
		case July: 		isDateValid=(day>=1 && day<JulyDays);
						break;
		case August: 	isDateValid=(day>=1 && day<AugustDays);
						break;
		case September: isDateValid=(day>=1 && day<SeptemberDays);
						break;
		case October: 	isDateValid=(day>=1 && day<OctoberDays);
						break;
		case November: 	isDateValid=(day>=1 && day<NovemberDays);
						break;
		case December: 	isDateValid=(day>=1 && day<DecemberDays);
						break;
	}
	return isDateValid;
}

// Precondicion: Ninguna.
// Postcondicion: 	Retorna TRUE si el a�o es bisiesto. Caso contrario FALSE.
bool IsLeapYear(unsigned int year){
	return ((year %4 == 0 and year %100 != 0) or year % 400 == 0);
}

// Precondicion: @dateTime es unba instancia valida, @toFormatMsg es una cadena de formato valida
// Postcondicion: 	Da formato al tipo @datetime en el formato@toFormatMsg
string FormatToFormatMsg(const DateTime* dateTime,const char* toFormatMsg){
	string test="";
	char dateTimeToFormat[80]="";

	time_t timeNow=time(&timeNow);
	struct tm * timeinfo=localtime( &timeNow );

	timeinfo->tm_year=dateTime->year-1900;
	timeinfo->tm_mon=dateTime->month-1;
	timeinfo->tm_mday=dateTime->day;
	timeinfo->tm_hour=dateTime->hour;
	timeinfo->tm_min=dateTime->minutes;
	timeinfo->tm_sec=dateTime->seconds;

	strftime(dateTimeToFormat,80,toFormatMsg,timeinfo);
	test=ConvertCharToString(dateTimeToFormat);
	return test;
}

// Precondicion: Ninguna.
// Postcondicion: 	Conviete cadena en tipo string.
string ConvertCharToString(char* cadena){
	string miString(cadena);
    return miString;
}


