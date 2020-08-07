#include "Kmap.hpp"

using namespace std;

//output the simplified expression
void kmap::solve()
{
    //store gray code of terms for one side of the table, with 2 signifying "don't use"
    //eg. a group spanning 100 and 110 has a gray of 120
    string gray;

    //store the simplified expression
    string expression;

    //used to cycle through the gray codes while accounting for wrap-around
    int index;

    for(int i = 0; i<groups.size(); i++)
    {
        if(groups[i].merged == false)
        {
            cout<<"group"<<endl;

            gray = vertical_gray[ groups[i].sone.first ];

            index = next_below(groups[i].sone.first);

            for(int j = next_below(groups[i].sone.first); j<=groups[i].stwo.first; j++ )
            {
                for(int k = 0; k<gray.size(); k++)
                {
                    cout<<"i index: "<<index<<endl;
                    if(gray[k] != vertical_gray[index][k])
                    {
                        gray[k] = 'x';
                    }
                }
                index = next_below(index);
            }

            //printing the minterm
            for(int j = 0; j<gray.size(); j++)
            {
                if(gray[j] == '1')
                {
                    cout<<vertical_vars[j];
                }

                if(gray[j] == '0')
                {
                    cout<<"(~"<<vertical_vars[j]<<")";
                }
            }

            gray = horizontal_gray[ groups[i].sone.second ];

            index = next_right(groups[i].sone.second);
     
            for(int j = next_right(groups[i].sone.second); j<=groups[i].stwo.second; j++ )
            {
                cout<<"j index: "<<index<<endl;
                for(int k = 0; k<gray.size(); k++)
                {
                    if(gray[k] != horizontal_gray[index][k])
                    {
                        gray[k] = 'x';
                    }
                }
                index = next_right(index);
            })

            //printing the minterm
            for(int j = 0; j<gray.size(); j++)
            {
                if(gray[j] == '1')
                {
                    cout<<horizontal_vars[j];
                }

                if(gray[j] == '0')
                {
                    cout<<"(~"<<horizontal_vars[j]<<")";
                }
            }

            cout<<" + ";
        }
    }
}
