#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int MAXN=15,MAXK=2;
string SC[MAXK*2]; int NC[MAXK*2]; 
vector<bool> used;
int N,K,NN;
int toNumber(const string& v){
    int rslt=0;
    for(int i=0;i<v.size();i++){
        if(v[i]=='1')rslt+=(1<<(v.size()-i-1));
    }
    return rslt;
}
string toBinaryString(int v){
    string rslt;
    if(v==0){
        for(int i=0;i<N;i++)rslt='0'+rslt;
        return rslt;
    }
    while(v!=0){
        if((v&1)==1)rslt='1'+rslt;
        else rslt='0'+rslt;
        v = v>>1;
    }
    while(rslt.size()<N){
        rslt='0'+rslt;
    }
    return rslt;
}
bool isGrayCode(const int& a, const int &b){
    int c = a^b;  if((c & c-1) == 0) return true;
    return false;
}
bool GrayCode2(int l,int r,int cnt,vector<int>& selected){
    //printf("l=[%d],r=[%d],cnt=[%d],selected.size=[%lu]\n",l,r,cnt,selected.size());
    //for(int& x:selected)printf("%d ",x);
    //printf("\n");
    if(r<l){
        if(isGrayCode(l,r))return true;
        return false;
    }
    bool rslt=false;
    bool flag = false; int fixedNext=0; int last = ((cnt&1)==0)?selected[l-1]:selected[(r+1)%NN];
    for(int k=0;k<2*K;k++){
        if(last==NC[k]){
            flag=true;  fixedNext=((k&1)==0)?NC[k+1]:NC[k-1]; 
            break;
        }
    }

    bool lr=false; int nextL=l,nextR=r,curIdx=l;
    if((cnt&1)==0){
        lr=true; ++nextL;
    }
    else{
        --nextR; curIdx=r;
    }
    //printf("lr=[%d],flag=[%d],fixedNext=[%d],last=[%d]\n",lr,flag,fixedNext,last);
    if(flag && !used[fixedNext]){
        used[fixedNext]=true;  selected[curIdx]=fixedNext; rslt=GrayCode2(nextL,nextR,++cnt,selected);
        if(!rslt){
            used[fixedNext]=false;selected[curIdx]=-1;
        }
    }else{
        for(int next=0;next<NN;next++){
            if(!used[next] && isGrayCode(next,last)){
                used[next]=true; selected[curIdx]=next; rslt=GrayCode2(nextL,nextR,++cnt,selected);
                if(!rslt){
                    used[next]=false;selected[curIdx]=-1;
                }else break;
            }   
        }
    }
    return rslt;
}

bool GrayCode(const int& used,const int& last,vector<int>& code){
    printf("used=[%d],last=[%d],code.size=[%lu]\n",used,last,code.size());
    if(used == ((1<<NN)-1))return isGrayCode(code.front(),code.back());
    int rslt=false;
    bool flag = false; int fixedNext=0;for(int k=0;k<2*K;k++){
        if(last==NC[k]){
            flag=true;  fixedNext=((k&1)==0)?NC[k+1]:NC[k-1]; 
            break;
        }
    }
    if(flag && (used & (1<<fixedNext))==0){
        printf("fixedNext=[%d]\n",fixedNext);
        int nextUsed = used + (1<<fixedNext); code.push_back(fixedNext);
        rslt = GrayCode(nextUsed,fixedNext,code);
        if(!rslt)code.pop_back();
    }else{
        for(int next=0;next<NN;next++){
            if(((used & (1<<next))==0) && isGrayCode(last,next)){
                int nextUsed = used + (1<<next); code.push_back(next);
                rslt = GrayCode(nextUsed,next,code);
                if(!rslt)code.pop_back();
                else break;
            }
        }
    }
    return rslt;
}
int main(){
    freopen("sample.txt","r",stdin);
    cin >> N >> K; NN = 1 << N; used=vector<bool>(NN,false);
    for(int k=0;k<K;k++){
        string a,b;
        cin >> SC[2*k] >> SC[2*k+1];
        NC[2*k] = toNumber(SC[2*k]); NC[2*k+1]=toNumber(SC[2*k+1]);
    }
    //printf("N=[%d],NN=[%d],K=[%d]\n",N,NN,K);
    // for(int i=0;i<2*K;i++)printf("%d\n",NC[i]);
    // for(int i=0;i<2*K;i++)printf("%s\n",SC[i].c_str());

    // vector<int> code; code.push_back(0);
    // if(GrayCode(1,0,code)){
    //     for(int i=0;i<code.size();i++){
    //         printf("%s ",toBinaryString(code[i]).c_str());
    //         if((i+1)%8==0)printf("\n");
    //     }
    // }else printf("-1");
    vector<int> code = vector<int>(NN,-1); code[0]=0; used[0]=true;
    if(GrayCode2(1,NN-1,0,code)){
        for(int i=0;i<code.size();i++){
            printf("%s ",toBinaryString(code[i]).c_str());
            if((i+1)%8==0)printf("\n");
        }
    }else printf("-1");

    return 0;
}