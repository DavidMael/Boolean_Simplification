#include <vector>

using namespace std;

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

class kmap
{
    //private: later make a reader function and make data member private
        
    public:
        //actual squares in the kmap
        vector<vector<bool>> squares;

        //signals if a square has been incorporated into a double
        vector<vector<bool>> flags;

        kmap(bool a,bool b,bool c,bool d, bool e, bool f, bool g, bool h)
        {
            squares = {{a, b, c, d}, {e, f, g, h}};

            flags = {{0, 0, 0, 0}, {0, 0, 0, 0}};
        }

        //scans the kmap for horizontal doubles
        vector<doub> horizontaldoubs();   

        //scans the kmap for vertical doubles
        vector<doub> verticaldoubs();     
};

//merges quads in the results of verticaldoubs or horizontaldoubs
//atm just merge doubles into quads, result does not include non merged doubles as doub functions do not include singles
vector<quad> mergedoubles (const vector<doub> & doubs,  const int & width, const int & height);


