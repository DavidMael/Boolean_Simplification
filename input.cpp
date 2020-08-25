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
    for(int i = 0; i<=string_s; i++)
    {
        //separates minterms, or the condition with a marker that the end of the expression has been reached
        if(boolean_expression[i] != '+' && i != string_s )
        {
            //add new variable to list
            if(vars.size() == 0)
            {
                vars.push_back( toupper(boolean_expression[i]) );
            } else {
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
            }

            minterm.push_back( boolean_expression[i] );

        } else {

            minterms.push_back(minterm);
            minterm.erase(minterm.begin(), minterm.end());

        }
    }

    cout<<"vars vector size: "<<vars.size()<<", variables: ";
    for(int i = 0; i<vars.size(); i++)
    {
        cout<<vars[i];
    }
    cout<<endl;

    cout<<"minterms:"<<endl;
    for(int i=0; i<minterms.size(); i++)
    {
        for(int j=0; j<minterms[i].size(); j++)
        {
            cout<<minterms[i][j];
        }
        cout<<endl;
    }

    cout<<endl;

    //set kmap parameters, temporary
    squares = {{a, b, c, d}, {e, f, g, h} };

    flags = {{0, 0, 0, 0}, {0, 0, 0, 0} };

    orphans = {{0, 0, 0, 0}, {0, 0, 0, 0} };

    height = squares.size();
    width = squares[0].size();

    //divide variables into row and column
    int halfpoint = vars.size()/2;
    //later change to set kmap members
    vector<char> row_vars;
    row_vars.assign( vars.begin(), vars.begin()+halfpoint );
    vector<char> column_vars;
    column_vars.assign( vars.begin()+halfpoint, vars.end() );
    /*/
    for(int i = 0; i<row_vars.size(); i++)
    {
        cout<<row_vars[i];
    }
    cout<<endl;
    for(int i = 0; i<column_vars.size(); i++)
    {
        cout<<column_vars[i];
    }
    cout<<endl;/*/

    //make vertical and horizontal gray vectors

    //create initial groups
    //cycle through each minterm
    for(int i = 0; i<minterms.size(); i++)
    {

    }
}