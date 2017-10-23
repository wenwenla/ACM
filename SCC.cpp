namespace SCC {
    //id 1 to n
    const int VN = 10005, EN = 100005;
    struct edge {
        int to, next;
        edge() {}
        edge(int _to, int _next) : to(_to), next(_next) {}
    } se[EN], re[EN];
    int shead[VN], rhead[VN], vs[VN], cmp[VN], vidx, stot, rtot, n;
    bool vis[VN];

    void init(int _n) {
        n = _n;
        stot = rtot = 0;
        memset(shead, 0xff, sizeof(shead));
        memset(rhead, 0xff, sizeof(rhead));
        vidx = 0;
    }

    void addedge(int from, int to) {
        se[stot] = edge(to, shead[from]);
        shead[from] = stot++;
        re[rtot] = edge(from, rhead[to]);
        rhead[to] = rtot++;
    }

    void dfs(int v) {
        vis[v] = true;
        for(int i = shead[v]; i != -1; i = se[i].next) {
            if(!vis[se[i].to]) {
                dfs(se[i].to);
            }
        }
        vs[vidx++] = v;
    }

    void rdfs(int v, int k) {
        vis[v] = true;
        cmp[v] = k;
        for(int i = rhead[v]; i != -1; i = re[i].next) {
            if(!vis[re[i].to]) {
                rdfs(re[i].to, k);
            }
        }
    }

    int scc() {
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= n; ++i) {
            if(!vis[i]) dfs(i);
        }
        memset(vis, 0, sizeof(vis));
        int k = 0;
        for(int i = vidx - 1; i >= 0; --i) {
            if(!vis[vs[i]]) rdfs(vs[i], k++);
        }
        return k;
    }
}