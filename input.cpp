#include "Kmap.hpp"

using namespace std;

//constructor
kmap::kmap(bool a,bool b,bool c,bool d, bool e, bool f, bool g, bool h, const string & boolean_expression)
{
    int string_s = boolean_expression.size();

    vector<char> vars;

    vector<vector<char>> minterms;

    vector<char> minterm;

    //cycle through the expression to list variables and minterms (do what with them?) 
    for(int i = 0; i<string_s; i++)
    {
        //separates minterms, or the condition with a marker that the end of the expression has been reached
        if(boolean_expression[i] != '+')
        {
            //add new variable to list
            for(int j = 0; j<vars.size(); j++)
            {
                if(vars[j] == toupper(boolean_expression[i]) )
                {
                    break;
                }

                if(j == (vars.size()-1) )
                {
                    vars.push_back( toupper(boolean_expression[i]) );
                }
            }

        } else {

        }
    }

    cout<<"vars vector size: "<<vars.size();
    for(int i = 0; i<vars.size(); i++)
    {
        cout<<vars[i];
    }
    cout<<endl;

    squares = {{a, b, c, d}, {e, f, g, h} };

    flags = {{0, 0, 0, 0}, {0, 0, 0, 0} };

    orphans = {{0, 0, 0, 0}, {0, 0, 0, 0} };

    height = squares.size();
    width = squares[0].size();
}