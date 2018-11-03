#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-6, pi = acos(-1.0);
const int maxn = 1000;

double sqr(double x) {
    return x*x;
}
int dcmp(double x) {
    if(fabs(x) < eps)
        return 0;
    else
        return x < 0 ? -1 : 1;
}
struct Circle {
    double x, y, r, angle;
    int d;
    Circle() {}
    Circle(double xx, double yy, double ang = 0, int t = 0) {
        x = xx;
        y = yy;
        angle = ang;
        d = t;
    }
    void get() {
        scanf("%lf%lf%lf", &x, &y, &r);
        d = 1;
    }
};
Circle cir[maxn],tp[maxn*2];
double area[maxn];
double dis(Circle a,Circle b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
double cross(Circle p0,Circle p1,Circle p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}
//Բ�ཻ
int CirCrossCir(Circle p1, double r1,Circle p2, double r2,Circle &cp1,Circle &cp2) {
    double mx = p2.x - p1.x, sx = p2.x + p1.x, mx2 = mx * mx;
    double my = p2.y - p1.y, sy = p2.y + p1.y, my2 = my * my;
    double sq = mx2 + my2, d = -(sq - sqr(r1 - r2)) * (sq - sqr(r1 + r2));
    if (d + eps < 0)
        return 0;
    if (d < eps)
        d = 0;
    else
        d = sqrt(d);
    double x = mx * ((r1 + r2) * (r1 - r2) + mx * sx) + sx * my2;
    double y = my * ((r1 + r2) * (r1 - r2) + my * sy) + sy * mx2;
    double dx = mx * d, dy = my * d;
    sq *= 2;
    cp1.x = (x - dy) / sq;
    cp1.y = (y + dx) / sq;
    cp2.x = (x + dy) / sq;
    cp2.y = (y - dx) / sq;
    if (d > eps)
        return 2;
    else
        return 1;
}
bool circmp(const Circle& u, const Circle& v) {
    return dcmp(u.r - v.r) < 0;
}
bool cmp(const Circle& u, const Circle& v) {
    if (dcmp(u.angle - v.angle))
        return u.angle < v.angle;
    return u.d > v.d;
}
//0.5*r*r*(K-sin(K))
double calc(Circle cir,Circle cp1,Circle cp2) {
    double ans = (cp2.angle - cp1.angle) * sqr(cir.r)
                 - cross(cir, cp1, cp2) + cross(Circle(0, 0), cp1, cp2);
    return ans / 2;
}

void CirUnion(Circle cir[], int n) {
    Circle cp1, cp2;
    sort(cir, cir + n, circmp);
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (dcmp(dis(cir[i], cir[j]) + cir[i].r - cir[j].r) <= 0)
                cir[i].d++;
    for (int i = 0; i < n; ++i) {
        int tn = 0, cnt = 0;
        for (int j = 0; j < n; ++j) {
            if (i == j)
                continue;
            if (CirCrossCir(cir[i], cir[i].r, cir[j], cir[j].r,
                            cp2, cp1) < 2)
                continue;
            cp1.angle = atan2(cp1.y - cir[i].y, cp1.x - cir[i].x);
            cp2.angle = atan2(cp2.y - cir[i].y, cp2.x - cir[i].x);
            cp1.d = 1;
            tp[tn++] = cp1;
            cp2.d = -1;
            tp[tn++] = cp2;
            if (dcmp(cp1.angle - cp2.angle) > 0)
                cnt++;
        }
        tp[tn++] = Circle(cir[i].x - cir[i].r, cir[i].y, pi, -cnt);
        tp[tn++] = Circle(cir[i].x - cir[i].r, cir[i].y, -pi, cnt);
        sort(tp, tp + tn, cmp);
        int p, s = cir[i].d + tp[0].d;
        for (int j = 1; j < tn; ++j) {
            p = s;
            s += tp[j].d;
            area[p] += calc(cir[i], tp[j - 1], tp[j]);
        }
    }
}

struct I {
    double x, y, z;
} in[maxn];

void genCircle(double h, double w, int n) {
    for(int i = 0; i < n; ++i) {
        cir[i].x = in[i].x;
        cir[i].y = in[i].y;
        cir[i].r = w / (in[i].z * sqrt(sqr(in[i].x) + sqr(in[i].y) + sqr(h)));
        cir[i].d = 1;
    }
    memset(area, 0, sizeof(area));
    CirUnion(cir, n);
    for(int i = 1; i <= n; ++i) {
        area[i]-=area[i+1];
    }
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, w, k, s;
        scanf("%d %d %d %d", &n, &w, &k, &s);
        for(int i = 0; i < n; ++i) {
            scanf("%lf %lf %lf", &in[i].x, &in[i].y, &in[i].z);
        }
        double l = 0, r = 505;
        double ans = -1;
        while((r - l) > eps) {
            double mid = (l + r) * 0.5;
            genCircle(mid, w, n);
            double a = 0;
            for(int i = k; i <= n; ++i) {
                a += area[i];
            }
            if(a > s) {
                l = mid;
                ans = mid;
            } else {
                r = mid;
            }
        }
        if(ans > 500) puts("Oops!");
        else if(ans < 0) puts("No solution!");
        else printf("%.4f\n", ans);
    }
    return 0;
}
