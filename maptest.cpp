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

    vector<bool> a(4, 0);

    vector<vector<bool>> b (4, a);

    cout<<b[0][0]<<" "<<b[0][1]<<" "<<b[0][2]<<" "<<b[0][3]<<" "<<b[1][0]<<" "<<b[1][1]<<" "<<b[1][2]<<" "<<b[1][3]<<" "
    <<b[2][0]<<" "<<b[2][1]<<" "<<b[2][2]<<" "<<b[2][3]<<" "<<b[3][0]<<" "<<b[3][1]<<" "<<b[3][2]<<" "<<b[3][3]<<endl;

}