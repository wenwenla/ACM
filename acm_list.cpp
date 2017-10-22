template<typename T>
struct ACM_list {
    static const int MAXN = 100005;
    static const int BEG = 0;
    static const int END = MAXN - 1;
    struct Node {
        T data;
        int next;
        int pre;
    } node[MAXN];
    int free[MAXN], fp;
    int sz;

    void init() {
        node[BEG] = {T{}, END, -1};
        node[END] = {T{}, -1, BEG};
        fp = MAXN - 3;
        for(int i = 0; i <= fp; ++i) {
            free[i] = i + 1;
        }
        sz = 0;
    }

    int ins_back(int idx, T val) {
        node[free[fp]].next = node[idx].next;
        node[free[fp]].data = val;
        node[free[fp]].pre = idx;
        node[idx].next = free[fp];
        node[node[free[fp]].next].pre = free[fp];
        ++sz;
        return free[fp--];
    }

    int ins_pre(int idx, T val) {
        idx = node[idx].pre;
        return ins_back(idx, val);
    }

    void del(int idx) {
        assert(idx != BEG && idx != END);
        node[node[idx].pre].next = node[idx].next;
        node[node[idx].next].pre = node[idx].pre;
        free[++fp] = idx;
        --sz;
    }

    Node& operator[](int idx) {
        return node[idx];
    }

    int begin() const {
        return node[BEG].next;
    }
    int end() const {
        return END;
    }
    int size() const {
        return sz;
    }
};
ACM_list<int> li;
