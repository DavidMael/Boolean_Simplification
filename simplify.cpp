#include "Kmap.hpp"

using namespace std;

string expr;

int main()
{
    cin>>expr;

    //build a kmap for the input Boolean expression
    kmap testmap (expr);

    /*/for(int i =  0; i<testmap.squares.size(); i++)
    {
        for(int j = 0; j<testmap.squares[1].size(); j++)
        {
            cerr <<'('<< i << ";" << j << ") " << testmap.squares[i][j] << " ";
        }
        cerr << endl;
    }/*/

    //gather the simplest horizontal pairings of 1s in the kmap
    testmap.horizontaldoubs();

    //cerr<<"horizontal doubs size: ";  

    //cerr<<testmap.groups.size()<<endl;

    //testmap.identify_orphans();

    //gather vertical pairs of 1s that are necessary or simplify the pairing
    testmap.verticaldoubs();

    //cerr<<"vertical 1 doubs size: ";    

    //cerr<<testmap.groups.size()<<endl;

    //testmap.identify_orphans();

    /*/for(int i = 0; i<testmap.groups.size(); i++)
    {
        cerr << testmap.groups[i].sone.first << ";" << testmap.groups[i].sone.second << " " << testmap.groups[i].stwo.first << ";" << testmap.groups[i].stwo.second <<" "<<testmap.groups[i].merged<<endl;
    } 

    cerr << "merged groups" << endl;/*/

    //merge groups into larger ones as is possible and improves the grouping of 1s (less and bigger groups)
    testmap.merge_function();

    /*/cerr<<"independant groups"<<endl;

    for(int i = 0; i<testmap.groups.size(); i++)
    {
        if(testmap.groups[i].merged == 0)
        {
            cerr << testmap.groups[i].sone.first << ";" << testmap.groups[i].sone.second << " " << testmap.groups[i].stwo.first << ";" << testmap.groups[i].stwo.second << endl;
        }
    }/*/ 

    //read and print minterms corresponding to (top level/non merge-flagged) groups 
    cout<<testmap.solve()<<endl;
}