#include "pExpressionFormatter.h"

ExpressionFormatter::ExpressionFormatter()
{
}

ExpressionFormatter::~ExpressionFormatter()
{
}

vector<string> ExpressionFormatter::FormateToInfix(vector<string>& Expression)
{
    string token, NextToken, AfterNextToken, buffer, function;
    string reincarnatedOperator = "*", reincarnatedOperand = "x", reincarnatedOpeningBracket = "(";
    Validator<string> validator;
    vector<string> InfixExpression;
    int ExpressionStart = 0, ExpressionEnd = Expression.size() - 1, PrevExpressionSize = Expression.size();

    for (int i = 0; i < Expression.size(); i++)
    {
        token = Expression[i];
        //buffer += token;
        if (validator.IsNumericalOperand(token)) //проверки численных операндов
        {
            FormateNumbers(Expression, i, InfixExpression, token, buffer);
        }
        else if(validator.IsArithmeticalOperator(token)) //проверки операторов
        {
            FormateOperators(Expression, i, InfixExpression, token, buffer);
        }
        else if (validator.IsLetterOperand(token)) //проверки буквенных операндов
        {
            FormateLetters(Expression, i, InfixExpression, token, buffer);
        }
        else if (IsFunction(token)) //проверка на соответствие операнда на соответствие имени существующих функций
        {
            FormateFunctions(Expression, i, InfixExpression, token, buffer);
        }
        else  //для скобок
        {
            FormateBrackets(Expression, i, InfixExpression, token, buffer);
        } 
    }
    return InfixExpression;
}

void ExpressionFormatter::FormateNumbers(vector<string>& Expression, int& i, vector<string>& InfixExpression, string& Token, string& NumbersCell)
{
    Validator<string> validator;
    string reincarnatedOperator = "*", NextToken;
    int ExpressionStart = 0, ExpressionEnd = Expression.size() - 1;

    if (i != ExpressionEnd) { NextToken = Expression[i + 1]; }
    else { NextToken = ""; }
    if (validator.IsArithmeticalOperator(NextToken) || validator.IsNumericalOperand(NextToken))
    {
        NumbersCell += Token;
    }
    else if (validator.IsLetterOperand(NextToken) || validator.IsOpeningBrackets(NextToken) || IsFunction(NextToken))
    {
        NumbersCell += Token;
        PlaceReincarnatedOperatorAfterNumericOperand(InfixExpression, NumbersCell, reincarnatedOperator);
        NumbersCell.clear();
    }
    else  //когда nexttoken = ""; и уже конец выражения
    {
        NumbersCell += Token;
        InfixExpression.push_back(NumbersCell);
        NumbersCell.clear();
    }
}

void ExpressionFormatter::FormateOperators(vector<string>& Expression, int& i, vector<string>& InfixExpression, string& Token, string& NumbersCell)
{
    Validator<string> validator;
    string ReincarnatedOperand = "x", PrevToken, NextToken, AfterNextToken;
    int ExpressionStart = 0, ExpressionEnd = Expression.size() - 1, PrevExpressionSize = Expression.size();
    if (i != ExpressionEnd) { NextToken = Expression[i + 1]; }
    if (Expression.size() > 1 && i > 0)
    {
        PrevToken = Expression[i - 1];
    }

    if (i == ExpressionStart) //проверяем если выражение начинается с оператора
    {
        if (validator.IsArithmeticalOperator(NextToken) || i == ExpressionEnd)
        {
            PlaceTokenBetweenReincarnatedOperands(InfixExpression, Token, ReincarnatedOperand);
        }
        else
        {
            if ((Token == "+" && IsFunction(NextToken)) || (validator.IsOperand(NextToken) && Token == "+")){}
            else
            {
                if ((IsFunction(NextToken) && (Token == "/" || Token == "*" || Token == "^")) ||
                    (validator.IsOperand(NextToken) && Token != "-" && Token != "+")) {
                    PlaceTokenAfterReincarnatedOperand(InfixExpression, ReincarnatedOperand, Token);
                }
                else{ InfixExpression.push_back(Token); }
            }
        }
    }
    else if (validator.IsOperand(NextToken) || validator.IsOpeningBrackets(NextToken))
    {
        if (!NumbersCell.empty())
        {
            PlacedTokenAfterNumericOperand(InfixExpression, NumbersCell, Token);
            NumbersCell.clear();
        }
        else
        {
            if (Token == "+" && !validator.IsOperand(PrevToken) &&
                !validator.IsArithmeticalOperator(PrevToken) && !validator.IsClosingBrackets(PrevToken)){}
            else if (Token == "+" && PrevToken == "+" && !validator.IsOperand(NextToken))
            {
                PlaceTokenAfterReincarnatedOperand(InfixExpression, ReincarnatedOperand, Token);
            }
            else{InfixExpression.push_back(Token); }
        }
    }
    else if (validator.IsArithmeticalOperator(NextToken))
    {
        if (!NumbersCell.empty())
        {
            PlaceReincarnatedOperandAfterNumericOperandAndToken(InfixExpression, NumbersCell, Token, ReincarnatedOperand);
            NumbersCell.clear();
        }
        else
        {
            if (Token == "+" && IsFunction(PrevToken)) {
               InfixExpression.push_back(ReincarnatedOperand);
            }
            else{
                if (Token == "+" && validator.IsOperand(PrevToken) && !validator.IsArithmeticalOperator(NextToken))
                {
                    InfixExpression.push_back(Token);
                }
                else
                {
                    PlaceTokenAndReincarnateOperand(InfixExpression, Token, ReincarnatedOperand);
                }
            }
        }
    }
    else if (validator.IsClosingBrackets(NextToken))
    {
        if (!NumbersCell.empty())
        {
            PlaceReincarnatedOperandAfterNumericOperandAndToken(InfixExpression, NumbersCell, Token, ReincarnatedOperand);
            NumbersCell.clear();
        }
        else{
            PlaceTokenAndReincarnateOperand(InfixExpression, Token, ReincarnatedOperand);
        }
    }
    else if (IsFunction(NextToken))
    {
        if (!NumbersCell.empty()) { InfixExpression.push_back(NumbersCell); NumbersCell.clear(); }
        if ((validator.IsOperand(PrevToken) && Token == "+") || (Token == "+" && IsFunction(PrevToken) && IsFunction(NextToken))){}
        else
        {
            InfixExpression.push_back(Token);
        }
    }
    else if (i == ExpressionEnd) //Когда оператор в конце не отнимает операнда
    {
        PlaceTokenAndReincarnateOperand(InfixExpression, Token, ReincarnatedOperand);
    }
}

