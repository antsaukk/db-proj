#include "date.h"

std::string Date::getDate() const {
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

  Date D(date[0], date[1], date[2]);

  std::cout << "we parsed the date: " << "'" << D.getYear() << "'"
  << "'" << D.getMonth() << "'" << "'" << D.getDay() << "'" << std::endl;

  return D;
}
