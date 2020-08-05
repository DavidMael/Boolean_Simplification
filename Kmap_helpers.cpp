#include <iostream>
#include "Kmap.hpp"

using namespace std;

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
    /*/
    if((groups[i].sone.second + increment) == groups[j].sone.second)
    {
        cout<<"no wrap "<<endl;
    }

    if( groups[j].sone.second == (width-groups[i].sone.second) )
    {
        cout<<"groups[j].sone.second == (width-groups[i].sone.second) "<<endl;
    }

    if( groups[i].sone.second > (width-1-increment) )
    {
        cout<<"groups[i].sone.second > (width-1-increment) "<<endl;
    }/*/
 
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

bool operator== (const group & lhs, const group & rhs)
{
    return(
        lhs.sone.first == rhs.sone.first && lhs.sone.second == rhs.sone.second &&
        lhs.stwo.first == rhs.stwo.first && lhs.stwo.second == rhs.stwo.second &&
        lhs.n == rhs.n && lhs.merged == rhs.merged
    );
}

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