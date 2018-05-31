#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N= 1e6 + 10;
struct Bit {
    ll bit[N];
    void init() { memset(bit, 0, sizeof(bit)); }

    void add(int i, ll v) {
        while(i < N) {
            bit[i] += v;
            i += (-i) & i;
        }
    }

    ll sum(int i) {
        ll ret = 0;
        while(i) {
            ret += bit[i];
            i -= (-i) & i;
        }
        return ret;
    }
} bit[2];

struct Tree {
    ll sum[N << 2], tag[N << 2];
    inline int lson(int rt) { return rt * 2; }
    inline int rson(int rt) { return rt * 2 + 1; }
    void build(int rt, int l, int r) {
        sum[rt] = tag[rt] = 0;
        if(l == r) return;
        int mid = (l + r) / 2;
        build(lson(rt), l, mid);
        build(rson(rt), mid + 1, r);
    }
    void push_up(int rt, int l, int r) {
        if(l != r) {
            int mid = (l + r) / 2;
            ll ls = sum[lson(rt)] + (mid - l + 1) * tag[lson(rt)];
            ll rs = sum[rson(rt)] + (r - mid) * tag[rson(rt)];
            sum[rt] = ls + rs;
        }
    }
    void push_down(int rt, int l, int r) {
        if(l != r) {
            int mid = (l + r) / 2;
            tag[lson(rt)] += tag[rt];
            tag[rson(rt)] += tag[rt];
            sum[rt] += (r - l + 1) * tag[rt];
            tag[rt] = 0;
        }
    }
    ll query(int rt, int l, int r, int ql, int qr) {
        if(l > qr || r < ql) return 0;
        if(l >= ql && r <= qr) return sum[rt] + tag[rt] * (r - l + 1);
        push_down(rt, l, r);
        int mid = (l + r) / 2;
        ll ans = query(lson(rt), l, mid, ql, qr) + query(rson(rt), mid + 1, r, ql, qr);
        push_up(rt, l, r);
        return ans;
    }
    void update(int rt, int l, int r, int ul, int ur, int dt) {
        if(l > ur || r < ul) return;
        if(l >= ul && r <= ur) {
            tag[rt] += dt;
            return;
        }
        push_down(rt, l, r);
        int mid = (l + r) / 2;
        update(lson(rt), l, mid, ul, ur, dt);
        update(rson(rt), mid + 1, r, ul, ur, dt);
        push_up(rt, l, r);
    }
    void show(int rt, int l, int r) {
        printf("%d %d %lld %lld\n", l, r, sum[rt], tag[rt]);
        if(l == r) return;
        int mid = (l + r) / 2;
        show(lson(rt), l, mid);
        show(rson(rt), mid + 1, r);
    }
} tr;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    tr.build(1, 1, n);
    while(m--) {
        int o, l, r, v;
        scanf("%d%d%d%d", &o, &l, &r, &v);
        if(o == 0) {
            tr.update(1, 1, n, l, r, v);
            //tr.show(1, 1, n);
        } else {
            printf("%lld\n", tr.query(1, 1, n, l, r));
        }
    }
    return 0;
}
