#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main() {

    /*/map<char, char> Map;

    Map['A'] = 'a';
    Map['B'] = 'b';

    cout<<Map['A']<<"|"<<Map['B']<<"|"<<Map['C']<<"|"<<Map['C']<<"|"<<endl;

    /*/

    string s = "string";
    char * p = &s[2];
    char c = s[2];


    cout<<s[2]<<endl;
    cout<<*p<<endl;
    cout<<p<<endl;
    cout<<c<<endl;
    
    cout<<endl;

    char a [6] = {'s', 't', 'r', 'i', 'n', 'g'};
    char * o = &a[2];
    char h = a[2];

    cout<<a[2]<<endl;
    cout<<*o<<endl;
    cout<<o<<endl;
    cout<<h<<endl;


}