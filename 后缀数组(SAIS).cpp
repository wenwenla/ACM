template<size_t size>
struct SuffixArray {
    bool type[size<<1];
    int bucket[size],bucket1[size];
    int sa[size],rk[size],ht[size];
    bool isLMS(const int i,const bool *type) { return i>0&&type[i]&&!type[i-1];}
    template<class T>
    void inducedSort(T s,int *sa,const int len,const int cm,const int sz,bool *type,int *bucket,int *cntbuf,int *p) {
        memset(bucket,0,sizeof(int) * cm);
        memset(sa,-1,sizeof(int) * len);
        for (int i=0;i<len;i++) bucket[s[i]]++;
        cntbuf[0]=bucket[0];
        for (int i=1;i<cm;i++) cntbuf[i]=cntbuf[i-1]+bucket[i];
        for (int i=sz-1;i>=0;i--) sa[--cntbuf[s[p[i]]]]=p[i];
        for (int i=1;i<cm;i++) cntbuf[i]=cntbuf[i-1]+bucket[i-1];
        for (int i=0;i<len;i++)
            if (sa[i]>0&&!type[sa[i]-1]) sa[cntbuf[s[sa[i]-1]]++]=sa[i]-1;
        cntbuf[0]=bucket[0];
        for (int i=1;i<cm;i++) cntbuf[i]=cntbuf[i-1]+bucket[i];
        for (int i=len-1;i>=0;i--)
            if (sa[i]>0&&type[sa[i]-1]) sa[--cntbuf[s[sa[i]-1]]]=sa[i]-1;
    }
    template<class T>
    void sais(T s,int *sa,int len,bool *type,int *bucket,int *bucket1,int cm) {
        int i,j,sz=0,cnt=0,p=-1,x,*cntbuf=bucket+cm;
        type[len-1]=1;
        for (i=len-2;i>=0;i--) type[i]=s[i]<s[i+1]||(s[i]==s[i+1]&&type[i+1]);
        for (i=1;i<len;i++)
            if (type[i]&&!type[i-1]) bucket1[sz++]=i;
        inducedSort(s,sa,len,cm,sz,type,bucket,cntbuf,bucket1);
        for (i=sz=0;i<len;i++)
            if (isLMS(sa[i],type)) sa[sz++]=sa[i];
        for (i=sz;i<len;i++) sa[i]=-1;
        for (i=0;i<sz;i++) {
            x=sa[i];
            for (j=0;j<len;j++) {
                if (p==-1||s[x+j] !=s[p+j]||type[x+j] !=type[p+j]) {
                    cnt++;p=x;break;
                } else {
                    if (j>0&&(isLMS(x+j,type)||isLMS(p+j,type))) break;
                }
            }
            x=(~x&1 ? x>>1 : x-1>>1),sa[sz+x]=cnt-1;
        }
        for (i=j=len-1;i>=sz;i--)
            if (sa[i]>=0) sa[j--]=sa[i];
        int *s1=sa+len-sz,*bucket2=bucket1+sz;
        if (cnt<sz) {
            sais(s1,sa,sz,type+len,bucket,bucket1+sz,cnt);
        } else {
            for (i=0;i<sz;i++) sa[s1[i]]=i;
        }
        for (i=0;i<sz;i++) bucket2[i]=bucket1[sa[i]];
        inducedSort(s,sa,len,cm,sz,type,bucket,cntbuf,bucket2);
    }
    template<class T>
    void getHeight(T s,int n) {
        int i, j, k = 0;
        for(i = 0; i < n; ++i) rk[sa[i]] = i;
        for(i = 0; i < n; ++i) {
            if(k) --k;
            j = sa[rk[i] - 1];
            while(s[i + k] == s[j + k]) ++k;
            ht[rk[i]] = k;
        }
    }
    template<class T>
    void init(T s,const int len,const int cm) {
        sais(s,sa,len,type,bucket,bucket1,cm);
        getHeight(s,len);
    }
};

char s[MAXN];//0base
SuffixArray<MAXN> sf;
sf.init(s,strlen(s)+1,256);
