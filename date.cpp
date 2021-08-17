#include "date.h"

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

std::string Date::getDate() {
	std::string year = getYear(); 
	std::string month = getMonth(); 
	std::string day = getDay(); 

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

	std::string build = (year + '-' + month + '-' + day);

	return build;
}


std::ostream& operator<<(std::ostream& out, const Date &date) {
	/*std::string year = date.getYear(); 
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
	}*/

	//out << year << '-' << month << '-' << day << std::endl;

	out << date.getDate() << std::endl;

	return out;
}
