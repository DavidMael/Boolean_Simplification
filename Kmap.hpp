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
                    //square not at the end of a line
                    if(j != (width-1))
                    {
                        if(squares[i][j] == 1 && squares[i][j+1] == 1)
                        {
                            vect.push_back({ {i, j}, {i, (j+1)} });
                        } 
                    } else {
                    //square at the end of a line    
                        if(squares[i][j] == 1 && squares[i][0] == 1)
                        {
                            vect.push_back({ {i, j}, {i, 0} });
                        }  
                    }
                }
            }

            return vect;
        }

        //scans the kmap for vertical doubles
        vector<doub> verticaldoubs()
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
                    if(i != (height-1))
                    {
                        //square not at the bottom of a column
                        if(squares[i][j] == 1 && squares[i+1][j] == 1)
                        {
                            vect.push_back({ {i, j}, {(i+1), j} });
                        } 
                    } else {
                        //square at the bottom of a column
                        if(squares[i][j] == 1 && squares[0][j] == 1)
                        {
                            vect.push_back({ {i, j}, {0, j} });
                        }    
                    }   
                }
            }
            return vect;            
        }



};

//merges quads in the results of verticaldoubs or horizontaldoubs
//atm just merge doubles into quads, result does not include non merged doubles as doub functions do not include singles
vector<quad> mergedoubles (const vector<doub> & doubs)
{
    //initialise vector of quads
    vector<quad> vect;
    for(int i = 0; i < doubs.size(); i++)
    {
        for(int j = 0; j < doubs.size(); j++)
        {
            //if currently checks for a quad of "sandwitched" horizontal doubs
            if(i != j && 
            doubs[i].sone.second == doubs[j].sone.second &&
            (doubs[i].sone.first + 1) == doubs[j].sone.first 
            )
            {
                //push back a quad made from doub[i] and doub[j]
                vect.push_back({ {doubs[i].sone.first, doubs[i].sone.second}, {doubs[j].stwo.first, doubs[j].stwo.second} });
            }
        }
    }

    return vect;
}