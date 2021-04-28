#pragma once
#include <iomanip>

#include "BSTNode.h"
#include "DLList.h"
#include <string>

template <class T>
class BST
{
    BSTNode<T>* root;
    int size;
    void removeNodeFromTree(BSTNode<T>*& node);
    void printRec(BSTNode<T>* node, int indent);
public:

    BST();
    ~BST();
    void rotateRight(BSTNode<T>* grandParent, BSTNode<T>* parent, BSTNode<T>* leftChild);
    void rotateLeft(BSTNode<T>* grandParent, BSTNode<T>* parent, BSTNode<T>* rightChild);
    void createPerfectTree();
    void print();
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
void BST<T>::rotateRight(BSTNode<T>* grandParent, BSTNode<T>* parent, BSTNode<T>* leftChild)
{
    if (parent != root)
        grandParent->right = leftChild;
    else root = leftChild;
    parent->left = leftChild->right;
    leftChild->right = parent;
}

template <class T>
void BST<T>::rotateLeft(BSTNode<T>* grandParent, BSTNode<T>* parent, BSTNode<T>* rightChild)
{
    if (parent != root)
        grandParent->right = rightChild;
    else root = rightChild;
    parent->right = rightChild->left;
    rightChild->left = parent;
}

template <class T>
void BST<T>::createPerfectTree()
{
    BSTNode<T>* grandParent = nullptr;
    BSTNode<T>* parent = root;
    BSTNode<T>* rightChild = nullptr;
    int m = pow(2, floor(log2(size + 1))) - 1;

    for (int i = m; i < size && parent != nullptr; ++i)
    {
        rightChild = parent->right;
        rotateLeft(grandParent, parent, rightChild);
        grandParent = rightChild;
        parent = grandParent->right;
    }    
    while (m > 1)
    {
        grandParent = nullptr;
        parent = root;
        rightChild = nullptr;
        m = m / 2;
        for (int i = 0; i < m && parent != nullptr; ++i)
        {
            rightChild = parent->right;
            rotateLeft(grandParent, parent, rightChild);
            grandParent = rightChild;
            parent = grandParent->right;
        }
    }
}

template <class T>
void BST<T>::print()
{
    printRec(root, 0);
}

template<class T>
void  BST<T>::printRec(BSTNode<T>* node, int indent)
{
    
    if (node != nullptr) 
    {
        
        if (node->right) {
            printRec(node->right, indent + 4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (node->right) std::cout << " /\n" << std::setw(indent) << ' ';
        std::cout << node->value << "\n ";
        if (node->left) {
            std::cout << std::setw(indent) << ' ' << " \\\n";
            printRec(node->left, indent + 4);
        }
    }
}



template <class T>
void BST<T>::makeBackBone()
{
    if (root == nullptr)
        throw("Error in BST<T>::makeBackBone(): root node is null");
    BSTNode<T>* grandParent = nullptr;
    BSTNode<T>* parent = root;
    BSTNode<T>* leftChild = nullptr;
    while (parent != nullptr)
    {
        leftChild = parent->left;
        if(leftChild != nullptr)
        {
            rotateRight(grandParent, parent, leftChild);
            parent = leftChild;           
        }
        else
        {
            grandParent = parent;
            parent = parent->right;            
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
