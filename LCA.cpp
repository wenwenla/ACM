#include <bits/stdc++.h>
using namespace std;

/*
 * https://cn.vjudge.net/problem/HDU-2586
 * O(1) getlca
 * */

const int VN = 50000, EN = 100000;

struct ST {
    //1 base, query O(1)
    int dp[VN << 1][20];
    int n;
    int arr[VN << 1];

    void make(int _n) {
        n = _n;
        for(int i = 1; i <= n; ++i) {
            dp[i][0] = i;
        }
        for(int j = 1; (1 << j) <= n; ++j) {
            for(int i = 1; (i + (1 << (j - 1))) <= n; ++i) {
                int l = dp[i][j - 1], r = dp[i + (1 << (j - 1))][j - 1];
                dp[i][j] = arr[l] < arr[r] ? l : r;
            }
        }
    }

    int query(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        int li = dp[l][k], ri = dp[r - (1 << k) + 1][k];
        return arr[li] < arr[ri] ? li : ri;
    }
} st;

struct edge {
    int to, cost, next;
    edge() {}
    edge(int _to, int _cost, int _next) : to(_to), cost(_cost), next(_next) {}
} eg[EN];
int head[VN], dis[VN], id[VN], la[VN << 1], lacnt, tot;
bool vis[VN];

void init() {
    memset(head, 0xff, sizeof(head));
    memset(vis, 0x00, sizeof(vis));
    tot = lacnt = 1;
}

void addedge(int from, int to, int cost) {
    eg[tot] = edge(to, cost, head[from]);
    head[from] = tot++;
}

void dfs(int v, int height) {
    vis[v] = true;
    id[v] = lacnt;
    st.arr[lacnt] = height;
    la[lacnt++] = v;
    for(int i = head[v]; i != -1; i = eg[i].next) {
        if(!vis[eg[i].to]) {
            dis[eg[i].to] = dis[v] + eg[i].cost;
            dfs(eg[i].to, height + 1);
            st.arr[lacnt] = height;
            la[lacnt++] = v;
        }
    }
}

int lca(int u, int v) {
    int l = min(id[u], id[v]), r = max(id[u], id[v]);
    return la[st.query(l, r)];
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, q;
        init();
        scanf("%d %d", &n, &q);
        for(int i = 0; i != n - 1; ++i) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            addedge(u, v, w);
            addedge(v, u, w);
        }
        dfs(1, 0);
        st.make(lacnt);
        while(q--) {
            int u, v;
            scanf("%d %d", &u, &v);
            int ans = dis[u] + dis[v] - 2 * dis[lca(u, v)];
            printf("%d\n", ans);
        }
    }
    return 0;
}
