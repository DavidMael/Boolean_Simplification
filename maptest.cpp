#include <iostream>
#include <map>

using namespace std;

int main() {

    map<char, int> Map;

    Map['A'] = 2;
    Map['B'] = 1;

    cout<<Map['A']<<" "<<Map['B']<<" "<<Map['C']<<" "<<Map['C']<<endl;

    int half = 5/2;

    cout<<half;

}