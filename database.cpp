#include "database.h"

void Database::Add(const Date& d, const std::string& e){
	if (db_balance[d].insert(e).second) { db_order[d].push_back(e); }
	assert(db_order.size() == db_balance.size());
}

std::ostream& Database::Print(std::ostream& os) const{
	for(const auto& [date, events] : db_order) {
		for (const auto& ev : events) {
			os << date << " " << ev << std::endl;
		}
	}
	return os;
}

std::string Database::Last(const Date& date) const{ 
	constexpr int step = 1;
	std::string message = "";
	auto date_iterator = db_order.upper_bound(date); 
	if (date_iterator != db_order.begin()) {
		auto pv_date_it = std::prev(date_iterator, step);
		message = pv_date_it->first.getDate() + " " + pv_date_it->second.back();
	} else {
		message = "No entries";
	}
	return message;
}