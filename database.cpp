#include "database.h"
#include "date.h"

void Database::Add(const Date& d, const std::string& e){
	bool t = db_balance[d].insert(e).second;
	std::cout << t << std::endl;
	if (t) db_order[d].push_back(e); 
	std::cout << db_order.size() << " " << db_balance.size() << std::endl;
}

std::ostream& Database::Print(std::ostream& os){ //printing format? 
	for(const auto& d : db_order) {
		for (const auto& e : d.second) {
			os << d.first << " " << e << std::endl;
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