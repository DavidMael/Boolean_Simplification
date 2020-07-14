#include <vector>

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
        //actual squares in the kmap
        vector<vector<bool>> squares;

        //flags 1s that have been incorporated in a double
        vector<vector<bool>> flags;

        //flags 1s that haven't been incoprorated into a double
        vector<vector<bool>> orphans;

        kmap(bool a,bool b,bool c,bool d, bool e, bool f, bool g, bool h)
        {
            squares = {{a, b, c, d}, {e, f, g, h}};

            flags = {{0, 0, 0, 0}, {0, 0, 0, 0}};

            orphans = {{0, 0, 0, 0}, {0, 0, 0, 0}};
        }

        //scans the kmap for horizontal doubles
        vector<group> horizontaldoubs(); 

        //identify 1s in the kmap not belonging to a double
        void identify_orphans();  

        //scans the kmap for vertical doubles
        vector<group> verticaldoubs();     
};

//merges quads in the results of verticaldoubs or horizontaldoubs
//atm just merge doubles into quads, result does not include non merged doubles as doub functions do not include singles
vector<group> mergegroups (const vector<group> & doubs,  const int & width, const int & height);


