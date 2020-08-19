#include <vector>
#include <string>
#include <iostream>

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

//compare two groups, return true if identical
bool operator== (const group & lhs, const group & rhs);

//compare two groups, return false if identical
bool operator!= (const group & lhs, const group & rhs);

//compare two groups only by their coordinates and return true if equal
bool operator>= (const group & lhs, const group & rhs);

//compare two groups only by their coordinates and return false if equal
bool operator<= (const group & lhs, const group & rhs);

class kmap
{
    //private: later make a reader function and make data member private
        
    public:
        //boolean variables
        string horizontal_vars = "AB";
        string vertical_vars = "C";

        //Gray code
        vector<string> horizontal_gray = { "00", "01", "11", "10" };
        vector<string> vertical_gray = { "0", "1" };

        //actual squares in the kmap
        vector<vector<bool>> squares;

        //flags 1s that have been incorporated in a double
        vector<vector<bool>> flags;

        //flags 1 squares that haven't been incoprorated into a double
        vector<vector<bool>> orphans;

        //groups of all sizes
        vector<group> groups;

        //height of the kmap
        int height;
        //width of the kmap
        int width;

        /*/kmap(bool a,bool b,bool c,bool d, bool e, bool f, bool g, bool h)
        {
            squares = {{a, b, c, d}, {e, f, g, h} };

            flags = {{0, 0, 0, 0}, {0, 0, 0, 0} };

            orphans = {{0, 0, 0, 0}, {0, 0, 0, 0} };

            height = squares.size();
            width = squares[0].size();
        }/*/

        //constructor taking a boolean expression as argument
        kmap(const string & boolean_expression);

        //scans the kmap for horizontal doubles
        void horizontaldoubs(); 

        //identify 1s in the kmap not belonging to a double
        void identify_orphans();  

        //scans the kmap for vertical doubles
        void verticaldoubs();  

        //merges groups of format new_n/2 into new_n format groups, merge_type determining whether or not merge-flagged groups can be merged
        void mergegroups (const int & new_n, bool merge_type);   

        //performs all possible merges, first between non merge-flagged groups then between all groups 
        // !!this results in a lot of redundancy!!
        void merge_function();

        //cout the simplified expression
        string solve();

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

        group find_extrema(const group & gi, const group & gj, const int & n, const int & m_flag);

        void wipe_flags();
};

//kmap cout override, no newline after last line
//std::ostream& operator<<(std::ostream& out, const kmap & karnaugh)

