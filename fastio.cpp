namespace fastio {
    const static int buf_size = 8388608;//about 8Mb
    static char buf[buf_size];
    char *ps = buf + buf_size, *pe = buf + buf_size;
    int pos;
    bool eof = false;

    inline void read_next() {
        pe = buf + fread(buf, 1, buf_size, stdin);
        ps = buf;
        if(ps == pe) eof = true;
    }

    inline bool blank(char x) {
        return x == ' ' || x == '\n' || x == '\t' || x == '\r';
    }

    inline char nc() {
        if(ps == pe) read_next();
        return *ps++;
    }

    template<typename T>
    inline void read_num(T& res) {
        bool neg = false;
        char now = nc();
        while(blank(now)) now = nc();
        if(now == '-') {
            neg = true;
            now = nc();
        }
        T ret = 0;
        while(!blank(now)) {
            ret = ret * 10 + now - '0';
            now = nc();
        }
        res = (neg ? -ret : ret);
    }

    template<typename T>
    inline void put_num(T x) {
        if(x < 0) {
            putchar('-');
            x = -x;
        }
        if(x == 0) {
            putchar('0');
        }
        char tmp[32];
        int cnt = 0;
        while(x) {
            tmp[cnt++] = x % 10 + '0';
            x /= 10;
        }
        while(cnt > 0) {
            putchar(tmp[cnt - 1]);
            --cnt;
        }
    }
}
