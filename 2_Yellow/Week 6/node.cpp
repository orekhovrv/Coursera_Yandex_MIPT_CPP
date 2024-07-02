#include "node.h"

using namespace std;


template <typename T>
bool Compare(const T& lhs, const T& rhs, Comparison comparison) {
    switch (comparison) {
        case Comparison::Less:
            return lhs < rhs;
        case Comparison::LessOrEqual:
            return lhs <= rhs;
        case Comparison::Equal:
            return lhs == rhs;
        case Comparison::NotEqual:
            return lhs != rhs;
        case Comparison::Greater:
            return lhs > rhs;
        case Comparison::GreaterOrEqual:
            return lhs >= rhs;
    }
    return false;
}



bool EmptyNode::Evaluate(const Date& date, const Event& event) {
    return true;
}


DateComparisonNode::DateComparisonNode(const Comparison& comparison, const Date& date)
        : ComparisonNode(comparison, date) {
}

bool DateComparisonNode::Evaluate(const Date& date, const Event& event) {
    return Compare(date, _value, _comparison);
}


EventComparisonNode::EventComparisonNode(const Comparison& comparison, const Event& value)
        : ComparisonNode(comparison, value) {
}

bool EventComparisonNode::Evaluate(const Date& date, const Event& event) {
    return Compare(event.value, _value.value, _comparison);
}


LogicalOperationNode::LogicalOperationNode(
        const LogicalOperation& logical_operation,
        const std::shared_ptr<Node>& left,
        const std::shared_ptr<Node>& right
) : _operation(logical_operation), _left(left), _right(right) {
}

bool LogicalOperationNode::Evaluate(const Date& date, const Event& event) {
    switch (_operation) {
        case LogicalOperation::And:
            return _left->Evaluate(date, event) && _right->Evaluate(date, event);
        case LogicalOperation::Or:
            return _left->Evaluate(date, event) || _right->Evaluate(date, event);
    }
    return false;
}
