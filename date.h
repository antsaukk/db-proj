#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

class Date {
public: 
	Date(int year, int month, int day) :
	_year(year), _month(month), _day(day) {}

	int getYear() const { return _year; }
	int getMonth() const { return _month; }
	int getDay() const { return _day; }

	std::string getDate() const;

private:
	int _year;
	int _month;
	int _day;
};


