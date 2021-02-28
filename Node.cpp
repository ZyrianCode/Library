#include "pNode.h"

template<class T>
Node<T>::Node(T value, Node* pNext) {
    this->Value = value;
    this->PNext = pNext;
}
