#pragma once
 
#include <string>
#include <memory>
 
#include "date.h"
 
enum class LogicalOperation {
    Or, And
};
 
enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};
 
class Node {
public:
    virtual bool Evaluate(const Date& date, const string& event);
};
 
class EmptyNode : public Node {
public:
    bool Evaluate(const Date& date, const string& event) const;
};
 
class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& cmp, const Date& main_date)
    : cmp_(cmp), main_date_(main_date) {}
    bool Evaluate(const Date& date, const string& event) const;
private:
    const Comparison cmp_;
    const Date main_date_;
};
 
class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cmp, const string& main_event)
    : cmp_(cmp), main_event_(main_event) {}
    bool Evaluate(const Date& date, const string& event) const;
private:
    const Comparison cmp_;
    const string main_event_;
};
 
class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation logical_operation,
                         const shared_ptr<Node>& node1, const shared_ptr<Node>& node2)
            : logical_operation_(logical_operation), node1_(node1), node2_(node2) {}
    bool Evaluate(const Date& date, const string& event) const;
private:
    LogicalOperation logical_operation_;
    const shared_ptr<Node> node1_;
    const shared_ptr<Node> node2_;
};

// .cpp 

#include "node.h"
#include "condition_parser.h"
#include "date.h"
 
#include <stdexcept>
 
using namespace std;
 
//virtual bool Node::Evaluate(const Date& date, const string& event);
 
bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    return true;
}
 
bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
    if (cmp_ == Comparison::Less) {
        return (date.Year() < main_date_.Year() && date.Month() < main_date_.Month() &&
                date.Day() < main_date_.Day());
    }
    if (cmp_ == Comparison::LessOrEqual) {
        return (date.Year() <= main_date_.Year() && date.Month() <= main_date_.Month() &&
                date.Day() <= main_date_.Day());
    }
    if (cmp_ == Comparison::Greater) {
        return (date.Year() > main_date_.Year() && date.Month() > main_date_.Month() &&
                date.Day() > main_date_.Day());
    }
    if (cmp_ == Comparison::GreaterOrEqual) {
        return (date.Year() >= main_date_.Year() && date.Month() >= main_date_.Month() &&
                date.Day() >= main_date_.Day());
    }
    if (cmp_ == Comparison::Equal) {
        return (date == main_date_);
    }
    if (cmp_ == Comparison::NotEqual) {
        return (date != main_date_);
    }
    throw invalid_argument("Surprise");
}
 
bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
    if (cmp_ == Comparison::Equal) return event == main_event_;
    if (cmp_ == Comparison::NotEqual) return event != main_event_;
    throw invalid_argument("Surprise");
}
 
bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    if (logical_operation_ == LogicalOperation::And)
        return node1_->Evaluate(date, event) && node2_->Evaluate(date, event);
    else return node1_->Evaluate(date, event) || node2_->Evaluate(date, event);
}