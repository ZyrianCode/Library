#pragma once
#include "Node.h"

/* Контейнер Stack */

template<class T>
class Stack
{
private:
    Node<T>* _head;
    int _size;
public:
    Stack();
    ~Stack();

    /// <summary>
    /// Возвращает размер стека
    /// </summary>
    /// <returns></returns>
    int size();

    /// <summary>
    /// Проверяет является ли стек пустым
    /// </summary>
    /// <returns></returns>
    bool is_empty();

    /// <summary>
    /// Добавляет элемент в стек
    /// </summary>
    /// <param name="value"></param>
    void push(T value);

    /// <summary>
    /// Очищает стек
    /// </summary>
    void clear();

    /// <summary>
    /// Убирает верхний элемент из стека
    /// </summary>
    /// <returns></returns>
    T pop();

    /// <summary>
    /// Позволяет посмотреть верхний элемент стека
    /// </summary>
    /// <returns></returns>
    T top();
};


