typedef long long ll;
typedef unsigned long long ull;

int km_match(char* pattern, char* str) {
    int plen = strlen(pattern);
    int slen = strlen(str);
    int dt = max(((plen - 1) >> 1), 1);
    int cnt = 0;
    ull phash = 0, shash = 0;
    ull con = 1;
    for(int i = 0; i < plen; ++i) {
        phash = ((phash << 7) + pattern[i]);
        shash = ((shash << 7) + str[i]);
        con <<= 7;
    }
    con >>= 7;
    for(int i = 0; i < slen - plen + 1; ++i) {
        if(phash == shash) {
            bool flag = true;
            for(int j = 0; j < plen; j += dt) {
                if(pattern[j] != str[i + j]) {
                    flag = false;
                    break;
                }
            }
            if(flag) ++cnt;
        }
        shash = (((shash - str[i] * con) << 7) + str[i + plen]);
    }
    return cnt;
}
