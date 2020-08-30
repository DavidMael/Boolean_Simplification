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
            //print '+' before all minterms but the first
            if(first_minterm == false)
            {
                expression.append("+");
            } else {
                first_minterm = false;
            }

            cerr<<"group: "<<i<<endl;

            //first: determine the vertical/row variables of the minterm
            gray = vertical_gray[ groups[i].sone.first ];

            //iterate through vertical grays starting from the upper index of the group
            index = groups[i].sone.first;
            while(index != groups[i].stwo.first)
            {
                cerr<<"i index: "<<index<<endl;
                //iterate through the gray bits, recording changes in bit values with an 'x'
                for(int k = 0; k<gray.size(); k++)
                {
                    if(gray[k] != vertical_gray[index][k])
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
                if(gray[k] != vertical_gray[groups[i].stwo.first][k])
                {
                    gray[k] = 'x';
                }
            }

            //add variables to minterm as appropriate
            cerr<<"vertical gray: "<<gray<<endl;
            for(int j = 0; j<gray.size(); j++)
            {
                to_append = vertical_vars[j];
                if(gray[j] == '1')
                {
                    expression.append(to_append);
                }

                if(gray[j] == '0')
                {
                    expression.append("(~");
                    expression.append(to_append);
                    expression.append(")");
                }
            }

            //second: determine the horizontal/column variables of the minterm
            gray = horizontal_gray[ groups[i].sone.second ];

            //iterate through horizontal grays from the leftmost index of the group
            index = groups[i].sone.second;
            while(index != groups[i].stwo.second)
            {
                cerr<<"j index: "<<index<<endl;
                //iterate through the gray bits, recording changes in bit values with an 'x'
                for(int k = 0; k<gray.size(); k++)
                {
                    if(gray[k] != horizontal_gray[index][k])
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
                if(gray[k] != horizontal_gray[groups[i].stwo.second][k])
                {
                    gray[k] = 'x';
                }
            }

            //add variables to the minterm as appropriate
            cerr<<"horizontal gray: "<<gray<<endl;
            for(int j = 0; j<gray.size(); j++)
            {
                to_append = horizontal_vars[j];
                if(gray[j] == '1')
                {
                    cerr<<"expression before appending: "<<expression<<endl;
                    cerr<<"append the following: "<<to_append<<endl;
                    expression.append(to_append);
                    cerr<<"expression after appending: "<<expression<<endl;
                }

                if(gray[j] == '0')
                {
                    expression.append("(~");
                    expression.append(to_append);
                    expression.append(")");
                }
            }
        }
    }

    return expression;
}
