#include "ExpressionDefragmentator.h"

int ExpressionDefragmentator::CheckPositionOfFirstLetterWhichMatchesToExistingFunctionName(string& Expression)
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

string ExpressionDefragmentator::GetFirstLetterFromString(string& str)
{
    int Size = 1, Index = 0;
    string FirstLetter;

    for (int i = 0; i < Size; i++)
    {
        FirstLetter = str[i];
        if (FirstLetter == "A")
        {
            return FirstLetter;
        }
        else if (FirstLetter == "C")
        {
            return FirstLetter;
        }
        else if (FirstLetter == "E")
        {
            return FirstLetter;
        }
        else if (FirstLetter == "l")
        {
            return FirstLetter;
        }
        else if (FirstLetter == "P")
        {
            return FirstLetter;
        }
        else if (FirstLetter == "S")
        {
            return FirstLetter;
        }
        else if (FirstLetter == "T")
        {
            return FirstLetter;
        }
        else
        {
            return "";
        }
    }
}

bool ExpressionDefragmentator::ContainsAnExistingLetterSimilarToFunctionName(string& str)
{
    int Size = 1, Index = 0;
    string FirstLetter;

    for (int i = 0; i < Size; i++)
    {
        FirstLetter = str[i];
        if (FirstLetter == "A" || FirstLetter == "C" || FirstLetter == "E" || FirstLetter == "l"
            || FirstLetter == "P" || FirstLetter == "S" || FirstLetter == "T")
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool ExpressionDefragmentator::HasSameLetter(string& First, string& Second)
{
    int Size = 1;
    string FirstLetter, SecondLetter;
    pair<string&, string&> Expr(First, Second);
    for (int i = 0; i < Size; i++)
    {
        if (Expr.first[i] == Expr.second[i]) { return true; }
        else { return false; }
    }
}

bool ExpressionDefragmentator::HasSameFirstLetter(pair<string&, string&> MyPair)
{
    return HasSameLetter(MyPair.first, MyPair.second);
}

bool ExpressionDefragmentator::CheckIfExpressionAlreadyMatchesTheFunctionName(string& Expression)
{
    if (Expression.size() < 2) { return false; }
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
    int a = CheckPositionOfFirstLetterWhichMatchesToExistingFunctionName(Expression);
    string Value = "T";
    Functions.resize(16, Value);
    Functions.resize(17);
    bool SameFirstLetter;

    for (a; ; a++)
    {
        pair<string&, string&> ExpressionAndFunctionName(Expression, Functions[a]);
        SameFirstLetter = HasSameFirstLetter(ExpressionAndFunctionName);
        if (!SameFirstLetter)
        {
            break;
        }
        else
        {
            if (Expression == Functions[a])
            {
                return true;
            }
            else continue;
        }
    }
    return false;
}

bool ExpressionDefragmentator::HasMatchesWithFunctionName(string& Current, string& Prev)
{
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
    string Merged = Prev + Current;
    string Token, Function, Value = "T";
    int EndOfPatternList = Functions.size();
    int MergedStringSize = Merged.size();
    int Index = -1, i = 0;
    int nPos = Merged.size() - 1;
    int PosNotFoundedCode = -1;
    bool SameFirstLetter;

    if (MergedStringSize == 1)
    {
        if (ContainsAnExistingLetterSimilarToFunctionName(Merged)) { return true; }
        else { return false; }
    }
    else
    {
        Token = Merged[nPos];
        Functions.resize(16, Value);
        Functions.resize(17);
        i = CheckPositionOfFirstLetterWhichMatchesToExistingFunctionName(Merged);
        pair<string&, string&> ExpressionAndFunctionName(Merged, Functions[i]);
        SameFirstLetter = HasSameFirstLetter(ExpressionAndFunctionName);
        for (i; SameFirstLetter; i++)
        {
            Function = Functions[i];
            Index = Function.find(Merged[nPos]);
            if (Index != PosNotFoundedCode)
            {
                return true;
            }
            else
            {
                if (HasSameLetter(Functions[i], Functions[i + 1]))
                {
                    continue;
                }
                else
                {
                    return false;
                }
            }
        }
    }
}

void ExpressionDefragmentator::TryParseConcatenatedLettersAndFunctions(string& Expression, int& Index, string& Token, string& NextToken, string& buffer, string& PrevMatchingElements, vector<string>& SeparatedExpression)
{
    Validator<string> validator;
    string NextLetter;
    bool HasMatchingElements, AlreadyFunction;
    int MinSizeToCheck = 2;
    Token = Expression[Index];
    buffer += Token;
    if (!PrevMatchingElements.empty())
    {
        if (HasSameLetter(PrevMatchingElements, buffer))
        {
            SeparatedExpression.push_back(PrevMatchingElements);
            PrevMatchingElements.clear();
        }
    }
    HasMatchingElements = HasMatchesWithFunctionName(buffer, PrevMatchingElements);
    if (HasMatchingElements)
    {
        NextLetter = Expression[Index + 1];

        PrevMatchingElements += buffer;
        buffer.clear();
        if (PrevMatchingElements.size() < MinSizeToCheck) { AlreadyFunction = false; }
        else { AlreadyFunction = CheckIfExpressionAlreadyMatchesTheFunctionName(PrevMatchingElements); }

        if (AlreadyFunction)
        {
            SeparatedExpression.push_back(PrevMatchingElements);
            PrevMatchingElements.clear();
        }
        if (ContainsAnExistingLetterSimilarToFunctionName(NextLetter))
        {
            if (!PrevMatchingElements.empty())
            {
                for (int k = 0; k < PrevMatchingElements.length(); k++)
                {
                    Token = PrevMatchingElements[k];
                    SeparatedExpression.push_back(Token);
                }
                Token.clear();
                PrevMatchingElements.clear();
            }
        }
        if (!validator.IsOperand(NextLetter = Expression[Index + 1]))
        {
            for (int k = 0; k < PrevMatchingElements.length(); k++)
            {
                Token = PrevMatchingElements[k];
                SeparatedExpression.push_back(Token);
            }
            Token.clear();
            PrevMatchingElements.clear();
        }
    }
    else
    {
        for (int j = 0; j < PrevMatchingElements.length(); j++)
        {
            Token = PrevMatchingElements[j];
            SeparatedExpression.push_back(Token);
        }
        SeparatedExpression.push_back(buffer);
        buffer.clear();
        PrevMatchingElements.clear();
    }
    if (!NextToken.empty() && !validator.IsNumericalOperand(NextToken) || !validator.IsArithmeticalOperator(NextToken) || !validator.IsOpeningBrackets(NextToken) || !validator.IsClosingBrackets(NextToken))
    {
        NextToken = Expression[Index + 1];
        if (NextToken.empty() && validator.IsNumericalOperand(NextToken) || validator.IsArithmeticalOperator(NextToken) || validator.IsOpeningBrackets(NextToken) || validator.IsClosingBrackets(NextToken)) {
            return;
        }
        ++Index;
    }
}

vector<string> ExpressionDefragmentator::DefragmentateExpression(string& Expression)
{
    string Token, NextToken, buffer, PrevMatchingElements;
    vector<string> SeparatedExpression;
    Validator<string> validator;
    int ExpressionEnd = Expression.size();
    int i = 0;
    for (i; i < Expression.size(); i++)
    {
        Token = Expression[i];
        NextToken = Expression[i + 1];
        if (validator.IsNumericalOperand(Token) || validator.IsArithmeticalOperator(Token) || validator.IsOpeningBrackets(Token) || validator.IsClosingBrackets(Token)) {
            SeparatedExpression.push_back(Token);
        }
        else
        {
            if (!validator.IsOperand(NextToken)) { SeparatedExpression.push_back(Token); }
            while (validator.IsLetterOperand(NextToken))
            {
                TryParseConcatenatedLettersAndFunctions(Expression, i, Token, NextToken, buffer, PrevMatchingElements, SeparatedExpression);
            }
            if (validator.IsNumericalOperand(NextToken) || validator.IsArithmeticalOperator(NextToken) || validator.IsOpeningBrackets(NextToken) || validator.IsClosingBrackets(NextToken))
            {
                continue;
            }
        }
    }
    return SeparatedExpression;
}
