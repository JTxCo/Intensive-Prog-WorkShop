#include "HashMap.hpp"
#include "Tree.hpp"
#include "Linear.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <iostream>

using std::cout;
using std::endl;

int main(){
    // Tree
    Tree<int> tree(5);
    tree.insertElement(tree.getRoot(), 3);
    tree.insertElement(tree.getRoot(), 7);
    tree.insertElement(tree.getRoot(), 2);
    cout<< tree<<endl;
}