#include <iostream>
#include <vector>

#include "BST.h"

int main()
{
    std::vector<int> testing;
    BST<int> tree;
    for (int i = 0; i < 5; ++i)
    {
        int value = /*rand() % 1000 - 500*/5-i;
        if (tree.addValue(value))
            testing.push_back(value);
    }

    tree.makeBackBone();
    for (int i = 0; i < testing.size(); ++i)
        tree.removeValue(testing[i]);

    std::cout << "Hello 2244 World!\n";
}

