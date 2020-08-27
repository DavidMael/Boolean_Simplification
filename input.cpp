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
    squares = {{0, 0, 0, 0}, {0, 0, 0, 0} };

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
    
    cout<<"row vars"<<endl;
    for(int i = 0; i<row_vars.size(); i++)
    {
        cout<<row_vars[i];
    }
    cout<<endl;
    cout<<"column vars"<<endl;
    for(int i = 0; i<column_vars.size(); i++)
    {
        cout<<column_vars[i];
    }
    cout<<endl;

    //make vertical and horizontal gray vectors: generate grays then variable-bit map vectors
    vector<string> row_grays;
    row_grays = make_gray( row_vars.size() );
    vector<string> column_grays;
    column_grays = make_gray( column_vars.size() );

    cout<<"grays check"<<endl;

    vector<map<char, char>> row_maps;
    row_maps = map_variables( row_vars, row_grays );  
    vector<map<char, char>> column_maps;
    column_maps = map_variables( column_vars, column_grays );

    cout<<"map check rows "<<row_maps.size()<<" "<<row_vars.size()<<endl;
    for(int i=0; i<row_maps.size(); i++)
    {
        for(int j=0; j<row_vars.size(); j++)
        {
            cout<<row_vars[j]<<" "<<row_maps[i][ row_vars[j] ]<<"| ";
        }
        cout<<endl;
    }
    
    cout<<"map check columns "<<column_maps.size()<<" "<<column_vars.size()<<endl;
    for(int i=0; i<column_maps.size(); i++)
    {
        for(int j=0; j<column_vars.size(); j++)
        {
            cout<<column_vars[j]<<" "<<column_maps[i][ column_vars[j] ]<<"| ";
        }
        cout<<endl;
    }

    //determine bounds of groups for each minterm
    //set to false if there is a mismatch between equivalent gray and minterm variables
    bool varok = true;
    //indicates that the lower value bound of the group has not been found
    bool mapmin = false;
    //containts lower and upper value bounds of each minterm group
    vector<int> rows(minterms.size());
    //vector<pair<int, int> columnbounds(minterms.size());
    //iterate through each minterm
    cout<<"relevant vector sizes: "<<minterms.size()<<" "<<row_maps.size()<<" "<<column_maps.size()<<endl;
    for(int i=0; i<minterms.size(); i++)
    {
        cout<<"----"<<endl;
        cout<<"minterms i="<<i<<endl;
        //iterate through each row map
        for(int j=0; j<row_maps.size(); j++)
        {
            cout<<"row_maps j="<<j<<endl;
            //for each minterm variable
            for(int k=0; k<minterms[i].size(); k++)
            {
                cout<<"minterm var k="<<k<<endl;
                if(varok == true)
                {
                    //cout<<"!: "<<minterms[i][k]<<" "<<islower(minterms[i][k])<<" "<<row_maps[j][ toupper(minterms[i][k])]<<endl;
                    if( isupper(minterms[i][k]) && (row_maps[j][ toupper(minterms[i][k]) ] == '0') )
                    {
                        cout<<"aaa"<<endl;
                        varok = false;
                        break;
                    } else if ( islower(minterms[i][k]) && (row_maps[j][ toupper(minterms[i][k]) ] == '1') ) {
                        cout<<"bbb"<<endl;
                        varok = false;
                        break;
                    }
                }
            }

            if(varok == true)
            {
                cout<<"OKed row: "<<j<<endl;
                rows.push_back(j);
            }
            varok = true;
        }
        cout<<"(saved) rows size: "<<rows.size()<<endl;

        //iterate through each column map
        for(int j=0; j<column_maps.size(); j++)
        {
            cout<<"column_maps j="<<j<<endl;
            //for each minterm variable
            for(int k=0; k<minterms[i].size(); k++)
            {
                cout<<"minterm var k="<<k<<endl;
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

            if(varok == true)
            {
                for(int k=0; k<rows.size(); k++)
                {
                    cout<<"write one in: row "<<rows[k]<<", column "<<j<<endl;
                    squares[ rows[k] ][j] = 1;
                }
            }
            varok = true;
        }

    }
}

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

vector<map<char, char>> map_variables(const vector<char> & variables, const vector<string> & grays)
{
    map<char, char> varmap;
    vector<map<char, char>> mapvector;

    //for each gray code
    for(int i=0; i<grays.size(); i++ )
    {
        //for each variable
        for(int j=0; j<variables.size(); j++)
        {
            varmap[variables[j]] = grays[i][j];
        }
        mapvector.push_back( varmap );
        varmap.erase( varmap.begin(), varmap.end() );
    }

    return mapvector;
}