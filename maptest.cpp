#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main() {

    map<char, char> Map;

    Map['A'] = 'a';
    Map['B'] = 'b';

    cout<<Map['A']<<"|"<<Map['B']<<"|"<<Map['C']<<"|"<<Map['C']<<"|"<<endl;

    /*/

    vector<bool> a(4, 0);

    vector<vector<bool>> b (4, a);

    cout<<b[0][0]<<" "<<b[0][1]<<" "<<b[0][2]<<" "<<b[0][3]<<" "<<b[1][0]<<" "<<b[1][1]<<" "<<b[1][2]<<" "<<b[1][3]<<" "
    <<b[2][0]<<" "<<b[2][1]<<" "<<b[2][2]<<" "<<b[2][3]<<" "<<b[3][0]<<" "<<b[3][1]<<" "<<b[3][2]<<" "<<b[3][3]<<endl;/*/

    (abc)+(abCd)+(Bcd)+(Abcd)+(ABC)+(AbC)

    0;0 1 0;1 1 0;2 0 0;3 1
    1;0 1 1;1 0 1;2 0 1;3 0
    2;0 1 2;1 0 2;2 1 2;3 1
    3;0 1 3;1 0 3;2 1 3;3 1

    (~A)(~B)(~C)+AC+!A(~D)!+(~B)(~D)+(~C)(~D)

    0;0 0;1
    2;2 3;3
    2;3 3;0
    3;3 0;0
    0;0 3;0

    --

    (cdAb)+(Bcd)+(abc)+(abCd)+(ABC)+(AbC)

    (0;0) 1 (0;1) 1 (0;2) 1 (0;3) 1
    (1;0) 1 (1;1) 0 (1;2) 0 (1;3) 0
    (2;0) 0 (2;1) 0 (2;2) 1 (2;3) 1
    (3;0) 1 (3;1) 0 (3;2) 1 (3;3) 1

    (~C)(~A)(~B)+(~C)(~D)+CA+(~D)(~B)

    0;0 1;0
    0;0 0;3
    2;2 3;3
    3;3 0;0

            //pointers to doubles that include equivalent position in "squares" above
        vector<vector<vector<group>>> grouppointers;

}