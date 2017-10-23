template<typename T, class _Comp = less<T>>
struct Treap {
    const static int NODECNT = _;
    struct Node {
        int ch[2], p, sz;
        T v;
        void make(int _l, int _r, int _p, const T& _v) {
            ch[0] = _l; ch[1] = _r; p = _p; v = _v; sz = 1;
        }
    } node[NODECNT];
    int m_rt, mp[NODECNT], mp_idx, node_idx;

    void maintain(int x) {
        node[x].sz = 1;
        node[x].sz += node[x].ch[0] == -1 ? 0 : node[node[x].ch[0]].sz;
        node[x].sz += node[x].ch[1] == -1 ? 0 : node[node[x].ch[1]].sz;
    }
    _Comp cmp;

    explicit Treap(const _Comp& c) : cmp(c) { unsigned seed = 19971023; srand(seed); clear(); }

    Treap() : cmp(_Comp()) { unsigned seed = 19971023; srand(seed); clear(); }

    void clear() { m_rt = -1; mp_idx = -1; node_idx = 0; }

    void ins(const T& val) { _ins(m_rt, val); }
    void _ins(int& rt, const T& val) {
        if(rt == -1) {
            if(mp_idx == -1) { node[rt = node_idx++].make(-1, -1, rand(), val); }
            else { node[rt = mp[mp_idx--]].make(-1, -1, rand(), val); }
        } else {
            int type = cmp(node[rt].v, val);
            _ins(node[rt].ch[type], val);
            maintain(rt);
            if(node[rt].p < node[node[rt].ch[type]].p) rotate(rt, type);
        }
    }

    void del(const T& val) { _del(m_rt, val); }
    void _del(int& rt, const T& val) {
		assert(rt != -1);
        if(node[rt].v == val) {
            if(node[rt].ch[0] == -1) {
                mp[++mp_idx] = rt;
                rt = node[rt].ch[1];
            } else if(node[rt].ch[1] == -1) {
                mp[++mp_idx] = rt;
                rt = node[rt].ch[0];
            } else {
                int next = node[node[rt].ch[0]].p < node[node[rt].ch[1]].p;
                rotate(rt, next);
                _del(node[rt].ch[next ^ 1], val);
                maintain(rt);
            }
        } else {
            _del(node[rt].ch[cmp(node[rt].v, val)], val);
            maintain(rt);
        }
    }

    int find(const T& val) {
        int rt = m_rt;
        while(rt != -1) {
            if(node[rt].v == val) return rt;
            rt = node[rt].ch[cmp(node[rt].v, val)];
        }
        return -1;
    }

    void rotate(int& rt, int type) {
        int tmp = node[rt].ch[type];
        node[rt].ch[type] = node[tmp].ch[type ^ 1];
        node[tmp].ch[type ^ 1] = rt;
        maintain(rt); maintain(tmp);
        rt = tmp;
    }

    int kth(int k) {
        assert(k >= 1 && k <= size());
        int rt = m_rt, res = -1;
        while(rt != -1) {
            int le = node[rt].ch[0] == -1 ? 0 : node[node[rt].ch[0]].sz;
            if(le == k - 1) {
                res = node[rt].v;
                break;
            } else if(le > k - 1) {
                rt = node[rt].ch[0];
            } else {
                k -= le + 1;
                rt = node[rt].ch[1];
            }
        }
        return res;
    }

    int rank(const T& val) {
        int rt = m_rt, cnt = 0;
        while(rt != -1) {
            int le = node[rt].ch[0] == -1 ? 0 : node[node[rt].ch[0]].sz;
            if(cmp(node[rt].v, val)) {
                cnt += le + 1;
                rt = node[rt].ch[1];
            } else {
                rt = node[rt].ch[0];
            }
        }
        return cnt + 1;
    }

    int size() { return node[m_rt].sz; }
};
