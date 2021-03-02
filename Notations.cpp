#pragma once
#include "pNotations.h"

void NotationConverter::PushToStack(std::stack<string>& Stack, string& Item)
{
    Stack.push(Item);
    Item.erase();
}

string NotationConverter::ConvertInfixToPostfix(string& Expression)
{
    std::stack<string> Stack;
    Validator<string> validator;
    string token, postfix;

    for (auto i = 0; i <= Expression.size() - 1; i++)
    {
        token = Expression[i];
        if (token == " " || token == ",") continue;
        else if (validator.IsOperand(token)){ postfix += token; }  // Если символ число, кладём его в очередь

        else if (validator.IsArithmeticalOperator(token))
        {
            while (!Stack.empty() && !validator.IsOpeningBrackets(Stack.top())  //Если оператор - проверяем пока не встретим открывающиеся скобки есть ли на верхушке стека оператор с более высоким приоритетом
                && validator.PriorityComparator(Stack.top(), token))
            {
                postfix += Stack.top(); 
                Stack.pop();
            }
            Stack.push(token); //Добавляем текущий оператор в стек
        }
        else if (validator.IsOpeningBrackets(token)){ Stack.push(token); }  //Если ( то добавляем в стек
        else if (validator.IsClosingBrackets(token)) //если ')' 
        {
            while (!Stack.empty() && !validator.IsOpeningBrackets(Stack.top())) { //кладём элементы в строку и удаляем операторы из стека, пока не встретим "("
                postfix += Stack.top();
                Stack.pop();
            }
            Stack.pop();
        }
    }
    while (!Stack.empty())
    {
        postfix += Stack.top();
        Stack.pop();
    }
    return postfix;
}

double NotationConverter::GetResult(double& left, double& right, string& operation)
{
    double result;
    if (operation == "+") { return result = left + right; }
    if (operation == "-") { return result = left - right; }
    if (operation == "/") { return result = left / right; }
    if (operation == "*") { return result = left * right; }
    if (operation == "%") { return result = (int)left % (int)right; }
}

string NotationConverter::GetResultFromPostfix(string& Postfix)
{
    std::stack<string> Stack;
    Validator<string> Validator;

    if (Validator.IsPostfixExpressionValid(Postfix)) { return "Could'not get the result: there are more operators than operands..."; }

    string buffer, operation;
    double left, right, result;
    regex isnum("[\\d]");
    regex isOperator("[\\+\\-\\/*%\\^]");
    for (auto i = 0; i < Postfix.size(); i++)
    {
        buffer = Postfix[i];
        if (regex_match(buffer, isnum)) {
            PushToStack(Stack, buffer);
        }
        else if (regex_match(buffer, isOperator)) {
            operation = buffer;
            right = atoi(Stack.top().c_str());
            Stack.pop();
            left = atoi(Stack.top().c_str());
            Stack.pop();
            result = GetResult(left, right, operation);
            Stack.push(to_string(result));
            buffer.erase();
        }
    }
    return Stack.top();
}
