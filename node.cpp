#include "node.h"

#include <stdexcept>

bool EmptyNode::Evaluate(const Date& date, const std::string& event) {
	return true; 
}

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

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) {
	bool result = true; 
	switch(_cmp) {
		case Comparison::Less:
			//resuls = Less(date, _date); 
			result = (date < _date); 
			break;
		case Comparison::LessOrEqual: 
			//result = Less(date, _date) || Equal(date, _date);
			result = (date <_date) || (date == _date);
			break;
		case Comparison::Greater:
			//result = Greater(date, _date);
			result = (date > _date);
			break; 
		case Comparison::GreaterOrEqual:
			//result = Greater(date, _date) || Equal(date, _date);
			result = (date > _date) || (date == date);
			break;
		case Comparison::Equal: 
			//result = Equal(date, _date);
			result = (date == _date);
			break; 
		case Comparison::NotEqual:
			//result = !Equal(date, _date);
			result = !(date == _date);
			break;
		default: 
			throw std::logic_error("Not valid comparison operator");
	}
	return result; 
}

bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) {
	bool result = true; 
	switch(_cmp) {
		case Comparison::Equal:
			result = (event == _name); 
			break; 
		case Comparison::NotEqual:
			result = (event != _name);
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