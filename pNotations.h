#pragma once
#include <string>
#include <regex>
#include <stack>
#include "InputOptions.h"
#include "Validator.h"

using std::string;
using std::regex;
using std::to_string;

class NotationConverter{

    double GetResult(double& left, double& right, string& operation);

public:
    
    void PushToStack(std::stack<string>& Stack, string& Item);

    /// <summary>
    /// Конвертирует префиксное выражение в инфиксное
    /// </summary>
    /// <param name="Expression"></param>
    /// <returns></returns>
    string ConvertPrefixToInfix(string& Expression);

    /// <summary>
    /// Конвертирует префиксное выражение в постфиксное
    /// </summary>
    /// <param name="Expression"></param>
    /// <returns></returns>
    string ConvertPrefixToPostfix(string& Expression);

    /// <summary>
        /// Конвертирует инфиксное выражение в постфиксную
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="Infix"></param>
        /// <param name="Postfix"></param>
        /// <returns></returns>
    string ConvertInfixToPostfix(string& Expression);

    /// <summary>
    /// Конвертирует инфиксное выражение в префиксное
    /// </summary>
    /// <param name="Expression"></param>
    /// <returns></returns>
    string ConvertInfixToPrefix(string& Expression);

    /// <summary>
    /// Конвертирует постфиксное выражение в инфиксное
    /// </summary>
    /// <param name="Expression"></param>
    /// <returns></returns>
    string ConvertPostfixToInfix(string& Expression);

    /// <summary>
    /// Конвертирует постфиксное выражение в префиксное
    /// </summary>
    /// <param name="Expression"></param>
    /// <returns></returns>
    string ConvertPostfixToPrefix(string& Expression);

    /// <summary>
        /// Возвращает результат конвертации постфиксного выражения
        /// </summary>
        /// <param name="Postfix"></param>
        /// <returns></returns>
    string GetResultFromPostfix(string& Postfix);

};
