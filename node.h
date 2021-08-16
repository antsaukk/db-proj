#include <vector>

//Node, EmptyNode, DateComparisonNode, EventComparisonNode и LogicalOperationNode

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
	virtual bool Evaluate(const Date& date, const std::string& event);
}

class EmptyNode : public Node {
public: 
	bool Evaluate(const Date& date, const std::string& event);
}

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
}

class EventComparisonNode : public Node {
public: 
	EventComparisonNode(const Comparison& cmp, const std::string& name) : 
	_cmp(cmp),
	_name(name)
	{}

	bool Evaluate(const Date& date, const std::string& event);
private: 
	Comparison _cmp; 
	std::string _name;
}

class LogicalOperationNode : public Node {
public: 
	bool Evaluate(const Date& date, const std::string& event);
}

