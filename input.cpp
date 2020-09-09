#include "Kmap.hpp"

using namespace std;

//kmap constructor taking as argument an SOP boolean expression
kmap::kmap(const string & boolean_expression)
{
    int string_s = boolean_expression.size();

    //vector of variables (uppercase) contained in the argument boolean_expression
    vector<char> vars;
    //list of minterms found in the SOP argument
    vector<vector<char>> minterms;
    //accumulates a minterm to be pushed into minterms while boolean_expression is being interated through
    vector<char> minterm;

    //cycle through the expression to list variables and minterms
    for(int i = 0; i<=string_s; i++)
    {
        //if iteration has not reached a '+' or the end of the argument, the character pointed to is part of a minterm
        if(boolean_expression[i] != '+' && i != string_s )
        {
            //add new variables to list
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

            //push character (variable) into the minterm container
            minterm.push_back( boolean_expression[i] );

        //if the condition is not satisfied, we've reached the end of a minterm so push back and erase the container
        } else {

            minterms.push_back(minterm);
            minterm.erase(minterm.begin(), minterm.end());

        }
    }

    /*/cerr<<"vars vector size: "<<vars.size()<<", variables: ";
    for(int i = 0; i<vars.size(); i++)
    {
        cerr<<vars[i];
    }
    cerr<<endl;

    cerr<<"minterms:"<<endl;
    for(int i=0; i<minterms.size(); i++)
    {
        for(int j=0; j<minterms[i].size(); j++)
        {
            cerr<<minterms[i][j];
        }
        cerr<<endl;
    }

    cerr<<endl;/*/

    //divide variables into row and column
    int halfpoint = (vars.size()+1)/2;
    column_vars.assign( vars.begin(), vars.begin()+halfpoint );
    row_vars.assign( vars.begin()+halfpoint, vars.end() );

    /*/cerr<<"column vars: ";
    for( int i=0; i<column_vars.size(); i++ )
    {
        cerr<<column_vars[i]<<" ";
    }
    cerr<<endl;
    
    cerr<<"row vars: ";
    for( int i=0; i<row_vars.size(); i++ )
    {
        cerr<<row_vars[i]<<" ";
    }
    cerr<<endl;/*/

    //take length of rows and columns
    height = pow(2, row_vars.size());
    width = pow(2, column_vars.size());

    //create the "matrix" data members as zero matrices
    vector<bool> squares_row ( width , 0);
    vector<vector<bool>> sq ( height , squares_row);
    squares = sq;
    vector<vector<bool>> fl ( height , squares_row);
    flags = fl;
    vector<vector<bool>> orph ( height , squares_row);
    orphans = orph;

    //setup the pointer grid
    vector<int> grps (0);
    vector<vector<int>> vgrps ( width, grps );
    vector<vector<vector<int>>> vvv ( height, vgrps );
    grouppointers = vvv;

    //make vertical and horizontal gray vectors: generate grays then variable-bit map vectors 
    row_grays = make_gray( row_vars.size() );
    column_grays = make_gray( column_vars.size() );

    //create mappings from variables to gray code bits
    vector<map<char, char>> row_maps;
    row_maps = map_variables( row_vars, row_grays );  
    vector<map<char, char>> column_maps;
    column_maps = map_variables( column_vars, column_grays );

    //populate squares data member by determining columns and rows corresponding to a minterm
    //set to false if there is a mismatch between equivalent gray and minterm variables
    bool varok = true;
    //indicates that the lower value bound of the group has not been found
    bool mapmin = false;
    //containts rows corresponding to each minterm group
    vector<int> rows;

    //iterate through each minterm
    for(int i=0; i<minterms.size(); i++)
    {
        /*/cerr<<"----"<<endl;
        for(int j=0; j<minterms[i].size(); j++)
        {
            cerr<<minterms[i][j];
        }
        cerr<<endl;/*/
        //iterate through each row map
        for(int j=0; j<row_maps.size(); j++)
        {
            //for each minterm variable
            for(int k=0; k<minterms[i].size(); k++)
            {
                //if none have been found, check for mismatches between minterm and row variables
                if(varok == true)
                {
                    if( isupper(minterms[i][k]) && (row_maps[j][ toupper(minterms[i][k]) ] == '0') )
                    {
                        varok = false;
                        break;
                    } else if ( islower(minterms[i][k]) && (row_maps[j][ toupper(minterms[i][k]) ] == '1') ) {
                        varok = false;
                        break;
                    }
                }
            }

            //if the minterm corresponds to a row, save its position
            if(varok == true)
            {
                //cerr<<"OKed row: "<<j<<endl;
                rows.push_back(j);
            }
            varok = true;
        }
        //cerr<<"(saved) rows size: "<<rows.size()<<endl;

        //iterate through each column map
        for(int j=0; j<column_maps.size(); j++)
        {
            //for each minterm variable
            for(int k=0; k<minterms[i].size(); k++)
            {
                //if none have been found, check for mismatches between minterm and column variables
                if(varok == true)
                {
                    if( isupper(minterms[i][k]) && column_maps[j][ toupper(minterms[i][k]) ] == '0' )
                    {
                        varok = false;
                        break;
                    } else if ( islower(minterms[i][k]) && column_maps[j][ toupper(minterms[i][k]) ] == '1' ) {
                        varok = false;
                        break;
                    }
                }
            }

            //if a minterm corresponds to the row, write one in all squares in the column and the saved rows
            if(varok == true)
            {
                for(int k=0; k<rows.size(); k++)
                {
                    //cerr<<"write one in: row "<<rows[k]<<", column "<<j<<endl;
                    squares[ rows[k] ][j] = 1;
                }
            }
            varok = true;
        }

        //clear saved rows once the minterm has been processed
        rows.clear();
    }
}

//produces n bit gray codes using a recursive algorithm
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

//return a vector of mappings between variables and binary values to represent row/column gray code minterms
vector<map<char, char>> map_variables(const vector<char> & variables, const vector<string> & grays)
{
    //variables mapped to gray code bit, stored as a char to allow new values to be mapped to a space rather than 0
    map<char, char> varmap;
    vector<map<char, char>> mapvector;

    //for each gray code
    for(int i=0; i<grays.size(); i++ )
    {
        //for each variable, map to the corresponding binary value from the gray code
        for(int j=0; j<variables.size(); j++)
        {
            varmap[variables[j]] = grays[i][j];
        }
        //push_back the map once all variables in a minterm have been mapped 
        mapvector.push_back( varmap );
        varmap.erase( varmap.begin(), varmap.end() );
    }

    return mapvector;
}