#include "Kmap.hpp"

using namespace std;

//output the simplified expression
string kmap::solve()
{
    //store gray code of terms for one side of the table, with 2 signifying "don't use"
    //eg. a group spanning 100 and 110 has a gray of 120
    string gray;

    //store the simplified expression
    string expression;

    //used to cycle through the gray codes while accounting for wrap-around
    int index;

    string to_append ;

    bool first_minterm = true;

    for(int i = 0; i<groups.size(); i++)
    {
        if(groups[i].merged == false)
        {

            if(first_minterm == false)
            {
                expression.append("+");
            } else {
                first_minterm = false;
            }

            cerr<<"group: "<<i<<endl;

            gray = vertical_gray[ groups[i].sone.first ];

            index = groups[i].sone.first;

            //what about 1-width groups? while loop skipped? change index initialization
            while(index != groups[i].stwo.first)
            {
                cerr<<"i index: "<<index<<endl;
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

            //printing the minterm
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

            gray = horizontal_gray[ groups[i].sone.second ];

            index = groups[i].sone.second;

            //cout<<"debug "<<index<<" "<<groups[i].stwo.second<<" "<<next_right(groups[i].stwo.second)<<endl;

            while(index != groups[i].stwo.second)
            {
                cerr<<"j index: "<<index<<endl;
                for(int k = 0; k<gray.size(); k++)
                {
                    if(gray[k] != horizontal_gray[index][k])
                    {
                        gray[k] = 'x';
                    }
                }
                index = next_right(index);
            }

            //manually add a cycle for the last row
            cerr<<"j index: "<<groups[i].stwo.second<<endl;
            for(int k = 0; k<gray.size(); k++)
            {
                if(gray[k] != horizontal_gray[groups[i].stwo.second][k])
                {
                    gray[k] = 'x';
                }
            }

            //printing the minterm
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
