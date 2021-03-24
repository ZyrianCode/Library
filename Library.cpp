#include <Windows.h>
#include "Queue.h"
#include "Stack.h"
#include "Notations.h"
#include "InputOptions.h"
#include "ExpressionFormatter.h"
#include "ExpressionDefragmentator.h"
#include "Parser.h"
#include <chrono>

using namespace std::chrono;
int main()
{
    setlocale(LC_ALL, "rus");
    string Prefix, Infix, Postfix, valid, result, exp;
    int x = 0;
    /*InputValidator<string> a;
    valid = a.Input(Infix);*/
    ExpressionDefragmentator ed;
    ExpressionFormatter ef;
    string Expression;
    vector<string> b, c;

    cin >> exp;

    auto start = steady_clock::now();
    b = ed.DefragmentateExpression(exp);
    auto finish = steady_clock::now();

    cout << "Time ms:" << duration_cast<milliseconds>(finish - start).count() << " " << "Defragmentator: " << endl;
    for (int i = 0; i <= b.size() - 1; i++)
    {
        cout << b[i] << endl;
    }

    auto start2 = steady_clock::now();
    c = ef.FormateToInfix(b);
    auto finish2 = steady_clock::now();

    cout << "Time ms:"<< duration_cast<milliseconds>(finish2 - start2).count() << " " << "Formatter: " << endl;

    for (int j = 0; j < c.size(); j++)
    {
        cout << c[j];
    }
    cout << endl;

    /*for (int i = 0; i < c.size(); i++)
    {
        Expression += c[i];
    }

    shared_ptr<Parser> parser = Parse(Expression.begin(), Expression.end(), x);

    cout << "Enter x: ";
    while (cin >> x)
    {
        cout << "Expression result: " << parser->Evaluate() << endl;
        cout << "Enter x: ";
    }*/
    /*NotationConverter b;
    Postfix = b.ConvertInfixToPostfix(valid);
    Prefix = b.ConvertPostfixToPrefix(Postfix);
    cout << "infix to Postfix: " << Postfix << endl;
    cout << "Result: " << b.GetResultFromPostfix(Postfix) << endl;
    cout << "Infix to prefix: " << b.ConvertInfixToPrefix(valid) << endl;
    cout << "Postfix to infix: " << b.ConvertPostfixToInfix(Postfix) << endl;
    cout << "Postfix to prefix: " << Prefix << endl;
    cout << "Prefix to infix: " << b.ConvertPrefixToInfix(Prefix) << endl;
    cout << "Prefix to postfix: " << b.ConvertPrefixToPostfix(Prefix) << endl;*/

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
