#include <iostream>
#include <sstream>

using namespace std;
vector<string> split(const string str, string delim) { // only gives the first two results
    size_t delim_pos;
    vector <string> strings;
    delim_pos = str.find(delim);
    strings.push_back(str.substr(0, delim_pos - 1));
    strings.push_back(str.substr(delim_pos + delim.length()));
    return strings;
}
