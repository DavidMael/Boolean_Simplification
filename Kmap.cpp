#include "Kmap.hpp"

using namespace std;

//scans the kmap for horizontal doubles
void kmap::horizontaldoubs()
{
    //track the index at which new groups are stored in the vector
    int group_index = groups.size()-1;

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

                            group_index++;
                        } else {
                            //cout<<"not one_right 2"<<endl;
                            groups.push_back({2, 0, {i, j}, {i, (next_right(j) )} });

                            //cout<<"reasonable number 3: "<<groups.size()-1<<" | "<<groups[ groups.size()-1 ].sone.first<<" "<<groups[ groups.size()-1 ].sone.second<<" "<<groups[ groups.size()-1 ].stwo.first<<" "<<groups[ groups.size()-1 ].stwo.second<<endl;

                            group_index++;

                            //push to the grid square-group pointers
                            grouppointers[i][j].push_back( group_index );
                            grouppointers[i][ next_right(j) ].push_back( group_index );
                        }
                    } else {
                        //cout<<"not flagged"<<endl;
                        groups.push_back({2, 0, {i, j}, {i, (next_right(j) )} });

                        //cout<<"reasonable number 2: "<<groups.size()-1<<" | "<<groups[ groups.size()-1 ].sone.first<<" "<<groups[ groups.size()-1 ].sone.second<<" "<<groups[ groups.size()-1 ].stwo.first<<" "<<groups[ groups.size()-1 ].stwo.second<<endl;

                        flags[i][j] = 1;
                        flags[i][ next_right(j) ] = 1;

                        group_index++;

                        //push to the grid square-group pointers
                        grouppointers[i][j].push_back( group_index );
                        grouppointers[i][ next_right(j) ].push_back( group_index );
                        //cout<<"test sone first: 3rd v index="<<grouppointers[i][ next_right(j) ].size()-1<<" i="<<i<<" j="<<next_right(j)<<" e="<<grouppointers[i][ next_right(j) ][ grouppointers[i][ next_right(j) ].size()-1 ]->sone.first<<endl;
                        //cout<<"hmm: e="<<grouppointers[1][1][0]->sone.first<<endl;    
                    }
                } else if(one_right(i, j, -1) == 0 ) {
                    //cout<<"orphan"<<endl;
                    orphans[i][j] = 1;
                }
            }
        }
    }
}

//identify 1s in the kmap not belonging to a double
void kmap::identify_orphans()
{   
    cerr<<"orphans"<<endl;
    //print orphan indices
    for(int i = 0; i<orphans.size(); i++)
    {
        for(int j = 0; j<orphans[0].size(); j++)
        {
            if(orphans[i][j] == 1)
            {
                cerr<<i<<';'<<j<<endl;
            }
        }
    }
}

