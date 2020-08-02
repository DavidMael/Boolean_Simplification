#include <iostream>
#include "Kmap.hpp"

using namespace std;

int main()
{
    kmap testmap {1, 0, 0, 0, 0, 1, 1, 1};

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

    testmap.identify_orphans();

    cout << "vertical doubs" << endl;  

    testmap.verticaldoubs();  

    for(int i = 0; i<testmap.groups.size(); i++)
    {
        cout << testmap.groups[i].sone.first << ";" << testmap.groups[i].sone.second << " " << testmap.groups[i].stwo.first << ";" << testmap.groups[i].stwo.second <<" "<<testmap.groups[i].merged<<endl;
    } 

    testmap.identify_orphans();

    cout << "quads" << endl;

    testmap.mergegroups(4);

    for(int i = 0; i<testmap.groups.size(); i++)
    {
        if(testmap.groups[i].n == 4)
        {
            cout << testmap.groups[i].sone.first << ";" << testmap.groups[i].sone.second << " " << testmap.groups[i].stwo.first << ";" << testmap.groups[i].stwo.second<<" "<<testmap.groups[i].merged << endl;
        }
    } 

    cout<<"independant groups"<<endl;

        for(int i = 0; i<testmap.groups.size(); i++)
    {
        if(testmap.groups[i].merged == 0)
        {
            cout << testmap.groups[i].sone.first << ";" << testmap.groups[i].sone.second << " " << testmap.groups[i].stwo.first << ";" << testmap.groups[i].stwo.second << endl;
        }
    } 
}