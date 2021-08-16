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

private:
	std::string _year;
	std::string _month;
	std::string _day;
};

//.cpp

/*std::ostream& operator<<(std::ostream& out, const Date &date) {
	string year = date.getYear(); 
	string month = date.getMonth(); 
	string day = date.getDay(); 

	if (year.length() < 4) {
		int r = 4 - year.length();
		year = '0' * r + year; 
	}
	if (month.length() != 2) {
		month = '0' + month;
	}
	if (day.length() != 2) {
		day = '0' + day;
	}

	out << day << '-' << month << '-' << year << endl;

	return out;
}*/

std::ostream& operator<<(std::ostream& out, const Date &date) {
	std::string year = date.getYear(); 
	std::string month = date.getMonth(); 
	std::string day = date.getDay(); 

	if (year.length() < 4) {
		unsigned int r = 4 - year.length();
		for (size_t i = 0; i < r; i++) {
			year = '0' + year; 
		}
	}	
	if (month.length() != 2) {
		month = '0' + month;
	}
	if (day.length() != 2) {
		day = '0' + day;
	}

	out << year << '-' << month << '-' << day << std::endl;

	return out;
}