#pragma once


#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <iterator>

class Database {
public:
	void Add(const Date& d, const std::string& e);

	std::ostream& Print(std::ostream& os); //???

	template <typename T>
	std::vector<std::string> FindIf(T pred) {
		int counter = 0;
		std::vector<std::string> res;
		for (auto& [date, events]: db_order){
			for (auto& e : events) {
				if (pred(date, e)) {
					res.push_back(date.getDate() + " " + e);
					counter+=1;
					//print? 
				}
			}
		}
		std::cout << "Found " << counter << " entries" << std::endl;
		return res;
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