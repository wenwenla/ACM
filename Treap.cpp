struct Treap {
    const static int NODECNT = 1000005;
    struct Node {
        int ch[2], p, v, sz;
        void make(int _l, int _r, int _p, int _v) {
            ch[0] = _l; ch[1] = _r; p = _p; v = _v; sz = 1;
        }
    } node[NODECNT];
    int m_rt, mp[NODECNT], mp_idx, node_idx;

    void maintain(int x) {
        node[x].sz = 1;
        node[x].sz += node[x].ch[0] == -1 ? 0 : node[node[x].ch[0]].sz;
        node[x].sz += node[x].ch[1] == -1 ? 0 : node[node[x].ch[1]].sz;
    }

    Treap() {
        unsigned seed = 19971023;//倩倩的生日拥有华丽的特效
        srand(seed);
        clear();
    }

    void clear() {
        m_rt = -1;
        mp_idx = -1;
        node_idx = 0;
    }

    void ins(int val) { _ins(m_rt, val); }
    void _ins(int& rt, int val) {
        if(rt == -1) {
            if(mp_idx == -1) { node[rt = node_idx++].make(-1, -1, rand(), val); }
            else { node[rt = mp[mp_idx--]].make(-1, -1, rand(), val); }
        } else {
            int type = node[rt].v < val;
            _ins(node[rt].ch[type], val);
            maintain(rt);
            if(node[rt].p < node[node[rt].ch[type]].p) rotate(rt, type);
        }
    }

    void del(int val) { _del(m_rt, val); }
    void _del(int& rt, int val) {
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
            _del(node[rt].ch[node[rt].v < val], val);
            maintain(rt);
        }
    }

    int find(int val) {
        int rt = m_rt;
        while(rt != -1) {
            if(node[rt].v == val) return rt;
            rt = node[rt].ch[node[rt].v < val];
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

    int rank(int val) {
        int rt = m_rt, cnt = 0;
        while(rt != -1) {
            int le = node[rt].ch[0] == -1 ? 0 : node[node[rt].ch[0]].sz;
            if(node[rt].v < val) {
                cnt += le + 1;
                rt = node[rt].ch[1];
            } else {
                rt = node[rt].ch[0];
            }
        }
        return cnt + 1;
    }

    int size() { return node[m_rt].sz; }
} tr;
