#include <bits/stdc++.h>
using namespace std;

namespace Path {
    using int64 = long long;
    struct edge {
        int to, cost, next;
        edge() {}
        edge(int _to, int _cost, int _next) : to(_to), cost(_cost), next(_next) {}
    } e[12500];
    int tot;
    int head[2505];

    void init_graph() {
        tot = 0;
        memset(head, -1, sizeof(head));
    }

    void addedge(int from, int to, int cost) {
        e[tot] = edge(to, cost, head[from]);
        head[from] = tot++;
    }

    int64 dis[2505];
    bool vis[2505];

    int64 dijkstra(int s, int t) {
        using PLI = pair<int64, int>;
        memset(dis, 0x3f, sizeof(dis));
        memset(vis, 0x00, sizeof(vis));
        priority_queue<PLI, vector<PLI>, greater<PLI>> pq;
        pq.push(PLI(0, s));
        dis[s] = 0;
        while(!pq.empty()) {
            PLI now = pq.top();
            pq.pop();
            if(vis[now.second]) continue;
            vis[now.second] = true;
            for(int i = head[now.second]; i != -1; i = e[i].next) {
                if(!vis[e[i].to] && e[i].cost + now.first < dis[e[i].to]) {
                    dis[e[i].to] = e[i].cost + now.first;
                    pq.push(PLI(dis[e[i].to], e[i].to));
                }
            }
        }
        return dis[t];
    }
}

int main() {
    return 0;
}
