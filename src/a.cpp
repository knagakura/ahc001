#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,N) for(int i=0;i<int(N);++i)
#define rep1(i,N) for(int i=1;i<int(N);++i)
#define all(a) (a).begin(),(a).end()
#define bit(k) (1LL<<(k))
#define SUM(v) accumulate(all(v), 0LL)

typedef pair<int, int> i_i;
typedef pair<ll, ll> l_l;
template <class T> using vec = vector<T>;
template <class T> using vvec = vector<vec<T>>;
struct fast_ios{ fast_ios(){ cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20); }; }fast_ios_;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define TOSTRING(x) string(#x)
template <typename T> istream &operator>>(istream &is, vector<T> &vec) { for (T &x : vec) is >> x; return is; }
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) { os  << "["; for(auto _: v) os << _ << ", "; os << "]"; return os; };
template <typename T> ostream &operator<<(ostream &os, set<T> &st) { os << "("; for(auto _: st) { os << _ << ", "; } os << ")";return os;}
template <typename T> ostream &operator<<(ostream &os, multiset<T> &st) { os << "("; for(auto _: st) { os << _ << ", "; } os << ")";return os;}
template <typename T, typename U> ostream &operator<<(ostream &os, const pair< T, U >& p){os << "{" <<p.first << ", " << p.second << "}";return os; }
template <typename T, typename U> ostream &operator<<(ostream &os, const map<T, U> &mp){ os << "["; for(auto _: mp){ os << _ << ", "; } os << "]" << endl; return os; }

#define DUMPOUT cerr
void dump_func(){ DUMPOUT << endl; }
template <class Head, class... Tail> void dump_func(Head &&head, Tail &&... tail) { DUMPOUT << head; if (sizeof...(Tail) > 0) { DUMPOUT << ", "; } dump_func(std::move(tail)...); }

#ifdef DEBUG
#define dbg(...) { dump_func(__VA_ARGS__) }
#define dump(...) DUMPOUT << string(#__VA_ARGS__) << ": "; dump_func(__VA_ARGS__)
#else
#define dbg(...)
#define dump(...)
#endif

const int INF = (ll)1e9;
const ll INFLL = (ll)1e18+1;
const ll MOD = 1000000007;
// const ll MOD = 998244353;
const long double PI = acos(-1.0);

const int dx[8] = {1, 0, -1, 0, 1, -1, -1, 1};
const int dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};
const string dir = "DRUL";

uint32_t XorShift(void) {
    static uint32_t x = 123456789;
    static uint32_t y = 362436069;
    static uint32_t z = 521288629;
    static uint32_t w = 88675123;
    uint32_t t;
 
    t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}


const int H = 10000;
const int W = 10000;

class Solver{
public:
    int N;
    vector<int> x, y, r;
    vector<int> a, b, c, d;
    Solver(){}
    void input(){
        cin >> N;
        x.resize(N);
        y.resize(N);
        r.resize(N);
        a.resize(N);
        b.resize(N);
        c.resize(N);
        d.resize(N);
        rep(i,N){
            cin >> x[i] >> y[i] >> r[i];
        }
    }
    bool check(int x1, int y1, int x2, int y2, int idx){
        return x1 <= x[idx] && x[idx] < x2 &&
               y1 <= y[idx] && y[idx] < y2;
    }
    void averageSets(){
        int cnt = 1;
        while(cnt * cnt < N){
            cnt++;
        }
        int length = H / cnt;
        // 14まで
        vector<bool> used(N, false);
        vector<bool> ok(cnt * cnt, false);
        vector<int> sq2Com(cnt*cnt, -1);
        rep(i,cnt)rep(j,cnt){
            int sx = i*length;
            int sy = j*length;
            int mask = i * cnt + j;
            rep(idx, N){
                if(used[idx])continue;
                if(check(sx, sy, sx+length, sy+length, idx)){
                    squareSet(sx, sy, length, idx);
                    ok[mask] = true;
                    sq2Com[mask] = idx;
                    used[idx] = true;
                    break;
                }
            }
        }
        rep(mask, cnt*cnt){
            int i = mask/cnt;
            int j = mask%cnt;
            rep(idx, N){
                if(not ok[mask] && not used[idx]){
                    int sx = i * length;
                    int sy = j * length;
                    squareSet(sx, sy, length, idx);
                    used[idx] = true;
                    ok[mask] = true;
                    sq2Com[mask] = idx;
                    break;
                }
            }
        }
        vector<int> lengthenDir(cnt * cnt, -1);
        rep(mask, cnt*cnt){
            int i = mask/cnt;
            int j = mask%cnt;
            if(not ok[mask]){
                rep(k,4){
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    int nmask = ni * cnt + nj;
                    if(0 <= ni && ni < cnt && 0 <= nj && nj < cnt){
                        if(ok[nmask]){
                            if(lengthenDir[nmask] == -1 || lengthenDir[nmask] == k%2){
                                // 元々一緒だった会社はどこか
                                int comIdx = sq2Com[nmask];
                                // const int dx[8] = {1, 0, -1, 0, 1, -1, -1, 1};
                                // const int dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};
                                // 下とマージ
                                if(k == 0){
                                    recSet(a[comIdx]-length, b[comIdx], c[comIdx]-a[comIdx]+length, d[comIdx]-b[comIdx], comIdx);
                                    lengthenDir[nmask] = lengthenDir[mask] = k%2;
                                }
                                // 右とマージ
                                if(k == 1){
                                    recSet(a[comIdx], b[comIdx]-length, c[comIdx]-a[comIdx], d[comIdx]-b[comIdx]+length, comIdx);
                                    lengthenDir[nmask] = lengthenDir[mask] = k%2;
                                }
                                // 上とマージ
                                if(k == 2){
                                    recSet(a[comIdx], b[comIdx], c[comIdx]-a[comIdx]+length, d[comIdx]-b[comIdx], comIdx);
                                    lengthenDir[nmask] = lengthenDir[mask] = k%2;
                                }
                                // 左とマージ
                                if(k == 3){
                                    recSet(a[comIdx], b[comIdx], c[comIdx]-a[comIdx], d[comIdx]-b[comIdx]+length, comIdx);
                                    lengthenDir[nmask] = lengthenDir[mask] = k%2;
                                }
                                sq2Com[mask] = comIdx;
                                ok[mask] = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    // 長方形[x1, x2), [y1, y2)
    void outSet(int x1, int y1, int x2, int y2, int idx){
        // cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
        a[idx] = x1;
        b[idx] = y1;
        c[idx] = x2;
        d[idx] = y2;
    }
    void outs(){
        rep(idx,N){
            cout << a[idx] << " " << b[idx] << " " << c[idx] << " " << d[idx] << endl;
        }
    }
    // 角(x, y),　縦rx, 横ryの長方形
    void recSet(int x, int y, int rx, int ry, int idx){
        outSet(x, y, x+rx, y+ry, idx);
    }
    // 角(x, y) 長さr0の正方形
    void squareSet(int x, int y, int r0, int idx){
        recSet(x, y, r0, r0, idx);
    }
    void pointSet(int a, int b, int idx){
        outSet(a, b, a+1, b+1, idx);
    }
    void pointSets(){
        rep(i,N){
            pointSet(x[i], y[i], i);
        }
    }
};
int main() {
    Solver aSolver;
    aSolver.input();
    // aSolver.pointOuts(); // 一番簡単
    aSolver.averageSets();
    aSolver.outs();
}