//scans the kmap for vertical doubles
void kmap::verticaldoubs()
{
    //in cases where merge would be 1, evaluate using the overlap_check function
    bool merge_flag_set;

    //track the index at which new groups are stored in the vector
    int group_index = groups.size()-1;

    //iterate through each square of the kmap 
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            //if the next two ones form a vertical double
            if(squares[i][j] && one_below(i, j, 1))
            {
                if( orphans[ next_below(i) ][j] || orphans[i][j]  )
                {    
                    //Case 1: two orphans
                    if( orphans[i][j] && orphans[ next_below(i) ][j] )
                    {
                        //cerr<<"-Case 1: two orphans"<<i<<';'<<j<<endl;

                        //push back a group with appropriate parameters
                        groups.push_back({2, 0, {i, j}, {next_below(i), j} });
                        //increase the group counter
                        group_index++;
                        //mark that included squares are no longer orphans
                        orphans[i][j] = 0;
                        orphans[ next_below(i) ][j] = 0;

                        //group is not merge-flagged, record index in grouppointers
                        grouppointers[i][j].push_back( group_index );
                        grouppointers[ next_below(i) ][j].push_back( group_index );

                    //only the top 1 is an orphan
                    } else if (orphans[i][j]) {
                        //Case 6.5: top square is an orphan below another orphan
                        if( orphans[ next_above(i) ][j] )
                        {
                            //cerr<<"-Case 6.5 (merge flag): one orphan below another "<<i<<';'<<j<<endl;

                            groups.push_back({2, 1, {i, j}, {next_below(i), j} });
                            group_index++;

                        //Cases 2.5 and 3.5: top square is an orphan but squares above and below aren't
                        } else {
                            //check for and merge-flag groups rendered redundant
                            merge_flag_set = orphan_overlap( next_below(i), j);

                            groups.push_back({2, 0, {i, j}, {next_below(i), j} });
                            group_index++;
                            orphans[i][j] = 0;

                            //group is not merge-flagged, record index in grouppointers
                            grouppointers[i][j].push_back( group_index );
                            grouppointers[ next_below(i) ][j].push_back( group_index );

                            if( !merge_flag_set )
                            {
                                //cerr<<"-Case 2.5: one orphan overlap "<<i<<';'<<j<<endl;
                            } else {
                                //cerr<<"-Case 3.5: one orphan no overlap "<<i<<';'<<j<<endl;
                            }
                        } 

                    //only the bottom 1 is an orphan
                    } else {
                        //Case 6: bottom square is an orphan above another orphan
                        if( orphans[ next_below(next_below(i)) ][j] )
                        {
                            //cerr<<"-Case 6 (merge flag): one orphan above another "<<i<<';'<<j<<endl;

                            groups.push_back({2, 1, {i, j}, {next_below(i), j} });
                            group_index++;

                        //Cases 2 and 3: bottom square is an orphan but squares above and below aren't
                        } else {
                            //check for and merge-flag groups rendered redundant
                            merge_flag_set = orphan_overlap(i, j);

                            groups.push_back({2, 0, {i, j}, {next_below(i), j} });
                            group_index++;
                            orphans[ next_below(i) ][j] = 0;

                            //group is not merge-flagged, record index in grouppointers
                            grouppointers[i][j].push_back( group_index );
                            grouppointers[ next_below(i) ][j].push_back( group_index );

                            if( !merge_flag_set )
                            {
                                //cerr<<"-Case 2: one orphan overlap "<<i<<';'<<j<<endl;
                            } else {
                                //cerr<<"-Case 3: one orphan no overlap "<<i<<';'<<j<<endl;
                            }
                        }
                    }

                //Cases 4 and 5: no orphans
                } else {
                    merge_flag_set = overlap_check(i, j);

                    groups.push_back({2, merge_flag_set, {i, j}, {next_below(i), j} });
                    group_index++;

                    if( !merge_flag_set )
                    {
                        //cerr<<"-Case 4: overlap, reduce n of doubles "<<i<<';'<<j<<endl;

                        //group is not merge-flagged, record index in grouppointers
                        grouppointers[i][j].push_back( group_index );
                        grouppointers[ next_below(i) ][j].push_back( group_index );
                    } else {
                        //cerr<<"-Case 5 (merge flag): no overlap "<<i<<';'<<j<<endl;
                    }
                }

            } 
        }
    } 

    //if set to false, we've not managed to improve group assignment with an overlap group
    bool improvement = true;
    //continue trying to make vertical doubles that simplify the groupings until failure to do so
    while( improvement )
    {
        improvement = false;

        //iterate accross the kmap
        for(int i = 0; i<height; i++)
        {
            for(int j = 0; j<width; j++)
            {
                //if the next two ones form a vertical double
                if(squares[i][j] && one_below(i, j, 1))
                {
                    //relevant? there should be no orphans left
                    if( !orphans[ next_below(i) ][j] && !orphans[i][j]  )
                    {
                        merge_flag_set = overlap_check(i, j);

                        if(!merge_flag_set)
                        {
                            groups.push_back({2, merge_flag_set, {i, j}, {next_below(i), j} });

                            //cerr<<"-Case 4 (extra loop): overlap, reduce n of doubles "<<i<<';'<<j<<endl;

                            improvement = true;
                        }

                    }    
                }
            }
        }
    }         
}

