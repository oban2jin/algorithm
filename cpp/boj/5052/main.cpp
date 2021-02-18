#include <iostream>
#include <memory.h>
#include <algorithm>
using namespace std;
char D[10000][11];
struct R{
    int i; int cnt;
}; R C[10000];
struct Node{
    bool leaf;
    Node* next[10];
    Node(bool leaf):leaf(leaf){
        memset(next,0,sizeof(next));
    }
    bool insert(char *c){
        if(c[0]=='\0'){
            this->leaf=true; return true;
        }
        int idx = c[0]-'0';
        if(next[idx]!=0){
            if(next[idx]->leaf){
                return false;
            }else{
                return  next[idx]->insert(c+1);
            }
        }else{
            Node* node = new Node(false);
            next[idx]=node; 
            return node->insert(c+1);
        }
    }
};
bool comp(const R& a,const R& b){
    return a.cnt < b.cnt;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    int T; cin >> T;
    for(int t=0;t<T;t++){
        int N; cin >> N;
        for(int n=0;n<N;n++){
            cin >> D[n]; 
            int cnt=0; for(int i=0;D[n][i]!='\0';i++)++cnt;
            C[n].i=n; C[n].cnt=cnt;
        }
        sort(C,C+N,comp);
        bool flag=true;
        Node* head = new Node(false);
        for(int n=0;n<N;n++){
            if(!head->insert(D[C[n].i])){
                flag=false; break;
            }
        }
        if(flag){
            cout << "YES" << "\n";
        }else{
            cout << "NO" << "\n";
        }
    }
}