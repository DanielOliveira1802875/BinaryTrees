#pragma once
template<class T>
class BSTNode
{
public:
    T value;
    BSTNode<T>* left;
    BSTNode<T>* right;
    BSTNode(const T& value, BSTNode<T>* left = nullptr, BSTNode<T>* right = nullptr);
};

template <class T>
BSTNode<T>::BSTNode(const T& value, BSTNode<T>* left, BSTNode<T>* right)
{
    this->value = value;
    this->left = left;
    this->right = right;
}

