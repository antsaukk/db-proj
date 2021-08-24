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

std::string zeroComplement(std::string& str);

bool operator<(const Date& d1, const Date& d2); 
bool operator==(const Date& d1, const Date& d2); 
bool operator>(const Date& d1, const Date& d2);

std::ostream& operator<<(std::ostream& out, const Date &date);

Date ParseDate(std::istream& is);

