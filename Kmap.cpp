#include <iostream>
#include "Kmap.hpp"

using namespace std;

//scans the kmap for horizontal doubles
void kmap::horizontaldoubs()
{
    //height of the kmap
    int height = squares.size();
    //width of the kmap
    int width = squares[1].size();
    //cycle through each square of the kmap 
    for(int i = 0; i<height; i++)
    {
        //simplify state machine

        //cout<<"i= "<<i<<endl;
        for(int j = 0; j<width; j++)
        {
            //cout<<i<<";"<<j<<endl;
            if(squares[i][j] == 1)
            {
                //cout<<"1 in square"<<endl;
                if(one_right(i, j, 1) )
                {
                    //cout<<"one_right 1"<<endl;
                    if(flags[i][j]==1)
                    {
                        //cout<<"flagged"<<endl;
                        if( one_right(i, j, 2) )
                        {
                            //cout<<"one_right 2"<<endl;
                            //cout<<"merged "<<i<<";"<<j<<endl;
                            groups.push_back({2, 1, {i, j}, {i, (next_right(j) )} });
                        } else {
                            //cout<<"not one_right 2"<<endl;
                            groups.push_back({2, 0, {i, j}, {i, (next_right(j) )} });
                        }
                    } else {
                    //cout<<"not flagged"<<endl;
                    groups.push_back({2, 0, {i, j}, {i, (next_right(j) )} });
                    flags[i][j] = 1;
                    flags[i][ next_right(j) ] = 1;
                    }
                } else if(one_right(i, j, -1) == 0 ) {
                    //cout<<"orphan"<<endl;
                    orphans[i][j] = 1;
                }
            }
        }
    }

    //might not be relevant
    //scrub flags for use in verticaldoubs
    //redo properly for n var kmaps to work
    flags = {{0, 0, 0, 0}, {0, 0, 0, 0}};
}

//identify 1s in the kmap not belonging to a double
void kmap::identify_orphans()
{   
    cout<<"orphans"<<endl;
    //print orphan indices
    for(int i = 0; i<orphans.size(); i++)
    {
        for(int j = 0; j<orphans[0].size(); j++)
        {
            if(orphans[i][j] == 1)
            {
                cout<<i<<';'<<j<<endl;
            }
        }
    }
}

//scans the kmap for vertical doubles
void kmap::verticaldoubs()
{
    //height of the kmap
    int height = squares.size();
    //width of the kmap
    int width = squares[1].size();
    //cycle through each square of the kmap 
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            if(squares[i][j] == 1)
            {
                if( one_below(i, j, 1) )
                {
                    if(orphans[i][j] || orphans[ next_below(i) ][j])
                    {
                        groups.push_back({2, 0, {i, j}, { next_below(i), j} });
                        orphans[i][j] = 0;
                        orphans[ next_below(i) ][j] = 0;
                        //is this relevant?
                        flags[i][j] = 1;
                        flags[ next_below(i) ][j] = 1;
                    } else {
                        groups.push_back({2, 1, {i, j}, { next_below(i), j} });
                        //is this relevant?
                        flags[i][j] = 1;
                        flags[ next_below(i) ][j] = 1;
                    }
                }
            } 
        }
    }         
}

