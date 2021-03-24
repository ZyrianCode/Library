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

class ExpressionDefragmentator
{

    int CheckPositionOfFirstLetterWhichMatchesToExistingFunctionName(string& Expression);
    string GetFirstLetterFromString(string& str);
    bool ContainsAnExistingLetterSimilarToFunctionName(string& str);
    bool HasSameLetter(string& First, string& Second);
    bool HasSameFirstLetter(pair<string&, string&> MyPair);
    bool CheckIfExpressionAlreadyMatchesTheFunctionName(string& Expression);
    bool HasMatchesWithFunctionName(string& Current, string& Prev);
    void TryParseConcatenatedLettersAndFunctions(string& Expression, int& Index, string& Token, string& NextToken, string& buffer, string& PrevMatchingElements, vector<string>& SeparatedExpression);
public:

    vector<string> DefragmentateExpression(string& Expression);
};

