#include <bits/stdc++.h>
using namespace std;
constexpr int N = 100005;

struct MergeTree {
    vector<int> val[N << 2];
    inline int lson(int rt) { return rt * 2; }
    inline int rson(int rt) { return rt * 2 + 1; }
    void build(int rt, int l, int r) {
        val[rt].clear();
        if(l == r) {
            int x;
            fastio::read_num(x);
            val[rt].push_back(x);
            return;
        }
        int mid = (l + r) / 2;
        build(lson(rt), l, mid);
        build(rson(rt), mid + 1, r);
        auto& ls = val[lson(rt)];
        auto& rs = val[rson(rt)];
        merge(ls.begin(), ls.end(), rs.begin(), rs.end(), back_inserter(val[rt]));
    }
    int query(int rt, int l, int r, int ql, int qr, int v) {
        if(l > qr || r < ql) return 0;
        if(l >= ql && r <= qr) {
            return lower_bound(val[rt].begin(), val[rt].end(), v) - val[rt].begin();
        }
        int ans = 0, mid = (l + r) / 2;
        ans += query(lson(rt), l, mid, ql, qr, v);
        ans += query(rson(rt), mid + 1, r, ql, qr, v);
        return ans;
    }
    void show(int rt, int l, int r) {
        printf("%d %d\n", l, r);
        for(auto i : val[rt]) {
            printf("%d ", i);
        }
        puts("");
        if(l == r) return;
        int mid = (l + r) / 2;
        show(lson(rt), l, mid);
        show(rson(rt), mid + 1, r);
    }
} tr;
/*二分求第K大*/