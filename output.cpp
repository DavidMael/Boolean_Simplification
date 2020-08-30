#include "Kmap.hpp"

using namespace std;

//output the simplified expression
string kmap::solve()
{
    //store gray code of terms for one side of the table, with 'x' signifying "don't use"
    //eg. a group spanning 100 and 110 has a gray of 1x0
    string gray;

    //store the simplified expression
    string expression;

    //used to cycle through the gray codes while accounting for wrap-around
    int index;

    //contains the variable to add to the expression
    string to_append;

    bool first_minterm = true;

    //iterate through each group
    for(int i = 0; i<groups.size(); i++)
    {
        //only give minterms from non merge-flagged groups
        if(groups[i].merged == false)
        {
            //return 1 if a group occupies the entire Kmap
            if( groups[i].sone.first == 0 && groups[i].sone.second == 0 &&
                groups[i].stwo.first == (height-1) && groups[i].stwo.second == (width-1) )
            {
                return "1";
            }

            //print '+' before all minterms but the first
            if(first_minterm == false)
            {
                expression.append("+");
            } else {
                first_minterm = false;
            }

            cerr<<"group: "<<i<<endl;

            //first: determine the horizontal/column variables of the minterm
            gray = column_grays[ groups[i].sone.second ];

            //iterate through horizontal grays from the leftmost index of the group
            index = groups[i].sone.second;
            while(index != groups[i].stwo.second)
            {
                cerr<<"j index: "<<index<<endl;
                //iterate through the gray bits, recording changes in bit values with an 'x'
                for(int k = 0; k<gray.size(); k++)
                {
                    if(gray[k] != column_grays[index][k])
                    {
                        gray[k] = 'x';
                    }
                }
                index = next_right(index);
            }
            //manually add a cycle for the last column
            cerr<<"j index: "<<groups[i].stwo.second<<endl;
            for(int k = 0; k<gray.size(); k++)
            {
                if(gray[k] != column_grays[groups[i].stwo.second][k])
                {
                    gray[k] = 'x';
                }
            }

            //add variables to the minterm as appropriate
            cerr<<"horizontal gray: "<<gray<<endl;
            for(int j = 0; j<gray.size(); j++)
            {
                //to_append = horizontal_vars[j];
                if(gray[j] == '1')
                {
                    to_append = column_vars[j];
                    //cerr<<"expression before appending: "<<expression<<endl;
                    //cerr<<"append the following: "<<to_append<<endl;
                    expression.append(to_append);
                    //cerr<<"expression after appending: "<<expression<<endl;
                }

                if(gray[j] == '0')
                {
                    to_append = tolower(column_vars[j]);
                    //expression.append("(~");
                    expression.append(to_append);
                    //expression.append(")");
                }
            }

            //second: determine the vertical/row variables of the minterm
            gray = row_grays[ groups[i].sone.first ];

            //iterate through vertical grays starting from the upper index of the group
            index = groups[i].sone.first;
            while(index != groups[i].stwo.first)
            {
                cerr<<"i index: "<<index<<endl;
                //iterate through the gray bits, recording changes in bit values with an 'x'
                for(int k = 0; k<gray.size(); k++)
                {
                    if(gray[k] != row_grays[index][k])
                    {
                        gray[k] = 'x';
                    }
                }
                index = next_below(index);
            }
            //manually add a cycle for the last row
            cerr<<"i index: "<<groups[i].stwo.first<<endl;
            for(int k = 0; k<gray.size(); k++)
            {
                if(gray[k] != row_grays[groups[i].stwo.first][k])
                {
                    gray[k] = 'x';
                }
            }

            //add variables to minterm as appropriate
            cerr<<"vertical gray: "<<gray<<endl;
            for(int j = 0; j<gray.size(); j++)
            {
                //to_append = vertical_vars[j];
                if(gray[j] == '1')
                {
                    to_append = row_vars[j];
                    //cerr<<"expression before appending: "<<expression<<endl;
                    //cerr<<"append the following: "<<to_append<<endl;
                    expression.append(to_append);
                    //cerr<<"expression after appending: "<<expression<<endl;
                }

                if(gray[j] == '0')
                {
                    to_append = tolower(row_vars[j]);
                    //expression.append("(~");
                    expression.append(to_append);
                    //expression.append(")");
                }
            }

        }
    }

    //add minterms from orphans !!might want to add a mechanism signalling if there are variables at all/a better storage system!!
    for(int i=0; i<orphans.size(); i++)
    {
        for(int j=0; j<orphans[i].size(); j++)
        {
            if( orphans[i][j] == 1 )
            {
                if(first_minterm == false)
                {
                    expression.append("+");
                } else {
                    first_minterm = false;
                }

                //horizontal/column vars
                gray = column_grays[ j ];
                for(int k = 0; k<gray.size(); k++)
                {
                    //to_append = horizontal_vars[j];
                    if(gray[k] == '1')
                    {
                        to_append = column_vars[k];
                        expression.append(to_append);
                    }

                    if(gray[k] == '0')
                    {
                        to_append = tolower(column_vars[k]);
                        //expression.append("(~");
                        expression.append(to_append);
                        //expression.append(")");
                    }
                }

                //vertical/row vars
                gray = row_grays[ i ];
                for(int k = 0; k<gray.size(); k++)
                {
                    //to_append = vertical_vars[j];
                    if(gray[k] == '1')
                    {
                        to_append = row_vars[k];
                        expression.append(to_append);
                    }

                    if(gray[k] == '0')
                    {
                        to_append = tolower(row_vars[k]);
                        //expression.append("(~");
                        expression.append(to_append);
                        //expression.append(")");
                    }
                }               
            }
        }
    }

    return expression;
}
