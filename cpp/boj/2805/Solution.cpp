#include <iostream>
#include <algorithm>
using namespace std;
int N,M;
const int MAXN=1000000;
int D[MAXN];
int BS(int r){
    int low=0; int high = r; int mid;
    while(low<high){
        mid=(low+high)>>1; long long CNT=0;
        for(int n=0;n<N;n++){
            int gap = D[n]-mid;
            if(0<gap)CNT += gap;
        }
cout << "low=" << low << ",high=" << high << ",CNT=" << CNT <<",mid="<<mid<< endl;        
        if(M<CNT){
            low=mid+1;
        }else{
            high=mid;
        }
    }
    return low;
}
int main(){
    cin >> N >> M;
    int MX=0; 
    for(int n=0;n<N;n++){
        scanf("%d",&D[n]); MX<D[n]?MX=D[n]:MX;
    }
    int ANS = BS(MX);
    cout << ANS;
}