#include <iostream>
#include <algorithm>
#include <queue>
char S[10001];
using namespace std;
struct Trie{
    Trie* go[26];
    Trie* fail;
    bool output;
    Trie(){
        fill(go,go+26,nullptr);
        fail=nullptr;
        output = false;
    }
    ~ Trie (){
        for(int i=0;i<26;i++){
            if(!go[i])delete go[i];
        }
    }
    void insert(char *c){
        if(*c=='\0'){
            output=true;
        }else{
            int idx = *c - 'a';
            if(!go[idx]){
                go[idx] = new Trie();
            }
            go[idx]->insert(c+1);
        }
    }
};
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N; 
    Trie* root = new Trie(); root->fail=root;
    for(int n=0;n<N;n++){
        cin >> S; root->insert(S);
    }
    //do Somethind about construct fail function for all node;
    queue<Trie*> Q; Q.push(root);
    while(!Q.empty()){
        Trie* current = Q.front(); Q.pop();
        for(int idx =0;idx <26;idx++){
            Trie* next = current->go[idx];
            if(!next)continue;
            if(current==root){
                next->fail=root;
            }else{ 
                Trie* dest = current->fail;
                //루트에서 가장 가까운 접미사 노드를 찾는다.
                while(dest!=root && !dest->go[idx]){
                    dest = dest->fail;
                }
                //fail(PX) : go(fail(P),X)
                if(dest->go[idx]){
                    dest = dest->go[idx];
                }
                next->fail = dest;
            }
            if(next->fail->output)next->output=true;
            Q.push(next);   
        }
    }

    int Qs; cin >> Qs;
    for(int q=0;q<Qs;q++){
        cin >> S; 
        Trie* current = root; bool flag = false;
        for(int i=0;S[i]!='\0';i++){
            int next = S[i] - 'a';
            while(current!=root && !current->go[next]){
                current = current -> fail;
            }
            if(current->go[next]){
                current = current->go[next];
            }
            if(current->output){
                flag = true; break;
            }
        }
        (flag) ? cout << "YES\n" : cout << "NO\n";
    }
    return 0;
}