#include <iostream>
#include "bTree.h"

int main()
{
    BinarySearchTree<int> tree;
    std::cout << "Elements in the tree: " << tree.getCount() << '\n';
  
    std::cout << "Filling the tree..." << '\n';
    tree.insert(5);
    tree.insert(7);
    tree.insert(10);
    tree.insert(3);
    tree.insert(4);
    tree.insert(6);
    tree.insert(11);
    
    tree.print(std::cout);

    std::cout << '\n' << "Is 13 in the tree: " << tree.iterativeSearch(13) << '\n';
    std::cout << "Is 7 in the tree: " << tree.iterativeSearch(7) << '\n';

    tree.deleteKey(5);
    tree.deleteKey(7);
    tree.deleteKey(11);
    
    tree.print(std::cout);

    std::cout << "Tree height: " << tree.getHeight() << '\n';

    tree.inorderWalk();
    std::cout << '\n';
    tree.iterativeInorderWalk();
    std::cout << '\n';
    tree.walkByLevels();
    std::cout << '\n';

    std::cout << "Creating a copy of tree in tree1 " << '\n';
    BinarySearchTree<int> tree1;
    tree1.insert(3);
    tree1.insert(4);
    tree1.insert(6);
    tree1.insert(10);
    
    std::cout << "Tree and tree1 are similar: " << tree.isSimilar(tree1) << '\n';
    std::cout << "Tree and tree1 have identical key: " << tree.isIdenticalKey(tree1) << '\n';

    std::cout << "Adding 9 to the tree1..." << '\n';
    tree1.insert(9);

    std::cout << "Tree and tree1 are similar: " << tree.isSimilar(tree1) << '\n';
    std::cout << "Tree and tree1 have identical key: " << tree.isIdenticalKey(tree1) << '\n';

    tree.~BinarySearchTree();
    tree1.~BinarySearchTree();

    return 0;

}