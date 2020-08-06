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

    for(int i = 0; i<groups.size(); i++)
    {
        if(groups[i].merged == false)
        {
            gray = vertical_gray[ groups[i].sone.first ];

            //first, test what this gives for 1 height/width groups
            /*/
            if(groups[i].sone.first != groups[i].stwo.second)
            {/*/
                for(int j = groups[i].sone.first+1; j<=groups[i].stwo.first; j++)
                {
                    for(int k = 0; k<gray.size(); k++)
                    {
                        if(gray[k] != vertical_gray[j][k])
                        {
                            gray[k] = 'x';
                        }
                    }
                }
            /*/} else {

            }/*/

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
     
            for(int j = groups[i].sone.second+1; j<=groups[i].stwo.second; j++)
            {
                for(int k = 0; k<gray.size(); k++)
                {
                    if(gray[k] != horizontal_gray[j][k])
                    {
                        gray[k] = 2;
                    }
                }
            }

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
        }

        cout<<" + ";
    }
}
