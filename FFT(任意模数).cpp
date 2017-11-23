
typedef long long LL;
const long double PI = acos(-1);
const int MOD =1000000007;
const int maxn=140100;
struct Complex {
    long double r,i;
    Complex(long double _r = 0.0,long double _i = 0.0) {
        r = _r;
        i = _i;
    }
    Complex operator +(const Complex &b) {
        return Complex(r+b.r,i+b.i);
    }
    Complex operator -(const Complex &b) {
        return Complex(r-b.r,i-b.i);
    }
    Complex operator *(const Complex &b) {
        return Complex(r*b.r-i*b.i,r*b.i+i*b.r);
    }
};
Complex conj(Complex a)
{
    return Complex(a.r,-a.i);
}
void change(Complex y[],int len)
{
    int i,j,k;
    for(i = 1, j = len/2; i < len-1; i++) {
        if(i < j)swap(y[i],y[j]);
        k = len/2;
        while( j >= k) {
            j -= k;
            k /= 2;
        }
        if(j < k) j += k;
    }
}
void FFT(Complex y[],int len,int on)  //len=2^k
{
    change(y,len);
    for(int h = 2; h <= len; h <<= 1) {
        Complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j = 0; j < len; j+=h) {
            Complex w(1,0);
            for(int k = j; k < j+h/2; k++) {
                Complex u = y[k];
                Complex t = w*y[k+h/2];
                y[k] = u+t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    if(on == -1)
        for(int i = 0; i < len; i++)
            y[i].r /= len;
}
int callen(int len1,int len2)
{
    int len=1;
    while(len < (len1<<1) || len < (len2<<1))len<<=1;
    return len;
}
LL fftans[maxn];
Complex A[maxn],B[maxn],dft[4][maxn],dt[4];
int td[4];
void fft(LL* y1,int len1,LL* y2,int len2,LL mod)
{
    int len=callen(len1,len2);
    for(int x=0; x<len1; x++)A[x]=Complex(y1[x]&32767,y1[x]>>15);
    for(int x=len1; x<len; x++)A[x]=Complex(0,0);
    for(int x=0; x<len2; x++)B[x]=Complex(y2[x]&32767,y2[x]>>15);
    for(int x=len2; x<len; x++)B[x]=Complex(0,0);
    FFT(A,len,1);
    FFT(B,len,1);
    int j;
    for(int x=0; x<len; x++) {
        j=(len-x)&(len-1);
        dt[0]=(A[x]+conj(A[j]))*Complex(0.5,0);
        dt[1]=(A[x]-conj(A[j]))*Complex(0,-0.5);
        dt[2]=(B[x]+conj(B[j]))*Complex(0.5,0);
        dt[3]=(B[x]-conj(B[j]))*Complex(0,-0.5);
        dft[0][j]=dt[0]*dt[2];
        dft[1][j]=dt[0]*dt[3];
        dft[2][j]=dt[1]*dt[2];
        dft[3][j]=dt[1]*dt[3];
    }
    for(int x=0; x<len; x++) {
        A[x]=dft[0][x]+dft[1][x]*Complex(0,1);
        B[x]=dft[2][x]+dft[3][x]*Complex(0,1);
    }
    FFT(A,len,1);
    FFT(B,len,1);
    for(int x=0; x<len; x++) {
        td[0]=(LL)(A[x].r/len+0.5)%mod;
        td[1]=(LL)(A[x].i/len+0.5)%mod;
        td[2]=(LL)(B[x].r/len+0.5)%mod;
        td[3]=(LL)(B[x].i/len+0.5)%mod;
        fftans[x]=(td[0]+((LL)(td[1]+td[2])<<15)+((LL)td[3]<<30))%mod;
    }
}
LL a[maxn],b[maxn];
fft(a,n,b,n,MOD);
