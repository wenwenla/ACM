using ll = long long;
struct seg_tree {
    static const int MAXN = 100005;
    struct Node {
        ll sum, tag;
    } node[MAXN << 2];
    ll arr[MAXN];

    int lson(int x) { return x << 1; }
    int rson(int x) { return (x << 1) + 1; }

    void make(int x, int xl, int xr) {
        if(xl == xr) {
            node[x].sum = arr[xl];
            node[x].tag = 0;
            return;
        }
        int mid = (xl + xr) >> 1;
        make(lson(x), xl, mid);
        make(rson(x), mid + 1, xr);
        node[x].sum = node[lson(x)].sum + node[rson(x)].sum;
        node[x].tag = 0;
    }

    void pushdown(int x, int xl, int xr) {
        node[x].sum += (xr - xl + 1) * node[x].tag;
        if(xl < xr) {
            node[lson(x)].tag += node[x].tag;
            node[rson(x)].tag += node[x].tag;
        }
        node[x].tag = 0;
    }

    void pushup(int x, int xl, int xr) {
        int mid = (xl + xr) >> 1;
        int lcnt = mid - xl + 1, rcnt = xr - mid;
        node[x].sum = node[lson(x)].sum + lcnt * node[lson(x)].tag + node[rson(x)].sum + rcnt * node[rson(x)].tag;
    }

    ll query(int x, int xl, int xr, int ql, int qr) {
        if(xl > qr || xr < ql) return 0;
        if(xl == ql && xr == qr) {
            return node[x].sum + (xr - xl + 1) * node[x].tag;
        }
        ll ans = 0;
        int mid = (xl + xr) >> 1;
        pushdown(x, xl, xr);
        ans += query(lson(x), xl, mid, ql, min(mid, qr));
        ans += query(rson(x), mid + 1, xr, max(ql, mid + 1), qr);
        return ans;
    }

    void update(int x, int xl, int xr, int cl, int cr, ll dt) {
        if(xr < cl || xl > cr) return;
        if(cl == xl && cr == xr) {
            node[x].tag += dt;
            return;
        }
        pushdown(x, xl, xr);
        int mid = (xl + xr) >> 1;
        update(lson(x), xl, mid, cl, min(mid, cr), dt);
        update(rson(x), mid + 1, xr, max(cl, mid + 1), cr, dt);
        pushup(x, xl, xr);
    }
} st;