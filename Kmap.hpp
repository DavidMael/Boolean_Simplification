#include <vector>

using namespace std;

struct group
//group of 1s of size n larger than 1
//stwo is below and to the right of sone: 0;0 3;3 is a normal group and 0;3 1;0 wraps around the edge
{
    //size of the group, might not actually be used
    int n;

    //flag indicating whether the group has yet been merged
    bool merged;

    //pairs the i (height) and j (width) indices of the two squares in the pair
    pair<int, int> sone;
    pair<int, int> stwo;
};

class kmap
{
    //private: later make a reader function and make data member private
        
    public:
        //actual squares in the kmap
        vector<vector<bool>> squares;

        //flags 1s that have been incorporated in a double
        vector<vector<bool>> flags;

        //flags 1 squares that haven't been incoprorated into a double
        vector<vector<bool>> orphans;

        //groups of all sizes
        vector<group> groups;

        kmap(bool a,bool b,bool c,bool d, bool e, bool f, bool g, bool h)
        {
            squares = {{a, b, c, d, e, f, g, h}, {0, 0, 0, 0, 0, 0, 0, 0}};

            flags = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};

            orphans = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};
        }

        //scans the kmap for horizontal doubles
        void horizontaldoubs(); 

        //identify 1s in the kmap not belonging to a double
        void identify_orphans();  

        //scans the kmap for vertical doubles
        void verticaldoubs();  

        //merges quads in the results of verticaldoubs or horizontaldoubs
        //atm just merge doubles into quads, result does not include non merged doubles as doub functions do not include singles
        void mergegroups (const int & new_n);   

        //helper functions use to read the kmap and simplify the state machine

        //return bool in square increment columns to the right of i;j, accounting for wrap around
        bool one_right(const int & i, const int & j, const int & increment);

        //return bool in square increment rows below i;j, accounting for wrap around
        bool one_below(const int & i, const int & j, const int & increment);

        //return the row index to the immediate right of j, accounting for wrap around 
        int next_right(const int & j);

        //return the column index immediately below i, accounting for wrap around 
        int next_below(const int & i);

        bool group_below(const int & increment, const int & i, const int & j);

        bool group_right(const int & increment, const int & i, const int & j);
};