//merges quads in the results of verticaldoubs or horizontaldoubs
//merge_type, when true, allows merges between merge and non merge-flagged groups
void kmap::mergegroups (const int & new_n, bool merge_type, const int & start)
{
    //capture group size before adding merges
    int groups_size = groups.size();

    group merger;

    for(int i = start; i < groups_size; i++)
    {
        for(int j = start; j < groups_size; j++)
        {
            //perhaps adapt to that all checks are not always performed
            //perhaps remove mention of stwo from quad?

            //check that merged groups are of the right size and don't cover identical areas
            if( groups[i] <= groups[j] && groups[j].n == new_n/2 )
            {
                //check that the groups satisfy merge_type conditions
                if( (merge_type || !(groups[i].merged || groups[j].merged) ) && groups[i].n == new_n/2 )
                {
                    //stacked groups of same format
                    if(i != j && groups[i].sone.second == groups[j].sone.second && next_below(groups[i].stwo.first) == groups[j].sone.first &&
                    groups[i].stwo.second == groups[j].stwo.second && groups[i].n == groups[j].n)
                    {
                        /*/cerr << groups[i].sone.first << ";" <<groups[i].sone.second << " " << groups[i].stwo.first << ";" << groups[i].stwo.second <<" + "
                        << groups[j].sone.first << ";" << groups[j].sone.second << " " << groups[j].stwo.first << ";" << groups[j].stwo.second <<
                        " (groups right: "<<group_right(2, i, j)<<")"<<" stacked -> ";/*/

                        if(groups[i].merged == 1 && groups[j].merged == 1)
                        {
                            merger = find_extrema(groups[i], groups[j], new_n, 1);
                            groups.push_back( merger );
        
                        } else {
                            merger = find_extrema(groups[i], groups[j], new_n, 0);
                            groups.push_back( merger );
                        }
                        //cerr << merger.sone.first << ";" << merger.sone.second << " " << merger.stwo.first << ";" << merger.stwo.second<<" "<<merger.merged << endl;

                        //flag merged groups as such
                        groups[i].merged = 1;
                        groups[j].merged = 1;
                        
                    //adjacent groups of same format
                    } else if(i != j && groups[i].sone.first == groups[j].sone.first && next_right(groups[i].stwo.second) == groups[j].sone.second &&
                    groups[i].stwo.first == groups[j].stwo.first && groups[i].n == groups[j].n)
                    {
                        /*/cerr << groups[i].sone.first << ";" <<groups[i].sone.second << " " << groups[i].stwo.first << ";" << groups[i].stwo.second <<" + "
                        << groups[j].sone.first << ";" << groups[j].sone.second << " " << groups[j].stwo.first << ";" << groups[j].stwo.second <<
                        " (groups right: "<<group_right(2, i, j)<<")"<<" adjacent -> ";/*/
                    
                        if(groups[i].merged == 1 && groups[j].merged == 1)
                        {
                            merger = find_extrema(groups[i], groups[j], new_n, 1);
                            groups.push_back( merger );
        
                        } else {
                            merger = find_extrema(groups[i], groups[j], new_n, 0);
                            groups.push_back( merger );
                        }
                        //cerr << merger.sone.first << ";" << merger.sone.second << " " << merger.stwo.first << ";" << merger.stwo.second<<" "<<merger.merged << endl;

                        //flag merged groups as such
                        groups[i].merged = 1;
                        groups[j].merged = 1;
                    }
                } 
            }
        }
    }
}
 
void kmap::merge_function()
{
    //index at which to start looking for variables to merge
    int start = 0;
    //index at which the newly merged groups will start
    int nextstart;

    for(int n = 4; n<=(width*height) ;n = n*2)
    {
        nextstart = groups.size();

        //cerr << "first merge n= " <<n<< endl;

        mergegroups(n, 0, start);

        //cerr << "second merge n= " <<n<< endl;

        mergegroups(n, 1, start);

        start = nextstart;
    }
}