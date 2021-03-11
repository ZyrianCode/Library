#include <Windows.h>
#include "Queue.h"
#include "Stack.h"
#include "Notations.h"
#include "InputOptions.h"


int main()
{
    setlocale(LC_ALL, "rus");
    string Prefix, Infix, Postfix, valid, result;
    InputValidator<string> a;
    valid = a.Input(Infix);

    NotationConverter b;
    Postfix = b.ConvertInfixToPostfix(valid);
    Prefix = b.ConvertPostfixToPrefix(Postfix);
    cout << "infix to Postfix: " << Postfix << endl;
    cout << "Result: " << b.GetResultFromPostfix(Postfix) << endl;
    cout << "Infix to prefix: " << b.ConvertInfixToPrefix(valid) << endl;
    cout << "Postfix to infix: " << b.ConvertPostfixToInfix(Postfix) << endl;
    cout << "Postfix to prefix: " << Prefix << endl;
    cout << "Prefix to infix: " << b.ConvertPrefixToInfix(Prefix) << endl;
    cout << "Prefix to postfix: " << b.ConvertPrefixToPostfix(Prefix) << endl;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
