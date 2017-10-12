template<typename T>
struct Alloc {
    static const int MCNT = 100005;
    int pool[MCNT], pool_idx;
    T data[MCNT];

    Alloc() { clear(); }

    int get() { return pool[pool_idx++]; }

    void del(int idx) { pool[--pool_idx] = idx; }

    void clear() {
        for(int i = 0; i < MCNT; ++i) pool[i] = i;
        pool_idx = 0;
    }

    T& operator[](int idx) { return data[idx]; }
};

struct Treap {
    struct Node {
        int ch[2], p, v, sz;
        void make(int _l, int _r, int _p, int _v) {
            ch[0] = _l; ch[1] = _r; p = _p; v = _v; sz = 1;
        }
    };
    static Alloc<Node> alloc;
    int m_rt;

    void maintain(int x) {
        alloc[x].sz = 1;
        alloc[x].sz += alloc[x].ch[0] == -1 ? 0 : alloc[alloc[x].ch[0]].sz;
        alloc[x].sz += alloc[x].ch[1] == -1 ? 0 : alloc[alloc[x].ch[1]].sz;
    }

    Treap() {
        m_rt = -1;
        unsigned seed = 19971023;//倩倩的生日拥有华丽的特效
        srand(seed);
        clear();
    }
    ~Treap() { clear(); }

    void clear() { _clear(m_rt); m_rt = -1; }
    void _clear(int x) {
        if(x == -1) return;
        _clear(alloc[x].ch[0]);
        _clear(alloc[x].ch[1]);
        alloc.del(x);
    }

    void ins(int val) { _ins(m_rt, val); }
    void _ins(int& rt, int val) {
        if(rt == -1) {
            alloc[rt = alloc.get()].make(-1, -1, rand(), val);
        } else {
            int type = alloc[rt].v < val;
            _ins(alloc[rt].ch[type], val);
            maintain(rt);
            if(alloc[rt].p < alloc[alloc[rt].ch[type]].p) rotate(rt, type);
        }
    }

    void del(int val) { _del(m_rt, val); }
    void _del(int& rt, int val) {
		assert(rt != -1);
        if(alloc[rt].v == val) {
            if(alloc[rt].ch[0] == -1) {
                alloc.del(rt);
                rt = alloc[rt].ch[1];
            } else if(alloc[rt].ch[1] == -1) {
                alloc.del(rt);
                rt = alloc[rt].ch[0];
            } else {
                int next = alloc[alloc[rt].ch[0]].p < alloc[alloc[rt].ch[1]].p;
                rotate(rt, next);
                _del(alloc[rt].ch[next ^ 1], val);
                maintain(rt);
            }
        } else {
            _del(alloc[rt].ch[alloc[rt].v < val], val);
            maintain(rt);
        }
    }

    int find(int val) {
        int rt = m_rt;
        while(rt != -1) {
            if(alloc[rt].v == val) return rt;
            rt = alloc[rt].ch[alloc[rt].v < val];
        }
        return -1;
    }

    void rotate(int& rt, int type) {
        int tmp = alloc[rt].ch[type];
        alloc[rt].ch[type] = alloc[tmp].ch[type ^ 1];
        alloc[tmp].ch[type ^ 1] = rt;
        maintain(rt); maintain(tmp);
        rt = tmp;
    }

    int kth(int k) {
        assert(k >= 1 && k <= size());
        int rt = m_rt, res = -1;
        while(rt != -1) {
            int le = alloc[rt].ch[0] == -1 ? 0 : alloc[alloc[rt].ch[0]].sz;
            if(le == k - 1) {
                res = alloc[rt].v;
                break;
            } else if(le > k - 1) {
                rt = alloc[rt].ch[0];
            } else {
                k -= le + 1;
                rt = alloc[rt].ch[1];
            }
        }
        return res;
    }

    int rank(int val) {
        int rt = m_rt, cnt = 0;
        while(rt != -1) {
            int le = alloc[rt].ch[0] == -1 ? 0 : alloc[alloc[rt].ch[0]].sz;
            if(alloc[rt].v < val) {
                cnt += le + 1;
                rt = alloc[rt].ch[1];
            } else {
                rt = alloc[rt].ch[0];
            }
        }
        return cnt + 1;
    }

    int size() { return alloc[m_rt].sz; }
};
Alloc<Treap::Node> Treap::alloc;
Treap tr[1000];