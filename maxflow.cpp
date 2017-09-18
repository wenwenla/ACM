/*
Ford-Fulkerson
O(FE)
*/

const int INF = 0x3f3f3f3f;
struct edge {
    int to, next;
    int cap;
    edge() {}
    edge(int _to, int _cap, int _next) : to(_to), next(_next), cap(_cap) {}
    static int rev(int x) {
        return x ^ 1;
    }
} e[1024];
int head[1024];
bool used[1024];
int tot;

void init() {
    tot = 0;
    memset(head, 0xff, sizeof(head));
}

void addedge(int from, int to, int cap) {
    e[tot] = edge(to, cap, head[from]);
    head[from] = tot++;
}

int dfs(int s, int t, int f) {
    if(s == t) return f;
    used[s] = true;
    for(int i = head[s]; i != -1; i = e[i].next) {
        if(!used[e[i].to] && e[i].cap > 0) {
            int d = dfs(e[i].to, t, min(f, e[i].cap));
            if(d > 0) {
                e[i].cap -= d;
                e[edge::rev(i)].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    while(true) {
        memset(used, 0x00, sizeof(used));
        int f = dfs(s, t, INF);
        if(f == 0) break;
        flow += f;
    }
    return flow;
}