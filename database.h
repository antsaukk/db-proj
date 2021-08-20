#pragma once

#include "date.h"

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <iterator>
#include <assert.h>

class Database {
public:
	void Add(const Date& d, const std::string& e);

	std::ostream& Print(std::ostream& os); //???

	template <typename T>
	std::vector<std::string> FindIf(T pred) { //Find date condition seems to work, but not with event
		int counter = 0;
		std::vector<std::string> result;
		for (auto& [date, events]: db_order){
			for (auto& e : events) {
				auto B = pred(date, e);
				std::cout << B << std::endl;
				if (B) {
					result.push_back(date.getDate() + " " + e);
					counter+=1;
					//print? 
				}
			}
		}
		//std::cout << "Found " << counter << " entries" << std::endl;
		return result;
	}

	/*template <typename T>
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
	}*/

	std::string Last(const Date& d); 

private:
	std::map<Date, std::set<std::string>> db_balance;
	std::map<Date, std::vector<std::string>> db_order;
};