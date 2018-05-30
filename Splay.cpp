#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
struct Node {
    int val, parent, child[2], sz;
} node[N];
int fp[N], fi, ni;

inline int get_node() { return (fi == 0) ? ni++ : fp[--fi]; }
inline void del_node(int i) { fp[fi++] = i; }
void init() { fi = 0; ni = 0; }

void R(int rt) {
    int p = node[rt].parent;
    //maintain size
    int tmp = node[p].sz - node[rt].sz;
    node[p].sz = tmp + (node[rt].child[1] == -1 ? 0 : node[node[rt].child[1]].sz);
    node[rt].sz = node[p].sz + (node[rt].child[0] == -1 ? 0 : node[node[rt].child[0]].sz) + 1;

    node[rt].parent = node[p].parent;
    if(node[p].parent != -1) {
        if(node[node[p].parent].child[0] == p) node[node[p].parent].child[0] = rt;
        else node[node[p].parent].child[1] = rt;
    }
    node[p].parent = rt;

    node[p].child[0] = node[rt].child[1];
    if(node[rt].child[1] != -1) node[node[rt].child[1]].parent = p;
    node[rt].child[1] = p;
}

void L(int rt) {
    int p = node[rt].parent;
    //maintain size
    int tmp = node[p].sz - node[rt].sz;
    node[p].sz = tmp + (node[rt].child[0] == -1 ? 0 : node[node[rt].child[0]].sz);
    node[rt].sz = node[p].sz + (node[rt].child[1] == -1 ? 0 : node[node[rt].child[1]].sz) + 1;

    node[rt].parent = node[p].parent;
    if(node[p].parent != -1) {
        if(node[node[p].parent].child[0] == p) node[node[p].parent].child[0] = rt;
        else node[node[p].parent].child[1] = rt;
    }
    node[p].parent = rt;
    node[p].child[1] = node[rt].child[0];
    if(node[rt].child[0] != -1) node[node[rt].child[0]].parent = p;
    node[rt].child[0] = p;
}

void zig_zag(int rt) {
    int p;
    while((p = node[rt].parent) != -1) {
        int g = node[p].parent;
        if(g == -1) {
            if(rt == node[p].child[0]) R(rt);
            else L(rt);
        } else {
            if(rt == node[p].child[0]) {
                if(p == node[g].child[0]) {
                    R(p); R(rt); //RR
                } else if(p == node[g].child[1]) {
                    R(rt); L(rt); //RL
                }
            } else if(rt == node[p].child[1]) {
                if(p == node[g].child[0]) {
                    L(rt); R(rt); //LR
                } else if(p == node[g].child[1]) {
                    L(p); L(rt);
                }
            }
        }
    }
}

int find(int rt, int x) {
    int p = rt;
    while(rt != -1) {
        p = rt;
        if(x < node[rt].val) {
            rt = node[rt].child[0];
        } else if(x > node[rt].val) {
            rt = node[rt].child[1];
        } else {
            p = rt;
            break;
        }
    }
    zig_zag(p);
    return p;
}

int ins(int rt, int val) {
    int pn = get_node();
    node[pn].val = val;
    node[pn].sz = 1;
    if(rt == -1) {
        node[pn].child[0] = node[pn].child[1] = node[pn].parent = -1;
    } else {
        int p = rt;
        //find_pos
        while(rt != -1) {
            ++node[rt].sz;
            if(val < node[rt].val) {
                p = rt;
                rt = node[rt].child[0];
            } else {
                p = rt;
                rt = node[rt].child[1];
            }
        }
        //ins
        node[pn].child[0] = node[pn].child[1] = -1;
        node[pn].parent = p;
        if(val < node[p].val) node[p].child[0] = pn;
        else node[p].child[1] = pn;
        //zig_zag
        zig_zag(pn);
    }
    return pn;
}

int del(int rt, int x) {
    int res = find(rt, x);
    assert(node[res].val == x);
    //show(res);
    int lrt = node[res].child[0], rrt = node[res].child[1];
    del_node(res);
    if(lrt == -1 && rrt == -1) return -1;
    if(lrt == -1) { node[rrt].parent = -1; return rrt; }
    if(rrt == -1) { node[lrt].parent = -1; return lrt; }
    node[lrt].parent = -1;
    node[rrt].parent = -1;
    while(node[lrt].child[1] != -1) {
        lrt = node[lrt].child[1];
    }
    zig_zag(lrt);
    assert(node[lrt].child[1] == -1);
    node[lrt].child[1] = rrt;
    node[rrt].parent = lrt;
    node[lrt].sz += node[rrt].sz;
    return lrt;
}

int kth(int rt, int k) {
    while(rt != -1) {
        int lc = (node[rt].child[0] == -1) ? 0 : node[node[rt].child[0]].sz;
        if(lc == k - 1) return node[rt].val;
        if(lc > k - 1) {
            rt = node[rt].child[0];
        } else {
            k -= lc + 1;
            rt = node[rt].child[1];
        }
    }
    return -1;
}

int sprk(int rt, int x) {
    int ans = 0;
    while(rt != -1) {
        if(node[rt].val < x) {
            ans += (node[rt].child[0] == -1 ? 1 : node[node[rt].child[0]].sz + 1);
            rt = node[rt].child[1];
        } else {
            rt = node[rt].child[0];
        }
    }
    return ans + 1;
}

int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        init();
        int rt = -1;
        while(n--) {
            int op, x;
            scanf("%d %d", &op, &x);
            if(op == 1) {
                rt = ins(rt, x);
            } else if(op == 2) {
                rt = del(rt, x);
            } else if(op == 3) {
                printf("%d\n", sprk(rt, x));
            } else if(op == 4) {
                printf("%d\n", kth(rt, x));
            } else if(op == 5) {
                printf("%d\n", kth(rt, sprk(rt, x) - 1));
            } else {
                //printf("DEBUG %d\n", sprk(rt, x + 1));
                printf("%d\n", kth(rt, sprk(rt, x + 1)));
            }
        }
    }
    return 0;
}
