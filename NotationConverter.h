#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <regex>
#include "Stack.h"
#include "Queue.h"

#pragma region Using

    using std::endl;
    using std::cout;
    using std::cin;
    using std::string;
    using std::to_string;
    using std::regex;

#pragma endregion


class NotationConverter
{
};


#pragma region Prototypes

    #pragma region InputChecks

        void ShowAllowedCharacters();
        string Input(string& Infix);

    #pragma endregion

    #pragma region Functional
        double GetResult(double& left, double& right, string& operation);

        /// <summary>
        /// Возвращает результат конвертации постфиксного выражения
        /// </summary>
        /// <param name="Postfix"></param>
        /// <returns></returns>
        int GetResultFromPostfix(string& Postfix);

        /// <summary>
        /// Проверяет приоритет операций
        /// </summary>
        /// <param name="sign"></param>
        /// <returns></returns>/// 
        int CheckOperatorPriority(string sign);
        void PushToStack(Stack<string>& stack, string& Item);

        /// <summary>
        /// Конвертирует инфиксную запись в постфиксную
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="Infix"></param>
        /// <param name="Postfix"></param>
        /// <returns></returns>
        string ConvertInfixToPostfix(string& Infix);

        /// <summary>
        /// Перекладывает из очереди в строку
        /// </summary>
        /// <param name="queue"></param>
        /// <param name="Postfix"></param>
        /// <returns></returns>
        string LoadFromQueueToPostfix(Queue<string>& queue, string& Postfix);

    #pragma endregion


#pragma endregion
#pragma region Realization

    #pragma region Defines

        #define PriorityInBuffer CheckOperatorPriority(buffer)
        #define PriorityInStack CheckOperatorPriority(stack.top())
        #define NotAnOpenBracket stack.top() != "("
        #define AnOpenBracket stack.top() == "("

    #pragma endregion

    #pragma region InputChecks

        void ShowAllowedCharacters()
        {
            cout << " =====| Allowed Characters List |====== " << endl;
            cout << "0123456789" << endl;
            cout << "() +-/*^%" << endl;
        }

        /// <summary>
        /// Проверяем соответствие строки формату
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="Infix"></param>
        string Input(string& Infix)
        {
            setlocale(LC_ALL, "ru");
            string result = "";
            regex r("^[\\d()\\+\\%\\/\\*\\-\\^]+$");
            while ((result.empty() || Infix.empty()) && !regex_match(Infix, r))
            {
                system("Cls");
                ShowAllowedCharacters();
                cout << "Введите строку: ";
                getline(cin, Infix);
            }
            if (regex_match(Infix, r) && !Infix.empty())
            {
                result = Infix;
                return result;
            }
            else { result = Infix; }
        }

    #pragma endregion

#pragma endregion

double GetResult(double& left, double& right, string& operation)
{
    double result;
    if (operation == "+") { return result = left + right; }
    if (operation == "-") { return result = left - right; }
    if (operation == "/") { return result = left / right; }
    if (operation == "*") { return result = left * right; }
    if (operation == "%") { return result = (int)left % (int)right; }
}

int CheckOperatorPriority(string sign)
{
    if (sign == "(") { return 0; }
    else if (sign == "+" || sign == "-") { return(1); }
    else if (sign == "*" || sign == "/" || sign == "%") { return(2); }
    else { return 3; }
}

string LoadFromQueueToPostfix(Queue<string>& queue, string& Postfix) {
    string Buffer;
    int Size = queue.size();
    for (auto i = 0; i < Size; i++)
    {
        Buffer = queue.pop();
        Postfix.push_back(Buffer.at(0));
        Buffer.erase();
    }
    return Postfix;
}

void PushToStack(Stack<string>& stack, string& Item) {
    stack.push(Item);
    Item.erase();
}

string ConvertInfixToPostfix(string& Infix)
{
    Input(Infix);

    Stack<string> stack;
    Queue<string> queue;

    regex isnum("[\\d]");
    regex lowerPriority("[+-]");
    regex higherPriority("[/*%]");
    regex isOperator("[\\+\\-\\/*%\\^]");

    string buffer, Postfix = "";

    for (auto i = 0; i < Infix.size(); i++)
    {
        buffer = Infix[i];
        if (regex_match(buffer, isnum)) { //+
            queue.add(buffer);
            buffer.erase();
        }
        else if (regex_match(buffer, isOperator)) {
            if (!stack.is_empty()) {
                while (PriorityInStack >= PriorityInBuffer)
                {
                    queue.add(stack.pop());
                    if (stack.is_empty()) { break; }
                }
            }
            PushToStack(stack, buffer);
        }
        else if (buffer == "(") { PushToStack(stack, buffer); }
        else if (buffer == ")") {

            while (NotAnOpenBracket)
            {
                queue.add(stack.pop());
            }
            if (!stack.is_empty()) {
                if (AnOpenBracket) { stack.pop(); }
            }
            else { stack.top() = ""; }
            buffer.erase();
        }

    }
    if (!stack.is_empty()) {
        for (auto j = 0; j < (stack.size()); j++)
        {
            queue.add(stack.pop());
        }
    }

    return LoadFromQueueToPostfix(queue, Postfix);
}

int GetResultFromPostfix(string& Postfix) {
    Stack<string> stack;

    string buffer, operation;
    double left, right, result;
    regex isnum("[\\d]");
    regex isOperator("[\\+\\-\\/*%\\^]");
    for (auto i = 0; i < Postfix.size(); i++)
    {
        buffer = Postfix[i];
        if (regex_match(buffer, isnum)) {
            PushToStack(stack, buffer);
        }
        else if (regex_match(buffer, isOperator)) {
            operation = buffer;
            right = atoi(stack.pop().c_str());
            left = atoi(stack.pop().c_str());
            result = GetResult(left, right, operation);
            stack.push(to_string(result));
            buffer.erase();
        }
    }
    return atoi(stack.pop().c_str());
}
