const int N = 1e5 + 10;
int fa[N];

inline void init_dst() {
    memset(fa, 0xff, sizeof(fa));
}

inline int _getfa(int u) {
    int rt = u;
    while(fa[rt] > 0) rt = fa[rt];
    while(fa[u] > 0) {
        int tmp = fa[u];
        fa[u] = rt;
        u = tmp;
    }
    return rt;
}

inline void _union(int u, int v) {
    int uf = _getfa(u);
    int vf = _getfa(v);
    if(uf != vf) {
        if(fa[uf] < fa[vf]) {
            fa[uf] += fa[vf];
            fa[vf] = uf;
        } else {
            fa[vf] += fa[uf];
            fa[uf] = vf;
        }
    }
}