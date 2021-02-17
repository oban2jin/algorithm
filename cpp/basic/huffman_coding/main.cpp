#include <iostream>
#include <queue>
using namespace std;
struct Node{
    Node* left;
    Node* right;
    char c;
    bool leaf;
};
struct HTNode{
    Node *node;
    int cnt;
};
bool operator <(const HTNode &a,const HTNode &b){
    return b.cnt < a.cnt;
}
Node* build_huffman(char* S,int len){
    int cnt[256] = {};
    for(int i=0;i<len;i++){
        ++cnt[S[i]];
    }
    priority_queue<HTNode> Q;
    for(int i=0;i<256;i++){
        if(cnt[i]){
            Node* node = new Node();
            node->leaf=true; node->c=i; 
            HTNode nnode = {node,cnt[i]};
            Q.push(nnode);
        }
    }
    while(Q.size()!=1){
        Node *node = new Node(); node->leaf=false; node->c=0;
        HTNode nnode = {node,0};

        HTNode lnode = Q.top(); Q.pop();
        HTNode rnode = Q.top(); Q.pop();
        nnode.cnt = lnode.cnt + rnode.cnt;
        nnode.node->left = lnode.node;
        nnode.node->right = rnode.node;
        Q.push(nnode);
    }
    return Q.top().node;
}
int sz;
char* code[256];
char code_binary[200];
void make_code(Node *node){
    if(node->leaf){
        code[node->c] = new char[sz];
        for(int i=0;i<sz;i++){
            code[node->c][i] = code_binary[i];
        }
        return;
    }
    code_binary[sz++]='0'; make_code(node->left); --sz;
    code_binary[sz++]='1'; make_code(node->right); --sz;
}
int encode(Node *node,char* Ori, char* Chg,int len){
    sz=0;
    make_code(node); int idx=0;
    for(int i=0;i<len;i++){
        for(int j=0;code[Ori[i]][j];j++){
            Chg[idx++]=code[Ori[i]][j];
        }
    }
    return idx;
}
int decode(Node *head,char* Ori,char* Chg,int len){
    int idx = 0;
    for(int i=0;i<len;){
        Node* node = head;
        while(!node->leaf){
            if(Chg[i++]=='0'){
                node = node->left;
            }else{
                node = node->right;
            }
        }
        Ori[idx++]=node->c;
    }
    return idx;
}
void printDebug(char *S,int s){
    for(int i=0;i<s;i++){
        cout << S[i] << " => ";
        for(int j=0;code[S[i]][j];j++){
            cout << code[S[i]][j];
        }
        cout << "\n";
    }
}
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    char S[200] = {}; 
    char C[1000] = {};
    int s=0; cin >> S; 
    while(1){
        if(S[s]=='\0')break;
        ++s;
    }
    cout << "S=>" << S;
    Node* head = build_huffman(S,s);
    int ecnt = encode(head,S,C,s);
    cout << "\nE=>"; for(int i=0;i<ecnt;i++)cout << C[i];
    memset(S,0,sizeof(S));
    int dcnt = decode(head,S,C,ecnt);
    cout << "\nD=>"; for(int i=0;i<dcnt;i++)cout << S[i]; cout << "\n";
    return 0;
}