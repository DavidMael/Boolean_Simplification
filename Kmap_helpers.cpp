#include <iostream>
#include "Kmap.hpp"

using namespace std;

//compare two groups, return true if identical
bool operator== (const group & lhs, const group & rhs)
{
    return(
        lhs.sone.first == rhs.sone.first && lhs.sone.second == rhs.sone.second &&
        lhs.stwo.first == rhs.stwo.first && lhs.stwo.second == rhs.stwo.second &&
        lhs.n == rhs.n && lhs.merged == rhs.merged
    );
}

//compare two groups, return false if identical
bool operator!= (const group & lhs, const group & rhs)
{
    return(
        !(lhs.sone.first == rhs.sone.first && lhs.sone.second == rhs.sone.second &&
        lhs.stwo.first == rhs.stwo.first && lhs.stwo.second == rhs.stwo.second &&
        lhs.n == rhs.n && lhs.merged == rhs.merged)
    );
}

//compare two groups only by their coordinates, return true if equal
bool operator>= (const group & lhs, const group & rhs)
{
    return(
        lhs.sone.first == rhs.sone.first && lhs.sone.second == rhs.sone.second &&
        lhs.stwo.first == rhs.stwo.first && lhs.stwo.second == rhs.stwo.second
    );
}

//compare two groups only by their coordinates, return false if equal
bool operator<= (const group & lhs, const group & rhs)
{
    return(
        !(lhs.sone.first == rhs.sone.first && lhs.sone.second == rhs.sone.second &&
        lhs.stwo.first == rhs.stwo.first && lhs.stwo.second == rhs.stwo.second)
    );
}

//return bool in square increment columns to the right of i;j, accounting for wrap around
bool kmap::one_right(const int & i, const int & j, const int & increment)
{
    //cout<<"one_right function"<<endl;

    //cout<<"one_right "<<increment<<": "<<i<<";"<<j<<" -> ";

    if( (j+increment) > (width-1) )
    {
        //cout<<i<<";"<<increment-width+j<<" wrap forwards : "<<squares[i][increment-width+j]<<endl;
        return squares[i][increment-width+j];
    } else if ( (j+increment) < 0 ){
        //cout<<i<<";"<<increment+width-j<<" wrap backwards : "<<squares[i][increment+width-j]<<endl;
        return squares[i][increment+width-j];
    } else {
        //cout<<i<<";"<<j+increment<<" : "<<squares[i][j+increment]<<endl;
        return squares[i][j+increment];
    }
}

//return bool in square increment rows below i;j, accounting for wrap around
bool kmap::one_below(const int & i, const int & j, const int & increment)
{
    if( (i + increment) > (height - 1) )
    {
        return squares[increment-height+i][j];
    } else {
        return squares[i+increment][j];
    }
}

//return the row index to the immediate right of j, accounting for wrap around 
int kmap::next_right(const int & j)
{
    if(j+1 > width-1) 
    {
        return 0;
    } else {
        return j+1;
    }
}

//return the column index immediately below i, accounting for wrap around 
int kmap::next_below(const int & i)
{
    if(i+1 > height-1)
    {
        return 0;
    } else {
        return i+1;
    }
}

//return the column index immediately above i, accounting for wrap around 
int kmap::next_above(const int & i)
{
    if(i == 0)
    {
        return (height-1);
    } else {
        return (i-1);
    }
}

bool kmap::group_below(const int & increment, const int & i, const int & j)
{
    return(
    (groups[i].sone.first + increment) == groups[j].sone.first
    //looping from top to bottom
    || (groups[i].sone.first + increment) != groups[j].sone.first && (groups[j].sone.first + increment) != groups[i].sone.first &&
    groups[i].sone.first > (height-1-increment) && groups[j].sone.first == (height-groups[i].sone.first)
    );
}

bool kmap::group_right(const int & increment, const int & i, const int & j)
{
    return(
    (groups[i].sone.second + increment) == groups[j].sone.second
    //looping around edges
    || (groups[i].sone.second + increment) != groups[j].sone.second && (groups[j].sone.second + increment) != groups[i].sone.second &&
    groups[i].sone.second > (width-1-increment) && groups[j].sone.second == (width-groups[i].sone.second)
    );
}


group kmap::find_extrema(const group & gi, const group & gj, const int & n, const int & m_flag)
{
    int minrow;
    int maxrow;
    int mincol;
    int maxcol;

    //if group j's leftmost column is 1 to the right of the rightmost column of group i
    if( next_right(gi.stwo.second) == gj.sone.second )
    {
        //if group i's leftmost column is 1 to the right of the rightmost column of group j
        if( next_right(gj.stwo.second) == gi.sone.second )
        {
            //groups are joined at both ends
            mincol = 0;
            maxcol = width-1;
        } else {
            mincol = gi.sone.second;
            maxcol = gj.stwo.second;
        }
    } else {
        mincol = gi.sone.second;
        maxcol = gj.stwo.second;
    }

    if( next_below(gi.stwo.first) == gj.sone.first )
    {
        if( next_below(gj.stwo.first) == gi.sone.first )
        {
            minrow = 0;
            maxrow = height-1;
        } else {
            minrow = gi.sone.first;
            maxrow = gj.stwo.first;
        }
    } else {
        minrow = gi.sone.first;
        maxrow = gj.stwo.first;
    }

    return {n, m_flag, {minrow, mincol}, {maxrow, maxcol} };
}

