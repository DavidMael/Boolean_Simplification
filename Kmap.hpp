#include <vector>

using namespace std;

struct doub
//basically a pair of pairs of ints, renamed for brevity in declarations and consistency  with quad and oct class
{
    //pairs the i (height) and j(width) coordinates of the two squares in the pair
        pair<int, int> sone;
        pair<int, int> stwo;
};

class kmap
{
    //private: later make a reader function and make data member private
        
    public:
        vector<vector<bool>> squares;

        kmap(bool a,bool b,bool c,bool d, bool e, bool f, bool g, bool h)
        {
            squares = {{a, b, c, d}, {e, f, g, h}};
        }

        //scans the kmap for horizontal doubles
        vector<doub> horizontaldoubs()
        {
            //initialise vector of doubles
            vector<doub>  vect;
            //height of the kmap
            int height = squares.size();
            //width of the kmap
            int width = squares[1].size();
            //cycle through each square of the kmap 
            for(int i = 0; i<height; i++)
            {
                for(int j = 0; j<width; j++)
                {
                    //square not at the end of the line
                    if(j != (width-1))
                    {
                        if(squares[i][j] == 1 && squares[i][j+1] == 1)
                        {
                            vect.push_back({ {i, j}, {i, (j+1)} });
                        } 
                    } else {
                    //square at end of line    
                        if(squares[i][j] == 1 && squares[0][0] == 1)
                        {
                            vect.push_back({ {i, j}, {0, 0} });
                        }  
                    }
                }
            }

            return vect;
        }

};