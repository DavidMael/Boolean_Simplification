#include <iostream>
#include "Kmap.hpp"

using namespace std;

int main()
{
    kmap testmap {1, 1, 0, 0, 1, 1, 1, 1};

    for(int i =  0; i<testmap.squares.size(); i++)
    {
        for(int j = 0; j<testmap.squares[1].size(); j++)
        {
            cout << i << ";" << j << " " << testmap.squares[i][j] << " ";
        }
        cout << endl;
    }

    cout << "horizontal doubs" << endl;  

    vector<doub> onedoubs = testmap.horizontaldoubs();

    for(int i = 0; i<onedoubs.size(); i++)
    {
        cout << onedoubs[i].sone.first << ";" << onedoubs[i].sone.second << " " << onedoubs[i].stwo.first << ";" << onedoubs[i].stwo.second << endl;
    }  

    cout << "vertical doubs" << endl;  

    vector<doub> onedoubsv = testmap.verticaldoubs();

    for(int i = 0; i<onedoubsv.size(); i++)
    {
        cout << onedoubsv[i].sone.first << ";" << onedoubsv[i].sone.second << " " << onedoubsv[i].stwo.first << ";" << onedoubsv[i].stwo.second << endl;
    }    
}