constexpr int block_size = 1024, N = 1000005;
int a[N];
vector<int> b[N / block_size + 1];

void update(int p, int v) {
    int bp = p / block_size;
    auto& bu = b[bp];
    int id = -1, len = bu.size();;
    for(int i = 0; i < len; ++i) {
        if(bu[i] == a[p]) {
            bu[i] = v;
            id = i;
            break;
        }
    }
    while(id > 0 && bu[id - 1] > bu[id]) {
        swap(bu[id], bu[id - 1]);
        --id;
    }
    while(id + 1 < len && bu[id] > bu[id + 1]) {
        swap(bu[id], bu[id + 1]);
        ++id;
    }
    a[p] = v;
}

int query(int l, int r, int v) {
    int ans = 0;
    if(l / block_size == r / block_size) {
        for(int i = l; i <= r; ++i) {
            if(a[i] < v) ++ans;
        }
        return ans;
    }
    while(l % block_size != 0) {
        if(a[l] < v) ++ans;
        ++l;
    }
    while((r + 1) % block_size != 0) {
        if(a[r] < v) ++ans;
        --r;
    }
    for(int bi = l / block_size; bi <= r / block_size; ++bi) {
        auto it = lower_bound(b[bi].begin(), b[bi].end(), v);
        ans += it - b[bi].begin();
    }
    return ans;
}
/*二分求第K大*/
