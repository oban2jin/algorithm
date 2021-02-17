#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int Ns[500000];
    int E[8001];
    int N; cin >> N; 
    double ave;
    int madi,MX,MN,SM;
    MX = -4001, MN = 4001;
    for(int n=0;n<N;n++){
        cin >> Ns[n];
        SM += Ns[n];
        if(MX<Ns[n])MX=Ns[n];
        if(Ns[n]<MN)MN=Ns[n];
        ++E[Ns[n]+4000];
    }
    sort(Ns,Ns+N);
    ave  = (double)SM/(double)N;

    int MXE = 0; vector<int> mxe;
    for(int n=0;n<8001;n++){
        if(MXE<=E[n]){
            if(MXE<E[n]){mxe.clear(); MXE=E[n];}
            mxe.push_back(n);
        }
    }
    sort(mxe.begin(),mxe.end());
    int XE = mxe.size() > 1 ? mxe[1]-4000:mxe[0]-4000;
    cout << round(ave) << endl;
    cout << Ns[N/2] << endl;
    cout << XE << endl;
    cout << MX-MN << endl;
}