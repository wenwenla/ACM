ll ct(int k, ll n) {
    ll res = 0 , x;
    if (k == 0 && n == 0) res = 1;
    for (ll i = 1;x = n / i;i *= 10) {
        ll high = x / 10;
        if (k == 0) {
            if (high) high--;
            else {
                res++;
                break;
            }
        }
        res += high * i;
        int cur = x % 10;
        if (cur > k) res += i;
        else if (cur == k) res += n - x * i + 1;
    }
    return res;
}