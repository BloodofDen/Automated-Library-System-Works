#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
#include<conio.h>
#include<ctime>
#include<direct.h>
#include<Windows.h>

using namespace std;

#include"md5.h"
#include"Entrance.h"
#include "Users_Functions.h"
#include "Admins_Functions.h"

class Label
{
public:
	static void _tag()
	{
		system("cls");
		cout << "\t\t<< ИП КНИЖНЫЙ ЧЕРВЬ >>" << endl;

		time_t presentTime = time(NULL);

		struct tm * timeInfo = localtime(&presentTime);
		cout << "Текущая дата/время: ";
		if (timeInfo->tm_mday / 10 < 1) cout << '0';
		cout << timeInfo->tm_mday << '.';
		if (timeInfo->tm_mon / 10 < 1) cout << '0';
		cout << timeInfo->tm_mon;
		switch (timeInfo->tm_wday)
		{
		case 0: cout << " |Воскресенье| "; break;
		case 1: cout << " |Понедельник| "; break;
		case 2: cout << " |Вторник| ";     break;
		case 3: cout << " |Среда| ";       break;
		case 4: cout << " |Четверг| ";     break;
		case 5: cout << " |Пятница| ";     break;
		case 6: cout << " |Суббота| ";     break;
		}
		if (timeInfo->tm_hour / 10 < 1) cout << '0';
		cout << timeInfo->tm_hour << ':';
		if (timeInfo->tm_min / 10 < 1) cout << '0';
		cout << timeInfo->tm_min << ':';
		if (timeInfo->tm_sec / 10 < 1) cout << '0';
		cout << timeInfo->tm_sec << endl << endl;
	}
};