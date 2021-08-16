#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <iterator>

class Database {
public:
	void Add(const Date& d, const std::string& e); //???

	std::ostream& Print(std::ostream& os); //???

	template <typename T>
	std::vector<std::string> FindIf(T pred) {
		int counter = 0;
		std::vector<std::string> res;
		for (auto& [date, events]: db_order){
			for (auto& e : events) {
				if (pred(date, e)) {
					res.push_back(date/*get string*/ + " " + e);
					counter+=1;
					//print? 
				}
			}
		}
		std::cout << "Found " << counter << " entries" << std::endl;
		return res;
	}

	template <typename T>
	int RemoveIf(T pred) {
		int counter = 0;
		//if predicate is empty - remove everything from database.h
		if (pred.empty()) { //empty is not implemented
			count = db_balance.size(); 
			db_balance.clear();
			db_order.clear();
		} else {
			for(auto& [date, events] : db_order) {
				for(auto& e : events) {
					 
				}
			}
		}
	}

	std::string Last(const Date& d); 

private:
	std::map<Date, std::set<std::string>> db_balance;
	std::map<Date, std::vector<std::string>> db_order;
}; 


//.cpp 

#include "database.h" 

void Database::Add(const Date& d, const std::string& e){
	if (db_balance[d].insert(e).second) db_order[d].push_back(e); 
}

std::ostream& Database::Print(std::ostream& os){ //printing format? 
	for(const auto& d : db_order) {
		for (const auto& e : d.second) {
			os << d.first/*get string*/ << " " << e << std::endl;
		}
	}
	return os;
}

std::string Last(const Date& d){
	std::string message;
	auto date_iterator = db_order.upper_bound(d); 
	if (date_iterator != db_order.begin()) {
		std::prev(date_iterator);
		message = date_iterator->first/*get string*/ 
		+ " " + date_iterator->second[date_iterator->second.size() - 1];
	} else {
		message = "No entries";
	}
	return message;
}