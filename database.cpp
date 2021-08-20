#include "database.h"
#include "date.h"

void Database::Add(const Date& d, const std::string& e){
	if (db_balance[d].insert(e).second) { db_order[d].push_back(e); }
	assert(db_order.size() == db_balance.size());
}

std::ostream& Database::Print(std::ostream& os){
	for(const auto& [date, events] : db_order) {
		for (const auto& ev : events) {
			os << date << " " << ev << std::endl;
		}
	}
	return os;
}

std::string Last(const Date& d){
	std::string message = "";
	/*auto date_iterator = db_order.upper_bound(d); 
	if (date_iterator != db_order.begin()) {
		std::prev(date_iterator);
		//message = date_iterator->first//get string 
		//+ " " + date_iterator->second[date_iterator->second.size() - 1];
	} else {
		message = "No entries";
	}*/
	return message;
}