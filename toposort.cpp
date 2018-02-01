const int VN = 300005, EN = 300005;
struct edge {
    int to, next;
} eg[EN], reg[EN];
int indeg[VN], head[VN], toposeq[VN], rhead[VN], tot, rtot;

void init() {
    memset(head, 0xff, sizeof(head));
    memset(rhead, 0xff, sizeof(rhead));
    tot = 0; rtot = 0;
}

void addedge(int from, int to) {
    eg[tot] = {to, head[from]};
    head[from] = tot++;
    reg[rtot] = {from, rhead[to]};
    rhead[to] = rtot++;
    ++indeg[to];
}

bool toposort(int n) {
    int idx = 0;
    queue<int> que;
    for(int i = 1; i <= n; ++i) {
        if(indeg[i] == 0) {
            que.push(i);
        }
    }
    while(!que.empty()) {
        int now = que.front();
        que.pop();
        toposeq[idx++] = now;
        for(int i = head[now]; i != -1; i = eg[i].next) {
            int to = eg[i].to;
            if(--indeg[to] == 0) que.push(to);
        }
    }
    return idx == n;
}