#pragma once

#include <memory>

#include "date.h"
#include "event.h"

enum class LogicalOperation {
    And,
    Or
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
    virtual bool Evaluate(const Date& date, const Event& event) = 0;
};


class EmptyNode: public Node {
public:
    bool Evaluate(const Date& date, const Event& event) override;
};

template<class ValueType>
class ComparisonNode: public Node {
public:

    ComparisonNode(const Comparison& comparison, const ValueType& value)
            : _comparison(comparison), _value(value) {
    }

    bool Evaluate(const Date& date, const Event& event) override = 0;


protected:
    const Comparison _comparison;
    const ValueType _value;
};


class DateComparisonNode: public ComparisonNode<Date> {
public:
    DateComparisonNode(const Comparison& comparison, const Date& date);

    bool Evaluate(const Date& date, const Event& event) override;
};



class EventComparisonNode: public ComparisonNode<Event> {
public:
    EventComparisonNode(const Comparison& comparison, const Event& date);

    bool Evaluate(const Date& date, const Event& event) override;
};


class LogicalOperationNode: public Node {
public:
    LogicalOperationNode(
            const LogicalOperation& logical_operation,
            const std::shared_ptr<Node>& left,
            const std::shared_ptr<Node>& right
    );

    bool Evaluate(const Date& date, const Event& event) override;

private:
    const LogicalOperation _operation;
    const std::shared_ptr<Node> _left, _right;
};
