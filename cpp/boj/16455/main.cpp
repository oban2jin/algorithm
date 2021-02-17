#include <iostream>
#include <vector>
using namespace std;
int partition2(vector<int> &a,int S,int E){
    int R = rand()%(E-S+1)+S;
    swap(a[S],a[R]);
    int pivot = a[S]; int i = S; 
    for(int j=S+1;j<=E;j++){
        if(a[j]<=pivot){
            ++i; swap(a[i],a[j]);
        }
    }
    swap(a[S],a[i]);
    return i;
}
int partition(vector<int> &a,int S,int E){
    int R = rand()%(E-S+1)+S;
    swap(a[S],a[R]);
    int pivot = a[S]; int l = S+1; int r = E;
    while(l<=r){
        while(a[l]<=pivot && l<=E)l++;
        while(pivot<=a[r] && (S+1)<=r)r--;
        if(l<=r)swap(a[l],a[r]);
    }
    swap(a[S],a[r]);
    return r;
}
int quickselect(vector<int> &a,int S,int E,int k){
    int nth = partition2(a,S,E);
    if(nth==k)return a[nth];
    else if (nth > k) return quickselect(a, S, nth - 1, k);
    else if (nth < k) return quickselect(a, nth + 1, E, k);
}
int kth(vector<int> &a,int k){
    int ans = quickselect(a,0,a.size()-1,--k);
    return ans;
}
int main(){
    vector<int> A; 
    A.push_back(11); 
    A.push_back(1); A.push_back(2); A.push_back(3); A.push_back(4); A.push_back(5); 
    A.push_back(6); A.push_back(7); A.push_back(8); A.push_back(9); A.push_back(10); 
    A.push_back(12); A.push_back(13); A.push_back(14); A.push_back(15);  
    A.push_back(16); A.push_back(17); A.push_back(18); A.push_back(19); A.push_back(20);
    cout << kth(A,11);      
    return 0;
}