#include <bits/stdc++.h>
using namespace std;

namespace Dinic {
    const int V = 32, E = 2048, INF = 1e9;
    struct edge {
        int to, next, cap, flow;
        edge() {}
        edge(int _to, int _next, int _cap) : to(_to), next(_next), cap(_cap), flow(0) {}
    } eg[E];
    int head[V], cur[V], dis[V], ecnt, s, t;
    bool vis[V];

    void init() {
        memset(head, 0xff, sizeof(head));
        ecnt = 0;
    }

    void addedge(int from, int to, int cap) {
        eg[ecnt] = edge(to, head[from], cap);
        head[from] = ecnt++;
        eg[ecnt] = edge(from, head[to], 0);
        head[to] = ecnt++;
    }

    bool bfs() {
        memset(vis, 0, sizeof(vis));
        queue<int> que;
        que.push(s);
        dis[s] = 0;
        vis[s] = true;
        while(!que.empty()) {
            int x = que.front();
            que.pop();
            for(int i = head[x]; i != -1; i = eg[i].next) {
                const edge& e = eg[i];
                if(!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = true;
                    dis[e.to] = dis[x] + 1;
                    que.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int dfs(int x, int a) {
        if(x == t || a == 0) return a;
        int flow = 0, f;
        for(int& i = cur[x]; i != -1; i = eg[i].next) {
            edge& e = eg[i];
            if(dis[x] + 1 == dis[e.to]) {
                f = dfs(e.to, min(e.cap - e.flow, a));
                if(f <= 0) continue;
                e.flow += f;
                eg[i ^ 1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }

    int solve(int _s, int _t) {
        s = _s; t = _t;
        int flow = 0;
        while(bfs()) {
            memcpy(cur, head, sizeof(cur));
            flow += dfs(s, INF);
        }
        return flow;
    }
};

int main() {
    int n, m;
    int T;
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        Dinic::init();
        scanf("%d %d", &n, &m);
        for(int i = 0; i < m; ++i) {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            Dinic::addedge(u, v, c);
        }
        printf("Case %d: %d\n", t, Dinic::solve(1, n));
    }
    return 0;
}
