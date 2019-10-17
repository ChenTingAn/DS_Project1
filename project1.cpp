#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

class tetris{
public:
    string type;       
    int index;   //left-bottom index
};
void T1(int **output,int *high,int ind);
void T2(int **output,int *high,int ind);
void T3(int **output,int *high,int ind);
void T4(int **output,int *high,int ind);
void L1(int **output,int *high,int ind);
void L2(int **output,int *high,int ind);
void L3(int **output,int *high,int ind);
void L4(int **output,int *high,int ind);
void J1(int **output,int *high,int ind);
void J2(int **output,int *high,int ind);
void J3(int **output,int *high,int ind);
void J4(int **output,int *high,int ind);
void S1(int **output,int *high,int ind);
void S2(int **output,int *high,int ind);
void Z1(int **output,int *high,int ind);
void Z2(int **output,int *high,int ind);
void I1(int **output,int *high,int ind);
void I2(int **output,int *high,int ind);
void O(int **output,int *high,int ind);
void eliminate(int ** output,int *high,int row,int col);
int main(){
    tetris tetris;
    int row,col,ind;
    int **output; 
    //read
    ifstream inF("Tetris.data", ios::in);
    if (!inF) {
        cout << "can't open Tetris.data" << endl;
        return 1;
    }
    //write
    ofstream outF("Tetris.final", ios::out); 
    if (!outF) {
        cout << "can't open Tetris.final" << endl;
        return 1;
    }
    inF>>row>>col;
    output=new int*[row+4];          //reserve space for exceeded tetris
    for(int i=0;i<row+4;i++)
        output[i]=new int[col+1];    //col(0) records rows change or not
    for(int i=0;i<row+4;i++)         //initialize output
        for(int j=0;j<col+1;j++)
            output[i][j]=0;
    int *high=new int[col+1];        // record the highest number in every col
    for(int i=0;i<col+1;i++)         //initialize high,nothing => high=row+4
        high[i]=row+4;
    while(1){
        int h;
        int check_exceed=0;
        inF>>tetris.type;
        if(tetris.type=="End"){
            break;
        }
        else inF>>tetris.index;
        ind=tetris.index;
        if(tetris.type=="T1")       T1(output,high,ind);
        else if(tetris.type=="T2")  T2(output,high,ind);
        else if(tetris.type=="T3")  T3(output,high,ind);
        else if(tetris.type=="T4")  T4(output,high,ind);
        else if(tetris.type=="L1")  L1(output,high,ind);
        else if(tetris.type=="L2")  L2(output,high,ind);
        else if(tetris.type=="L3")  L3(output,high,ind);
        else if(tetris.type=="L4")  L4(output,high,ind);
        else if(tetris.type=="J1")  J1(output,high,ind);
        else if(tetris.type=="J2")  J2(output,high,ind);
        else if(tetris.type=="J3")  J3(output,high,ind);
        else if(tetris.type=="J4")  J4(output,high,ind);
        else if(tetris.type=="S1")  S1(output,high,ind);
        else if(tetris.type=="S2")  S2(output,high,ind);
        else if(tetris.type=="Z1")  Z1(output,high,ind);
        else if(tetris.type=="Z2")  Z2(output,high,ind);
        else if(tetris.type=="I1")  I1(output,high,ind);
        else if(tetris.type=="I2")  I2(output,high,ind);
        else                        O(output,high,ind);
        eliminate(output,high,row,col);       
        for(int i=1;i<col+1;i++){             //exceed or not
            if(high[i]<4){
                check_exceed=1;
                break;
            }
        }
        if(check_exceed==1){
            break;
        }
    }
    for(int i=4;i<row+4;i++){          //show the output
        for(int j=1;j<col+1;j++)
            outF<<output[i][j];   
        outF<<endl;     
    }
    inF.close();
    outF.close();                     
    return 0;
}
void T1(int **output,int *high,int ind){
    int h;
    //middle is the highest or as high as left or right
    if(high[ind+1]<=high[ind]&&high[ind+1]<=high[ind+2]){
        h=high[ind+1];
        for(int i=ind;i<ind+3;i++){
            output[h-2][i]=1;
            high[i]=h-2;
        }
        output[h-1][ind+1]=1;
        for(int i=h-1;i>h-3;i--)      //record which rows change
            output[i][0]=1;
    }
    //right or left is the highest
    else{
        h=min(high[ind],high[ind+2]);
        for(int i=ind;i<ind+3;i++){
            output[h-1][i]=1;
            high[i]=h-1;
        }
        output[h][ind+1]=1;
        for(int i=h;i>h-2;i--)        //record which rows change
            output[i][0]=1;
    }
}
void T2(int **output,int *high,int ind){
    int h;
    //right is higher or as high as left
    if(high[ind]>=high[ind+1]){
        h=high[ind+1];
        output[h-2][ind]=1;
        for(int i=h-1;i>h-4;i--){
            output[i][ind+1]=1;
            output[i][0]=1;        
        }
        high[ind]=h-2;
        high[ind+1]=h-3;
    }
    //left is higher
    else{
        h=high[ind];
        output[h-1][ind]=1;
        for(int i=h;i>h-3;i--){
            output[i][ind+1]=1;
            output[i][0]=1;       
        }
        high[ind]=h-1;
        high[ind+1]=h-2;
    }
}
void T3(int **output,int *high,int ind){
    int h;
    //no matter which column is the highest,the processes below are the same
    h=min(min(high[ind],high[ind+1]),high[ind+2]);
    for(int i=ind;i<ind+3;i++){
        output[h-1][i]=1;
        high[i]=h-1;
    }
    output[h-2][ind+1]=1;
    high[ind+1]=h-2;
    for(int i=h-1;i>h-3;i--)     
        output[i][0]=1;
}
void T4(int **output,int *high,int ind){
    int h;
    //left is higher or as high as right
    if(high[ind]<=high[ind+1]){
        h=high[ind];
        output[h-2][ind+1]=1;
        for(int i=h-1;i>h-4;i--){
            output[i][ind]=1;
            output[i][0]=1;          
        }
        high[ind]=h-3;
        high[ind+1]=h-2;
    }
    //right is higher
    else{
        h=high[ind+1];
        output[h-1][ind+1]=1;
        for(int i=h;i>h-3;i--){
            output[i][ind]=1;
            output[i][0]=1;          
        }
        high[ind]=h-2;
        high[ind+1]=h-1;
    }
}
void L1(int **output,int *high,int ind){
    int h;
    //no matter which column is the highest,the processes below are the same
    h=min(high[ind],high[ind+1]);
    for(int i=h-1;i>h-4;i--){
        output[i][ind]=1;
        output[i][0]=1;            
    }
    output[h-1][ind+1]=1;
    high[ind]=h-3;
    high[ind+1]=h-1;    
}
void L2(int **output,int *high,int ind){
    int h;
    //left is the highest or as high as middle or right
    if(high[ind]<=high[ind+1]&&high[ind]<=high[ind+2]){
        h=high[ind];
        output[h-1][ind]=1;
        for(int i=ind;i<ind+3;i++){
            output[h-2][i]=1;
            high[i]=h-2;
        }
        for(int i=h-1;i>h-3;i--)     
            output[i][0]=1;    
    }
    //middle or right is the highest
    else{
        h=min(high[ind+1],high[ind+2]);
        output[h][ind]=1;
        for(int i=ind;i<ind+3;i++){
            output[h-1][i]=1;
            high[i]=h-1;
        }
        for(int i=h;i>h-2;i--)     
            output[i][0]=1;    
    }
}
void L3(int **output,int *high,int ind){
    int h;
    //left is higher than right at least 2
    if(high[ind]+2<=high[ind+1]){
        h=high[ind];
        output[h-1][ind]=1;
        for(int i=h-1;i<h+2;i++){
            output[i][ind+1]=1;
            output[i][0]=1;
        }
        high[ind]=h-1;
        high[ind+1]=h-1;
    }
    //right is higher or left is higher less than 2
    else{
        h=high[ind+1];
        output[h-3][ind]=1;
        for(int i=h-1;i>h-4;i--){
            output[i][ind+1]=1;
            output[i][0]=1;
        }
        high[ind]=h-3;
        high[ind+1]=h-3;
    }
}
void L4(int **output,int *high,int ind){
    int h;
    //no matter which column is the highest,the processes below are the same
    h=min(min(high[ind],high[ind+1]),high[ind+2]);
    output[h-2][ind+2]=1;
    for(int i=ind;i<ind+3;i++){
        output[h-1][i]=1;
        high[i]=h-1;    
    }
    high[ind+2]=h-2;
    for(int i=h-1;i>h-3;i--)     
        output[i][0]=1;    
}
void J1(int **output,int *high,int ind){
    int h;
    //no matter which column is the highest,the processes below are the same
    h=min(high[ind],high[ind+1]);
    for(int i=h-1;i>h-4;i--){
        output[i][ind+1]=1;
        output[i][0]=1;
    }
    output[h-1][ind]=1;
    high[ind+1]=h-3;
    high[ind]=h-1; 
}
void J2(int **output,int *high,int ind){
    int h;
    //no matter which column is the highest,the processes below are the same
    h=min(min(high[ind],high[ind+1]),high[ind+2]);
    output[h-2][ind]=1;
    for(int i=ind;i<ind+3;i++){
        output[h-1][i]=1;
        high[i]=h-1;    
    }
    high[ind]=h-2;
    for(int i=h-1;i>h-3;i--)     
        output[i][0]=1;        
}
void J3(int **output,int *high,int ind){
    int h;
    //right is higher than left at least 2
    if(high[ind+1]+2<=high[ind]){
        h=high[ind+1];
        output[h-1][ind+1]=1;
        for(int i=h-1;i<h+2;i++){
            output[i][ind]=1;
            output[i][0]=1;
        }
        high[ind]=h-1;
        high[ind+1]=h-1;
    }
    //left is higher or right is higher less than 2
    else{
        h=high[ind];
        output[h-3][ind+1]=1;
        for(int i=h-1;i>h-4;i--){
            output[i][ind]=1;
            output[i][0]=1;
        }
        high[ind]=h-3;
        high[ind+1]=h-3;
    }
}
void J4(int **output,int *high,int ind){
    int h;
    //right is the highest or as high as middle or left
    if(high[ind+2]<=high[ind+1]&&high[ind+2]<=high[ind]){
        h=high[ind+2];
        output[h-1][ind+2]=1;
        for(int i=ind;i<ind+3;i++){
            output[h-2][i]=1;
            high[i]=h-2;
        }
        for(int i=h-1;i>h-3;i--)     
            output[i][0]=1;    
    }
    //middle or left is the highest
    else{
        h=min(high[ind],high[ind+1]);
        output[h][ind+2]=1;
        for(int i=ind;i<ind+3;i++){
            output[h-1][i]=1;
            high[i]=h-1;
        }
        for(int i=h;i>h-2;i--)     
            output[i][0]=1;
    }
}
void S1(int **output,int *high,int ind){
    int h;
    //right is the highest
    if(high[ind+2]<high[ind]&&high[ind+2]<high[ind+1]){
        h=high[ind+2];
        for(int i=h;i>h-2;i--){
            output[i][ind+1]=1;
            output[i][0]=1;
        }
        output[h][ind]=1;
        output[h-1][ind+2]=1;
        high[ind]=h;
        high[ind+1]=h-1;
        high[ind+2]=h-1; 
    }
    //left or middle is the highest or as high as right
    else{
        h=min(high[ind],high[ind+1]);
        for(int i=h-1;i>h-3;i--){
            output[i][ind+1]=1;
            output[i][0]=1;
        }
        output[h-1][ind]=1;
        output[h-2][ind+2]=1;
        high[ind]=h-1;
        high[ind+1]=h-2;
        high[ind+2]=h-2;
    }
}
void S2(int **output,int *high,int ind){
    int h;
    //left is higher
    if(high[ind]<high[ind+1]){
        h=high[ind];
        output[h-1][ind]=1;
        output[h-2][ind]=1;
        output[h][ind+1]=1;
        output[h-1][ind+1]=1;
        high[ind]=h-2;
        high[ind+1]=h-1;
        for(int i=h;i>h-3;i--)
            output[i][0]=1;
    }
    //right is higher or as high as left
    else{
        h=high[ind+1];
        output[h-2][ind]=1;
        output[h-3][ind]=1;
        output[h-1][ind+1]=1;
        output[h-2][ind+1]=1;
        high[ind]=h-3;
        high[ind+1]=h-2;
        for(int i=h-1;i>h-4;i--)
            output[i][0]=1;
    }
}
void Z1(int **output,int *high,int ind){
    int h;
    //left is the highest
    if(high[ind]<high[ind+1]&&high[ind]<high[ind+2]){
        h=high[ind];
        for(int i=h;i>h-2;i--){
            output[i][ind+1]=1;
            output[i][0]=1;
        }
        output[h-1][ind]=1;
        output[h][ind+2]=1;
        high[ind]=h-1;
        high[ind+1]=h-1;
        high[ind+2]=h;
    }
    //right or middle is the highest or as high as left
    else{
        h=min(high[ind+1],high[ind+2]);
        for(int i=h-1;i>h-3;i--){
            output[i][ind+1]=1;
            output[i][0]=1;
        }
        output[h-2][ind]=1;
        output[h-1][ind+2]=1;
        high[ind]=h-2;
        high[ind+1]=h-2;
        high[ind+2]=h-1;
    }
}
void Z2(int **output,int *high,int ind){
    int h;
    //right is higher
    if(high[ind+1]<high[ind]){
        h=high[ind+1];
        output[h-1][ind+1]=1;
        output[h-2][ind+1]=1;
        output[h][ind]=1;
        output[h-1][ind]=1;
        high[ind]=h-1;
        high[ind+1]=h-2;
        for(int i=h;i>h-3;i--)
            output[i][0]=1;
    }
    //left is higher or as high as right
    else{
        h=high[ind];
        output[h-1][ind]=1;
        output[h-2][ind]=1;
        output[h-2][ind+1]=1;
        output[h-3][ind+1]=1;
        high[ind]=h-2;
        high[ind+1]=h-3;
        for(int i=h-1;i>h-4;i--)
            output[i][0]=1;
    }
}
void I1(int **output,int *high,int ind){
    int h=high[ind];
    for(int i=h-1;i>h-5;i--){
        output[i][ind]=1;
        output[i][0]=1;
    }
    high[ind]=h-4;
}
void I2(int **output,int *high,int ind){
    int h;
    //no matter which column is the highest,the processes below are the same
    h=min(min(high[ind],high[ind+1]),min(high[ind+2],high[ind+3]));
    for(int i=ind;i<ind+4;i++){
        output[h-1][i]=1;
        high[i]=h-1;
    }
    output[h-1][0]=1;
}
void O(int **output,int *high,int ind){
    int h;
    //no matter which column is the highest,the processes below are the same
    h=min(high[ind],high[ind+1]);
    for(int i=ind;i<ind+2;i++){
        output[h-1][i]=1;
        output[h-2][i]=1;
        high[i]=h-2;
    }
    for(int i=h-1;i>h-3;i--)
        output[i][0]=1;
}
void eliminate(int **output,int *high,int row,int col){
    int check=0;                       //if check==row,then eliminate the row
    int checkrow=4;
    while(1){
        if(checkrow==row+4) break;
        else{
            if(output[checkrow][0]==1){
            for(int i=1;i<col+1;i++){
                if(output[checkrow][i]==0){
                    check=0;
                    break;
                }
                else check++;
            }
            }
            else{
                checkrow++;
                continue;
            }
            if(check==col){                                  //eliminate
                check=0; 
                for(int k=checkrow;k>0;k--)                  //move upper rows down 
                    for(int l=1;l<col+1;l++)
                        output[k][l]=output[k-1][l];
                for(int k=1;k<col+1;k++)                     //make sure row(0) would be all 0
                    output[0][k]=0;        
            }
            else checkrow++;  
        }  
    }                      
    for(int i=0;i<row+4;i++)            //intitialize the record for changing of every row
        output[i][0]=0;
    int check1=0;                         
    for(int i=1;i<col+1;i++){           //find the highest row in every col
        for(int j=0;j<row+4;j++){   
            if(output[j][i]==1){
                high[i]=j;
                check1=0;
                break;
            }
            else check1++;
        }
        if(check1==row+4){          //if check1==row+4,then means that col is empty
            high[i]=row+4;
            check1=0;
        }    
    }
}