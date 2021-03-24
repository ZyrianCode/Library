#pragma once
#include <string>
#include <vector>
#include <stack>
#include <utility>
#include "Validator.h"

using std::string;
using std::to_string;
using std::stack;
using std::vector;
using std::pair;

class ExpressionFormatter
{
    string _expression;
public:
    ExpressionFormatter();
   ~ExpressionFormatter();
    vector<string> FormateToInfix(vector<string> &Expression);
private:
    void FormateNumbers(vector<string>& Expression, int& i, vector<string>& InfixExpression, string& Token, string& NumbersCell);
    void FormateOperators(vector<string>& Expression, int& i, vector<string>& InfixExpression, string& Token, string& NumbersCell);
    void FormateLetters(vector<string>& Expression, int& i, vector<string>& InfixExpression, string& Token, string& NumbersCell);
    void FormateFunctions(vector<string>& Expression, int& i, vector<string>& InfixExpression, string& Token, string& NumbersCell);
    void FormateBrackets(vector<string>& Expression, int& i, vector<string>& InfixExpression, string& Token, string& NumbersCell);

    bool IsFunction(string& Token);
    int CheckPositionOfFirstLetterWhichMatchesToExistingFunctionName(string& Expression);

    void ReincarnateInBracketsExpression(vector<string>& InfixExpression, string& Token, string& ReincarnatedOpeningBracket, string& ReincarnatedOperand, string& ReincarnatedClosingBracket);

    void ReincarnateOpeningBracketAfterToken(vector<string>& InfixExpression, string& Token, string& ReincarnatedOpeningBracket);

    void ReincarnateBracketBetweenTokenAndOperand(vector<string>& InfixExpression, string& Token, string& ReincarnatedBracket, string& ReincarnatedOperand);

    void PlaceReincarnatedOperandAfterToken(vector<string>& InfixExpression, string& Token, string& ReincarnatedOperand);

    void PlaceTokenAfterReincarnatedOperand(vector<string>& InfixExpression, string& ReincarnatedOperand, string& Token);

    void PlaceReincarnatedOperatorAfterNumericOperand(vector<string>& InfixExpression, string& NumericOperand, string& ReincarnatedOperator);

    void PlacedTokenAfterNumericOperand(vector<string>& InfixExpression, string& NumericOperand, string& Token);

    void PlaceReincarnatedOperatorBetweenTokenAndReincarnatedOperand(vector<string>& InfixExpression, string& Token, string& ReincarnatedOperator, string& ReincarnatedOperand);

    void PlaceReincarnatedOperatorBetweenNumericOperandAndToken(vector<string>& InfixExpression, string& NumericOperand, string& ReincarnatedOperator, string& Token);

    void PlaceTokenBetweenReincarnatedOperands(vector<string>& InfixExpression, string& Token, string& ReincarnatedOperand);

    void PlaceTokenAndReincarnateOperand(vector<string>& InfixExpression, string& Token, string& ReincarnatedOperand);

    void PlaceTokenAndReincarnateOperator(vector<string>& InfixExpression, string& Token, string& ReincarnatedOperator);

    void PlaceReincarnatedOperandAfterNumericOperandAndToken(vector<string>& InfixExpression, string& NumericOperand, string& Token, string& ReincarnatedOperand);
};

