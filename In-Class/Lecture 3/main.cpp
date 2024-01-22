#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::string;
using std::stringstream;

#include "functions_to_implement.h"


int main(){
    string whole = "hello world";
    string separator = " ";
    vector<string> res = Split(whole, separator);
    for (int i = 0; i < res.size(); i++){
        std::cout << res[i] << std::endl;
    }


    //test 2 
    vector<int> a = {1,2,3,4,5,6,7,8,9};
    const vector<int> b = {1,3,5,7,9};

    vector<int> c = MatchVectors(a,b);
    for (int i = 0; i < c.size(); i++){
        std::cout << c[i] << std::endl;
    }


    //test 3
    // vector <int> d = {1,2,3,4,5,6,7,8,9};
    // d = MultiplesFilter(d, 3);
    // for (int i = 0; i < d.size(); i++){
    //     std::cout << d[i] << std::endl;
    // }
}


