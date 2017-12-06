namespace SPFA {
    const int N = 100010, M = 600010, INF = 0x3f3f3f3f;
    struct edge {
        int to, next, cost;
        edge() {}
        edge(int _to, int _next, int _cost) : to(_to), next(_next), cost(_cost) {}
    } eg[M];
    int head[N], dis[N], cnt[N], tot, incnt[N];

    void init() {
        memset(head, -1, sizeof(head));
        tot = 0;
    }

    void addedge(int from, int to, int cost) {
        eg[tot] = edge(to, head[from], cost);
        head[from] = tot++;
    }

    bool spfa(int s, int n) {
        fill(cnt, cnt + n + 1, 0);
        fill(dis, dis + n + 1, INF);
        fill(incnt, incnt + n + 1, 0);
        queue<int> q;
        q.push(s);
        dis[s] = 0; cnt[s] = 1; incnt[s] = 1;
        while(!q.empty()) {
            int now = q.front();
            q.pop();
            if(incnt[now] == 1) {
                for(int i = head[now]; i != -1; i = eg[i].next) {
                    edge& e = eg[i];
                    if(dis[e.to] > dis[now] + e.cost) {
                        dis[e.to] = dis[now] + e.cost;
                        if(++cnt[e.to] > n) return false;
                        q.push(e.to);
                        ++incnt[e.to];
                    }
                }
            }
            --incnt[now];
        }
        return true;
    }
}