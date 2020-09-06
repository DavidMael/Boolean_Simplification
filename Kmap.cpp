#include "Kmap.hpp"

using namespace std;

//scans the kmap for horizontal doubles
void kmap::horizontaldoubs()
{
    //record the index at which new groups are stored in the vector
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

    //might not be relevant
    //scrub flags for use in verticaldoubs
    //redo properly for n var kmaps to work
    //flags = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    wipe_flags();
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
    //in cases where merge would be 1, evaluate using the overlap_check function
    bool merge_flag_set;

    //record the index at which new groups are stored in the vector
    int group_index = groups.size()-1;

    //cycle through each square of the kmap 
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            if(squares[i][j] == 1)
            {
                if( one_below(i, j, 1) )
                {
                    if( orphans[i][j] || orphans[ next_below(i) ][j]  )
                    {    
                        if(flags[i][j]==1)
                        {
                            //cout<<"flagged"<<endl;
                            if( one_below(i, j, 2) )
                            {
                                cout<<"case 1, orpans&flags&1below "<<endl;
                                merge_flag_set = overlap_check(i, j);
                                //cout<<"one_right 2"<<endl;
                                //cout<<"merged "<<i<<";"<<j<<endl;
                                groups.push_back({2, merge_flag_set, {i, j}, { next_below(i), j} });

                                group_index++;

                                if(!merge_flag_set)
                                {
                                    //push to the grid square-group pointers
                                    grouppointers[i][j].push_back( group_index );
                                    grouppointers[ next_below(i) ][j].push_back( group_index );

                                    flags[i][j] = 1;
                                    flags[ next_below(i) ][j] = 1;

                                    orphans[i][j] = 0;
                                    orphans[ next_below(i) ][j] = 0;
                                }
                            } else {
                                cout<<"case 2, orphans&flags&0below"<<endl;
                                merge_flag_set = overlap_check(i, j);
                                //cout<<"not one_right 2"<<endl;
                                groups.push_back({2, 0, {i, j}, { next_below(i), j} });

                                group_index++;

                                //push to the grid square-group pointers
                                grouppointers[i][j].push_back( group_index );
                                grouppointers[ next_below(i) ][j].push_back( group_index );
                            }
                        } else {
                            cout<<"!case 3, noflags&orphans: "<<orphans[i][j]<<" "<<orphans[ next_below(i) ][j]<<"|"<<i<<';'<<j<<" "<<next_below(i)<<';'<<j<<endl;
                            //cout<<"not flagged"<<endl;
                            merge_flag_set = overlap_check(i, j);

                            groups.push_back({2, 0, {i, j}, { next_below(i), j} });
                            //cout<<"reasonable number: "<<groups.size()-1<<" | "<<groups[ groups.size()-1 ].sone.first<<" "<<groups[ groups.size()-1 ].sone.second<<" "<<groups[ groups.size()-1 ].stwo.first<<" "<<groups[ groups.size()-1 ].stwo.second<<endl;

                            group_index++;
                            //push to the grid square-group pointers
                            grouppointers[i][j].push_back( group_index );
                            grouppointers[ next_below(i) ][j].push_back( group_index );
                            
                            flags[i][j] = 1;
                            flags[ next_below(i) ][j] = 1;

                            orphans[i][j] = 0;
                            orphans[ next_below(i) ][j] = 0;
                        }
                    } else {
                        cout<<"case 4, no orphans, flags:"<<flags[i][j]<<" "<<flags[next_below(i)][j]<<endl;
                        merge_flag_set = overlap_check(i, j);

                        groups.push_back({2, merge_flag_set, {i, j}, { next_below(i), j} });

                        group_index++;

                        if(!merge_flag_set)
                        {
                            //push to the grid square-group pointers
                            grouppointers[i][j].push_back( group_index );
                            grouppointers[ next_below(i) ][j].push_back( group_index );

                            flags[i][j] = 1;
                            flags[ next_below(i) ][j] = 1;
                        }
                        //is this correct?
                        //flags[i][j] = 1;
                        //flags[ next_below(i) ][j] = 1;
                    }
                }
            } 
        }
    }         
}

//merges quads in the results of verticaldoubs or horizontaldoubs
//atm just merge doubles into quads, result does not include non merged doubles as doub functions do not include singles
//merge_type, when true, allows merges between merge and non merge-flagged groups
void kmap::mergegroups (const int & new_n, bool merge_type)
{
    //capture group size before adding merges
    int groups_size = groups.size();

    group merger;

    for(int i = 0; i < groups_size; i++)
    {
        for(int j = 0; j < groups_size; j++)
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
                        cout << groups[i].sone.first << ";" <<groups[i].sone.second << " " << groups[i].stwo.first << ";" << groups[i].stwo.second <<" + "
                        << groups[j].sone.first << ";" << groups[j].sone.second << " " << groups[j].stwo.first << ";" << groups[j].stwo.second <<
                        " (groups right: "<<group_right(2, i, j)<<")"<<" stacked -> ";

                        if(groups[i].merged == 1 && groups[j].merged == 1)
                        {
                            merger = find_extrema(groups[i], groups[j], new_n, 1);
                            groups.push_back( merger );
        
                        } else {
                            merger = find_extrema(groups[i], groups[j], new_n, 0);
                            groups.push_back( merger );
                        }
                        cout << merger.sone.first << ";" << merger.sone.second << " " << merger.stwo.first << ";" << merger.stwo.second<<" "<<merger.merged << endl;

                        //flag merged groups as such
                        groups[i].merged = 1;
                        groups[j].merged = 1;
                        
                    //adjacent groups of same format
                    } else if(i != j && groups[i].sone.first == groups[j].sone.first && next_right(groups[i].stwo.second) == groups[j].sone.second &&
                    groups[i].stwo.first == groups[j].stwo.first && groups[i].n == groups[j].n)
                    {
                        cout << groups[i].sone.first << ";" <<groups[i].sone.second << " " << groups[i].stwo.first << ";" << groups[i].stwo.second <<" + "
                        << groups[j].sone.first << ";" << groups[j].sone.second << " " << groups[j].stwo.first << ";" << groups[j].stwo.second <<
                        " (groups right: "<<group_right(2, i, j)<<")"<<" adjacent -> ";
                    
                        if(groups[i].merged == 1 && groups[j].merged == 1)
                        {
                            merger = find_extrema(groups[i], groups[j], new_n, 1);
                            groups.push_back( merger );
        
                        } else {
                            merger = find_extrema(groups[i], groups[j], new_n, 0);
                            groups.push_back( merger );
                        }
                        cout << merger.sone.first << ";" << merger.sone.second << " " << merger.stwo.first << ";" << merger.stwo.second<<" "<<merger.merged << endl;

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
    for(int n = 4; n<=(width*height) ;n = n*2)
    {
        cout << "first merge n= " <<n<< endl;

        mergegroups(n, 0);

        cout << "second merge n= " <<n<< endl;

        mergegroups(n, 1);
    }
}