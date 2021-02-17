#include <iostream>
using namespace std;
int N,M;
int S[100001];
int main(){
    ios::sync_with_stdio(false);
    cin >> N >> M;
    for(int n=1;n<N+1;n++){
        int c; cin >> c;
        S[n] = S[n-1] + c;
    }
    for(int m=0;m<M;m++){
        int a,b; cin >> a >> b;
        cout << S[b]-S[a-1] << endl;
    }
    return 0;
}