#include "pInputValidator.h"


template<class T>
InputValidator<T>::InputValidator()
{
    
}

template<class T>
InputValidator<T>::InputValidator(T value)
{
    this->_value = value;
}

template<class T>
InputValidator<T>::~InputValidator()
{
}

template<class T>
T InputValidator<T>::Input(T value)
{
    setlocale(LC_ALL, "ru");
    std::string result = "";
    std::regex r("^[\\d\\w()\\+\\%\\/\\*\\-\\^]+$");
    while ((result.empty() || value.empty()) && !std::regex_match(value, r))
    {
        system("Cls");
        //ShowAllowedCharacters();
        std::cout << "Input string: ";
        getline(cin, value);
    }
    if (std::regex_match(value, r) && !value.empty())
    {
        result = value;
        return result;
    }
    else { result = value; }
}
