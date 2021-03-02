#pragma once
#include "InputOptions.cpp"
#include <regex>
#include <string>
#include <iostream>

using namespace std;

template<class T>
class InputValidator : public InputOptions<T>
{
    T _value;
public:
    InputValidator();
    InputValidator(T value);
    ~InputValidator();
    T Input(T value) override;
};

