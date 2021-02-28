#include "pList.h"
#include <string>
#include <stdexcept>


template<class T>
List<T>::List()
{
    _head = nullptr;
    _size = 0;
}

template<class T>
List<T>::~List()
{
    clear();
}

template<class T>
int List<T>::size()
{
    return _size;
}

template<class T>
bool List<T>::is_empty()
{
    return _size == 0;
}

template<class T>
void List<T>::clear()
{
    while (_size)
    {
        pop_front();
    }
}

template<class T>
void List<T>::pop_front()
{
    if (_size <= 0) return;
    Node<T>* current = _head;
    _head = _head->PNext;
    delete current;
    _size--;
}

template<class T>
void List<T>::pop_back()
{
    remove_at(_size - 1);
}

template<class T>
void List<T>::push_front(T value)
{
    _head = new Node<T>(value, _head);
    _size++;
}

template<class T>
void List<T>::push_back(T value)
{
    if (_head == nullptr) {
        _head = _end = new Node<T>(value, nullptr);
    }
    else {
        Node<T>* current = this->_head;
        while (current->PNext != nullptr)
        {
            current = current->PNext;
        }
        current->PNext = new Node<T>(value);
    }
    _size++;
}

template<class T>
void List<T>::place_after(Node<T>* index, T value)
{
    Node<T>* current = index;
    Node<T>* newNode = new Node<T>(value, current->PNext);
    current->PNext = newNode;
    _size++;
}

template<class T>
void List<T>::place_after(T _index, T value)
{
    if (_index < 0) { invalid_index(); }
    else if (_index > _size) {
        _index = _size + 1;
        push_back(value);
    }
    else {
        if (_index == _size - 1) { push_back(value); }
        else {
            Node<T>* current = this->_head;
            auto prevIndex = _index - 1;
            for (auto i = 0; i <= prevIndex; i++)
            {
                current = current->PNext;
            }
            Node<T>* newNode = new Node<T>(value, current->PNext);
            current->PNext = newNode;
            _size++;
        }
    }
}


template<class T>
void List<T>::remove_after(Node<T>* index)
{
    Node<T>* removableNode = index->PNext;
    index->PNext = removableNode->PNext;
    removableNode->PNext = nullptr;
    if (removableNode == _end) {
        _end = index;
    }
    else if (removableNode == _head) { _head = index; }
    else if (index == _head) { invalid_index(); }
    _size--;
}

template<class T>
void List<T>::remove_after(T _index)
{
    auto current_pos = _index + 1;
    auto list_size = size();
    if (_index > _size || _index < 0) { invalid_index(); }
    else {
        Node<T>* current = this->_head; //где сейчас находимся (нужно для проверки следующего элемента)
        Node<T>* prev = this->_head;
        for (auto i = 0; i < current_pos - 1; i++) //находим предыдущий элемент
        {
            prev = prev->PNext; //перемещаем адрес в предыдущий элемент
        }
        for (current_pos; current_pos < list_size; current_pos++)
        {
            Node<T>* removableNode = prev->PNext; //храним адрес старого элемента на который указывал предыдущий элемент
            prev->PNext = removableNode->PNext; //соединяем предыдущий элемент с последующим
            delete removableNode;
            _size--;
        }
    }
}

template<class T>
void List<T>::remove_at(Node<T>* index)
{
    Node<T>* current = this->_head;
    while (current < index)
    {
        current = current->PNext;
    }

    if (current != nullptr) {
        Node<T>* removableNode = current; //храним адрес старого элемента на который указывал предыдущий элемент
        current->PNext = removableNode->PNext; //соединяем предыдущий элемент с последующим
        delete removableNode;
        _size--;
    }
    else {
        if (_head == _end) {
            _head = _end = nullptr;
            _size--;
        }
        else {
            remove_after(find_prev(index));
        }
    }
}

template<class T>
void List<T>::remove_at(T _index)
{
    if (_index < 0) { invalid_index(); }
    else if (_index >= _size) {
        while (_index >= _size)
        {
            _index = _size - 1;
        }
        remove(_index);
        return;
    }
    else if (_index == 0) { pop_front(); }
    else {
        remove(_index);
    }
}

template<class T>
Node<T>* List<T>::find(T value)
{
    Node<T>* ptr = this->_head;
    while (ptr != nullptr)
    {
        if (ptr->Value == value) return ptr;
        else ptr = ptr->PNext;
    }
}

template<class T>
Node<T>* List<T>::find_prev(Node<T>* index)
{
    Node<T>* prev = nullptr;
    Node<T>* current = _head;
    //добавить искл. для поиска предыдущего головы
    while (current != nullptr) {
        prev = current;
        current = current->PNext;
    }
    return prev;
}

template<class T>
Node<T>* List<T>::first()
{
    return _head;
}

template<class T>
Node<T>* List<T>::last()
{
    return _end;
}

template<class T>
T& List<T>::operator[](const T index)
{
    //начинаем с head. И если значение счётчика совпадает с индексом, который мы получили, то мы возвращаем данные
    if (index > _size - 1 || index < 0) { invalid_index(); }
    auto current_pos = 0;
    Node<T>* current = this->_head; //где сейчас находимся (нужно для проверки следующего элемента)
    while (current != nullptr) //пока указатель не станет равен null
    {
        if (current_pos == index) {
            return current->Value; //если текущая позиция совпала с входящим индексом, возвращаем данные по индексу
        }
        current = current->PNext; //присваиваем текущему эл.адрес следующего, для этого у текущего элемента спрашиваем адрес следующего
        current_pos++;
    }
}

template<class T>
void List<T>::invalid_index()
{
    string message = "Недопустимый индекс ";
    message.append(to_string((int)index));
    throw out_of_range(message);
}

template<class T>
void List<T>::remove(T _index)
{
    Node<T>* prev = this->_head;
    for (auto i = 0; i < _index - 1; i++)
    {
        prev = prev->PNext; //перемещаем адрес в предыдущий элемент
    }
    Node<T>* removableNode = prev->PNext; //храним адрес старого элемента на который указывал предыдущий элемент
    prev->PNext = removableNode->PNext; //соединяем предыдущий элемент с последующим
    delete removableNode;
    _size--;
}

template<class T>
bool List<T>::compare(const T& val1, const T& val2)
{
    if (less<T>() (val1, val2)) { return 0; }
    return 1;
}
