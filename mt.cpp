#include "date.h"
#include "token.cpp"

#include <iostream>
#include <sstream>
#include <algorithm>


using namespace std; 

void ParseEvent(istream& is){

	string e;

	is >> e;

	cout << e << endl;

};


Date ParseDate(istream& is){

	string d;

	is >> d;

	replace(d.begin(), d.end(), '-', ' ');

	cout << d << endl;

	stringstream ss(d); 

	vector<string> date(3);

	for (size_t i = 0; i < 3; i++) {
		ss >> date[i]; 
		cout << date[i] << endl;
	}

	Date D(date[0], date[1], date[2]);

    return D;
};

ostream& operator<<(ostream& out, const Date &date) {
	string year = date.getYear(); 
	string month = date.getMonth(); 
	string day = date.getDay(); 

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

	out << year << '-' << month << '-' << day << endl;

	return out;
}


int main() {

	for (string line; getline(cin, line); ) {
    	istringstream is(line);

   		string command;
    	is >> command;
    	if (command == "Add") {
    		cout << command << endl; 
    		cout << is.str() << endl; 

    		auto D = ParseDate(is);

    		cout << "test :" << endl; 
			/*cout << D.getYear() << endl;
			cout << D.getMonth() << endl;
			cout << D.getDay() << endl;*/ 

    		cout << D;

			cout << "done" << endl;

    		//ParseEvent(is);
    	}
	}
	return 0;
}