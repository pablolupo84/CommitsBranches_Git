#include <ctime>
#include <iostream>
#include "DateTime.h"
#include "Context.h"
#include "User.h"

unsigned int MAXUSERRANDOM = 5;
unsigned long ADDTOTIMEINSECONDS =185;
using UUser::User;

unsigned int InitRamdom();
UUser::User* CreateRandomUserUnique();
unsigned long ConvertTimeToLong();
UDateTime::DateTime* ConvertLongToTime(unsigned long timeLong );
UDateTime::DateTime* SimulateTimeNow(unsigned long addToTimeInSeconds);

unsigned int seedsRamdom=InitRamdom();
//UUser::User* uniqueInstance= CreateRandomUserUnique();
UUser::User* uniqueInstance= UContext::GetCurrentUser();

UDateTime::DateTime* timeNow= UDateTime::Now();

UUser::User* UContext::GetCurrentUser(){
	return CreateRandomUserUnique();
}

UDateTime::DateTime* UContext::GetNow(){
	return SimulateTimeNow(ADDTOTIMEINSECONDS);
}

void UContext::DestroyContext(){
	if(uniqueInstance!=NULL){
		UUser::DestroyUser(uniqueInstance);
		uniqueInstance=NULL;
	}
}

unsigned int InitRamdom(){
	srand(time(NULL));
	return rand();
}

UUser::User* CreateRandomUserUnique(){
	string userRandomNickName[MAXUSERRANDOM]={"@srcoco","@domeric","@pepelui","@diegote","@lobolupo"};
	return UUser::CreateUser(userRandomNickName[rand() % (MAXUSERRANDOM)]);;
}

UDateTime::DateTime* SimulateTimeNow(unsigned long addToTimeInSeconds){
	unsigned long timeToLong = ConvertTimeToLong();
	return timeNow=ConvertLongToTime(timeToLong+addToTimeInSeconds);
}

unsigned long ConvertTimeToLong(){
	unsigned long timeToLong=UDateTime::GetYear(timeNow)/100;
	timeToLong= timeToLong*12+(UDateTime::GetMonth(timeNow)-1);
	timeToLong= timeToLong*31+(UDateTime::GetDay(timeNow)-1);
	timeToLong= timeToLong*24+(UDateTime::GetHour(timeNow));
	timeToLong= timeToLong*60+(UDateTime::GetMinutes(timeNow));
	timeToLong= timeToLong*60+(UDateTime::GetSeconds(timeNow));
	return timeToLong;
}

UDateTime::DateTime* ConvertLongToTime(unsigned long timeLong ){
	UDateTime::DateTime* timeNow;
	unsigned int seg = timeLong%60; timeLong/=60;
	unsigned int min = timeLong%60; timeLong/=60;
	unsigned int hor = timeLong%24; timeLong/=24;
	unsigned int dia = (timeLong%31 + 1); timeLong/=31;
	unsigned int mes = (timeLong%12 + 1); timeLong/=12;
	unsigned int anio = timeLong+2000;
	timeNow=UDateTime::CreateDateTime(anio,mes,dia,hor,min,seg);
	return timeNow;
}
