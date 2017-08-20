#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long lld;
const int MAXN = 100005;
struct P
{
    lld x, y;
}pList[MAXN],ST[MAXN];
lld dist(P a, P b) {
    lld dx = a.x - b.x; lld dy = a.y - b.y;
    return dx*dx + dy*dy;
}
int ccw(P a, P b,P c) {
    lld bx = b.x - a.x; lld by = b.y - a.y;
    lld cx = c.x - a.x; lld cy = c.y - a.y;
    lld val = bx*cy - by*cx;
    if (val < 0) return -1;
    if (val > 0) return 1;
    return 0;
}
bool comp(P a,P b) {
    int t = ccw(pList[1], a, b);
    if (t > 0 || (t==0 && dist(pList[1],a) <= dist(pList[1], b)))return true;
    return false;
}
int N;
int main() {
    // freopen("./sample.txt","r",stdin);
    setbuf(stdout, NULL);
    int idx=1;
    cin >> N; for (int n = 1; n <= N; n++) {
        scanf("%lld%lld", &pList[n].x, &pList[n].y);
        if (pList[n].y < pList[idx].y || (pList[n].y == pList[idx].y && pList[n].x <= pList[idx].x)) idx=n;
    }

    swap(pList[1], pList[idx]);
    sort(pList+2, pList+1+N,comp);

    int top=0 ; ST[top=1] = pList[1];
    for (int i = 2; i <= N; i++) {
        if (top < 2) {
            ST[++top] = pList[i];
        }
        else {
            while (top >= 2 && ccw(ST[top-1],ST[top],pList[i]) <=0) top--; 
            ST[++top] = pList[i];
        }
    }
 
    printf("%d\n", top);
    return 0;
}
