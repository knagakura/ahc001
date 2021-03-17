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
struct Box{
    ll x1;
    ll y1;
    ll x2;
    ll y2;
    pair<ll,ll> lowerBound;
    pair<ll,ll> upperBound;
    int idx;
    Box(){}
    Box(ll x1_, ll y1_, ll x2_, ll y2_, int idx_):x1(x1_), y1(y1_), x2(x2_), y2(y2_), idx(idx_), lowerBound(x1, y2), upperBound(x2, y2){
    }
    ll size(){
        return lenx() * leny();
    }
    ll ratio(){
        return max(lenx(), leny()) / min(lenx(), leny());
    }
    ll lenx(){
        return (x2 - x1);
    }
    ll leny(){
        return (y2 - y1);
    }
    friend std::ostream& operator<<(std::ostream& os, const Box& a){
        os << a.x1 << " " << a.y1 << " " << a.x2 << " " << a.y2;
        return os;
    }
    bool operator<(const Box& b){
        return x1 < b.x1;
    }
};
bool intersect(const Box &a, const Box &b){
    return min(a.x2, b.x2) > max(a.x1, b.x1) && min(a.y2, b.y2) > max(a.y1, b.y1);
}

const int MAXN = 222;
int N;
int x[MAXN], y[MAXN];
ll r[MAXN];
ll dist[MAXN][MAXN];
vector<int> distIdx[MAXN];
int calcedCnt[MAXN][16];
class Solver{
public:
    Box out[MAXN];
    Solver(){
        input();
        rep(i,N){
            rep(j,N){
                dist[i][j] = abs(x[i]-x[j]) + abs(y[i]-y[j]);
                distIdx[i].push_back(j);
            }
            sort(all(distIdx[i]), [&](int a, int b){
                return dist[i][a] < dist[i][b];
            });
        }
    }
    void input(){
        cin >> N;
        rep(i,N){
            cin >> x[i] >> y[i] >> r[i];
        }
    }
    bool check(int x1, int y1, int x2, int y2, int idx){
        return x1 <= x[idx] && x[idx] < x2 &&
               y1 <= y[idx] && y[idx] < y2;
    }
    long double calcScore(int idx){
        long long s = out[idx].size();
        long double tmp = (long double)(min(r[idx], s)) / (long double)(max(r[idx], s));
        long double res = (long double)1.0f - (long double)((long double)1.0f - tmp) * (long double)((long double)1.0f - tmp);
        return res;
    }
    long long calcScoreAll(){
        long double score = 0.0;
        rep(i,N){
            score += calcScore(i);
        }
        return (long long)(round((long double)1e9 * score) / (long double)(N));
    }
    bool checkIn(const Box &a){
        return a.x1 <= x[a.idx] && x[a.idx] < a.x2 && 
        a.y1 <= y[a.idx] && y[a.idx] < a.y2;
    }
    void RandomMove(){
        int cnt = 20;
        int itr = 0;
        while(itr < cnt){
            int idx = XorShift()%N;
            ll ddx = out[idx].x2 - out[idx].x1;
            ll ddy = out[idx].y2 - out[idx].y1;
            int diffX = XorShift()%200+3;
            int diffY = XorShift()%200+3;
            int dir = XorShift() % 8;
            auto tmp = out[idx];
            if(XorShift()%2)tmp.x1 += diffX * dx[dir];
            if(XorShift()%2)tmp.x2 += diffX * dx[dir];
            if(XorShift()%2)tmp.y1 += diffY * dy[dir];
            if(XorShift()%2)tmp.y2 += diffY * dy[dir];
            if(tmp.size() > out[idx].size())continue;
            // if(not isValidMove(tmp))continue;
            if(not IsIn(tmp.x1, tmp.y1) || not IsIn(tmp.x2, tmp.y2)){
                continue;
            }
            if(not checkIn(tmp)){
                continue;
            }
            bool ok = true;
            if(not(
                    tmp.x1 == out[idx].x1 &&
                    tmp.x2 == out[idx].x2 &&
                    tmp.y1 == out[idx].y1 &&
                    tmp.y2 == out[idx].y2
            )){
                rep(j,N){
                    if(j == 0)continue;
                    if(intersect(tmp, out[distIdx[idx][j]])){
                        ok = false;
                        break;
                    }
                }
            }
            if(not ok)continue;
            if(ok){
                swap(out[idx], tmp);
                if(XorShift()%100 < 20)pointSet(idx);
                itr++;
                // break;
            }
        }
    }
    void HogeSets(bool shuffle = false, int dir = 0){
        // pointSets();
        vector<int> idxes;
        rep(i,N)idxes.push_back(i);
        if(shuffle){
            std::mt19937_64 mt;
            std::shuffle(all(idxes), mt);
        }
        else{
            sort(all(idxes), [&](int i, int j){
                // return r[i] < r[j];
                return make_pair(x[i]*dx[dir+4], y[i]*dy[dir+4]) < make_pair(x[j]*dx[dir+4], y[j]*dy[dir+4]);
            });
        }
        for(auto &idx: idxes){
            if(out[idx].ratio() > 20 && XorShift() % 100 < 20){
                pointSet(idx);
            }
        }
        rep(i,N)rep(j,16){
            calcedCnt[i][j] = 0;
        }
        if(not shuffle){
            for(auto &idx: idxes){
                setGreedyXY(idx);
            }
        }
        for(auto &idx: idxes){
            setGreedy(idx, XorShift()%2, XorShift()%2, XorShift()%2, XorShift()%2);
        }
        for(auto &idx: idxes){
            setGreedy(idx, XorShift()%2, XorShift()%2, XorShift()%2, XorShift()%2);
        }
        for(auto &idx: idxes){
            setGreedy(idx, XorShift()%2, XorShift()%2, XorShift()%2, XorShift()%2);
        }
        for(auto &idx: idxes){
            setGreedyXY(idx);
        }
        bool f  = XorShift()%2;
        if(f){
            for(auto &idx: idxes){
                setGreedyY(idx);
            }
            for(auto &idx: idxes){
                setGreedyX(idx);
            }
        }
        else{
            for(auto &idx: idxes){
                setGreedyX(idx);
            }
            for(auto &idx: idxes){
                setGreedyY(idx);
            }
        }
        f  = XorShift()%2;
        if(f){
            for(auto &idx: idxes){
                setGreedyY1(idx);
                setGreedyY2(idx);
            }
            for(auto &idx: idxes){
                setGreedyX1(idx);
                setGreedyX2(idx);
            }
        }else{
            for(auto &idx: idxes){
                setGreedyX1(idx);
                setGreedyX2(idx);
            }
            for(auto &idx: idxes){
                setGreedyY1(idx);
                setGreedyY2(idx);
            }
        }
    }
    void setGreedyXY(int idx){
        setGreedy(idx, true, true, true, true);
    }
    void setGreedyX(int idx){
        setGreedy(idx, true, true, false, false);
    }
    void setGreedyY(int idx){
        setGreedy(idx, false, false, true, true);
    }
    void setGreedyX1(int idx){
        setGreedy(idx, true, false, false, false);
    }
    void setGreedyX2(int idx){
        setGreedy(idx, false, true, false, false);
    }
    void setGreedyY1(int idx){
        setGreedy(idx, false, false, true, false);
    }
    void setGreedyY2(int idx){
        setGreedy(idx, false, false, false, true);
    }
    bool isValidMove(const Box &a){
        if(not IsIn(a.x1, a.y1) || not IsIn(a.x2, a.y2)){
            return false;
        }
        rep(j,N){
            if(j == a.idx)continue;
            if(intersect(a, out[j]))return false;
        }
        return true;
    }
    void setGreedy(int idx, bool x1, bool x2, bool y1, bool y2){
        int j = bit(3)*x1+bit(2)*x2+bit(1)*y1+bit(0)*y2;
        if(not(x1 || x2 || y1 || y2))return;
        if(calcedCnt[idx][j])return;
        auto check = [&](int mid) -> bool{
            Box tmp = out[idx];
            if(x1)tmp.x1 -= mid;
            if(x2)tmp.x2 += mid;
            if(y1)tmp.y1 -= mid;
            if(y2)tmp.y2 += mid;
            if(tmp.size() > r[idx])return false;
            if(not IsIn(tmp.x1, tmp.y1) || not IsIn(tmp.x2, tmp.y2)){
                return false;
            }
            rep(j,N){
                if(j == 0)continue;
                if(intersect(tmp, out[distIdx[idx][j]]))return false;
            }
            return true;
        };
        if(!check(1)){
            return;
        }
        int ok = 0;
        int ng = W/2;
        while(ng - ok > 1){
            int mid = (ok + ng) / 2;
            if(check(mid))ok = mid;
            else ng = mid;
        }
        if(x1)out[idx].x1 -= ok;
        if(x2)out[idx].x2 += ok;
        if(y1)out[idx].y1 -= ok;
        if(y2)out[idx].y2 += ok;
        calcedCnt[idx][j]++;
    }
    void swapXYofOut(){
        rep(i,N){
            out[i] = Box(out[i].y1, out[i].x1, out[i].y2, out[i].x2, out[i].idx);
        }
    }
    // 長方形[x1, x2), [y1, y2)
    void outSet(int x1, int y1, int x2, int y2, int idx){
        out[idx] = Box({x1, y1, x2, y2, idx});
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
    void pointSet(int idx){
        pointSet(x[idx], y[idx], idx);
    }
    void pointSets(){
        rep(i,N){
            pointSet(x[i], y[i], i);
        }
    }
    void debug(){
        for(Box &a: out){
            dump(a.idx, a.x2 - a.x1, a.y2 - a.y1, a.size(), r[a.idx], a.ratio());
        }
    }
    void pointReset(int idx){
        pointSet(x[out[idx].idx], y[out[idx].idx], out[idx].idx);
    }
    void ratioSet(int idx){
        if(out[idx].ratio() > 10){
            if(out[idx].lenx() > out[idx].leny()){
                pointReset(idx);
                setGreedyY(idx);
                setGreedyX(idx);
            }
            else{
                pointReset(idx);
                setGreedyX(idx);
                setGreedyY(idx);
            }
        }
    }
    void ratioSets(){
        rep(idx, N)ratioSet(idx);
    }
};
int main() {
    aMyTimer.reset();
    Solver aSolver;
    aSolver.pointSets(); // 一番簡単
    aSolver.HogeSets(false, 0);
    long long maxx = aSolver.calcScoreAll();
    rep(dir,4){
        auto tSolver = aSolver;
        tSolver.pointSets();
        tSolver.HogeSets(false, dir);
        if(chmax(maxx, tSolver.calcScoreAll())){
            dump(dir, maxx);
            swap(tSolver, aSolver);
        }
    }
    int itr = 0;
    long double startTime = aMyTimer.get();
    long double nowTime = startTime;
    long double startTemp = 500;
    long double endTemp = 100;

    long long startScore = aSolver.calcScoreAll();
    bool f = startScore <= 800000000;
    // bool f = false;
    int itr = 0;
    while(nowTime < 5.33){
        auto tSolver = aSolver;
        itr++;
        aSolver.RandomMove();
        aSolver.HogeSets(true);
        ll preScore = tSolver.calcScoreAll();
        ll newScore = aSolver.calcScoreAll();
        nowTime = aMyTimer.get();
        long double tmp = startTemp + (endTemp - startTemp) * (nowTime - startTime);
        long double prob = exp((newScore-preScore)/tmp);
        if(f){
            if(prob > (XorShift()%INF)/(long double)INF){
                swap(tSolver, aSolver);
            }
        }
        else{
            if(preScore > newScore){
                swap(tSolver, aSolver);
            }
        }
        if(itr % 1000 == 0){
            dump(itr, aSolver.calcScoreAll());
        }
    }
    aSolver.outPut();
}


