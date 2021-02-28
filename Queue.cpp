#include "pQueue.h"


template<class T>
Queue<T>::Queue() {

}

template<class T>
Queue<T>::~Queue()
{
    clear();
}

template<class T>
void Queue<T>::add(T value)
{
    push(value);
}

template<class T>
int Queue<T>::size()
{
    return _size;
}

template<class T>
void Queue<T>::clear()
{
    while (!is_empty())
    {
        pop();
    }
}

template<class T>
bool Queue<T>::is_empty()
{
    return _size == 0;
}

template<class T>
void Queue<T>::push(T value)
{
    Node<T>* newNode = new Node<T>(value, nullptr); // элемент не имеет ук. на след. эл., т.к находится в конце очереди
    if (is_empty()) {
        _head = _end = newNode; //начало и конец ук. на 1 элемент если эл. один
    }
    else {
        _end->PNext = newNode; //добавляемая нода встаёт в конец очереди
        _end = newNode;
    }
    _size++;
}

template<class T>
T Queue<T>::pop()
{
    T value = _head->Value;
    if (_head == _end) { //если очередь из одного элемента
        _head = _end = nullptr;
    }
    else { _head = _head->PNext; }
    _size--;
    return value;
}

template<class T>
T Queue<T>::first()
{
    return _head->Value;
}

template<class T>
T Queue<T>::last()
{
    return _end->Value;
}
