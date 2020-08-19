#include "Kmap.hpp"

using namespace std;

//constructor
kmap::kmap(const string & boolean_expression)
{
    int string_s = boolean_expression.size();

    vector<char> vars;

    vector<vector<char>> minterms;

    vector<char> minterm;

    //cycle through the expression to list variables and minterms (do what with them?) 
    for(int i = 0; i<string_s; i++)
    {
        //separates minterms
        if(string_s(i) != '+')
        {
            //add new variable to list
            for(int j = 0; j<vars.size(); j++)
            {
                if(vars(j) == string_s(i))
                {
                    break;
                }

                vars.push_back(string_s(i));
            }


        } else {

        }
    }
}