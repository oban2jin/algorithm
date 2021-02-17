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
void make_code(Node *head){

}
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    char S[200]; int s; cin >> s >> S;
    Node* head = build_huffman(S,s);
    return 0;
}