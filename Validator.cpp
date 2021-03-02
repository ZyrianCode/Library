#include "pValidator.h"

template<class T>
Validator<T>::Validator()
{
}

template<class T>
Validator<T>::Validator(T value)
{
    this->_value = value;
}

template<class T>
Validator<T>::~Validator()
{
}

template<class T>
bool Validator<T>::IsPostfixExpressionValid(T& Expression)
{
    auto CountOfOperators = 0, CountOfOperands = 0;
    string token = "";
    for (auto i = 0; i < Expression.size(); i++)
    {
        token = Expression[i];
        if (IsArithmeticalOperator(token)) { CountOfOperators++; }
        else { CountOfOperands++; }
    }

    return CountOfOperands <= CountOfOperators;
}

template<class T>
bool Validator<T>::IsOperand(T Character)
{
    regex isOperand("[\\d]");
    return regex_match(Character, isOperand);
}

template<class T>
bool Validator<T>::IsArithmeticalOperator(T Character)
{
    regex isOperator("[\\+\\%\\/\\*\\-\\^]");
    return regex_match(Character, isOperator);
}

template<class T>
bool Validator<T>::IsRightAssociative(T Character)
{
    return (Character == "^") ? true : false;
}

template<class T>
bool Validator<T>::PriorityComparator(T first, T second)
{
    int FirstPriority = GetArithmeticalOperatorPriorityWeight(first);
    int SecondPriority = GetArithmeticalOperatorPriorityWeight(second);
    if (FirstPriority == SecondPriority) { return IsRightAssociative(first) ? false : true; }
    return FirstPriority > SecondPriority ? true : false;
}

template<class T>
int Validator<T>::GetArithmeticalOperatorPriorityWeight(T Operator)
{
    int PriorityWeight = -1;
    if (Operator == "^") { PriorityWeight = 3; }
    if (Operator == "*" || Operator == "/" || Operator == "%") { PriorityWeight = 2; }
    if (Operator == "+" || Operator == "-") { PriorityWeight = 1; }
    return PriorityWeight;
}

template<class T>
bool Validator<T>::IsOpeningBrackets(T Character)
{
    if (Character == "(" || Character == "{" || Character == "[") return true;
    return false;
}

template<class T>
bool Validator<T>::IsClosingBrackets(T Character)
{
    if (Character == ")" || Character == "}" || Character == "]") return true;
    return false;
}