void ExpressionFormatter::FormateLetters(vector<string>& Expression, int& i, vector<string>& InfixExpression, string& Token, string& NumbersCell)
{
    Validator<string> validator;
    string reincarnatedOperator = "*", reincarnatedOperand = "x", NextToken;
    int ExpressionStart = 0, ExpressionEnd = Expression.size() - 1;

    if (i != ExpressionEnd) { NextToken = Expression[i + 1]; }
    else { NextToken = ""; }
    if (validator.IsOperand(NextToken) || validator.IsOpeningBrackets(NextToken) || IsFunction(NextToken))
    {
        PlaceTokenAndReincarnateOperator(InfixExpression, Token, reincarnatedOperator);
    }
    else if (validator.IsArithmeticalOperator(NextToken))
    {
        InfixExpression.push_back(Token);
    }
    else if (!NumbersCell.empty())
    {
        PlaceReincarnatedOperatorBetweenNumericOperandAndToken(InfixExpression, NumbersCell, reincarnatedOperator, Token);
        NumbersCell.clear();
    }
    else
    {
        InfixExpression.push_back(Token);
    }
}

void ExpressionFormatter::FormateFunctions(vector<string>& Expression, int& i, vector<string>& InfixExpression, string& Token, string& NumbersCell)
{
    Validator<string> validator;
    string reincarnatedOperator = "*", reincarnatedOpeningBracket = "(", reincarnatedOperand = "x", reincarnatedClosingBracket = ")", NextToken, AfterNextToken;
    int ExpressionStart = 0, ExpressionEnd = Expression.size() - 1, PrevExpressionSize = Expression.size();
    
    if (i != ExpressionEnd) {
        Expression.resize(PrevExpressionSize + 1);
        NextToken = Expression[i + 1];  AfterNextToken = Expression[i + 2];
    }
    if (validator.IsOpeningBrackets(NextToken) || validator.IsClosingBrackets(NextToken)){
        if (NextToken.empty() || validator.IsClosingBrackets(NextToken)) {
            if (validator.IsOpeningBrackets(AfterNextToken) || validator.IsOperand(AfterNextToken) || IsFunction(AfterNextToken))
            {
                ReincarnateInBracketsExpression(InfixExpression, Token, reincarnatedOpeningBracket, reincarnatedOperand, reincarnatedClosingBracket);
                InfixExpression.push_back(reincarnatedOperator);
            }
            else{
                ReincarnateInBracketsExpression(InfixExpression, Token, reincarnatedOpeningBracket, reincarnatedOperand, reincarnatedClosingBracket);
            }
            i++;
        }
        else
        {
            InfixExpression.push_back(Token);
        }
    }
    else if (validator.IsArithmeticalOperator(NextToken))
    {
        if (NextToken == "*" || NextToken == "/"){
            ReincarnateBracketBetweenTokenAndOperand(InfixExpression, Token, reincarnatedOpeningBracket, reincarnatedOperand);
        }
        else{
            ReincarnateOpeningBracketAfterToken(InfixExpression, Token, reincarnatedOpeningBracket);
        }
    }
    else if (validator.IsOperand(NextToken)){
        ReincarnateOpeningBracketAfterToken(InfixExpression, Token, reincarnatedOpeningBracket);
    }
    else if (IsFunction(NextToken)){
        ReincarnateOpeningBracketAfterToken(InfixExpression, Token, reincarnatedOpeningBracket);
    }
    else{
        if (NextToken.empty()){
            ReincarnateInBracketsExpression(InfixExpression, Token, reincarnatedOpeningBracket, reincarnatedOperand, reincarnatedClosingBracket);
        }
        else{ InfixExpression.push_back(Token); }
    }
    Expression.resize(PrevExpressionSize);
}

