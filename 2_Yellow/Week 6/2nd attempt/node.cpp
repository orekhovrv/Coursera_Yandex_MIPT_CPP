#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <iomanip>
#include <memory>
#include "event.cpp"
#include "date.cpp"


using namespace std;

enum class Comparison {
    Less,
    Equal,
    Greater,
    GreaterOrEqual,
    LessOrEqual,
    NotEqual,
};

enum class LogicalOperation {
    Or,
    And,
};

class Node {
public:

};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation expression, shared_ptr<Node> node, shared_ptr<Node> node_ptr) {

    }
};

class EmptyNode : public Node  {
public:

};

class EventComparisonNode : public Node  {
public:
    EventComparisonNode(Comparison comparison, Event event) {

    }
};

class DateComparisonNode : public Node  {
public:
    DateComparisonNode(Comparison comparison, Date date) {

    }
};


