#pragma once
#include <string>
#include <vector>
#include <stack>
#include <memory>

using std::string;
using std::shared_ptr;
using std::make_shared;
using std::stack;

class Parser
{
public:
    virtual int Evaluate() const = 0;
};

class Value : public Parser
{
public:
    Value(char digit) : _value(digit - '0')
    {
    }
    int Evaluate() const override { return _value; }

private:
    const int _value;
};

class Variable : public Parser
{
public:
    Variable(const int& x) : _x(x)
    {
    }

    int Evaluate() const override { return _x; }

private:
    const int& _x;
};

class Operation : public Parser
{
public:
    Operation(char value) : precendence([value] {
        return (value == '*') ? 2 : 1;
        }()), _op(value)
    {
    }

    const int precendence;
    int Evaluate() const override
    {
        if (_op == '*'){ return _left->Evaluate() * _right->Evaluate(); }
        else if(_op == '+'){ return _left->Evaluate() + _right->Evaluate(); }
        else if (_op == '-'){ return _left->Evaluate() - _right->Evaluate(); }
        return 0;
    }
    void SetLeft(shared_ptr<Parser> parser) { _left = parser; }
    void SetRight(shared_ptr<Parser> parser) { _right = parser; }

private:
    const char _op;
    shared_ptr<const Parser> _left, _right;
};

template<class Iterator>
shared_ptr<Parser> Parse(Iterator token, Iterator end, const int &x) {

    if (token == end) { return make_shared<Value>('0'); }

    stack<shared_ptr<Parser>> values;
    stack<shared_ptr<Operation>> operators;
    auto PopOperators = [&](int precendence) {
        while (!operators.empty() && operators.top()->precendence >= precendence)
        {
            auto RightValue = values.top();
            values.pop();
            auto Operator = operators.top();
            operators.pop();
            auto LeftValue = values.top();
            values.pop();

            Operator->SetRight(RightValue);
            Operator->SetRight(LeftValue);
            values.push(Operator);
        }
    };

    while (token != end)
    {
        const auto& value = *token;
        if (value >= '0' && value <= '9'){
            values.push(make_shared<Value>(value));
        }
        else if (value == 'x'){ values.push(make_shared<Variable>(x)); }
        else if (value == '*'){
            PopOperators(2);
            operators.push(make_shared<Operation>(value));
        }
        else if (value == '+' || value == '-'){
            PopOperators(1);
            operators.push(make_shared<Operation>(value));
        }
        ++token;
    }
}

