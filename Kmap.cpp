#include <iostream>
#include "Kmap.hpp"

using namespace std;

//scans the kmap for horizontal doubles
vector<doub> kmap::horizontaldoubs()
{
    //initialise vector of doubles
    vector<doub> vect;
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

            if(squares[i][j] == 1 && squares[i][j+1] == 0 && squares[i][j-1] == 0)
            {
                orphans[i][j] == 1;
            } else {
                if(j != (width-1)){
                    //look forward
                    if(squares[i][j] == 1 && squares[i][j+1] == 1)
                    {
                        //create double if the square pointed to doesn't belong to one, and flag the double in both squares
                        //should this be a separate if?
                        if (flags[i][j] == 0)
                        {
                            vect.push_back({ {i, j}, {i, (j+1)} });
                            flags[i][j] = 1;
                            flags[i][j+1] = 1;
                        }
                    //1110 case: if pointing to a 1 followed by a 0, not in a pair bc the previous 1 was skipped, look back to make a pair
                    } else if(j != 0) {
                        if (squares[i][j] == 1 && squares[i][j-1] == 1 && flags[i][j] == 0) {
                            vect.push_back({ {i, j-1}, {i, j} });
                            flags[i][j] = 1;
                            //ever needed?
                            flags[i][j-1] = 1;
                        }
                    } 
                } else if(squares[i][j] == 1 && squares[i][0] == 1 && flags[i][j] == 0) {
                    //square at the end of a line    
                    vect.push_back({ {i, j}, {i, 0} });
                    flags[i][j] = 1;
                    //ever needed?
                    flags[i][0] = 1; 
                }
            }

        //cout<<"square "<<i<<":"<<j<<" done"<<endl;
        }
    }

    //scrub flags for use in verticaldoubs
    //redo properly for n var kmaps to work
    flags = {{0, 0, 0, 0}, {0, 0, 0, 0}};

    return vect;
}

//identify 1s in the kmap not belonging to a double
void kmap::identify_orphans()
{
    
}

//scans the kmap for vertical doubles
vector<doub> kmap::verticaldoubs()
{
    //initialise vector of doubles
    vector<doub> vect;
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
                if(squares[i][j] == 1 && squares[i+1][j] == 1)
                {
                    //create double if the square pointed to doesn't belong to one, and flag the double in both squares
                    //should this be a separate if?
                    if (flags[i][j] == 0 && orphans[i][j] == 1)
                    {
                        vect.push_back({ {i, j}, {(i+1), j} });
                        flags[i][j] = 1;
                        flags[i+1][j] = 1;
                        orphans[i][j] = 0;
                    }
                //1110 case: if pointing to a 1 followed by a 0, not in a pair bc the previous 1 was skipped, look back up to make a pair
                } else if(i != 0) {
                    if(squares[i][j] == 1 && squares[i-1][j] == 1 && flags[i][j] == 0 && orphans[i][j] == 1) 
                    {
                        vect.push_back({ {i-1, j}, {i, j} });
                        flags[i][j] = 1;
                        //ever needed?
                        flags[i-1][j] = 1;
                        orphans[i][j] = 0;
                    }
                }
            } else {
                //square at the bottom of a column
                if(squares[i][j] == 1 && squares[0][j] == 1 && flags[i][j] == 0 && orphans[i][j] == 1)
                {
                    vect.push_back({ {i, j}, {0, j} });
                    flags[i][j] = 1;
                    //ever needed?
                    flags[0][j] = 1;
                    orphans[i][j] = 0;
                }    
            }   
        }
    }
    return vect;            
}

//merges quads in the results of verticaldoubs or horizontaldoubs
//atm just merge doubles into quads, result does not include non merged doubles as doub functions do not include singles
vector<quad> mergedoubles (const vector<doub> & doubs,  const int & width, const int & height)
{
    //initialise vector of quads
    vector<quad> vect;
    for(int i = 0; i < doubs.size(); i++)
    {
        for(int j = 0; j < doubs.size(); j++)
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
            if(i != j && doubs[i].sone.second == doubs[j].sone.second)
            {
                //horizontal doubs
                if(doubs[i].stwo.first == doubs[i].sone.first && doubs[j].stwo.first == doubs[j].sone.first)
                {
                    if(
                    (doubs[i].sone.first + 1) == doubs[j].sone.first
                    //looping from top to bottom
                    || (doubs[i].sone.first + 1) != doubs[j].sone.first && (doubs[j].sone.first + 1) != doubs[i].sone.first &&
                    (doubs[i].sone.first == 0 && doubs[j].sone.first == (height-1) || doubs[i].sone.first == (height-1) && doubs[j].sone.first == 0)
                    )
                    {
                        //cout << i << " " << j << endl;
                        cout << "S H" << endl;
                        //push back a quad made from doub[i] and doub[j]
                        vect.push_back({ {doubs[i].sone.first, doubs[i].sone.second}, {doubs[j].stwo.first, doubs[j].stwo.second} });
                    }
                }

                //vertical doubs
                if(doubs[i].stwo.second == doubs[i].sone.second && doubs[j].stwo.second == doubs[j].sone.second)
                {
                    if( 
                    (doubs[i].sone.first + 2) == doubs[j].sone.first
                    || (doubs[i].sone.first + 2) != doubs[j].sone.first && (doubs[j].sone.first + 2) != doubs[i].sone.first &&
                    (doubs[i].sone.first == 0 && doubs[j].sone.first == (height-2) || doubs[i].sone.first == (height-2) && doubs[j].sone.first == 0)
                    )
                    {
                        cout << "S V" << endl;
                        //push back a quad made from doub[i] and doub[j]
                        vect.push_back({ {doubs[i].sone.first, doubs[i].sone.second}, {doubs[j].stwo.first, doubs[j].stwo.second} });
                    } 
                }
            }

            //adjacent doubs
            if(i != j && doubs[i].sone.first == doubs[j].sone.first)
            {
                //horizontal doubs
                if(doubs[i].stwo.first == doubs[i].sone.first && doubs[j].stwo.first == doubs[j].sone.first)
                {
                    if( (doubs[i].sone.second + 2) == doubs[j].sone.second
                    //looping around edges
                    || (doubs[i].sone.second + 2) != doubs[j].sone.second && (doubs[j].sone.second + 2) != doubs[i].sone.second &&
                    (doubs[i].sone.second == 0 && doubs[j].sone.second == (width-2) || doubs[i].sone.second == (width-2) && doubs[j].sone.second == 0)
                    )
                    {
                        cout << "A H " << endl;
                        //push back a quad made from doub[i] and doub[j]
                        vect.push_back({ {doubs[i].sone.first, doubs[i].sone.second}, {doubs[j].stwo.first, doubs[j].stwo.second} });
                    }
                }

                //vertical doubs
                if(doubs[i].stwo.second == doubs[i].sone.second && doubs[j].stwo.second == doubs[j].sone.second)
                {
                    if(
                    (doubs[i].sone.second + 1) == doubs[j].sone.second
                    //looping from top to bottom
                    || (doubs[i].sone.second + 1) != doubs[j].sone.second && (doubs[j].sone.second + 1) != doubs[i].sone.second && 
                    (doubs[i].sone.second == 0 && doubs[j].sone.second == (width-1) || doubs[i].sone.second == (width-1) && doubs[j].sone.second == 0)
                    )
                    {
                        cout << "A V" << endl;
                        //push back a quad made from doub[i] and doub[j]
                        vect.push_back({ {doubs[i].sone.first, doubs[i].sone.second}, {doubs[j].stwo.first, doubs[j].stwo.second} });
                    }
                }
            } 
        }
    }

    return vect;
}