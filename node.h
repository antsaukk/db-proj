#pragma once

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation {
	Or,
	And
};

class Node {
public:
	virtual bool Evaluate(const Date& date, const std::string& event) = 0;
};

class EmptyNode : public Node {
public: 
	bool Evaluate(const Date& date, const std::string& event);
};

class DateComparisonNode : public Node {
public: 
	DateComparisonNode(const Comparison& cmp, const Date& date) : 
	_cmp(cmp),
	_date(date) 
	{}

	bool Evaluate(const Date& date, const std::string& event);

private:
	Comparison _cmp;
	Date _date; 
};

class EventComparisonNode : public Node {
public: 
	EventComparisonNode(const Comparison& cmp, const std::string& name) : 
	_cmp(cmp),
	_name(name)
	{}

	bool Evaluate(const Date& date, const std::string& event);
	bool compareEvents(const std::string& str);
private: 
	Comparison _cmp; 
	const std::string _name;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation& op, 
						const std::shared_ptr<Node>& n1, 
						const std::shared_ptr<Node>& n2) : 
	_op(op), 
	_n1(n1),
	_n2(n2)
	{}
	bool Evaluate(const Date& date, const std::string& event);
private: 
	LogicalOperation _op;
	std::shared_ptr<Node> _n1;
	std::shared_ptr<Node> _n2;
};