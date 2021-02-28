#pragma once
#pragma once
#include "Node.h"

using namespace std;

/* Контейнер Односвязный список */

template<class T>
class List
{
private:

    Node<T>* _head;
    Node<T>* _end;
    Node<T>* index;
    int _size;
    T _index;

public:
    List();
    ~List();
    /// <summary>
    /// Определяет размер списка
    /// </summary>
    /// <returns></returns>
    int size();

    /// <summary>
    /// Проверяет является ли список пустым.
    /// </summary>
    /// <returns></returns>
    bool is_empty();

    /// <summary>
    /// Очищает элементы списка
    /// </summary>
    void clear();

    /// <summary>
    /// Удаляет передний элемент списка
    /// </summary>
    void pop_front();

    /// <summary>
    /// Удаляет последний элемент списка
    /// </summary>
    void pop_back();

    /// <summary>
    /// Добавляет элементы в начало списка
    /// </summary>
    /// <param name="value"></param>
    void push_front(T value);

    /// <summary>
    /// Добавляет элементы в конец списка
    /// </summary>
    /// <param name="value"></param>
    void push_back(T value);

    /// <summary>
    /// Добавляет элемент после указанного узла
    /// </summary>
    /// <param name="index"></param>
    /// <param name="value"></param>
    void place_after(Node<T>* index, T value);

    /// <summary>
    /// Добавляет элемент после указанного индекса
    /// </summary>
    /// <param name="index"></param>
    /// <param name="value"></param>
    void place_after(T index, T value);

    /// <summary>
    /// Удаляет элемент после указанного узла
    /// </summary>
    /// <param name="index"></param>
    void remove_after(Node<T>* index);

    /// <summary>
    /// Удаляет элемент после указанного индекса
    /// </summary>
    /// <param name="index"></param>
    void remove_after(T index);

    /// <summary>
    /// Удаляет элемент по указанному узлу
    /// </summary>
    /// <param name="index"></param>
    void remove_at(Node<T>* index);

    /// <summary>
    /// Удаляет элемент по указанному индексу
    /// </summary>
    /// <param name="_index"></param>
    void remove_at(T _index);

    /// <summary>
    /// Находит элемент
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    Node<T>* find(T value);

    /// <summary>
    /// Находит узел
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    Node<T>* find_prev(Node<T>* index);

    /// <summary>
    /// Возвращает адрес начального элемента
    /// </summary>
    /// <returns></returns>
    Node<T>* first();

    /// <summary>
    /// Возвращает адрес конечного элемента
    /// </summary>
    /// <returns></returns>
    Node<T>* last();
    T& operator[](const T index);
private:
    void invalid_index();
    void remove(T _index);
    bool compare(const T& val1, const T& val2);
};

