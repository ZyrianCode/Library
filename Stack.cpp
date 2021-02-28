#include "pStack.h"

template<class T>
Stack<T>::Stack()
{

}

template<class T>
Stack<T>::~Stack()
{
    clear();
}

template<class T>
int Stack<T>::size() {
    return this->_size;
}

template<class T>
bool Stack<T>::is_empty()
{
    return _size == 0;
}

template<class T>
void Stack<T>::push(T value)
{
    _head = new Node<T>(value, _head); //_head указ. на вершину стэка
    _size++;
}

template<class T>
void Stack<T>::clear()
{
    while (!is_empty())
    {
        pop();
    }
}

template<class T>
T Stack<T>::pop()
{
    T value = _head->Value;
    _head = _head->PNext; //ранее следовавший за вершиной элемент
    _size--;
    return value;
}

template<class T>
T Stack<T>::top()
{
    return _head->Value;
}
