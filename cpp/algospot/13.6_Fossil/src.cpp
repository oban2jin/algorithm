#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXNM = 100;
struct Point{
    double x,y;
}Ni[MAXNM], Mi[MAXNM];
typedef pair<Point,Point> ppp;
vector<ppp> uHull,lHull;
int T,N,M;
double vertical(double x){
    double rslt;
    return rslt;
}
int main(){
    freopen("./sample.txt","r",stdin);
    cin >> T; for(int t=0;t<T;t++){
        uHull.clear(); lHull.clear();
        cin >> N >> M;
        for(int n=0;n<N;n++)scanf("%lf%lf",&Ni[n].x,&Ni[n].y); 
        for(int m=0;m<M;m++)scanf("%lf%lf",&Mi[m].x,&Mi[m].y);
        //윗쪽, 아랫쪽 선분을 구분
        for(int i=0;i<N;i++){
            if(Ni[i].x<Ni[(i+1)%N].x){
                lHull.push_back(make_pair(Ni[i],Ni[(i+1)%N]));
            }else{
                uHull.push_back(make_pair(Ni[i],Ni[(i+1)%N]));
            }
        }
        for(int i=0;i<M;i++){
            if(Mi[i].x<Mi[(i+1)%M].x){
                lHull.push_back(make_pair(Mi[i],Mi[(i+1)%M]));
            }else{
                uHull.push_back(make_pair(Mi[i],Mi[(i+1)%M]));
            }
        }

        //삼분 검색
        double lo; double hi;
        for(int iter=0;iter<100;iter++){
            double aab = (2*lo+hi)/3, abb=(lo+2*hi)/3;
            if(vertical(aab) < vertical(abb)){
                lo = aab;
            }else{
                hi = abb;
            }
        }
        printf("%lf\n",vertical(hi));
    }
    return 0;
}