#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lld;
struct P{
	int x; int y;
	bool operator < (const P &o){
		if(x==o.x){
			return y < o.y;
		}else{
			return x < o.x;
		}
	}
};
vector<P> Ps;
int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
	int N; cin >> N;  for (int n = 0; n < N; n++) {
		int x; int y; cin >> x >> y;  Ps.push_back({x,y});
	}
	sort(Ps.begin(),Ps.end());
	lld ANS =0; int cS = 0; int cE = 0; int cL = 0;
	for(int i=0;i<N;i++){
		if(i==0){
			cS = Ps[0].x; cE = Ps[0].y; cL = cE - cS;
			continue;
		}
		//x는 cS보다 같거나, 이후인 값이다.
		P here = Ps[i];
		if( cS<=here.x && here.x<=cE){
			if(cE<here.y){
				cE=here.y; cL = cE - cS;
			}
		}else if(cS < here.x){
			ANS += cL; cS = here.x; cE = here.y; cL = cE - cS;
		}
	}
	cout << ANS + cL;
	return 0;
}