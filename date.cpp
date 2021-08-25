#include "date.h"

std::string zeroComplement(std::string& str){
	return '0' + str;
}

std::string Date::getDate() const {
	std::string year = std::to_string(getYear()); 
	std::string month = std::to_string(getMonth()); 
	std::string day = std::to_string(getDay()); 

	if (year.length() < 4) {
		unsigned int r = 4 - year.length();
		for (size_t i = 0; i < r; i++) {
			year = zeroComplement(year);
		}
	}	
	if (month.length() != 2) {
		month = zeroComplement(month);
	}
	if (day.length() != 2) {
		day = zeroComplement(day);
	}

	return (year + '-' + month + '-' + day);
}

bool operator<(const Date& d1, const Date& d2) {
	int day1 = d1.getDay(); 
	int day2 = d2.getDay();

	int month1 = d1.getMonth(); 
	int month2 = d2.getMonth();

	int year1 = d1.getYear(); 
	int year2 = d2.getYear();

	if (year1 < year2) { return true; }
	else if (year1 == year2) {
		if (month1 < month2) { return true; }
		else if(month1 == month2) {
			if (day1 < day2) { return true; }
			else { return false; }
		} else { return false; }
	} else { return false; }
}

bool operator==(const Date& d1, const Date& d2) {
	return (!(d1 < d2) && !(d2 < d1));
}

bool operator>(const Date& d1, const Date& d2) {
	return (!(d1 < d2) && !(d1 == d2));
}

std::ostream& operator<<(std::ostream& out, const Date &date) {
	out << date.getDate();
	return out;
}

Date ParseDate(std::istream& is) {
  std::string d;
  is >> d;
  std::replace(d.begin(), d.end(), '-', ' ');

  std::stringstream ss(d);
  std::vector<std::string> date(3);

  for (size_t i = 0; i < 3; i++) {
    ss >> date[i];
  }

  Date D(std::stoi(date[0]), std::stoi(date[1]), std::stoi(date[2]));

  return D;
}
