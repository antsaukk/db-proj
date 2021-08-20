#include "date.h"

#include "node.cpp"

#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>


using namespace std; 

string ParseEvent(istream& is){

	string e; 
	vector<string> event_tokenz;

	while (is >> e) {event_tokenz.push_back(e);}

	//is >> e;

	/*for(size_t i = 0; i < event_tokenz.size(); i++) {
		cout << event_tokenz[i] << " ";
	}*/

	const char* const delim = " ";

	ostringstream imploded;
	copy(event_tokenz.begin(), event_tokenz.end(), ostream_iterator<string>(imploded, delim));

	return imploded.str();

	//cout << imploded.str() << imploded.str().length() << endl;;
	//cout << is.str() << endl;
	/*string e; 
	getline(is, e, {});
	cout << e << endl;*/ 
};


Date ParseDate(istream& is){

	string d;

	is >> d;

	replace(d.begin(), d.end(), '-', ' ');

	//cout << d << endl;

	stringstream ss(d); 

	vector<string> date(3);

	for (size_t i = 0; i < 3; i++) {
		ss >> date[i]; 
		//cout << date[i] << endl;
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

	out << year << '-' << month << '-' << day;

	return out;
}


int main() {

	string y = "2017"; 
	string m = "07"; 
	string dd = "08";

	string y1 = "2017";
	string m1 = "06";
	string dd1 = "01";

	map<Date, set<string>> db_balance;
	map<Date, vector<string>> db_order;

	for (string line; getline(cin, line); ) {
    	istringstream is(line);

   		string command;
    	is >> command;
    	if (command == "Add") {
    		//cout << command << endl; 
    		//cout << is.str() << endl; 

    		auto D = ParseDate(is);
    		auto E = ParseEvent(is);

    		cout << E << endl;

			//bool t = db_balance[D].insert(E).second;

			if (!db_balance.count(D)) {
				cout << "DOES NOT EXIST\n";
				if (db_balance[D].insert(E).second) { db_order[D].push_back(E); }	
			} else {
				cout << "EXIST\n";
				if (db_balance.at(D).insert(E).second) { db_order.at(D).push_back(E); } 
			}

			cout << "\nprinting balanced collection: " << endl;
			for (auto& [date, event]: db_balance) {
				cout << date << " ";
				for(auto it = event.begin(); it != event.end(); it++) {
					cout << *it << endl;
				}
			}
			cout << "\nprinting ordered collection: " << endl;
			for (auto& [date, event]: db_order) {
				cout << date << " "; 
				for(auto it = event.begin(); it != event.end(); it++) {
					cout << *it << endl;
				}
			}

			
    		/*Date d1(y, m, dd);
    		Date d2(y, m, dd);

    		cout << (d1 == d2) << endl;
    		cout << (d1 < d2) << endl;
    		cout << (d1 > d2) << endl;
    		cout << "---" << endl;

    		Date d3(y1, m1, dd1);

    		cout << (d1 == d3) << endl;
    		cout << (d1 < d3) << endl;
    		cout << (d1 > d3) << endl;
    		cout << "---" << endl;

    		cout << (d2 == d3) << endl;
    		cout << (d2 < d3) << endl;
    		cout << (d2 > d3) << endl;
    		cout << "---" << endl;

    		cout << (d3 == d3) << endl;
    		cout << (d3 < d3) << endl;
    		cout << (d3 > d3) << endl;
    		cout << "---" << endl;

    		cout << (d2 == d2) << endl;
    		cout << (d2 < d2) << endl;
    		cout << (d2 > d2) << endl;
    		cout << "---" << endl;

    		cout << (d1 == d1) << endl;
    		cout << (d1 < d1) << endl;
    		cout << (d1 > d1) << endl;
    		cout << "---" << endl;

    		ParseEvent(is);*/
    	}
	}

	return 0;
}