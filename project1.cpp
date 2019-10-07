#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class tetris{
public:
    string type;       
    int index;   //left-bottom index
};

int main(){
    tetris tetris;
    int row,col,ind;
    //create output
    int **output;
    output=new int*[row+4];
    for(int i=0;i<row+4;i++)
        output[i]=new int[col];
    //read
    ifstream inF("tetris.data", ios::in);
    if (!inF) {
        cout << "can't open tetris.data" << endl;
        return 1;
    }
    //write
    ofstream outF("tetris.final", ios::out); 
    if (!outF) {
        cout << "can't open tetris.final" << endl;
        return 1;
    }
    inF>>row>>col;
    while(1){
        int h;
        int high[16]={0}; // record the highest number in every col
        inF>>tetris.type;
        if(tetris.type=="End"){
            break;
        }
        else inF>>tetris.index;
        ind=tetris.index;
        if(tetris.type=="T1"){
            //middle is the highest
            if(high[ind+1]<=high[ind]&&high[ind+1]<=high[ind+2]){
                h=high[ind+1];
                for(int i=ind;i<ind+3;i++){
                    output[h-2][i]=1;
                    high[i]=h-2;
                }
                output[h-1][ind+1]=1;
            }
            //left is the highest
            else if(high[ind]<high[ind+1]&&high[ind]<=high[ind+2]){
                h=high[ind];
                for(int i=ind;i<ind+3;i++){
                    output[h-1][i]=1;
                    high[i]=h-1;
                }
                output[h][ind+1]=1;
            }
            //right is the highest
            else{
                h=high[ind+2];
                for(int i=ind;i<ind+3;i++){
                    output[h-1][i]=1;
                    high[i]=h-1;
                }
                output[h][ind+1]=1;
            }
        }
        else if(tetris.type=="T2"){
            //right is higher
            if(high[ind]>=high[ind+1]){
                h=high[ind+1];
                output[h-2][ind]=1;
                for(int i=h-1;i>h-4;i--){
                    output[i][ind+1]=1;
                }
                high[ind]=h-2;
                high[ind+1]=h-3;
            }
            else{
                h=high[ind];
                output[h-1][ind]=1;
                for(int i=h;i>h-3;i--){
                    output[i][ind+1]=1;
                }
                high[ind]=h-1;
                high[ind+1]=h-2;
            }
        }
    }
    return 0;
}