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