#include <iostream>
#include <string>
#include <Windows.h>
#include "Queue.h"
#include "Stack.h"
#include "NotationConverter.h"


int main()
{
    setlocale(LC_ALL, "rus");
    //system("chcp 65001");
    SetConsoleCP(866);
    string Infix, Postfix;
    Postfix = ConvertInfixToPostfix(Infix);
    cout << "Постфиксная запись: " << Postfix << endl;
    cout << "Результат: " << GetResultFromPostfix(Postfix);
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
