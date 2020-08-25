#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<string> make_gray(int n)
{
    vector<string> gray = {"0", "1"};

    if(n>1)
    {
        vector<string> reflected;
        for(int i=1; i<n; i++)
        {
            //reflect gray code
            reflected.resize(gray.size());
            reverse_copy(gray.begin(), gray.end(), reflected.begin());
            //prefix original codes with 0 and reflected with 1
            for(int j=0; j<gray.size(); j++)
            {
                gray[j].insert(0, 1, '0');
                reflected[j].insert(0, 1, '1');
            }
            //add reflected to the end of gray
            gray.insert(gray.end(), reflected.begin(), reflected.end());
        }
        
    }

    return gray;
}

int main() {

    /*/map<char, int> Map;

    Map['A'] = 2;
    Map['B'] = 1;

    cout<<Map['A']<<" "<<Map['B']<<" "<<Map['C']<<" "<<Map['C']<<endl;

    int half = 5/2;

    cout<<half;/*/

    int n;

    cin>>n;

    vector<string> gray_n;
    gray_n = make_gray(n);

    for(int i=0; i<gray_n.size(); i++)
    {
        cout<<gray_n[i]<<" ";
    }

}