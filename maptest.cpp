#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main() {

    vector<int> test {0, 1, 2, 3, 4, 5, 6};

    for (int i=0; i<test.size(); i++)
    {
        cout<<test[i]<<" ";
    }
    cout<<endl;

    test.erase(test.begin() + 2);

    for (int i=0; i<test.size(); i++)
    {
        cout<<test[i]<<" ";
    }
    cout<<endl;
}