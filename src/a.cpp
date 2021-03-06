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

constexpr double TL = 5.00;
constexpr long long CYCLES_PER_SEC = 2800000000;
struct MyTimer {
    long long start;
    MyTimer() { reset(); }
 
    void reset() { start = getCycle(); }
        inline double get() { return (double) (getCycle() - start) / CYCLES_PER_SEC; }

        inline long long getCycle() {
            unsigned low, high;
            __asm__ volatile ("rdtsc" : "=a" (low), "=d" (high));
            return ((long long) low) | ((long long) high << 32);
    }
}aMyTimer;
const int H = 10000;
const int W = 10000;

bool IsIn(int i,int j){
    return 0 <= i && i < H && 0 <= j && j < W;
};
// 長方形
struct Rect{
    ll x1;
    ll y1;
    ll x2;
    ll y2;
    int idx;
    ll size(){
        return (x2 - x1) * (y2 - y1);
    }
    friend std::ostream& operator<<(std::ostream& os, const Rect& a){
        os << a.x1 << " " << a.y1 << " " << a.x2 << " " << a.y2;
        return os;
    }
};
bool intersect(const Rect &a, const Rect &b){
    return min(a.x2, b.x2) > max(a.x1, b.x1) && min(a.y2, b.y2) > max(a.y1, b.y1);
}

