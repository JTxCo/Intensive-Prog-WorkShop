#ifndef FUNCTIONS_TO_IMPLEMENT_H
#define FUNCTIONS_TO_IMPLEMENT_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::string;
using std::stringstream;


vector<string> Split(string whole, string separator);
vector<int> MatchVectors(vector<int> a, const vector<int>& b);
vector<int> MultiplesFilter(vector<int> v, int n);

#endif // FUNCTIONS_TO_IMPLEMENT_H