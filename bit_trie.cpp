/*
0 <= key <= 2e9
*/

struct bit_trie {
    const static int node_cnt = 4000000;
    struct Node {
        int cnt[2];
        int next[2];
        void make(int c_0, int c_1, int n_0, int n_1) {
            cnt[0] = c_0; cnt[1] = c_1; next[0] = n_0; next[1] = n_1;
        }
    } node[node_cnt];

    int alloc, rt, num_cnt;

    bit_trie() : alloc(1), rt(0), num_cnt(0) {
        node[rt].make(0, 0, -1, -1);
    }

    void clear() {
        alloc = 1;
        node[rt].make(0, 0, -1, -1);
    }

    void ins(int x) {
        assert(x <= 2e9);
        ++num_cnt;
        int pos = rt;
        for(int i = 31; i >= 0; --i) {
            int ins_num = ((x >> i) & 1);
            //cout << ins_num;
            ++node[pos].cnt[ins_num];
            if(node[pos].next[ins_num] == -1) {
                node[pos].next[ins_num] = alloc;
                node[alloc++].make(0, 0, -1, -1);
            }
            pos = node[pos].next[ins_num];
        }
        //cout << endl;
    }

    void del(int x) {
        assert(x <= 2e9);
        --num_cnt;
        int pos = rt;
        for(int i = 31; i >= 0; --i) {
            int del_num = ((x >> i) & 1);
            assert(node[pos].cnt[del_num] > 0);
            --node[pos].cnt[del_num];
            pos = node[pos].next[del_num];
        }
    }

    int rank(int x) {
        assert(x <= 2e9);
        int pos = rt;
        int ans = 1;
        for(int i = 31; i >= 0; --i) {
            int bit = ((x >> i) & 1);
            if(pos == -1) break;
            if(bit) {
                ans += node[pos].cnt[0];
            }
            pos = node[pos].next[bit];
        }
        return ans;
    }

    int kth(int rank) {
        assert(rank >= 1 && rank <= num_cnt);
        int ans = 0;
        int pos = rt;
        while((node[pos].next[0] & node[pos].next[1]) != -1) {
            if(node[pos].cnt[0] >= rank) {
                //cout << 0;
                ans = (ans << 1);
                pos = node[pos].next[0];
            } else {
                //cout << 1;
                rank -= node[pos].cnt[0];
                assert(rank >= 0);
                ans = (ans << 1) + 1;
                pos = node[pos].next[1];
            }
        }
        //cout << endl;
        return ans;
    }

    int succ(int x) {
        return kth(rank(x) - 1);
    }

    int pre(int x) {
        return kth(rank(x + 1));
    }
} bt;