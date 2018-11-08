typedef long long ll;
ll powmod(int x, int e, int m) {
    if(e == 0) return 1;
    if(e == 1) return x;
    ll tmp = powmod(x, e / 2, m);
    tmp = (tmp * tmp) % m;
    if(e & 1) return tmp * x % m;
    else return tmp;
}

vector<ll> calc(const char* str, int seg, int MO) {
    vector<ll> res;
    int base = 26;
    assert(MO <= 1000000007);
    ll inv = powmod(base, MO - 2, MO);
    int len = strlen(str);
    ll now = 0, exp = 1;
    for(int i = 0; i < seg; ++i) {
        (now += (str[i] - 'A') * exp % MO) %= MO;
        if(i != seg - 1) (exp *= base) %= MO;
    }
    res.push_back(now);
    for(int i = seg; i < len; ++i) {
        (now -= (str[i - seg] - 'A')) %= MO;
        (now *= inv) %= MO;
        (now += ((str[i] - 'A') * exp) % MO) %= MO;
        if(now < 0) now += MO;
        res.push_back(now);
    }
    //sort(res.begin(), res.end());
    return res;
}