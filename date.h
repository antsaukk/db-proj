#pragma once

#include <string>
#include <iostream>
#include <sstream>

//.h

class Date {
public: 
	Date(std::string &year, std::string &month, std::string &day) :
	_year(year), _month(month), _day(day) {}

	std::string getYear() const { return _year; }
	std::string getMonth() const { return _month; }
	std::string getDay() const { return _day; }

	std::string getDate();

private:
	std::string _year;
	std::string _month;
	std::string _day;
};


