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

  Date D(std::stoi(date[0]), std::stoi(date[1]), std::stoi(date[2]));

  return D;
}
