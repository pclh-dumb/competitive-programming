// 12657
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
struct Node{
    int data;
    Node *next, *prev;
    Node() {next = prev = nullptr;}
};
Node *root, *tail;
Node* cat(Node* cur, int data) { // insert to right
    Node* tmp = new Node();
    tmp->data = data;

    tmp->next = cur->next;
    if(cur->next != nullptr) {
        cur->next->prev = tmp;
    }
    else {
        tail = cur->next;
    }

    tmp->prev = cur;
    cur->next = tmp;
    return tmp;
}
Node* build(int n) {
    Node* cur = new Node();
    cur->data = 1;
    Node* root = new Node();
    root = cur;
    if(n == 1) {
        return cur;
    }
    for(int i = 1; i <= n-2; i++) {
        cur = cat(cur, i+1);
    }
    Node* last = new Node();
    last->data = n;
    last->prev = cur;
    cur->next = last;
    tail = last;
    return root;
}
void rm(Node* cur) {
    if(cur->prev == nullptr) {
        root = cur->next;
        cur->next->prev = nullptr;
        cur->next = nullptr;
        delete cur;
        return;
    }
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    if(cur->next == nullptr) tail = cur->prev;
    delete cur;
}
void swp(Node* a, Node* b) {
    int tmp = a->data;
    a->data = b->data;
    b->data = tmp;
}
int main() {
    int n, m;
    int Case = 1;
    while(scanf("%d %d", &n, &m)) {
        root = build(n);
        while(m--) {
            int kind; scanf("%d", &kind);
            int x, y;
            Node *idxX, *idxY;
            if(kind != 4) scanf("%d %d", &x, &y);
            if(kind == 1) {
                //int nodeCnt = 1;
                for(Node* i = root; i != nullptr; i = i->next) {
                    //printf("data=%d\n", i->data);
                    if(i->data == x) {idxX = i;}
                    if(i->data == y) {idxY = i;}
                    //nodeCnt++
                }
                //printf("x=%d y=%d\n", x, y);
                //printf("%d %d\n", idxX->data, idxY->data);
                if(idxY->prev == idxX) continue;
                if(idxY->prev != nullptr) {
                    rm(idxX);
                    cat(idxY->prev, x);
                }
                else {
                    rm(idxX);
                    Node* xNode = new Node();
                    xNode->data = x;
                    idxY->prev = xNode;
                    xNode->next = idxY;
                }
            }
            else if(kind == 2) {
                //int nodeCnt = 1;
                for(Node* i = root; i != nullptr; i = i->next) {
                    if(i->data == x) idxX = i;
                    if(i->data == y) idxY = i;
                    //nodeCnt++;
                }
                if(idxY->next == idxX) continue;
                cat(idxY, x);
                rm(idxX);
            }
            else if(kind == 3) {
                //int nodeCnt = 1;
                for(Node* i = root; i != nullptr; i = i->next) {
                    if(i->data == x) idxX = i;
                    if(i->data == y) idxY = i;
                    //nodeCnt++;
                }
                //printf("x=%d y=%d\n", idxX->data, idxY->data);
                swp(idxY, idxX);
            }
            else {
                Node *l = root, *r = tail;
                for(; l != r && l->next != r; l = l->next, r = r->prev) {
                    //printf("swap %d %d\n", l->data, r->data);
                    int tmp = l->data;
                    l->data = r->data;
                    r->data = tmp;
                }
                std::swap(l->data, r->data);
            }
            //for(Node* i = root; i != nullptr; i = i->next) printf("%d ", i->data);
            //printf("\n");
        }
        long cnt = 1;
        long long ans = 0;
        for(Node* i = root; i != nullptr; i = i->next) {
            if(cnt % 2) ans += i->data;
            cnt++;
        }
        printf("Case %d: %lld\n", Case++, ans);
    }
    return 0;
}
