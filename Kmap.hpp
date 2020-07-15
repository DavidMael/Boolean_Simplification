#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*/
struct doub
//basically a pair of pairs of ints, renamed for brevity in declarations and consistency with quad and oct types
{
    //pairs the i (height) and j (width) indices of the two squares in the pair
    pair<int, int> sone;
    pair<int, int> stwo;
};

struct quad
{
    //quads are defined with the first square of the top/left double and second of the bottom/right one
    pair<int, int> qtopleft;
    pair<int, int> qbottomright;
};
/*/

struct group
//group of 1s of size n larger than 1
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
        //format
        int width;
        int height;

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

        kmap(bool a,bool b,bool c,bool d, bool e, bool f, bool g, bool h)
        {
            squares = {{a, b, c, d}, {e, f, g, h}};

            flags = {{0, 0, 0, 0}, {0, 0, 0, 0}};

            orphans = {{0, 0, 0, 0}, {0, 0, 0, 0}};
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

        //cout the simplified expression
        void solve();   
};


