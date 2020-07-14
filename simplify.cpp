#include <iostream>
#include "Kmap.hpp"

using namespace std;

int main()
{
    kmap testmap {0, 1, 0, 0, 1, 0, 1, 1};

    for(int i =  0; i<testmap.squares.size(); i++)
    {
        for(int j = 0; j<testmap.squares[1].size(); j++)
        {
            cout << i << ";" << j << " " << testmap.squares[i][j] << " ";
        }
        cout << endl;
    }

    cout << "horizontal doubs" << endl;  

    testmap.horizontaldoubs();

    cout << "vertical doubs" << endl;  

    testmap.verticaldoubs();

    for(int i = 0; i<testmap.groups.size(); i++)
    {
        cout << testmap.groups[i].sone.first << ";" << testmap.groups[i].sone.second << " " << testmap.groups[i].stwo.first << ";" << testmap.groups[i].stwo.second << endl;
    }   

    testmap.identify_orphans();

    cout << "quads" << endl;

    int length = testmap.squares.size();
    int width = testmap.squares[0].size();

    testmap.mergegroups(width, length);

    for(int i = 0; i<testmap.groups.size(); i++)
    {
        if(testmap.groups[i].n == 4)
        {
            cout << testmap.groups[i].sone.first << ";" << testmap.groups[i].sone.second << " " << testmap.groups[i].stwo.first << ";" << testmap.groups[i].stwo.second << endl;
        }
    } 
}