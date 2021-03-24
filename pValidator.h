#pragma once
#include <string>
#include <regex>
#include <stdexcept>

using std::string;
using std::regex;

template<class T>
class Validator
{
private:
    T _value;
public:
    Validator();
    Validator(T value);
    ~Validator();
    /// <summary>
    /// Проверяет на исправность постфиксные выражения
    /// </summary>
    /// <param name="Expression"></param>
    /// <returns></returns>
    bool IsPostfixExpressionValid(T& Expression);

    /// <summary>
    /// Определяет является ли входящий параметр операндом
    /// </summary>
    /// <param name="Character"></param>
    /// <returns></returns>
    bool IsOperand(T Character);

    /// <summary>
    /// Определяет является ли входящий параметр буквенным операндом
    /// </summary>
    /// <param name="Character"></param>
    /// <returns></returns>
    bool IsLetterOperand(T Character);

    /// <summary>
    /// Определяет является ли входящий параметр численным операндом
    /// </summary>
    /// <param name="Character"></param>
    /// <returns></returns>
    bool IsNumericalOperand(T Character);

    /// <summary>
    /// Проверяет является ли входящий параметр арифметическим оператором
    /// </summary>
    /// <param name="Character"></param>
    /// <returns></returns>
    bool IsArithmeticalOperator(T Character);

    /// <summary>
    /// Проверяет является ли входящий параметр правоассоциативным оператором
    /// </summary>
    /// <param name="Character"></param>
    /// <returns></returns>
    bool IsRightAssociative(T Character);

    /// <summary>
    /// Сравнивает приоритет операторов
    /// </summary>
    /// <param name="First"></param>
    /// <param name="Second"></param>
    /// <returns></returns>
    bool PriorityComparator(T First, T Second);

    /// <summary>
    /// Возвращает "вес" приоритета арифметического оператора
    /// </summary>
    /// <param name="Operator"></param>
    /// <returns></returns>
    int GetArithmeticalOperatorPriorityWeight(T Operator);

    /// <summary>
    /// Проверяет является ли входящий параметр открывающейся скобкой
    /// </summary>
    /// <param name="Character"></param>
    /// <returns></returns>
    bool IsOpeningBrackets(T Character);

    /// <summary>
    /// Проверяет является ли входящий параметр закрывающейся скобкой
    /// </summary>
    /// <param name="Character"></param>
    /// <returns></returns>
    bool IsClosingBrackets(T Character);
};

