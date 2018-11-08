#include <bits/stdc++.h>
using namespace std;

const int N = 1000006;
struct MQ {
    int q[N], t[N], qh, qe, now;
    void init() { qh = qe = now = 0; }
    void push(int x) {
        while(size() > 0 && q[qe - 1] <= x) { --qe; }
        q[qe] = x; t[qe] = now;
        ++qe; ++now;
    }
    int top() const {
        assert(size() > 0);
        return q[qh];
    }
    void pop_until(int k) {
        while(size() > 0 && t[qh] < k) ++qh;
    }
    int size() const {
        return qe - qh;
    }
} mq;

int main() {
    mq.init();
    char cmd[20];
    scanf("%s", cmd);
    int pnow = 0, x;
    while(scanf("%s", cmd), cmd[0] != 'E') {
        if(cmd[0] == 'I') {
            //push
            scanf("%d", &x);
            mq.push(x);
        } else {
            //pop
            if(mq.size()) {
                mq.pop_until(pnow + 1);
                ++pnow;
            }
        }
        //q_max
        if(mq.size() != 0) printf("%d\n", mq.top());
        else printf("%d\n", -1);
    }
    return 0;
}
