namespace Int {
    const double eps = 1e-6;
    template<class _Callable>
    double Simpson(double lb, double ub, const _Callable& f) {
        double mid = (lb + ub) * .5;
        return (ub - lb) * (f(lb) + 4 * f(mid) + f(ub)) / 6.;
    }

    template<class _Callable>
    double _asr(double lb, double ub, double pre, double eps, const _Callable& f) {
        double mid = (lb + ub) * .5;
        double L = Simpson(lb, mid, f), R = Simpson(mid, ub, f);
        if(fabs(L + R - pre) < 15 * eps) return (L + R) + (L + R - pre) / 15.;
        return _asr(lb, mid, L, eps / 2, f) + _asr(mid, ub, R, eps / 2, f);
    }

    template<class _Callable>
    double asr(double lb, double ub, const _Callable& f) {
        return _asr(lb, ub, Simpson(lb, ub, f), eps, f);
    }
}