#include "node.h"

bool operator<(const Date& d1, const Date& d2) {
	int day1 = std::stoi(d1.getDay()); 
	int day2 = std::stoi(d2.getDay());

	int month1 = std::stoi(d1.getMonth()); 
	int month2 = std::stoi(d2.getMonth()); 

	int year1 = std::stoi(d1.getYear()); 
	int year2 = std::stoi(d2.getYear());

	bool res = true; 

	if (year1 < year2) { res = true; }
	else if (year1 == year2) {
		if (month1 < month2) { res = true; }
		else if(month1 == month2) {
			if (day1 < day2) { res = true; }
			else { res = false; }
		} else { res = false; }
	} else { res = false; }

	return res; 
}

bool operator==(const Date& d1, const Date& d2) {
	return (!(d1 < d2) && !(d2 < d1));
}

bool operator>(const Date& d1, const Date& d2) {
	return (!(d1 < d2) && !(d1 == d2));
}

bool EmptyNode::Evaluate(const Date& date, const std::string& event) {
	return true; 
}

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) {
	bool result = true; 
	switch(_cmp) {
		case Comparison::Less:
			result = (date < _date); 
			break;
		case Comparison::LessOrEqual: 
			result = (date < _date) || (date == _date);
			break;
		case Comparison::Greater:
			result = (date > _date);
			break; 
		case Comparison::GreaterOrEqual:
			result = (date > _date) || (date == _date);
			break;
		case Comparison::Equal: 
			result = (date == _date);
			break; 
		case Comparison::NotEqual:
			result = !(date == _date);
			break;
		default: 
			throw std::logic_error("Not valid comparison operator");
	}
	return result; 
}

bool EventComparisonNode::compareEvents(const std::string& str) {
	/*std::cout << str << " " << _name << " " << _name.compare(str) << std::endl;
	if (!str.compare(_name)) return true;
	else return false;*/
	std::cout << (str.length() == _name.length()) << str.length() << " " << _name.length() << std::endl;
	std::cout << "'";
	for(size_t i = 0; i < str.length(); i++) {
		std::cout << str[i]; 
	}
	std::cout << "'";
	if (str.length() != _name.length()) return false; 
	bool r = (str[0] == _name[0]);
	std::cout << r;
	for(size_t i = 1; i < str.length(); i++) {
		r &= (str[i] == _name[i]);
		std::cout << r; 
	}
	return r;
}

bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) {
	bool result = true; 
	/*std::string n = "Holiday"; 
	std::string t = "Holiday";
	std::cout << !n.compare(t) << " ";*/
	switch(_cmp) { 
		case Comparison::Equal: 
			result = compareEvents(event);

			std::cout << "EQ " << event << " " << _name << " " << result << std::endl;

			break; 
		case Comparison::NotEqual:
			result = !compareEvents(event); 
			std::cout << "NOT " << event << " " << _name << " " << result << std::endl;

			break; 
		default: 
			throw std::logic_error("Not valid comparison operator");
	}
	return result;
}

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event){
	bool result = true; 
	switch(_op) {
		case LogicalOperation::Or: 
			result = _n1->Evaluate(date, event) || _n2->Evaluate(date, event);
			break; 
		case LogicalOperation::And:
			result = _n1->Evaluate(date, event) && _n2->Evaluate(date, event);
			break; 
		default: 
			throw std::logic_error("Not valid comparison operator");
	}
	return result;
}