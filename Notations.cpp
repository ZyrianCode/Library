#pragma once
#include "pNotations.h"

void NotationConverter::PushToStack(std::stack<string>& Stack, string& Item)
{
    Stack.push(Item);
    Item.erase();
}

string NotationConverter::ConvertPrefixToInfix(string& Expression)
{
    if (Expression.empty())
    {
        return "Expression was null";
    }
    stack<string> Stack;
    Validator<string> validator;
    string token, FirstOperand = "", SecondOperand, Concatenated;
    int Size = Expression.size();
    for (int i = Size; i >= 0; i--)
    {
        token = Expression[i];
        if (validator.IsArithmeticalOperator(token)) {
            if (Stack.empty()) { FirstOperand = "x"; }
            else
            {
                FirstOperand = Stack.top();
                Stack.pop();
            }
            if (Stack.empty()) { SecondOperand = "x"; }
            else
            {
                SecondOperand = Stack.top();
                Stack.pop();
            }
            Concatenated = (FirstOperand + token + SecondOperand);
            Stack.push(Concatenated);
        }
        else
        {
            Stack.push(string(token));
        }
    }
    return Stack.top();
}

string NotationConverter::ConvertPrefixToPostfix(string& Expression)
{
    if (Expression.empty())
    {
        return "Expression was null";
    }
    stack<string> Stack;
    Validator<string> validator;
    string token, FirstOperand, SecondOperand, Concatenated;
    int Size = Expression.size();
    for (int i = Size; i >= 0; i--)
    {
        token = Expression[i];
        if (validator.IsArithmeticalOperator(token)) {
            if (Stack.empty()) { FirstOperand = "x"; }
            else
            {
                FirstOperand = Stack.top();
                Stack.pop();
            }
            if (Stack.empty()) { SecondOperand = "x";  }
            else
            {
                SecondOperand = Stack.top();
                Stack.pop();
            }
            Concatenated = ( FirstOperand + SecondOperand + token );
            Stack.push(Concatenated);
        }
        else
        {
            Stack.push(string(token));
        }
    }
    return Stack.top();
}

string NotationConverter::ConvertInfixToPostfix(string& Expression)
{
    if (Expression.empty())
    {
        return "Expression was null";
    }
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

string NotationConverter::ConvertInfixToPrefix(string& Expression)
{
    if (Expression.empty())
    {
        return "Expression was null";
    }
    string token;
    Validator<string> validator;
    auto Size = Expression.size();
    reverse(Expression.begin(), Expression.end());
    for (auto i = 0; i < Size; i++)
    {
        token = Expression[i];
        if (validator.IsOpeningBrackets(token)) {
            Expression[i] = ')';
            i++;
        }
        else if(validator.IsClosingBrackets(token))
        {
            Expression[i] = '(';
            i++;
        }
    }
    string prefix = ConvertInfixToPostfix(Expression);
    reverse(prefix.begin(), prefix.end());
    return prefix;
}

string NotationConverter::ConvertPostfixToInfix(string& Expression)
{
    if (Expression.empty())
    {
        return "Expression was null";
    }
    stack<string> Stack;
    Validator<string> validator;
    string token, FirstOperator, SecondOperator;
    for (auto i = 0; i < Expression.size(); i++)
    {
        token = Expression[i];
        if (validator.IsOperand(token)) {
            string operand(token);
            Stack.push(operand);
        }
        else
        {
            if (Stack.empty()){ FirstOperator = "x"; }
            else
            {
                FirstOperator = Stack.top();
                Stack.pop();
            }
            if(Stack.empty()){ SecondOperator = "x"; }
            else
            {
                SecondOperator = Stack.top();
                Stack.pop();
            }

            Stack.push(SecondOperator + token + FirstOperator);
        }
    }
    return Stack.top();
}

string NotationConverter::ConvertPostfixToPrefix(string& Expression)
{
    if (Expression.empty())
    {
        return "Expression was null";
    }
    stack<string> Stack;
    Validator<string> validator;
    string token, FirstOperand, SecondOperand, Concatenated, Result = "";
    auto Size = Expression.size();
    for (auto i = 0; i < Size; i++)
    {
        token = Expression[i];
        if (validator.IsArithmeticalOperator(token)) {
            if (Stack.empty()) { FirstOperand = "x"; }
            else
            {
                FirstOperand = Stack.top();
                Stack.pop();
            }
            if(Stack.empty()){ SecondOperand = "x";}
            else{
                SecondOperand = Stack.top();
                Stack.pop();
            }
            Concatenated = token + SecondOperand + FirstOperand;
            Stack.push(Concatenated);
        }
        else
        {
            Stack.push(string(token));
        }
    }
    while (!Stack.empty())
    {
        Result += Stack.top();
        Stack.pop();
    }
    return Result;
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
    if (Postfix.empty())
    {
        return "Expression was null";
    }
    std::stack<string> Stack;
    Validator<string> Validator;

    if (Validator.IsPostfixExpressionValid(Postfix)) { return "Could'not get the result: there are more operators than operands..."; }

    string buffer, operation;
    double left, right, result;
    regex isnum("[\\d\\w]");
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