void ExpressionFormatter::FormateBrackets(vector<string>& Expression, int& i, vector<string>& InfixExpression, string& Token, string& NumbersCell)
{
    Validator<string> validator;
    string reincarnatedOperator = "*", reincarnatedOpeningBracket = "(", reincarnatedOperand = "x", NextToken, AfterNextToken;
    int ExpressionStart = 0, ExpressionEnd = Expression.size() - 1, PrevExpressionSize = Expression.size();

    if (i != ExpressionEnd) { NextToken = Expression[i + 1]; }
    else { NextToken = ""; }
    if (validator.IsClosingBrackets(Token) && (validator.IsOpeningBrackets(NextToken) || validator.IsOperand(NextToken) || IsFunction(NextToken)))
    {
        PlaceTokenAndReincarnateOperator(InfixExpression, Token, reincarnatedOperator);
    }
    else if (validator.IsClosingBrackets(Token) && validator.IsArithmeticalOperator(NextToken))
    {
        InfixExpression.push_back(Token);
    }
    else if (validator.IsOpeningBrackets(Token) && validator.IsArithmeticalOperator(NextToken))
    {
        if (i != Expression.size() - 1) { Expression.resize(PrevExpressionSize + 2); AfterNextToken = Expression[i + 2]; }
        if (validator.IsClosingBrackets(AfterNextToken) || NextToken == "*" || NextToken == "/" || NextToken == "^") {
            PlaceTokenAndReincarnateOperand(InfixExpression, Token, reincarnatedOperand);
        }
        else if (AfterNextToken.empty()){ PlaceTokenAndReincarnateOperand(InfixExpression, Token, reincarnatedOperand); }
        else{ InfixExpression.push_back(Token); }
        Expression.resize(PrevExpressionSize);
        //PlaceTokenAndReincarnateOperand(InfixExpression, token, reincarnatedOperand);
    }
    else if (validator.IsOpeningBrackets(Token) && validator.IsClosingBrackets(NextToken)) //если скобки пустые, заполняем их
    {
        PlaceReincarnatedOperandAfterToken(InfixExpression, Token, reincarnatedOperand);
    }
    else{
        InfixExpression.push_back(Token);
    }
}

bool ExpressionFormatter::IsFunction(string& Token)
{
    int MinSizeToSearch = 2;
    Validator<string> validator;
    if (Token == "" || Token.size() < MinSizeToSearch || validator.IsArithmeticalOperator(Token) || validator.IsOpeningBrackets(Token) || validator.IsClosingBrackets(Token) || validator.IsOperand(Token))
    {
        return false;
    }
    vector<string> Functions{
        "Abs",
        "Arcsin",
        "Arccos",
        "Arctg",
        "Arcctg",
        "Cos",
        "Ctg",
        "Exp",
        "ln",
        "log",
        "Pow",
        "Sin",
        "Sign",
        "Sqrt",
        "Tg"
    };
    int EndOfPatternList = Functions.size();
    int i = CheckPositionOfFirstLetterWhichMatchesToExistingFunctionName(Token);
    for (i; i < EndOfPatternList; i++)
    {
        if (Token == Functions[i]) { return true; }
        else
        {
            if (i != EndOfPatternList) { continue; }
            else{ return false; }
        }
    }
    return false;
}

