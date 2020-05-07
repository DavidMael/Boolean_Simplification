#include <vector>

using namespace std;

struct doub
//basically a pair of pairs of pairs, renamed for brevity in declarations
{
    //pairs the i (height) and j(width) coordinates of the two squares in the pair
    pair<int, int> first;
    pair<int, int> second;
}

class kmap
{
    private:
        vector<vector<bool> bits;
    public:
        kmap(bool a,bool b,bool c,bool d, bool e, bool f, bool g, bool h)
        {
            bits {{a, b, c, d}, {e, f, g, h}};
        }

        //scans the kmap for horizontal doubles
        vector<doub> horizontaldoubs(const kmap& k)
        {
            //holder for detected doubles
            doub hold;
            //initialise vector of doubles
            vect vector<doub>;
            //height of the kmap
            int height = k.bits.size();
            //width of the kmap
            int width = k.bits[1].size();
            //cycle through each square of the kmap 
            for(int i = 0; i<height; i++)
            {
                for(int j = 0; j<width; j++)
                {
                    //square not at the end of the line
                    if(j != (width-1))
                    {
                        if(k[i][j] == 1 && k[i][j+1] == 1)
                        {
                            hold = {pair<i, j>, pair<i, (j+1)>};
                            vect.push_back(hold);
                        } 
                    } else {
                    //square at end of line    
                        if(k[i][j] == 1 && k[0][0] == 1)
                        {
                            hold = {pair<i, j>, pair<i, (j+1)>};
                            vect.push_back(hold);
                        }  
                    }
                }
            }

            return vect;
        }

};