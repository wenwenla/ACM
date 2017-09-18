struct Bit {
    //1 Base
    int arr[300005];
    int n;

    int lowbit(int x) { return x & (-x); }

    void add(int i, int x) {
        int pos = i;
        while(pos <= n) {
            arr[pos] += x;
            pos += lowbit(pos);
        }
    }

    int sum(int i) {
        int pos = i, ans = 0;
        while(pos) {
            ans += arr[pos];
            pos -= lowbit(pos);
        }
        return ans;
    }

    void init(int _n) {
        n = _n;
        for(int i = 1; i <= n; ++i) {
            arr[i] += sum(i - 1) - sum(i - lowbit(i));
        }
    }
} bit;