int ExpressionFormatter::CheckPositionOfFirstLetterWhichMatchesToExistingFunctionName(string& Expression)
{
    int Size = 1, Index = 0;
    string FirstLetter;

    for (int i = 0; i < Size; i++)
    {
        FirstLetter = Expression[i];
        if (FirstLetter == "A")
        {
            return Index = 0;
        }
        else if (FirstLetter == "C")
        {
            return Index = 5;
        }
        else if (FirstLetter == "E")
        {
            return Index = 7;
        }
        else if (FirstLetter == "l")
        {
            return Index = 8;
        }
        else if (FirstLetter == "P")
        {
            return Index = 10;
        }
        else if (FirstLetter == "S")
        {
            return Index = 11;
        }
        else if (FirstLetter == "T")
        {
            return Index = 14;
        }
        else
        {
            return -1;
        }
    }
}

void ExpressionFormatter::ReincarnateInBracketsExpression(vector<string>& InfixExpression, string& Token, string& ReincarnatedOpeningBracket, string& ReincarnatedOperand, string& ReincarnatedClosingBracket)
{
    InfixExpression.push_back(Token);
    InfixExpression.push_back(ReincarnatedOpeningBracket);
    InfixExpression.push_back(ReincarnatedOperand);
    InfixExpression.push_back(ReincarnatedClosingBracket);
}

void ExpressionFormatter::ReincarnateOpeningBracketAfterToken(vector<string>& InfixExpression, string& Token, string& ReincarnatedOpeningBracket)
{
    InfixExpression.push_back(Token);
    InfixExpression.push_back(ReincarnatedOpeningBracket);
}

void ExpressionFormatter::ReincarnateBracketBetweenTokenAndOperand(vector<string>& InfixExpression, string& Token, string& ReincarnatedBracket, string& ReincarnatedOperand)
{
    InfixExpression.push_back(Token);
    InfixExpression.push_back(ReincarnatedBracket);
    InfixExpression.push_back(ReincarnatedOperand);
}

void ExpressionFormatter::PlaceReincarnatedOperandAfterToken(vector<string>& InfixExpression, string& Token, string& ReincarnatedOperand)
{
    InfixExpression.push_back(Token);
    InfixExpression.push_back(ReincarnatedOperand);
}

void ExpressionFormatter::PlaceTokenAfterReincarnatedOperand(vector<string>& InfixExpression, string& ReincarnatedOperand, string& Token)
{
    InfixExpression.push_back(ReincarnatedOperand);
    InfixExpression.push_back(Token);
}

void ExpressionFormatter::PlaceReincarnatedOperatorAfterNumericOperand(vector<string>& InfixExpression, string& NumericOperand, string& ReincarnatedOperator)
{
    InfixExpression.push_back(NumericOperand);
    InfixExpression.push_back(ReincarnatedOperator);
}

void ExpressionFormatter::PlacedTokenAfterNumericOperand(vector<string>& InfixExpression, string& NumericOperand, string& Token)
{
    InfixExpression.push_back(NumericOperand);
    InfixExpression.push_back(Token);
}

void ExpressionFormatter::PlaceReincarnatedOperatorBetweenTokenAndReincarnatedOperand(vector<string>& InfixExpression, string& Token, string& ReincarnatedOperator, string& ReincarnatedOperand)
{
    InfixExpression.push_back(Token);
    InfixExpression.push_back(ReincarnatedOperator);
    InfixExpression.push_back(ReincarnatedOperand);
}

void ExpressionFormatter::PlaceReincarnatedOperatorBetweenNumericOperandAndToken(vector<string>& InfixExpression, string& NumericOperand, string& ReincarnatedOperator, string& Token)
{
    InfixExpression.push_back(NumericOperand);
    InfixExpression.push_back(ReincarnatedOperator);
    InfixExpression.push_back(Token);
}

void ExpressionFormatter::PlaceTokenBetweenReincarnatedOperands(vector<string>& InfixExpression, string& Token, string& ReincarnatedOperand)
{
    InfixExpression.push_back(ReincarnatedOperand);
    InfixExpression.push_back(Token);
    InfixExpression.push_back(ReincarnatedOperand);
}

void ExpressionFormatter::PlaceTokenAndReincarnateOperand(vector<string>& InfixExpression, string& Token, string& ReincarnatedOperand)
{
    InfixExpression.push_back(Token);
    InfixExpression.push_back(ReincarnatedOperand);
}

void ExpressionFormatter::PlaceTokenAndReincarnateOperator(vector<string>& InfixExpression, string& Token, string& ReincarnatedOperator)
{
    InfixExpression.push_back(Token);
    InfixExpression.push_back(ReincarnatedOperator);
}

void ExpressionFormatter::PlaceReincarnatedOperandAfterNumericOperandAndToken(vector<string>& InfixExpression, string& NumericOperand, string& Token, string& ReincarnatedOperand)
{
    InfixExpression.push_back(NumericOperand);
    InfixExpression.push_back(Token);
    InfixExpression.push_back(ReincarnatedOperand);
}


