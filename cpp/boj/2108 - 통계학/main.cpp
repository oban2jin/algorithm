#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int Ns[500001];
    int E[8001];
	for(int i=0;i<8001;i++)E[i]=0;
    int N; cin >> N; 
    int madi,SM;
	int CNT = 0; 
    for(int n=0;n<N;n++){
        cin >> Ns[n];
        SM += Ns[n];
		 int temp = (temp <= 0) ? abs(temp) : temp + 4000;
        ++E[temp];
		if(CNT<E[temp])CNT=E[temp];
    }
    sort(Ns,Ns+N);
	int MXE = 0;
	vector<int> Xs;
	for(int n=0;n<8001;n++){
		if(CNT==E[n]){
           int mode = (mode <= 4000) ? -mode : mode - 4000;			
			Xs.push_back(mode);
		}
	}
	sort(Xs.begin(),Xs.end());
	MXE = (Xs.size()>=2)?Xs[1]:Xs[0];
    cout << round(SM/(double)N) << endl;
    cout << Ns[N/2] << endl;
    cout << MXE << endl;
    cout << Ns[N-1]-Ns[0] << endl;
}