class Solver{
public:
    int N;
    vector<int> x, y;
    vector<long long> r;
    vector<Rect> out;
    Solver(){}
    void input(){
        cin >> N;
        x.resize(N);
        y.resize(N);
        r.resize(N);
        out.resize(N);
        rep(i,N){
            cin >> x[i] >> y[i] >> r[i];
        }
    }
    bool check(int x1, int y1, int x2, int y2, int idx){
        return x1 <= x[idx] && x[idx] < x2 &&
               y1 <= y[idx] && y[idx] < y2;
    }
    // pub fn score(input: &Input, out: &Vec<Rect>) -> i64 {
    //     let n = input.ps.len();
    //     let mut score = 0.0;
    //     for i in 0..n {
    //         if out[i].x1 < 0 || out[i].x2 > W || out[i].y1 < 0 || out[i].y2 > W {
    //             eprintln!("rectangle {} is out of range", i);
    //             return 0;
    //         }
    //         if out[i].x1 >= out[i].x2 || out[i].y1 >= out[i].y2 {
    //             eprintln!("rectangle {} does not have positive area", i);
    //             return 0;
    //         }
    //         if !(out[i].x1 <= input.ps[i].0 && input.ps[i].0 < out[i].x2 && out[i].y1 <= input.ps[i].1 && input.ps[i].1 < out[i].y2) {
    //             eprintln!("rectangle {} does not contain point {}", i, i);
    //             continue;
    //         }
    //         for j in 0..i {
    //             if intersect(&out[i], &out[j]) {
    //                 eprintln!("rectangles {} and {} overlap", j, i);
    //                 return 0;
    //             }
    //         }
    //         let s = out[i].size().min(input.size[i]) as f64 / out[i].size().max(input.size[i]) as f64;
    //         score += 1.0 - (1.0 - s) * (1.0 - s);
    //     }
    //     (1e9 * score / n as f64).round() as i64
    // }
    // long long calcScore(){
    //     float score = 0.0;
    //     rep(i,N){
    //         long long s = ll(c[i]-a[i])*ll(d[i]-b[i]);
    //         long double tmp = (long double)(min(r[i], s)) / (long double)(max(r[i], s));
    //         dump(s);
    //         dump(tmp);
    //         score += (long double)1.0f - (long double)((long double)1.0f - tmp) * (long double)((long double)1.0f - tmp);
    //         dump(score);
    //     }
    //     return (long long)(round((long double)1e9 * score) / (long double)(N));
    // }
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
        /*
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
        */
    }
    bool checkIn(const Rect &a){
        return a.x1 <= x[a.idx] && x[a.idx] < a.x2 && 
        a.y1 <= y[a.idx] && y[a.idx] < a.y2;
    }
    void RandomMove(){
        while(true){
            int idx = XorShift()%N;
            ll ddx = out[idx].x2 - out[idx].x1;
            ll ddy = out[idx].y2 - out[idx].y1;
            int diff = XorShift()%100+3;
            int dir = XorShift() % 4;
            auto tmp = out[idx];
            tmp.x1 += diff * dx[dir];
            if(XorShift()%2)tmp.x2 += diff * dx[dir];
            tmp.y1 += diff * dy[dir];
            if(XorShift()%2)tmp.y2 += diff * dy[dir];
            if(tmp.size() > out[idx].size())continue;
            // if(not isValidMove(tmp))continue;
            if(not IsIn(tmp.x1, tmp.y1) || not IsIn(tmp.x2, tmp.y2)){
                continue;
            }
            if(not checkIn(tmp)){
                continue;
            }
            bool ok = true;
            rep(j,N){
                if(j == idx)continue;
                if(intersect(tmp, out[j])){
                    ok = false;
                    break;
                }
            }
            if(not ok)continue;
            if(ok){
                swap(out[idx], tmp);
                break;
            }
        }
    }
    void HogeSets(){
        // pointSets();
        vector<int> idxes;
        rep(i,N)idxes.push_back(i);
        sort(all(idxes), [&](int i, int j){
            return r[i] < r[j];
        });
        for(auto &idx: idxes){
            setGreedyXY(idx);
        }
        for(auto &idx: idxes){
            setGreedyX(idx);
        }
        for(auto &idx: idxes){
            setGreedyY(idx);
        }
        for(auto &idx: idxes){
            setGreedyX1(idx);
            setGreedyX2(idx);
        }
        for(auto &idx: idxes){
            setGreedyY1(idx);
            setGreedyY2(idx);
        }
    }
    void setGreedyXY(int idx){
        setGreedy(idx, true);
    }
    void setGreedyX(int idx){
        setGreedy(idx, false);
    }
    void setGreedyY(int idx){
        swapXYofOut();
        setGreedyX(idx);
        swapXYofOut();
    }
    void setGreedyX1(int idx){
        setGreedy(idx, false, true, false);
    }
    void setGreedyX2(int idx){
        setGreedy(idx, false, false, true);
    }
    void setGreedyY1(int idx){
        swapXYofOut();
        setGreedy(idx, false, true, false);
        swapXYofOut();
    }
    void setGreedyY2(int idx){
        swapXYofOut();
        setGreedy(idx, false, false, true);
        swapXYofOut();
    }
    bool isValidMove(const Rect &a){
        if(not IsIn(a.x1, a.y1) || not IsIn(a.x2, a.y2)){
            return false;
        }
        rep(j,N){
            if(j == a.idx)continue;
            if(intersect(a, out[j]))return false;
        }
        return true;
    }
    void setGreedy(int idx, bool Ytoo = false, bool one = true, bool two = true){
        auto check = [&](int mid) -> bool{
            Rect tmp = out[idx];
            if(one)tmp.x1 -= mid;
            if(two)tmp.x2 += mid;
            if(Ytoo){
                if(one)tmp.y1 -= mid;
                if(two)tmp.y2 += mid;
            }
            if(not IsIn(tmp.x1, tmp.y1) || not IsIn(tmp.x2, tmp.y2)){
                return false;
            }
            rep(j,N){
                if(j == idx)continue;
                if(intersect(tmp, out[j]))return false;
            }
            if(tmp.size() > r[idx])return false;
            return true;
        };
        int ok = 0;
        int ng = W;
        while(ng - ok > 1){
            int mid = (ok + ng) / 2;
            if(check(mid))ok = mid;
            else ng = mid;
        }
        if(one)out[idx].x1 -= ok;
        if(two)out[idx].x2 += ok;
        if(Ytoo){
            if(one)out[idx].y1 -= ok;
            if(two)out[idx].y2 += ok;
        }
    }
    void swapXYofOut(){
        rep(i,N){
            out[i] = Rect{out[i].y1, out[i].x1, out[i].y2, out[i].x2, out[i].idx};
        }
    }
    // 長方形[x1, x2), [y1, y2)
    void outSet(int x1, int y1, int x2, int y2, int idx){
        out[idx] = Rect({x1, y1, x2, y2, idx});
    }
    void outPut(){
        rep(idx,N){
            cout << out[idx] << endl;
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
    aMyTimer.reset();
    Solver aSolver;
    aSolver.input();
    aSolver.pointSets(); // 一番簡単
    // aSolver.averageSets(); // 大きさ考慮してないのでダメダメ。21.8 million点
    aSolver.HogeSets();
    while(aMyTimer.get() < 5){
        aSolver.RandomMove();
        aSolver.HogeSets();
    }
    aSolver.HogeSets();
    // dump(aSolver.calcScore());
    dump(aMyTimer.get());
    aSolver.outPut();
}
