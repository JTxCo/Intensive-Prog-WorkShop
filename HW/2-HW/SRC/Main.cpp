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
    // linear
    Linear<int> l;
    l.insertElement(1);
    cout<<"is 1 in the list: " << l.search(1) << endl;
    return 0;
}