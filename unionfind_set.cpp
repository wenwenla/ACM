namespace UFS {
	//1 base
    const int N = 1e5 + 10;
    int fa[N];
    inline void init() { memset(fa, 0xff, sizeof(fa)); }
    inline int id(int u) {
        int rt = u;
        while(fa[rt] > 0) rt = fa[rt];
        while(fa[u] > 0) { int tmp = fa[u]; fa[u] = rt; u = tmp; }
        return rt;
    }
    inline void join(int u, int v) {
        int uf = id(u);
        int vf = id(v);
        if(uf != vf) {
            if(fa[uf] < fa[vf]) { fa[uf] += fa[vf]; fa[vf] = uf; }
            else { fa[vf] += fa[uf]; fa[uf] = vf; }
        }
    }
    inline int size(int u) { return -fa[id(u)]; }
};