void kmap::wipe_flags()
{
    for(int i = 0; i<height; i++)
    {
       fill(flags[i].begin(), flags[i].end(), 0); 
    }
}

//if there is a double A over (i,j) and the other square is part of another double B, merge-flag A and return false
bool kmap::overlap_check(const int & i, const int & j)
{
    bool retval = true;
    bool retval2 = true;
    //indices of the other square of the overlapping double
    int e;
    int g;
    //function must be applied twice, once for each square in the vertical double
    int y = next_below(i);

    int groupindex;

    //containts groupindex, i/y, j, e, g and c of a certain group slated to be removed and merge-flagged if (retval||retval2)==false
    vector<tuple<int, int, int, int, int>> removal_info;

    //cerr<<"first size: "<<grouppointers[i][j].size()<<endl;

    for(int c=0; c<grouppointers[i][j].size(); c++ )
    {
        groupindex = grouppointers[i][j][c];
        
        //look accross any groups pointed to, check if i,j corresponds to sone of overlapping double
        if( groups[ groupindex ].sone.first == i && groups[ groupindex ].sone.second == j )
        {
            //look at stwo
            e = groups[ groupindex ].stwo.first;
            g = groups[ groupindex ].stwo.second;
            //cerr<<"after assigning 1 c="<<c<<" i="<<i<<" j="<<j<<" e="<<e<<" g="<<g<<endl;
            //cerr<<"merge flag: "<<groups[ groupindex ].merged<<endl;
            if( grouppointers[e][g].size() > 1 )
            {
                retval = false;
                //group i;j e;g is no longer top level, merge-flag it and delete its index from the vector grid
                /*/groups[ groupindex ].merged = true;
                (grouppointers[i][j]).erase( (grouppointers[i][j]).begin() + c );
                for(int k=0; k<grouppointers[e][g].size(); k++)
                {
                    if( grouppointers[e][g][k] == groupindex )
                    {
                        grouppointers[e][g].erase( grouppointers[e][g].begin() + k );
                    }
                }/*/
                removal_info.push_back( { groupindex, i, e, g, c } );
                //cerr<<"after this 1"<<endl;
            }
        } else {
            //look at sone
            e = groups[ groupindex ].sone.first;
            g = groups[ groupindex ].sone.second;
            //cerr<<"after assigning 2 c="<<c<<" i="<<i<<" j="<<j<<" e="<<e<<" g="<<g<<endl;
            //cerr<<"merge flag: "<<groups[ groupindex ].merged<<endl;
            if( grouppointers[e][g].size() > 1 )
            {
                retval = false;
                //group i;j e;g is no longer top level, merge-flag it and delete its index from the vector grid
                /*/groups[ groupindex ].merged = true;
                grouppointers[i][j].erase( grouppointers[i][j].begin() + c );
                for(int k=0; k<grouppointers[e][g].size(); k++)
                {
                    if( grouppointers[e][g][k] == groupindex )
                    {
                        grouppointers[e][g].erase( grouppointers[e][g].begin() + k );
                    }
                }/*/
                removal_info.push_back( { groupindex, i, e, g, c } );
                //cerr<<"after this 2"<<endl;
            }
        }    
    }

    for(int c=0; c<grouppointers[y][j].size(); c++ )
    {
        groupindex = grouppointers[y][j][c];

        //look accross any groups pointed to, check if i,j corresponds to sone of overlapping double
        if( groups[ groupindex ].sone.first == y && groups[ groupindex ].sone.second == j )
        {
            //look at stwo
            e = groups[ groupindex ].stwo.first;
            g = groups[ groupindex ].stwo.second;
            //cerr<<"after assigning 3 c="<<c<<" y="<<y<<" j="<<j<<" e="<<e<<" g="<<g<<endl;
            //cerr<<"merge flag: "<<groups[ groupindex ].merged<<endl;
            if( grouppointers[e][g].size() > 1 )
            {
                retval2 = false;
                //group y;j e;g is no longer top level, merge-flag it and delete its index from the vector grid
                /*/groups[ groupindex ].merged = true;
                grouppointers[y][j].erase( grouppointers[y][j].begin() + c );
                for(int k=0; k<grouppointers[e][g].size(); k++)
                {
                    if( grouppointers[e][g][k] == groupindex )
                    {
                        grouppointers[e][g].erase( grouppointers[e][g].begin() + k );
                    }
                }/*/
                removal_info.push_back( { groupindex, y, e, g, c } );
                //cerr<<"after this 3"<<endl;
            }
        } else {
            //look at sone
            e = groups[ groupindex ].sone.first;
            g = groups[ groupindex ].sone.second;
            //cerr<<"after assigning 4 c="<<c<<" y="<<y<<" j="<<j<<" e="<<e<<" g="<<g<<endl;
            //cerr<<"merge flag: "<<groups[ groupindex ].merged<<endl;
            if( grouppointers[e][g].size() > 1 )
            {
                retval2 = false;
                //group y;j e;g is no longer top level, merge-flag it and delete its index from the vector grid
                /*/groups[ groupindex ].merged = true;
                grouppointers[y][j].erase( grouppointers[y][j].begin() + c );
                for(int k=0; k<grouppointers[e][g].size(); k++)
                {
                    if( grouppointers[e][g][k] == groupindex )
                    {
                        grouppointers[e][g].erase( grouppointers[e][g].begin() + k );
                    }
                }/*/
                removal_info.push_back( { groupindex, y, e, g, c } );
                //cerr<<"after this 4"<<endl;
            }
        }    
    }

    //if both groups at i;j and y;j will be overlapped
    if( !( retval || retval2 ) )
    {
        //hold values for i/y and c from removal_info
        int iy;
        int c;

        for(int f=0; f<removal_info.size(); f++)
        {
            //group i/y;j e;g is no longer top level, merge-flag it and delete its index from the vector grid
            groupindex = get<0>(removal_info[f] );
            iy = get<1>(removal_info[f] );
            e = get<2>(removal_info[f] );
            g = get<3>(removal_info[f] );
            c = get<4>(removal_info[f] );

            groups[ groupindex ].merged = true;
            (grouppointers[iy][j]).erase( (grouppointers[iy][j]).begin() + c );
            for(int k=0; k<grouppointers[e][g].size(); k++)
            {
                if( grouppointers[e][g][k] == groupindex )
                {
                    grouppointers[e][g].erase( grouppointers[e][g].begin() + k );
                }
            } 
        }  
    }

    //cerr<<"end of fcn: "<<(retval || retval2)<<endl;

    //return false only if there is an completely overlapped group at i;j and y;j
    return (retval || retval2);
}

