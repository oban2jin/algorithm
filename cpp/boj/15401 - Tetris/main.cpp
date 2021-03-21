#include <iostream>
using namespace std;
char S[10][3][3] = {
                        {{0,1,0},{1,1,1},{0,1,0}}, {{1,1,1},{1,0,0},{1,0,0}},
                        {{1,1,0},{0,1,1},{0,0,1}}, {{0,1,1},{0,1,0},{1,1,0}},
                        {{1,1,0},{0,1,0},{0,1,1}}, {{0,1,0},{0,1,0},{1,1,1}},  
                        {{0,1,0},{1,1,1},{0,1,1}}, {{0,1,0},{0,1,1},{1,1,0}},
                        {{0,1,1},{1,1,1},{1,1,0}}, {{0,0,1},{1,1,1},{1,1,0}}               
                    };
int SB[10][4];
void convertB(int d,int r){
    int tmp = 0; int cnt = 8;
    for(int i=2;0<=i;i--){
        for(int j=0;j<3;j++){
            if(S[d][i][j]==1)tmp = tmp|(1<<(cnt--));
        }
    }
    SB[d][r] = tmp;
}
void printS(int d){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(S[d][i][j]==1)cout << "*";
            else cout << " ";
        }
        cout << "\n";
    }
    cout << "SB = " << SB[d] << "\n";
    cout << "-------------------" << "\n";   
}
void rotate(int d,int r){
    char tmp[3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            tmp[2-j][i] = S[d][i][j];
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            S[d][i][j] = tmp[i][j];
        }
    }
    convertB(d,r);
    printS(d);
}                    
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    for(int d=0;d<10;d++){
        cout << "D=" << d << "\n";
        for(int i=0;i<4;i++)rotate(d,i);
        cout << "\n";
    }
    return 0;
}