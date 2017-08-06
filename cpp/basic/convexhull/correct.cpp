#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>
using namespace std;
  
struct PT
{
    long long x, y;
};
PT basePoint;
double dist(PT a, PT b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
 
long long left(PT p1, PT p2, PT p3)
{
    return ((p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x)); 
}
 
bool anglegt(PT a, PT b)
{
    long long c = left(basePoint, a, b);
    //return c > 0 || c == 0 && (a.y < b.y || a.y == b.y && a.x < b.x);
    if(c > 0) return 1;
    if(c < 0) return 0;
    else
    {
        //return (a.y < b.y || a.y == b.y && a.x < b.x);
        if(dist(basePoint, a) < dist(basePoint, b))
            return 1;
        else
        {
            return 0;
        } 
    } 
}
  
  
int main()
{
  
    int n;
    cin >> n;
    vector<PT> pts;
    for(int i=0; i<n; i++)
    {
        PT temp;
        cin >> temp.x >> temp.y;
        temp.x *= -1;
        temp.y *= -1;
        pts.push_back(temp);
    }
    int minIndex = 0;
    for(int i=0; i<pts.size(); i++)
    {
        if(pts[i].y < pts[minIndex].y || pts[i].y == pts[minIndex].y && pts[i].x < pts[minIndex].x)
        {
            minIndex = i;
        } 
    }
    basePoint = pts[minIndex];
    swap(pts[0], pts[minIndex]);
    sort(pts.begin() + 1, pts.end(), anglegt);
  
    vector<PT> convex;
    convex.push_back(pts[0]);
    convex.push_back(pts[1]);
  
    for(int i=2; i<pts.size(); i++)
    {
        while(convex.size() >= 2 && left(convex[convex.size() - 2], convex.back(), pts[i]) <= 0)
        {
            convex.pop_back();
        }
        convex.push_back(pts[i]); 
    } 
    int solution = 0;
    solution = convex.size();
    cout << solution;
  
    return 0;
}