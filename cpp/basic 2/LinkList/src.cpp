#include <iostream>

struct ListNode{
    int value; ListNode* Perv; ListNode* Next;
    int size;
    ListNode(){
        value=0;Perv=NULL; Next=NULL;size=0;
    }
    void add(int v){
        ListNode* Iter = this;
        while(Iter->Next!=NULL){
            // printf("Iter->value=[%d]\n",Iter->value);
            Iter=Iter->Next;
        }
        ListNode * node = new ListNode(); ++this->size;
        node ->value = v; 
        Iter->Next=node; node->Perv = Iter;
    };
};
int main(){
    ListNode* Plist = new ListNode();

    Plist->add(20); Plist->add(20); Plist->add(30); Plist->add(40); Plist->add(50); Plist->add(60);

    ListNode* Iter = Plist;
    while(Iter->Next!=NULL){
        printf("Iter->Value=[%d]\n",Iter->value);
        Iter=Iter->Next;
    }
    printf("Plist size=[%d]\n",Plist->size);
    return 0;
}