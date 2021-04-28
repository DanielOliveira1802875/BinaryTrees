#include <iostream>
#include <vector>

#include "BST.h"

int main()
{
    std::vector<int> testing;
    BST<int> tree;
    for (; testing.size() < 1023;)
    {
        int value = rand() % 2000;
        if (tree.addValue(value))
            testing.push_back(value);
    }

    tree.makeBackBone();
    tree.createPerfectTree();
    tree.print();
    for (int i = 0; i < testing.size(); ++i)
        if (!tree.removeValue(testing[i]))
            throw("Nodes nao batem certo");

    std::cout << "Hello 2244 World!\n";
}