//check if the non-orphan square causes a group to be entirely overlapped, if yes merge-flag the group
bool kmap::orphan_overlap(const int & i, const int & j)
{
    bool retval = true;
    //indices of the other square of the overlapping double
    int e;
    int g;

    int groupindex;

    for(int c=0; c<grouppointers[i][j].size(); c++ )
    {
        groupindex = grouppointers[i][j][c];
        
        //look accross any groups pointed to, check if i,j corresponds to sone of overlapping double
        if( groups[ grouppointers[i][j][c] ].sone.first == i && groups[ grouppointers[i][j][c] ].sone.second == j )
        {
            //look at stwo
            e = groups[ groupindex ].stwo.first;
            g = groups[ groupindex ].stwo.second;
            //cerr<<"after assigning 1 c="<<c<<" i="<<i<<" j="<<j<<" e="<<e<<" g="<<g<<endl;
            //cerr<<"merge flag: "<<groups[ groupindex ].merged<<endl;
            if( grouppointers[e][g].size() > 1 )
            {
                retval = false;
                //group i;j e;g is no longer top level, merge-flag it and delete its index from the vector grid
                groups[ groupindex ].merged = true;
                (grouppointers[i][j]).erase( (grouppointers[i][j]).begin() + c );
                for(int k=0; k<grouppointers[e][g].size(); k++)
                {
                    if( grouppointers[e][g][k] == groupindex )
                    {
                        grouppointers[e][g].erase( grouppointers[e][g].begin() + k );
                    }
                }
                //cerr<<"after this 1"<<endl;
            }
        } else {
            //look at sone
            e = groups[ groupindex ].sone.first;
            g = groups[ groupindex ].sone.second;
            //cerr<<"after assigning 2 c="<<c<<" i="<<i<<" j="<<j<<" e="<<e<<" g="<<g<<endl;
            //cerr<<"merge flag: "<<groups[ groupindex ].merged<<endl;
            if( grouppointers[e][g].size() > 1 )
            {
                retval = false;
                //group i;j e;g is no longer top level, merge-flag it and delete its index from the vector grid
                groups[ groupindex ].merged = true;
                grouppointers[i][j].erase( grouppointers[i][j].begin() + c );
                for(int k=0; k<grouppointers[e][g].size(); k++)
                {
                    if( grouppointers[e][g][k] == groupindex )
                    {
                        grouppointers[e][g].erase( grouppointers[e][g].begin() + k );
                    }
                }
                //cerr<<"after this 2"<<endl;
            }
        } 
    }

    return retval;
}