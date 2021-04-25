#pragma once
#include "BSTNode.h"
#include "DLList.h"
#include <string>

template <class T>
class BST
{
    BSTNode<T>* root;
    int size;
    void removeNodeFromTree(BSTNode<T>*& node);
public:

    BST();
    ~BST();
    void rotateRight(BSTNode<T>* grandParent, BSTNode<T>* parent, BSTNode<T>* child);
    void createPerfectTree();
    void makeBackBone();
    bool addValue(T value);
    bool removeValue(T value);
};

template <class T>
BST<T>::BST()
{
    this->root = nullptr;
    size = 0;
}

template <class T>
BST<T>::~BST()
{
}

template <class T>
void BST<T>::rotateRight(BSTNode<T>* grandParent, BSTNode<T>* parent, BSTNode<T>* child)
{
    if (grandParent != nullptr)
        grandParent->left = child;
    parent->left = child->right;
    child->right = parent;
}

template <class T>
void BST<T>::createPerfectTree()
{
    int m = pow(2, log2(size + 1) - 1);
    while (m > 1)
    {
        m = m / 2;
    }
}

template <class T>
void BST<T>::makeBackBone()
{
    BSTNode<T>* tmp = root;
    BSTNode<T>* aux = nullptr;
    BSTNode<T>* prev = nullptr;
    while (tmp != nullptr)
    {
        if (tmp->left != nullptr)
        {
            aux = tmp->left;
            tmp->left = aux->right;
            aux->right = tmp;
            if (prev != nullptr)
                prev->right = aux;
            else
                root = aux;
            tmp = aux;
        }
        else
        {
            prev = tmp;
            tmp = tmp->right;
        }
    }
}

template <class T>
bool BST<T>::addValue(T value)
{
    if (root == nullptr)
    {
        root = new BSTNode<T>(value);
        ++size;
        return true;
    }
    BSTNode<T>* prev = nullptr;
    BSTNode<T>* tmp = root;
    while (tmp != nullptr)
    {
        prev = tmp;
        if (value < tmp->value)
        {
            tmp = tmp->left;
            continue;
        }
        if (value > tmp->value)
        {
            tmp = tmp->right;
            continue;
        }
        // valor ja existe
        return false;
    }
    if (value < prev->value)
        prev->left = new BSTNode<T>(value);
    else
        prev->right = new BSTNode<T>(value);
    ++size;
    return true;
}

template <class T>
bool BST<T>::removeValue(T value)
{
    BSTNode<T>* prev = nullptr;
    BSTNode<T>* tmp = root;
    while (tmp != nullptr)
    {
        if (tmp->value == value)
            break;
        prev = tmp;
        if (value < tmp->value)
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }
    if (tmp == nullptr)
        return false;
    if (tmp == root)
        removeNodeFromTree(root);
    else if (prev->left == tmp)
        removeNodeFromTree(prev->left);
    else
        removeNodeFromTree(prev->right);
    --size;
    return true;
}


template <class T>
void BST<T>::removeNodeFromTree(BSTNode<T>*& node)
{
    if (node == nullptr)
        return;
    BSTNode<T>* tmp = node;
    if (node->right == nullptr)
    {
        node = node->left;
        delete tmp;
        return;
    }
    if (node->left == nullptr)
    {
        node = node->right;
        delete tmp;
        return;
    }
    // tem dois filhos, deleteByMerging
    tmp = node->left;
    while (tmp->right != nullptr)
        tmp = tmp->right;
    tmp->right = node->right;
    tmp = node;
    node = node->left;
    delete tmp;
}
