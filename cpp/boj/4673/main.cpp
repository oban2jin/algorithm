#include  <iostream>
using namespace std;
int SN[10001];
void selfNo(int a){
    int rst = a; int A = a;
    int d; int r; 
    while(1){
        d = a/10; r = a%10;
        if(d==0&&r==0)break;
        rst += r; a = d;
    }
    if(rst <= 10000)SN[rst]=A;
}
int main(){
    for(int i=1;i<10001;i++){
        selfNo(i);
    }
    for(int i=1;i<10001;i++){
        if(SN[i]==0)cout << i <<"\n";
    }
    return 0;
}