//merges quads in the results of verticaldoubs or horizontaldoubs
//atm just merge doubles into quads, result does not include non merged doubles as doub functions do not include singles
void kmap::mergegroups (const int & new_n)
{
    int width = squares.size();

    int height = squares[0].size();

    //capture group size before adding merges
    int groups_size = groups.size();

    for(int i = 0; i < groups_size; i++)
    {
        for(int j = 0; j < groups_size; j++)
        {
            //perhaps adapt to that all checks are not always performed
            //perhaps remove mention of stwo from quad?

            cout << groups[i].sone.first << ";" <<groups[i].sone.second << " " << groups[i].stwo.first << ";" << groups[i].stwo.second <<" | "
            << groups[j].sone.first << ";" << groups[j].sone.second << " " << groups[j].stwo.first << ";" << groups[j].stwo.second <<
            "(groups right: "<<group_right(2, i, j)<<")"<<" -> "<<endl;

            //stacked doubs
            if(i != j && groups[i].sone.second == groups[j].sone.second)
            {
                //horizontal doubs
                if(groups[i].stwo.first == groups[i].sone.first && groups[j].stwo.first == groups[j].sone.first)
                {
                    if(group_below(1, i, j) )
                    {
                        //cout << i << " " << j << endl;
                        cout << "S H " << endl;
                        //push back a quad made from doub[i] and doub[j]
                        if(groups[i].merged == 1 && groups[j].merged == 1)
                        {
                            groups.push_back({new_n, 1, {groups[i].sone.first, groups[i].sone.second}, {groups[j].stwo.first, groups[j].stwo.second} });
                        } else {
                            groups.push_back({new_n, 0, {groups[i].sone.first, groups[i].sone.second}, {groups[j].stwo.first, groups[j].stwo.second} });
                        }

                        //flag merged groups as such
                        groups[i].merged = 1;
                        groups[j].merged = 1;
                    }
                }

                //vertical doubs
                if(groups[i].stwo.second == groups[i].sone.second && groups[j].stwo.second == groups[j].sone.second)
                {
                    if( group_below(2, i, j) )
                    {
                        cout << "S V" << endl;
                        //push back a quad made from doub[i] and doub[j]
                        if(groups[i].merged == 1 && groups[j].merged == 1)
                        {
                            groups.push_back({new_n, 1, {groups[i].sone.first, groups[i].sone.second}, {groups[j].stwo.first, groups[j].stwo.second} });
                        } else {
                            groups.push_back({new_n, 0, {groups[i].sone.first, groups[i].sone.second}, {groups[j].stwo.first, groups[j].stwo.second} });
                        }

                        //flag merged groups as such
                        groups[i].merged = 1;
                        groups[j].merged = 1;
                    } 
                }
            }

            //adjacent doubs
            if(i != j && groups[i].sone.first == groups[j].sone.first)
            {
                //horizontal doubs
                if(groups[i].stwo.first == groups[i].sone.first && groups[j].stwo.first == groups[j].sone.first)
                {
                    if( group_right(2, i, j) )
                    {
                        cout << "A H " << endl;
                        //push back a quad made from doub[i] and doub[j]
                        if(groups[i].merged == 1 && groups[j].merged == 1)
                        {
                            groups.push_back({new_n, 1, {groups[i].sone.first, groups[i].sone.second}, {groups[j].stwo.first, groups[j].stwo.second} });
                        } else {
                            groups.push_back({new_n, 0, {groups[i].sone.first, groups[i].sone.second}, {groups[j].stwo.first, groups[j].stwo.second} });
                        }

                        //flag merged groups as such
                        groups[i].merged = 1;
                        groups[j].merged = 1;
                    }
                }

                //vertical doubs
                if(groups[i].stwo.second == groups[i].sone.second && groups[j].stwo.second == groups[j].sone.second)
                {
                    if( group_right(1, i, j) )
                    {
                        cout << "A V" << endl;
                        //push back a quad made from doub[i] and doub[j]
                        if(groups[i].merged == 1 && groups[j].merged == 1)
                        {
                            groups.push_back({new_n, 1, {groups[i].sone.first, groups[i].sone.second}, {groups[j].stwo.first, groups[j].stwo.second} });
                        } else {
                            groups.push_back({new_n, 0, {groups[i].sone.first, groups[i].sone.second}, {groups[j].stwo.first, groups[j].stwo.second} });
                        }

                        //flag merged groups as such
                        groups[i].merged = 1;
                        groups[j].merged = 1;
                    }
                }
            } 
        }
    }
}