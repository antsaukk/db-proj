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

	std::ostream& Print(std::ostream& os) const;

	template <typename T>
	std::vector<std::string> FindIf(T predicate) const{
		int counter = 0;
		std::vector<std::string> result;
		for (auto& [date, events]: db_order){
			for (auto& e : events) {
				if (predicate(date, e)) {
					result.push_back(date.getDate() + " " + e);
					counter++;
				}
			}
		}
		return result;
	}

	template <typename T>
	int RemoveIf(T predicate) {
		int counter = 0;
		std::vector<Date> empty_keys;

		for(auto& [date, events] : db_order) {
			auto pred = [predicate, date=date](const std::string& event) {
        		return !predicate(date,event);
      		};
			auto elements_to_delete = std::stable_partition(events.begin(), events.end(), pred);
			counter += events.end() - elements_to_delete;
			for(auto it = elements_to_delete; it != events.end(); it++) {
				db_balance.at(date).erase(*it);
			}
			events.erase(elements_to_delete, events.end());
			if (events.empty()) {
				empty_keys.push_back(date); 
			}
		}

		for(auto& date : empty_keys) {
			db_balance.erase(date); 
			db_order.erase(date);
		}

		assert(db_order.size() == db_balance.size());

		return counter;
	}

	std::string Last(const Date& d) const; 

private:
	std::map<Date, std::set<std::string>> db_balance;
	std::map<Date, std::vector<std::string>> db_order;
};