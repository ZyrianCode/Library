#pragma once
#include "Node.h"

/*Контейнер Очередь*/

template<class T>
class Queue
{
private:
    Node<T>* _head; //начало очереди
    Node<T>* _end; //конец очереди
    int _size;

    void push(T value);
public:
    Queue();
    ~Queue();

    /// <summary>
    /// Добавляет элемент в очередь
    /// </summary>
    /// <param name="value"></param>
    void add(T value);

    /// <summary>
    /// Возвращает размер очереди
    /// </summary>
    /// <returns></returns>
    int size();

    /// <summary>
    /// Очищает очередь
    /// </summary>
    void clear();

    /// <summary>
    /// Проверяет является ли очередь пустой
    /// </summary>
    /// <returns></returns>
    bool is_empty();

    /// <summary>
    /// Удаляет элемент из очереди
    /// </summary>
    /// <returns></returns>
    T pop();

    /// <summary>
    /// Позволяет посмотреть первый элемент очереди без удаления
    /// </summary>
    /// <returns></returns>
    T first();

    /// <summary>
    /// Позволяет посмотреть последний элемент очереди
    /// </summary>
    /// <returns></returns>
    T last();
};
