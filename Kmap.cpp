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
            //cout<<"j= "<<j<<endl;
            //square not at the end of a line

            if(squares[i][j] == 1)
            {            
                if(j != (squares[0].size()-1) && j != 0 && squares[i][j+1] == 0 && squares[i][j-1] == 0)
                {
                    orphans[i][j] = 1;
                } else if (j == (squares[0].size()-1) && squares[i][0] == 0 && squares[i][j-1] == 0){
                    orphans[i][j] = 1;
                } else if (j == 0 && squares[i][j+1] == 0 && squares[i][squares[0].size()-1] == 0){
                    orphans[i][j] = 1;
                } else {
                    if(j != (width-1)){
                        //look forward
                        if(squares[i][j+1] == 1)
                        {
                            //create double if the square pointed to doesn't belong to one, and flag the double in both squares
                            //should this be a separate if?
                            if (flags[i][j] == 0)
                            {
                                groups.push_back({2, 0, {i, j}, {i, (j+1)} });
                                flags[i][j] = 1;
                                flags[i][j+1] = 1;
                            }
                        //1110 case: if pointing to a 1 followed by a 0, not in a pair bc the previous 1 was skipped, look back to make a pair
                        } else if(j != 0) {
                            if (squares[i][j-1] == 1 && flags[i][j] == 0) {
                                groups.push_back({2, 0, {i, j-1}, {i, j} });;
                                flags[i][j] = 1;
                                //ever needed?
                                flags[i][j-1] = 1;
                            }
                        } 
                    } else if(squares[i][0] == 1 && (flags[i][0] == 0 || flags[i][j] == 0) ) {
                        //square at the end of a line 
                        groups.push_back({2, 0, {i, j}, {i, 0} });
                        flags[i][j] = 1;
                        //ever needed?
                        flags[i][0] = 1; 
                    }
                }
            }
        }

        //cout<<"square "<<i<<":"<<j<<" done"<<endl;
    }

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
            //square not at the bottom of a column
            if(i != (height-1))
            {
                //look down
                if(squares[i][j] == 1 && squares[i+1][j] == 1 && orphans[i][j] == 1)
                {
                    //create double if the square pointed to doesn't belong to one, and flag the double in both squares
                    //should this be a separate if?
                    if (flags[i][j] == 0)
                    {
                        groups.push_back({2, 0, {i, j}, {(i+1), j} });
                        flags[i][j] = 1;
                        flags[i+1][j] = 1;
                        orphans[i][j] = 0;
                    }
                //1110 case: if pointing to a 1 followed by a 0, not in a pair bc the previous 1 was skipped, look back up to make a pair
                } else if(i != 0) {
                    if(squares[i][j] == 1 && squares[i-1][j] == 1 && flags[i][j] == 0 && orphans[i][j] == 1) 
                    {
                        groups.push_back({2, 0, {i-1, j}, {i, j} });
                        flags[i][j] = 1;
                        //ever needed?
                        flags[i-1][j] = 1;
                        orphans[i][j] = 0;
                    }
                }
            } else {
                //square at the bottom of a column
                if(squares[i][j] == 1 && squares[0][j] == 1 && flags[i][j] == 0  && orphans[i][j] == 1)
                {
                    groups.push_back({2, 0, {i, j}, {0, j} });
                    flags[i][j] = 1;
                    //ever needed?
                    flags[0][j] = 1;
                    orphans[i][j] = 0;
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
            /*/
            cout<<"i = "<<i<<"&j = "<<j<<endl;
            cout << doubs[i].sone.first << ";" << doubs[i].sone.second << " " << doubs[i].stwo.first << ";" << doubs[i].stwo.second << endl;
            cout << doubs[j].sone.first << ";" << doubs[j].sone.second << " " << doubs[j].stwo.first << ";" << doubs[j].stwo.second << endl;
            cout << "."<<endl;
            /*/

            //stacked doubs
            if(i != j && groups[i].sone.second == groups[j].sone.second)
            {
                //horizontal doubs
                if(groups[i].stwo.first == groups[i].sone.first && groups[j].stwo.first == groups[j].sone.first)
                {
                    if(
                    (groups[i].sone.first + 1) == groups[j].sone.first
                    //looping from top to bottom
                    || (groups[i].sone.first + 1) != groups[j].sone.first && (groups[j].sone.first + 1) != groups[i].sone.first &&
                    (groups[i].sone.first == 0 && groups[j].sone.first == (height-1) || groups[i].sone.first == (height-1) && groups[j].sone.first == 0)
                    )
                    {
                        //cout << i << " " << j << endl;
                        cout << "S H" << endl;
                        //push back a quad made from doub[i] and doub[j]
                        groups.push_back({new_n, 0, {groups[i].sone.first, groups[i].sone.second}, {groups[j].stwo.first, groups[j].stwo.second} });

                        //flag merged groups as such
                        groups[i].merged = 1;
                        groups[j].merged = 1;
                    }
                }

                //vertical doubs
                if(groups[i].stwo.second == groups[i].sone.second && groups[j].stwo.second == groups[j].sone.second)
                {
                    if( 
                    (groups[i].sone.first + 2) == groups[j].sone.first
                    || (groups[i].sone.first + 2) != groups[j].sone.first && (groups[j].sone.first + 2) != groups[i].sone.first &&
                    (groups[i].sone.first == 0 && groups[j].sone.first == (height-2) || groups[i].sone.first == (height-2) && groups[j].sone.first == 0)
                    )
                    {
                        cout << "S V" << endl;
                        //push back a quad made from doub[i] and doub[j]
                        groups.push_back({new_n, 0, {groups[i].sone.first, groups[i].sone.second}, {groups[j].stwo.first, groups[j].stwo.second} });

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
                    if( (groups[i].sone.second + 2) == groups[j].sone.second
                    //looping around edges
                    || (groups[i].sone.second + 2) != groups[j].sone.second && (groups[j].sone.second + 2) != groups[i].sone.second &&
                    (groups[i].sone.second == 0 && groups[j].sone.second == (width-2) || groups[i].sone.second == (width-2) && groups[j].sone.second == 0)
                    )
                    {
                        cout << "A H " << endl;
                        //push back a quad made from doub[i] and doub[j]
                        groups.push_back({new_n, 0, {groups[i].sone.first, groups[i].sone.second}, {groups[j].stwo.first, groups[j].stwo.second} });

                        //flag merged groups as such
                        groups[i].merged = 1;
                        groups[j].merged = 1;
                    }
                }

                //vertical doubs
                if(groups[i].stwo.second == groups[i].sone.second && groups[j].stwo.second == groups[j].sone.second)
                {
                    if(
                    (groups[i].sone.second + 1) == groups[j].sone.second
                    //looping from top to bottom
                    || (groups[i].sone.second + 1) != groups[j].sone.second && (groups[j].sone.second + 1) != groups[i].sone.second && 
                    (groups[i].sone.second == 0 && groups[j].sone.second == (width-1) || groups[i].sone.second == (width-1) && groups[j].sone.second == 0)
                    )
                    {
                        cout << "A V" << endl;
                        //push back a quad made from doub[i] and doub[j]
                        groups.push_back({new_n, 0, {groups[i].sone.first, groups[i].sone.second}, {groups[j].stwo.first, groups[j].stwo.second} });

                        //flag merged groups as such
                        groups[i].merged = 1;
                        groups[j].merged = 1;
                    }
                }
            } 
        }
    }
}