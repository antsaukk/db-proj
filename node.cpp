#include "node.h"

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
	if (str.length() != _name.length()) return false;
	bool r = (str[0] == _name[0]);
	for(size_t i = 1; i < str.length(); i++) {
		r &= (str[i] == _name[i]);
	}
	return r;
}

bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) {
	bool result = true; 
	switch(_cmp) { 
		case Comparison::Equal:
			result = compareEvents(event);
			break; 
		case Comparison::NotEqual:
			result = !compareEvents(event);
			break; 
		case Comparison::Less:
			result = (event < _name);
			break;
		case Comparison::LessOrEqual:
			result = (event <= _name);
			break;
		case Comparison::Greater:
			result = (event > _name);
			break;
		case Comparison::GreaterOrEqual:
			result = (event >= _name);
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