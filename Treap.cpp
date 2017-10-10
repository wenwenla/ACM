struct Treap {
    const static int NODECNT = 1000005;
    struct Node {
        int ch[2], p, v;
        void make(int _l, int _r, int _p, int _v) {
            ch[0] = _l; ch[1] = _r; p = _p, v = _v;
        }
    } node[NODECNT];
    int m_rt, sz, mp[NODECNT], mp_idx;

    Treap() {
        unsigned seed = 19971023;//倩倩的生日拥有华丽的特效
        srand(seed);
        clear();
    }

    void clear() {
        m_rt = -1;
        mp_idx = 0;
        for(int i = 0; i < NODECNT; ++i) mp[i] = i;
        sz = 0;
    }

    void ins(int val) { _ins(val, m_rt); ++sz; }
    void _ins(int val, int& rt) {
        if(rt == -1) {
            node[rt = mp[mp_idx++]].make(-1, -1, rand(), val);
        } else {
            int type = node[rt].v < val;
            _ins(val, node[rt].ch[type]);
            if(node[rt].p < node[node[rt].ch[type]].p) rotate(rt, type);
        }
    }

    void del(int x) { _del(m_rt, x); --sz; }
    void _del(int& rt, int x) {
		assert(rt != -1);
        if(node[rt].v == x) {
            if(node[rt].ch[0] == -1) {
                mp[--mp_idx] = rt;
                rt = node[rt].ch[1];
            } else if(node[rt].ch[1] == -1) {
                mp[--mp_idx] = rt;
                rt = node[rt].ch[0];
            } else {
                int next = node[node[rt].ch[0]].p < node[node[rt].ch[1]].p;
                rotate(rt, next);
                _del(node[rt].ch[next ^ 1], x);
            }
        } else {
            _del(node[rt].ch[node[rt].v < x], x);
        }
    }

    int find(int x) {
        int rt = m_rt;
        while(rt != -1) {
            if(node[rt].v == x) return rt;
            rt = node[rt].ch[node[rt].v < x];
        }
        return -1;
    }

    void rotate(int& rt, int type) {
        int tmp = node[rt].ch[type];
        node[rt].ch[type] = node[tmp].ch[type ^ 1];
        node[tmp].ch[type ^ 1] = rt;
        rt = tmp;
    }

    int min() {
        int res, rt = m_rt;
        while(rt != -1) {
            res = node[rt].v;
            rt = node[rt].ch[0];
        }
        return res;
    }

    int max() {
        int res, rt = m_rt;
        while(rt != -1) {
            res = node[rt].v;
            rt = node[rt].ch[1];
        }
        return res;
    }
} tr;