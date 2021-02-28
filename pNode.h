#pragma once
/*Узел для контейнеров*/

template<class T>
class Node
{
public:
    T Value;
    Node* PNext;
    Node(T value = T(), Node* pNext = nullptr);

};
