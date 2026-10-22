// Clibor C++ snippets. Independent fragments; not a single compilable program.
// Original code and reference comments are preserved.

// ==================== Clibor entry 001 ====================
#if !LOCAL
#pragma GCC target("avx2")
#endif
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;
#define rep(i, n) for (ll i = 0; i < (ll)n; ++i)
#define rrep(i, n) for (ll i = n - 1; i >= 0; --i)
#define all(c) begin(c), end(c)
#define rall(c) rbegin(c), rend(c)
#define PI acos(-1)
#define oo (1LL << 62)
#define EPS 1e-9
#define __bt(c) __builtin_popcountl(c)
void cincout() {
  //  cin.tie(0); coutを待たずにcinを行う
  ios::sync_with_stdio(0);  cout << fixed << setprecision(10);}
template <typename T1, typename T2>
bool chmax(T1 &a, T2 b) { if (a >= b) return false; a = b; return true; }
template <typename T1, typename T2>
bool chmin(T1 &a, T2 b) { if (a <= b) return false; a = b; return true; }
ld euclidDist(ld x1, ld y1, ld x2, ld y2) { return (sqrtl((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))); }
// 座標圧縮
template <typename T>
map<T, ll> comp(vector<T> &A) { map<T, ll> mp; for (auto p : A) mp[p] = 0; ll sz = 0; for (auto &p : mp) p.second = sz++; for (auto &a : A) a = mp[a]; return mp; }
/*
preA={0,5,2,4,...}
aftA={0,3,1,2,...}
mp[0] = 0
mp[2] = 1
mp[4] = 2
...
*/
ll dx[] = {0, 1, 0, -1};
ll dy[] = {-1, 0, 1, 0};
bool is_pop(ll hash, ll d) { return (hash >> d) & 1; }
bool isn_field(ll y, ll x, ll H, ll W) {
  if (y < 0 || y >= H || x < 0 || x >= W) return true;
  return false;
}
ll seed = 123456789;
size_t xorshift() {
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 7;
	return seed;
}
size_t randxor(ll l, ll r) {
	return l + ll(xorshift() % (r - l));
}
// priority_queue<ll, vector<ll>, greater<ll>> Q;
// std::function<bool(ll)> dfs = [&](ll d)->bool{};
// multiset.erase(a)は、すべてのaを削除する
// multiset.erase(multiset.find(a))は、aを1つ削除する
/*

*/
int main() {
  cincout();
  
}

// ==================== Clibor entry 003 ====================
// mint
ll MOD = 998244353;
// https://atcoder.jp/contests/abc228/editorial/2932
// M^(K^N)%MOD == M^(K^N%(MOD-1))%MOD
ll modpow(ll a, ll n, ll mod) {
  a %= mod;
  if (a == 0) return 0;
  if (n == 0) return 1;
  if (n % 2 == 1)
    return (a * modpow(a, n - 1, mod)) % mod;
  else {
    ll t = modpow(a, n / 2, mod) % mod;
    return (t * t) % mod;
  }
}
// 逆元 modが素数の場合
ll modinv(ll n, ll mod) { return modpow(n, mod - 2, mod); }

// ※(a, mod)が素でない場合逆元が存在しない
// （modが素数以外）https://atcoder.jp/contests/abc186/tasks/abc186_e
ll modinv2(ll a, ll m) {  // ret = inv(a) mod m
  ll b = m, u = 1, v = 0;
  while (b) {
    ll t = a / b;
    a -= t * b;
    swap(a, b);
    u -= t * v;
    swap(u, v);
  }
  u %= m;
  if (u < 0) u += m;
  return u;
}

class mint {
 public:
  long long x;
  mint(long long x = 0) : x((x % MOD + MOD) % MOD) {}
  mint operator-() const { return mint(-x); }
  mint& operator+=(const mint& a) {
    if ((x += a.x) >= MOD) x -= MOD;
    return *this;
  }
  mint& operator-=(const mint& a) {
    if ((x += MOD - a.x) >= MOD) x -= MOD;
    return *this;
  }
  mint& operator*=(const mint& a) {
    (x *= a.x) %= MOD;
    return *this;
  }
  mint& operator++() {
    ++x;
    if (x >= MOD) x -= MOD;
    return *this;
  }
  mint& operator--() {
    --x;
    if (x < 0) x += MOD;
    return *this;
  }
  mint operator++(int) {
    mint tmp(*this);
    ++x;
    if (x >= MOD) x -= MOD;
    return tmp;
  }
  mint operator--(int) {
    mint tmp(*this);
    --x;
    if (x < 0) x += MOD;
    return tmp;
  }
  mint pow(long long t) const {
    if (!t) return 1;
    mint a = pow(t >> 1);
    a *= a;
    if (t & 1) a *= *this;
    return a;
  }

  // for prime mod
  mint inv() const { return pow(MOD - 2); }
  mint& operator/=(const mint& a) { return (*this) *= a.inv(); }
};

// 非メンバ関数にすることで mint + 整数、整数 + mint の両方を扱える
mint operator+(mint lhs, const mint& rhs) { return lhs += rhs; }
mint operator-(mint lhs, const mint& rhs) { return lhs -= rhs; }
mint operator*(mint lhs, const mint& rhs) { return lhs *= rhs; }
mint operator/(mint lhs, const mint& rhs) { return lhs /= rhs; }

ostream& operator<<(ostream& os, const mint& m) {
  return os << m.x;
}
istream& operator>>(istream& is, mint& m) {
  long long value;
  is >> value;
  m = mint(value);
  return is;
}
bool operator==(const mint& x, const mint& y) { return x.x == y.x; }
bool operator!=(const mint& x, const mint& y) { return !(x == y); }
bool operator>(const mint& x, const mint& y) { return x.x > y.x; }
bool operator<(const mint& x, const mint& y) { return x.x < y.x; }
bool operator>=(const mint& x, const mint& y) { return !(x < y); }
bool operator<=(const mint& x, const mint& y) { return !(x > y); }

// ==================== Clibor entry 004 ====================
//nCk
const ll MAX = 2000010;

long long fac[MAX], finv[MAX], inv[MAX];

void COMinit(){
  fac[0] = fac[1]=1;
  finv[0] = finv[1]=1;
  inv[1] = 1;
  for(int i=2; i<MAX; i++){
    fac[i] = fac[i-1] * i % MOD;
    inv[i] = MOD-inv[MOD%i] * (MOD/i) % MOD;
    finv[i] = finv[i-1] * inv[i] % MOD;//逆元の階上
  }
}

ll COM(int n, int k){
  if (n<k)
    return 0;
  if (n<0 || k<0)
    return 0;
  return fac[n] * (finv[k] * finv[n-k] % MOD) % MOD;
}

ll HOM(int n, int k){ // nHk
  return COM(n + k - 1, k);
}

int main(){
  cincout();
  COMinit();
}

// ==================== Clibor entry 005 ====================
// UnionFind
// https://atcoder.jp/contests/arc028/submissions/37993104
struct UnionFind {
  vector<ll> par, children;
  UnionFind(ll N) : par(N), children(N, 1) {
    for (int i = 0; i < N; i++) {
      par[i] = i;
    }
  }

  ll root(ll x) {
    if (par[x] == x) return x;
    return par[x] = root(par[x]);
  }

  void unite(ll x, ll y) {
    ll rx = root(x), ry = root(y);
    if (rx == ry) return;
    if (rx > ry) swap(rx, ry);
    par[ry] = rx;  // ryの子供の親はryのまま。root()で統一される
    children[rx] += children[ry];
  }

  bool issame(ll x, ll y) { return root(x) == root(y); }

  ll getSize(ll x) { return children[x]; }
};

/*

*/
int main() {
  cincout();

  ll N;
  cin >> N;
  UnionFind tree(N);
}

// ==================== Clibor entry 006 ====================
// indexを+1して格納する。
// https://atcoder.jp/contests/abc174/submissions/57113393 LからRまでの玉の種類数。R順に見る。色が最後に出現したindexを記録する
// https://atcoder.jp/contests/abc368/submissions/57112403 Aの和をとるか、Bの積をとる。クエリを最大化する
struct Bit
{
  ll N;
  vector<ll> dat;
  Bit(ll N) : N(N) {
    dat.assign(N + 5, 0);
  }
  void add(ll i, ll x){
    ++i;
    for(; i < N; i += i&-i) dat[i] += x;
  }
  // iの値を取り出したいときはsum(i)
  ll sum(ll i){ // [0, i]
    if (i < 0) return 0;
    if (i >= N - 1) i = N - 2;
    ++i;
    ll res = 0;
    for(; i > 0; i -= i&-i) res += dat[i];
    return res;
  }
  ll rangesum(ll L, ll R){ // [L, R)
    return sum(R - 1) - sum(L - 1);
  }
};

// ==================== Clibor entry 007 ====================
// 二部グラフの判定
// https://atcoder.jp/contests/code-festival-2017-qualb/tasks/code_festival_2017_qualb_c

vector<vector<ll>> G;
int colors[200005];
bool is_bipartite_graph(int v, int c) {
    colors[v] = c;
    for (int u: G[v]) {
        if (colors[u] == c) {
            return false;
        }
        if (colors[u] == 0 && !is_bipartite_graph(u, -c)) {
            return false;
        }
    }
    return true;
}

int main(){
  ll N, M;
  cin >> N >> M;
  G.assign(N+1, vector<ll>());
  rep(i, M){
    ll a, b;
    cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  ll ans = 0;
  if (is_bipartite_graph(1, 1) == true){ //スタート地点投げるだけ
    ll w=0, b=0;
    for(ll i=1; i<=N; i++){
      if (colors[i]>0) w++;
      else if (colors[i]<0) b++;
    }
    ans = w*b-M;
  }
  else ans = (N*(N-1))/2-M;
  cout << ans << endl;
}

// ==================== Clibor entry 008 ====================
//エラトステネス（nまでの素数抽出）
vector<ll> getPrime(ll n){
  vector<ll> prime(0);
  vector<bool> N(n + 1, true);
  N[0] = false;
  N[1] = false;
  for(int i = 2; i <= n; i++){
    if (N[i])
      prime.push_back(i);
    for(int j = 2; i * j <= n; ++j){
      N[i * j] = false;
    }
  }
  return prime;
}

int main() {
  cincout();

  auto prime = getPrime(2e7); // 373ms  1e8: 3035ms
}

// ==================== Clibor entry 009 ====================
// ワーシャルフロイド
// https://atcoder.jp/contests/abc243/submissions/56628601
class wf {
 public:
  vector<vector<ll>> D;
  ll N;

  wf(ll N) : N(N) {
    D.resize(N, vector<ll>(N, oo));
    rep(i, N) D[i][i] = 0;
  }  
  void add(ll a, ll b, ll c, bool force = false) {
    if (force){
      D[a][b] = c;
      D[b][a] = c;
      return ;
    }
    D[a][b] = min(D[a][b], c);
    D[b][a] = min(D[b][a], c);
  }
  void run() {
    rep(k, N) rep(i, N) rep(j, N) chmin(D[i][j], D[i][k] + D[k][j]);
  }
  void addEdge(int u, int v, ll w){
    if (D[u][v] <= w)
      return; // 現在の最短距離が新しい距離より短い場合は何もしない
    D[u][v] = w;
    D[v][u] = w;

    // 再計算
    rep(i, N) rep(j, N){
      if (D[i][u] < oo && D[v][j] < oo)
      {
        D[i][j] = min(D[i][j], D[i][u] + D[u][v] + D[v][j]);
      }
      if (D[i][v] < oo && D[u][j] < oo)
      {
        D[i][j] = min(D[i][j], D[i][v] + D[v][u] + D[u][j]);
      }
    }
  }
};

int main(){  
  ll N, M;
  cin >> N >> M;
  wf w(N);
  vector<ll> A(M), B(M), C(M);
  rep(i, M){
    cin >> A[i] >> B[i] >> C[i];
    --A[i], --B[i];
    w.add(A[i], B[i], C[i]);
  }
  w.run();
  ll ans = 0;
  rep(i, M){
    ll a = A[i], b = B[i], c = C[i];
    if (w.D[a][b] < c){
      ++ans;
      continue;
    }
    bool ok = false;
    // dp[A][x] + dp[x][B] == Cとなるxが存在するか
    rep(j, N){
      if (j == a || j == b) continue;
      if (w.D[a][j] + w.D[j][b] <= c){
        ok = true;
        break;
      }
    }
    if(ok) ++ans;
  }
  cout << ans << endl;
}

// ==================== Clibor entry 010 ====================
// MinCostFlow
// https://atcoder.jp/contests/acl1/tasks/acl1_c
typedef ll FLOW;       // フローを表す型、今回は ll 型
typedef ll COST;       // コストを表す型、今回は ll 型
const ll MAX_V = 3000; // グラフの最大ノード数
const COST INF = oo;   // 十分大きい値

// グラフの辺の構造体
struct Edge
{
  ll rev, from, to;
  FLOW cap, icap;
  COST cost;
  Edge(ll r, ll f, ll t, FLOW ca, COST co) : rev(r), from(f), to(t), cap(ca), icap(ca), cost(co) {}
};

// グラフ構造体
struct Graph
{
  ll V;
  vector<Edge> list[MAX_V];

  Graph(ll n = 0) : V(n)
  {
    for (ll i = 0; i < MAX_V; ++i)
      list[i].clear();
  }
  void init(ll n = 0)
  {
    V = n;
    for (ll i = 0; i < MAX_V; ++i)
      list[i].clear();
  }
  void resize(ll n = 0) { V = n; }
  void reset()
  {
    for (ll i = 0; i < V; ++i)
      for (ll j = 0; j < (ll)list[i].size(); ++j)
        list[i][j].cap = list[i][j].icap;
  }
  inline vector<Edge> &operator[](ll i) { return list[i]; }

  Edge &redge(Edge &e)
  {
    if (e.from != e.to)
      return list[e.to][e.rev];
    else
      return list[e.to][e.rev + 1];
  }

  void addedge(ll from, ll to, FLOW cap, COST cost)
  {
    list[from].push_back(Edge((ll)list[to].size(), from, to, cap, cost));
    list[to].push_back(Edge((ll)list[from].size() - 1, to, from, 0, -cost));
  }
};

// 最小費用流を求める関数
COST MinCostFlow(Graph &G, ll s, ll t, FLOW inif)
{
  COST dist[MAX_V];
  ll prevv[MAX_V];
  ll preve[MAX_V];

  COST res = 0;
  FLOW f = inif;
  while (f > 0)
  {
    fill(dist, dist + G.V, INF);
    dist[s] = 0;
    while (true)
    {
      bool update = false;
      for (ll v = 0; v < G.V; ++v)
      {
        if (dist[v] == INF)
          continue;
        for (ll i = 0; i < (ll)G[v].size(); ++i)
        {
          Edge &e = G[v][i];
          if (e.cap > 0 && dist[e.to] > dist[v] + e.cost)
          {
            dist[e.to] = dist[v] + e.cost;
            prevv[e.to] = v;
            preve[e.to] = i;
            update = true;
          }
        }
      }
      if (!update)
        break;
    }

    if (dist[t] == INF)
      return 0;

    FLOW d = f;
    for (ll v = t; v != s; v = prevv[v])
    {
      d = min(d, G[prevv[v]][preve[v]].cap);
    }
    f -= d;
    res += dist[t] * d;
    for (ll v = t; v != s; v = prevv[v])
    {
      Edge &e = G[prevv[v]][preve[v]];
      Edge &re = G.redge(e);
      e.cap -= d;
      re.cap += d;
    }
  }
  return res;
}

int main()
{
  ll N, M;
  cin >> N >> M;
  vector<string> S(N);
  rep(i, N) cin >> S[i];

  Graph G(N * M + 2);
  ll from = N * M, to = N * M + 1;
  ll jobs = 0;
  vector<vector<ll>> cost(N, vector<ll>(M, oo));

  auto init_cost=[&](ll sy, ll sx){
    cost.assign(N, vector<ll>(M, oo));
    queue<pll> Q;
    Q.push({sy, sx});
    cost[sy][sx] = 0;
    while(!Q.empty()){
      auto[y, x] = Q.front(); Q.pop();
      rep(d, 2){
        ll ny = y + dy[d], nx = x + dx[d];
        if (isn_field(ny, nx, N, M) || S[ny][nx] == '#') continue;
        if (chmin(cost[ny][nx], cost[y][x] + 1)){
          Q.push({ny, nx});
          G.addedge(sy * M + sx, ny * M + nx, 1, -cost[ny][nx]);
        }
      }
    }
  };

  rep(i, N) rep(j, M)
  {
    if (S[i][j] == '#')
      continue;
    if (S[i][j] == 'o')
    {
      G.addedge(from, i * M + j, 1, 0); // from, to, cap(その辺に流せる最大の流量), cost
      init_cost(i, j);
      ++jobs;
    }
    G.addedge(i * M + j, to, 1, 0);
  }

  // 最小費用流を求める
  COST res = MinCostFlow(G, from, to, jobs); // graph, from, to, スタート地点に流す数

  // 出力
  cout << -res << endl;
  return 0;
}

/*
9 10
.#....o#..
.#..#..##o
.....#o.##
.###.#o..o
#.#...##.#
..#..#.###
#o.....#..
....###..o
o.......o#

24
*/

// ==================== Clibor entry 011 ====================
//Convolution
/*
c0 = a0b0
c1 = a0b1 + a1b0
c2 = a0b2 + a1b1 + a2b0
c3 = a0b3 + a1b2 + a2b1 + a3b0
c(N+M-1) = a0b(N+M-1) + ...

https://kopricky.github.io/code/FFTs/ntt.html

4 5
1 2 3 4
5 6 7 8 9

5 16 34 60 70 70 59 36
*/
// 特殊な剰余と原始根
// (924844033, 5)
// (998244353, 3)
// (1012924417, 5)
// (167772161, 3)
// (469762049, 3)
// (1224736769, 3)
 
#define MOD 998244353
#define root 3
 
unsigned int add(const unsigned int x, const unsigned int y)
{
    return (x + y < MOD) ? x + y : x + y - MOD;
}
 
unsigned int sub(const unsigned int x, const unsigned int y)
{
    return (x >= y) ? (x - y) : (MOD - y + x);
}
 
unsigned int mul(const unsigned int x, const unsigned int y)
{
    return (unsigned long long)x * y % MOD;
}
 
unsigned int mod_pow(unsigned int x, unsigned int n)
{
    unsigned int res = 1;
    while(n > 0){
        if(n & 1){ res = mul(res, x); }
        x = mul(x, x);
        n >>= 1;
    }
    return res;
}
 
unsigned int inverse(const unsigned int x)
{
    return mod_pow(x, MOD - 2);
}
 
void ntt(vector<int>& a, const bool rev = false)
{
    unsigned int i, j, k, l, p, q, r, s;
    const unsigned int size = a.size();
    if(size == 1) return;
    vector<int> b(size);
    r = rev ? (MOD - 1 - (MOD - 1) / size) : (MOD - 1) / size;
    s = mod_pow(root, r);
    vector<unsigned int> kp(size / 2 + 1, 1);
    for(i = 0; i < size / 2; ++i) kp[i + 1] = mul(kp[i], s);
    for(i = 1, l = size / 2; i < size; i <<= 1, l >>= 1){
        for(j = 0, r = 0; j < l; ++j, r += i){
            for(k = 0, s = kp[i * j]; k < i; ++k){
                p = a[k + r], q = a[k + r + size / 2];
                b[k + 2 * r] = add(p, q);
                b[k + 2 * r + i] = mul(sub(p, q), s);
            }
        }
        swap(a, b);
    }
    if(rev){
        s = inverse(size);
        for(i = 0; i < size; i++){ a[i] = mul(a[i], s); }
    }
}
 
vector<int> convolute(const vector<int>& a, const vector<int>& b)
{
    const int size = (int)a.size() + (int)b.size() - 1;
    int t = 1;
    while(t < size){ t <<= 1; }
    vector<int> A(t, 0), B(t, 0);
    for(int i = 0; i < (int)a.size(); i++){ A[i] = a[i]; }
    for(int i = 0; i < (int)b.size(); i++){ B[i] = b[i]; }
    ntt(A), ntt(B);
    for (int i = 0; i < t; i++){ A[i] = mul(A[i], B[i]); }
    ntt(A, true);
    A.resize(size);
    return A;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(0);
  
  int N, M;
  cin >> N >> M;
  
  vector<int> A(N, 0), B(M, 0);
  rep(i, N) cin >> A[i];
  rep(i, M) cin >> B[i];
  auto C = convolute(A, B);
  rep(i, N+M-1){
    cout << C[i];
    if (i == N+M-2)
      cout << endl;
    else
      cout << " ";
  }
}

// ==================== Clibor entry 012 ====================
//SCC 
/*
https://atcoder.jp/contests/abc296/submissions/40266529
閉路の要素数の合計を求める。

strongly_connected_component
ライブラリ
https://kopricky.github.io/code/GraphDecomposition/strongly_connected_component.html

トポロジカルソート
https://hkawabata.github.io/technical-note/note/Algorithm/graph/scc.html
1 -> 2 -> 3 -> 1 -> 2 ...
ってなっているときに、2 1 3と出してはいけない
*/
vector<vector<int>> topo(500000, vector<int>(0, 0));

class SCC {
private:
    const int V;
    vector<vector<int> > G;
    vector<int> ord, low;
    stack<int> st;
    void dfs(const int u, int& tm){
        ord[u] = low[u] = tm++, st.push(u);
        for(int v : G[u]){
            if(ord[v] < 0){
                dfs(v, tm);
                low[u] = min(low[u], low[v]);
            }else if(cmp[v] < 0){
                low[u] = min(low[u], ord[v]);
            }
        }
        if(ord[u] == low[u]){
            while(true){
                const int v = st.top();
                st.pop();
                cmp[v] = cnt;
//cout << "v:" << v << " cmp[" << v << "]:" << cmp[v]
//  << " cnt:" << cnt << endl;
                topo[cnt].push_back(v);
                if(v == u) break;
            }
            ++cnt;
        }
    }
public:
    vector<vector<int> > graph;
    vector<int> cmp;
    int cnt;
    SCC(const int node_size)
        : V(node_size), G(V), ord(V, -1), low(V), cmp(V, -1), cnt(0){}
    void add_edge(const int from, const int to){
        G[from].push_back(to);
    }
    int solve(){
        int tm = 0;
        for(int i = 0; i < V; ++i){
            if(ord[i] < 0) dfs(i, tm);
        }
        for(int i = 0; i < V; ++i) cmp[i] = cnt - 1 - cmp[i];
        return cnt;
    }
    void make_graph(){ //ループしてない辺をgraphに抽出
        graph.resize(cnt);
        for(int i = 0; i < V; ++i){
            for(int j : G[i]){
                if(cmp[i] != cmp[j]){
                    graph[cmp[i]].push_back(cmp[j]);
                }
            }
        }
    }
};

int main(){
  cincout();

  int N;
  cin >> N;
  SCC scc(N);
  vector<ll> A(N);
  ll ans = 0;
  rep(i, N){
    cin >> A[i];
    --A[i];
    // 単方向グラフ scc.add_edge(a, b)  a->b
    scc.add_edge(i, A[i]);
    if (i == A[i]) ++ans; // 自己ループ。ループでない要素と判別できないので、ここでする。
  }
  int scc_num = scc.solve();
  scc.make_graph();
  
  /*
  3
  2 3 3
  G[0] = {1};
  G[1] = {2};
  G[2] = {2};
  -----------------
  scc_num:3 // グループ数
  1:0 // 要素1は、自己ループかループじゃないかのどちらか。判定はできない。
  1:1
  1:2 // 自己ループ

  3
  2 3 1
  G[0] = {1};
  G[1] = {2};
  G[2] = {0};
  -----------------
  scc_num:1 // 2個以上のループは1つのグループとしてみなされる
  3:0 1 2
  
  5
  2 3 4 5 3
  -----------------
  scc_num:3
  1:0 // ループしていない
  1:1 // ループしていない
  3:4 3 2 // 3要素のループ

  */
  cerr << "scc_num:" << scc_num << endl; // グループ数
  for (int i = scc_num - 1; i >= 0; i--){
    int tsz = topo[i].size();
    if(tsz >= 2) ans += tsz;
    cerr << tsz << ":"; // グループの要素数
    for(ll j = tsz - 1; j >= 0; --j){ // topoは逆順に入っている？ので後ろから出力すれば順序通り
      cerr << topo[i][j] << " \n"[j == 0]; // グループの要素
    }
  }
  cout << ans << endl;
}

// ==================== Clibor entry 013 ====================
// 拡張 Euclid の互除法
// https://atcoder.jp/contests/abc340/submissions/50183254
// ap + bq = gcd(a, b) となる (p, q) を求め、d = gcd(a, b) をリターンします
// p, qは参照渡しで値が書き換わる。
ll extGcd(long long a, long long b, long long &p, long long &q) {  
    if (b == 0) { p = 1; q = 0; return a; }  
    long long d = extGcd(b, a%b, q, p);  
    q -= a/b * p;  
    return d;
}

int main() {
  cincout();
  
  ll X, Y;
  cin >> X >> Y;

  // |pY - qX| = 2となる(p, q)を求める
  ll p, q;

  // |51y - 100x| = 2 を求める
  auto g = abs(extGcd(Y, -X, p, q)); // (100, -51, p, q) => g = 1, p = 25, q = 49
  if (g > 2){
    cout << -1 << endl;
    return 0;
  }
  // 求めたいのは51p - 100q = 1ではなく = 2なので2倍
  cout << p * 2 / g << " " << q * 2 / g << endl;
}

// ==================== Clibor entry 014 ====================
//中国人剰余定理CRT
//https://atcoder.jp/contests/abc193/tasks/abc193_e

inline long long mod(long long a, long long m) {
    return (a % m + m) % m;
}

// 拡張 Euclid の互除法
// ap + bq = gcd(a, b) となる (p, q) を求め、d = gcd(a, b) をリターンします
long long extGcd(long long a, long long b, long long &p, long long &q) {  
    if (b == 0) { p = 1; q = 0; return a; }  
    long long d = extGcd(b, a%b, q, p);  
    q -= a/b * p;  
    return d;  
}

pair<long long, long long> ChineseRem(long long b1, long long m1, long long b2, long long m2) {
  long long p, q;
  long long d = extGcd(m1, m2, p, q); // p is inv of m1/d (mod. m2/d)
  if ((b2 - b1) % d != 0) return make_pair(0, -1);
  long long m = m1 * (m2/d); // lcm of (m1, m2)
  long long tmp = (b2 - b1) / d * p % (m2/d);
  long long r = mod(b1 + m1 * tmp, m);
  return make_pair(r, m);
}

int main(){
  cincout();
  
  // x≡2(mod5), x≡1(mod6) を満たす最小値を求める。
  // リターン値を (r, m) とすると解は x ≡ r (mod m)
  // 解なしの場合 (0, -1) をリターン
  auto r = ChineseRem(2, 5, 1, 6); // 7 30 = {min, lcm}
}

// ==================== Clibor entry 015 ====================
// ダイクストラ
/*
https://atcoder.jp/contests/nikkei2019-2-qual/tasks/nikkei2019_2_qual_da
[L,R]すべてが行き来できるグラフ。1つ戻るコスト0の辺を追加すれば、L~Rすべてに辺をはらなくてよい。
*/
struct Graph
{
  ll V;
  vector<vector<pll>> G; // cost, to
  vector<ll> d;
  vector<ll> prev;
  vector<bool> used;

  Graph(ll n)
  {
    init(n);
  }

  void init(ll n)
  {
    V = n;
    G.resize(V);
    d.resize(V);
    prev.resize(V);
  }

  void add_edge(ll s, ll t, ll cost)
  {
    G[s].emplace_back(t, cost);
  }

  void del_edge(ll s, ll t, ll cost)
  {
    for (auto it = G[s].begin(); it != G[s].end();)
    {
      auto [_to, _cost] = *it;
      if (_to == t && _cost == cost)
      {
        it = G[s].erase(it);
      }
      else
      {
        it++;
      }
    }
  }

  void dijkstra(ll s)
  {
    rep(i, V)
    {
      d[i] = oo;
      prev[i] = -1;
    }
    d[s] = 0;
    priority_queue<pll, vector<pll>, greater<pll>> que;
    que.push(pll(0, s)); // cost, v
    while (!que.empty())
    {
      ll qsz = que.size();
      rep(i, qsz)
      {
        auto [cost, v] = que.top();
        que.pop();
        if (d[v] < cost)
          continue;
        for (auto [to, ncost] : G[v])
        {
          if (d[to] > d[v] + ncost)
          {
            d[to] = d[v] + ncost;
            que.push(pll(d[to], to));
            prev[to] = v; // vからe.toについた
          }
        }
      }
    }
  }

  vector<ll> get_path(int g, int s)
  {
    // s 1->2->3 g
    // path[0]=1 path[1]=2 path[2]=3 を返す
    vector<ll> path;
    for (int cur = g; cur != s; cur = prev[cur])
    { // goalまで
      path.push_back(cur);
    }
    path.push_back(s);
    reverse(path.begin(), path.end()); // 逆順なのでひっくり返す
    return path;
  }

  vector<ll> get_path(int g, int s, vector<ll> prev)
  {
    // s 1->2->3 g
    // path[0]=1 path[1]=2 path[2]=3 を返す
    vector<ll> path;
    for (int cur = g; cur != s; cur = prev[cur])
    { // goalまで
      path.push_back(cur);
    }
    path.push_back(s);
    reverse(path.begin(), path.end()); // 逆順なのでひっくり返す
    return path;
  }
};

int main()
{
  cincout();

  ll N, M;
  cin >> N >> M;
  Graph g(N + 1);
  rep(i, M)
  {
    ll L, R, C;
    cin >> L >> R >> C;
    L--;
    R--;
    g.add_edge(L, R, C);
  }
  g.dijkstra(0);
  if (g.d[N - 1] == oo)
    cout << -1 << endl;
  else
    cout << g.d[N - 1] << endl;
}

// ==================== Clibor entry 016 ====================
//トポロジカルソート
/*
https://atcoder.jp/contests/nikkei2019-qual/tasks/nikkei2019_qual_d
*/
ll in[100010]; //入次数。親の数
vector<vector<ll>> G(100010);
vector<vector<ll>> ans(100010);
ll pars[100010];
queue<ll> Q;

void bfs()
{
  while (!Q.empty()){
    ll sz = Q.size();
    rep(i, sz){
      ll now = Q.front();
      Q.pop();
      for(auto n: G[now]){
        in[n]--;
        if (!in[n]){
          Q.push(n);
          ans[now].push_back(n);
        }
      }
    }
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(0);
  ll N, M;
  cin >> N >> M;
  rep(i, N + M){
    ll A, B;
    cin >> A >> B;
    G[A].push_back(B);
    in[B]++;
  }
  ll par = -1;
  for(ll i=1; i<=N; i++){
    if (!in[i]){
      par = i;
      break;
    }
  }
  Q.push(par);
  bfs();
  for(ll i=1; i<=N; i++){
    for(auto v: ans[i]){
      pars[v] = i;
    }
  }
  for(ll i=1; i<=N; i++) cout << pars[i] << endl;
}

// ==================== Clibor entry 017 ====================
// nck(simple)
// DP[60][30]:118264581564861424
// DP[61][30]:232714176627630544
// DP[62][31]:465428353255261088
// DP[63][31]:916312070471295267
// DP[65][32]:3609714217008132870
// DP[66][33]:7219428434016265740 ここまで
ll DP[110][110];
void nck(){
  DP[0][0] = 1;
  rep(i, 100){
    rep(j, i+1){
      DP[i+1][j] += DP[i][j];
      DP[i+1][j+1] += DP[i][j];
    }
  }
}

int main(){
  cincout();
  nck();
  for(ll i=67; i<=100; i++) rep(j, i/2+1) cout << "DP["<<i<<"]["<<j<<"]:"<<DP[i][j]<<endl;
}

// ==================== Clibor entry 018 ====================
// montmort
// https://atcoder.jp/contests/arc009/submissions/21973763
ll MOD = 1777777777;
ll MM[1000010];

void montmort(ll n){ // n以下までMMにinit
  MM[0]=1;
  MM[1]=0;
  MM[2]=1;
  for(ll i=3; i<=n; i++)
    (MM[i] = (i-1) * (MM[i-1] + MM[i-2])%MOD)%=MOD;
}

// ==================== Clibor entry 019 ====================
// セグ木
/*
https://atcoder.jp/contests/typical90/tasks/typical90_ak
*/
class RangeMax{
public:
  ll size_ = 1;
  vector<ll> dat;
  void init(ll sz, ll def = -oo){ // sz, default_val
    while (size_ <= sz) size_ *= 2;
    dat.resize(size_ * 2, def);
  }
  void update(ll pos, ll x){
    pos += size_;
    if (dat[pos] == x) return ;
    dat[pos] = x;
    while (pos >= 2){
      pos >>= 1;
      dat[pos] = max(dat[pos * 2], dat[pos * 2 + 1]);
    }
  }
  
  ll query_(ll l, ll r, ll k, ll a, ll b){
    if (r <= a || b <= l) return -oo;
    if (l <= a && b <= r) return dat[k];
    ll v1 = query_(l, r, k*2, a, (a+b)>>1);
    ll v2 = query_(l, r, k*2+1, (a+b)>>1, b);
    return max(v1, v2);
  }
  
  ll query(ll l, ll r){
    return query_(l, r, 1, 0, size_);
  }
  
  ll getval(ll id){
    id += size_;
    return (dat[id]);
  }
};


class RangeMin{
public:
  ll size_ = 1;
  vector<ll> dat;
  void init(ll sz, ll def = oo){ // sz, default_val
    while (size_ <= sz) size_ *= 2;
    dat.resize(size_ * 2, def);
  }
  void update(ll pos, ll x){
    pos += size_;
    if (dat[pos] == x) return ;
    dat[pos] = x;
    while (pos >= 2){
      pos >>= 1;
      dat[pos] = min(dat[pos * 2], dat[pos * 2 + 1]);
    }
  }
  
  ll query_(ll l, ll r, ll k, ll a, ll b){
    if (r <= a || b <= l) return oo;
    if (l <= a && b <= r) return dat[k];
    ll v1 = query_(l, r, k*2, a, (a+b)>>1);
    ll v2 = query_(l, r, k*2+1, (a+b)>>1, b);
    return min(v1, v2);
  }
  
  ll query(ll l, ll r){
    return query_(l, r, 1, 0, size_);
  }
  
  ll getval(ll id){
    id += size_;
    return (dat[id]);
  }
};

// https://atcoder.jp/contests/abc254/submissions/32323766
class RangeGCD {
 public:
  ll size_ = 1;
  vector<ll> dat;
  void init(ll sz) {
    while (size_ <= sz) size_ *= 2;
    // 0start
    dat.resize(size_ * 2, 0);
  }
  void update(ll pos, ll x) {
    pos += size_;
    if (dat[pos] == x) return;
    dat[pos] = x;
    while (pos >= 2) {
      pos >>= 1;
      // 0のときはgcdをとらない
      if (dat[pos * 2] > 0 && dat[pos * 2 + 1] > 0) {
        dat[pos] = gcd(dat[pos * 2], dat[pos * 2 + 1]);
      } else {
        dat[pos] = max(dat[pos * 2], dat[pos * 2 + 1]);
      }
    }
  }

  ll query_(ll l, ll r, ll k, ll a, ll b) {
    if (r <= a || b <= l) return -oo;
    if (l <= a && b <= r) return dat[k];
    ll v1 = query_(l, r, k * 2, a, (a + b) >> 1);
    ll v2 = query_(l, r, k * 2 + 1, (a + b) >> 1, b);
    // 0のときはgcdをとらない
    if (v1 > 0 && v2 > 0) {
      return gcd(v1, v2);
    } else {  // どっちか0
      return max(v1, v2);
    }
  }

  ll query(ll l, ll r) { return query_(l, r, 1, 0, size_); }

  ll getval(ll id) {
    id += size_;
    return (dat[id]);
  }
};


int main(){
  cincout();

  ll W, N;
  cin >> W >> N;

  RangeMax Z;
  Z.init(W, -oo);
  Z.update(0, 0);
  rep(i, N){
    ll L, R, V;
    cin >> L >> R >> V;
    for(ll j = W; j >= L; --j){
      ll high = Z.query(max(j - R, 0LL), j-L+1);
      if (high == -oo) continue;
      Z.update(j, high + V); // id, val
    }
  }
  if (Z.getval(W) == -oo) cout << -1 << endl;
  else cout << Z.getval(W) << endl;
}

// ==================== Clibor entry 020 ====================
//遅延セグ（lazy加算 + range_max) or atcLibrary
/*
https://atcoder.jp/contests/dp/tasks/dp_w
Library
https://atcoder.jp/contests/abc357/submissions/54364018
*/
class segment_tree {
private:
  ll sz;
  vector<ll> seg;
  vector<ll> lazy;
  void push(ll k){
    if (k < sz){
      lazy[k * 2] += lazy[k];
      lazy[k * 2 + 1] += lazy[k];
    }
    seg[k] += lazy[k];
    lazy[k] = 0;
  }
  void update(ll a, ll b, ll x, ll k, ll l, ll r){
    push(k);
    if (r <= a || b <= l) return ;
    if (a <= l && r <= b){
      lazy[k] = x;
      push(k);
      return ;
    }
    update(a, b, x, k * 2, l, (l + r) >> 1);
    update(a, b, x, k * 2 + 1, (l + r) >> 1, r);
    // 
    seg[k] = max(seg[k * 2], seg[k * 2 + 1]);
  }
  ll range_max(ll a, ll b, ll k, ll l, ll r){
    push(k);
    if (r <= a || b <= l) return -oo;
    if (a <= l && r <= b) return seg[k];
    ll lc = range_max(a, b, k * 2, l, (l + r) >> 1);
    ll rc = range_max(a, b, k * 2 + 1, (l + r) >> 1, r);
    return max(lc, rc);
  }
public:
  segment_tree() : sz(0), seg(), lazy() {};
  segment_tree(ll N, ll val = 0){
    sz = 1;
    while (sz < N){
      sz *= 2;
    }
    seg = vector<ll>(sz * 2, val);
    lazy = vector<ll>(sz * 2, 0);
  }
  void update(ll l, ll r, ll x){
    update(l, r, x, 1, 0, sz);
  }
  ll range_max(ll l, ll r){
    return (range_max(l, r, 1, 0, sz));
  }
  void debug(){
    ll id = 1;
    cout << "--- seg ---" << endl;
    while (id <= sz){
      ll j = id;
      id *= 2;
      while (j < id){
        cout << seg[j] << " ";
        ++j;
      }
      cout << endl;
    }
    id = 1;
    cout << " --- lazy ---" << endl;
    while (id <= sz){
      ll j = id;
      id *= 2;
      while (j < id){
        cout << lazy[j] << " ";
        ++j;
      }
      cout << endl;
    }
  }

  ll getval(ll id){
    range_max(id, id+1);
    return seg[id + sz];
  }

};

vector<pll> G[200010];

int main(){
  cincout();
  ll N, M;
  cin >> N >> M;
  segment_tree seg(N+1);
  rep(i, M){ // 0-indexedは危険。seg.update(0, , ) が更新されない現象。
    ll L, R, A;
    cin >> L >> R >> A;
    --L;
    --R;
    G[R].push_back({L, A});
  }
  rep(i, N){
    // update([L, R), addVal);
    seg.update(i, i+1, max(seg.range_max(0, i), 0LL));
    for(auto p: G[i]){
      seg.update(p.first, i+1, p.second);
    }
  }
//    seg.debug();
  // range_max([L, R));
  cout << max(0LL, seg.range_max(0, N)) << endl;
}

// ==================== Clibor entry 021 ====================
//遅延セグ（lazyはmax更新)
/*
https://atcoder.jp/contests/typical90/tasks/typical90_ac
*/
class segment_tree {
private:
  ll sz;
  vector<ll> seg;
  vector<ll> lazy;
  ll def_val = 0;
  void push(ll k){
    if (k < sz){
      lazy[k * 2] = max(lazy[k * 2], lazy[k]);
      lazy[k * 2 + 1] = max(lazy[k * 2 + 1], lazy[k]);
    }
    seg[k] = max(seg[k], lazy[k]);
    lazy[k] = def_val;
  }
  void update(ll a, ll b, ll x, ll k, ll l, ll r){
    push(k);
    if (r <= a || b <= l) return ;
    if (a <= l && r <= b){
      lazy[k] = x;
      push(k);
      return ;
    }
    update(a, b, x, k * 2, l, (l + r) >> 1);
    update(a, b, x, k * 2 + 1, (l + r) >> 1, r);
    // 
    seg[k] = max(seg[k * 2], seg[k * 2 + 1]);
  }
  ll range_max(ll a, ll b, ll k, ll l, ll r){
    push(k);
    if (r <= a || b <= l) return -oo;
    if (a <= l && r <= b) return seg[k];
    ll lc = range_max(a, b, k * 2, l, (l + r) >> 1);
    ll rc = range_max(a, b, k * 2 + 1, (l + r) >> 1, r);
    return max(lc, rc);
  }
public:
  segment_tree() : sz(0), seg(), lazy() {};
  segment_tree(ll N, ll val = 0){
    sz = 1;
    while (sz < N){
      sz *= 2;
    }
    seg = vector<ll>(sz * 2, val);
    lazy = vector<ll>(sz * 2, val);
    def_val = val;
  }
  void update(ll l, ll r, ll x){
    update(l, r, x, 1, 0, sz);
  }
  ll range_max(ll l, ll r){
    return (range_max(l, r, 1, 0, sz));
  }
  void debug(){
    ll id = 1;
    cout << "--- seg ---" << endl;
    while (id <= sz){
      ll j = id;
      id *= 2;
      while (j < id){
        cout << seg[j] << " ";
        ++j;
      }
      cout << endl;
    }
    id = 1;
    cout << " --- lazy ---" << endl;
    while (id <= sz){
      ll j = id;
      id *= 2;
      while (j < id){
        cout << lazy[j] << " ";
        ++j;
      }
      cout << endl;
    }
  }

  ll getval(ll id){
    range_max(id, id+1);
    return seg[id + sz];
  }
};

int main(){
  cincout();
  ll W, N;
  cin >> W >> N;
  segment_tree seg(W);
  rep(i, N){ // 0-indexedは危険。 seg.update(0, , )が更新されない現象
    ll L, R;
    cin >> L >> R;
    ll height = seg.range_max(L-1, R) + 1;
    seg.update(L-1, R, height);
//    seg.debug();
    cout << height << endl;
  }
}

// ==================== Clibor entry 022 ====================
// LIS 単調増加列の最長一致
// https://atcoder.jp/contests/typical90/tasks/typical90_bh
// DPの中身は特に意味をなさない。DPの長さ=最長長さというだけ。
vector<ll> LIS(vector<ll> A){
  vector<ll> DP;
  rep(i, A.size()){
    ll pos = lower_bound(all(DP), A[i]) - DP.begin();
    if (pos >= (ll)DP.size()){
      DP.emplace_back(A[i]);
    }
    else{
      DP[pos] = A[i];
    }
  }
  return DP;
}

// 最長増加部分列のうち、辞書順で最大のものを復元する
vector<ll> LIS_largest(const vector<ll>& A) {
  ll N = A.size();
  if (N == 0) return {};

  vector<ll> xs = A;
  sort(all(xs));
  xs.erase(unique(all(xs)), xs.end());

  // suffixLen[i] = A[i]から始まるLISの最大長
  vector<ll> suffixLen(N);
  vector<ll> bit(xs.size() + 1, 0);

  auto bitMax = [&](ll p) {
    ll res = 0;
    for (; p > 0; p -= p & -p) chmax(res, bit[p]);
    return res;
  };
  auto bitUpdate = [&](ll p, ll value) {
    for (; p < (ll)bit.size(); p += p & -p) chmax(bit[p], value);
  };

  ll longest = 0;
  for (ll i = N - 1; i >= 0; --i) {
    ll rank = lower_bound(all(xs), A[i]) - xs.begin();
    ll reversedRank = (ll)xs.size() - rank;
    suffixLen[i] = bitMax(reversedRank - 1) + 1;
    bitUpdate(reversedRank, suffixLen[i]);
    chmax(longest, suffixLen[i]);
  }

  vector<vector<ll>> indices(longest + 1);
  rep(i, N) indices[suffixLen[i]].emplace_back(i);

  vector<ll> result;
  ll lastIndex = -1;
  ll lastValue = 0;
  bool hasLast = false;

  for (ll need = longest; need >= 1; --need) {
    ll bestIndex = -1;

    for (ll i : indices[need]) {
      if (i <= lastIndex) continue;
      if (hasLast && A[i] <= lastValue) continue;

      if (bestIndex == -1 || A[i] > A[bestIndex] ||
          (A[i] == A[bestIndex] && i < bestIndex)) {
        bestIndex = i;
      }
    }

    result.emplace_back(A[bestIndex]);
    lastIndex = bestIndex;
    lastValue = A[bestIndex];
    hasLast = true;
  }

  return result;
}

// ==================== Clibor entry 023 ====================
// Convex Hull Trick f(x) = a * x + b (x ∈ [l, r))
// https://atcoder.jp/contests/abc353/submissions/53373407
template <typename T>
class CHT
{
private:
  struct node
  {
    node *left, *right;
    static const T inf = numeric_limits<T>::max();
    T a, b, l, r;
    node(const T _a, const T _b, const T _l, const T _r)
        : left(nullptr), right(nullptr), a(_a), b(_b), l(_l), r(_r) {}
    T f(const T x) const
    {
      return (l <= x && x < r) ? (a * x + b) : inf;
    }
    T tf(const T x) const
    {
      return a * x + b;
    }
    bool isLine(const T _l, const T _r) const
    {
      return (l == _l) && (r == _r);
    }
  };
  static void swap(node *x, node *y)
  {
    std::swap(x->a, y->a), std::swap(x->b, y->b), std::swap(x->l, y->l), std::swap(x->r, y->r);
  }
  void _add_segment(node *cur, node *nw, T l, T r)
  {
    while (true)
    {
      const T mid = (l + r) / 2;
      if (cur->f(nw->l) <= nw->tf(nw->l) && cur->f(nw->r - 1) <= nw->tf(nw->r - 1))
      {
        break;
      }
      if (cur->tf(cur->l) >= nw->f(cur->l) && cur->tf(cur->r - 1) >= nw->f(cur->r - 1))
      {
        swap(cur, nw);
        break;
      }
      if (cur->isLine(l, r) && nw->isLine(l, r))
      {
        if (nw->tf(l) < cur->tf(l))
          swap(cur, nw);
        if (cur->tf(mid) <= nw->tf(mid))
        {
          if (!cur->right)
          {
            cur->right = new node(nw->a, nw->b, mid, r);
            break;
          }
          else
          {
            cur = cur->right, l = mid, nw->l = mid;
          }
        }
        else
        {
          swap(cur, nw);
          if (!cur->left)
          {
            cur->left = new node(nw->a, nw->b, l, mid);
            break;
          }
          else
          {
            cur = cur->left, r = mid, nw->r = mid;
          }
        }
        continue;
      }
      if (nw->isLine(l, r))
        swap(cur, nw);
      if (nw->r <= mid)
      {
        if (!cur->left)
        {
          cur->left = new node(*nw);
          break;
        }
        else
        {
          cur = cur->left, r = mid;
        }
      }
      else if (mid <= nw->l)
      {
        if (!cur->right)
        {
          cur->right = new node(*nw);
          break;
        }
        else
        {
          cur = cur->right, l = mid;
        }
      }
      else
      {
        node _nw(nw->a, nw->b, mid, nw->r);
        nw->r = mid;
        if (!cur->left)
        {
          cur->left = new node(*nw);
        }
        else
        {
          _add_segment(cur->left, nw, l, mid);
        }
        if (!cur->right)
        {
          cur->right = new node(_nw);
        }
        else
        {
          _add_segment(cur->right, &_nw, mid, r);
        }
        break;
      }
    }
  }
  T query(node *cur, const T k, T l, T r) const
  {
    T ans = numeric_limits<T>::max();
    while (cur)
    {
      ans = min(ans, cur->f(k));
      const T mid = (l + r) / 2;
      if (k < mid)
      {
        cur = cur->left, r = mid;
      }
      else
      {
        cur = cur->right, l = mid;
      }
    }
    return ans;
  }
  void clear(node *cur)
  {
    if (cur->left)
      clear(cur->left);
    if (cur->right)
      clear(cur->right);
    delete cur;
  }
  const T lpos, rpos;
  node *root;

public:
  CHT(const T _lpos, const T _rpos)
      : lpos(_lpos), rpos(_rpos),
        root(new node(0, numeric_limits<T>::max(), lpos, rpos))
  {
    assert(lpos < rpos);
  }
  // ~CHT(){ clear(root); }
  // f(x) = a * x + b を挿入
  void add_line(const T a, const T b)
  {
    node nw(a, b, lpos, rpos);
    return _add_line(root, &nw, lpos, rpos);
  }
  // f(x) = a * x + b (x ∈ [l, r)) を挿入
  void add_segment(const T a, const T b, const T l, const T r)
  {
    assert(l < r);
    node nw(a, b, l, r);
    return _add_segment(root, &nw, lpos, rpos);
  }
  // x = k での最小値
  T query(const T k) const
  {
    return query(root, k, lpos, rpos);
  }
};

int main()
{
  cincout();

  ll N, C, M;
  cin >> N >> C >> M;
  CHT<ll> cht(0, N);

  cht.add_segment(C, 0, 0, N); // Cx+0: [0, N)
  rep(i, M)
  {
    ll T, P;
    cin >> T >> P;
    --T;
    ll r = cht.query(T) - P; // get min value
    cht.add_segment(-C, r + C * T, 0, T + 1);
    cht.add_segment(C, r - C * T, T, N);
  }
  ll ans = oo;
  rep(i, N)
  {
    ll r = cht.query(i);
    chmin(ans, cht.query(i));
  }
  cout << -ans << endl;
}

// ==================== Clibor entry 024 ====================
// 2部マッチング
typedef int FLOW;                // フローを表す型、今回は int 型
typedef int COST;                // コストを表す型、今回は int 型
const int MAX_V = 100;           // グラフの最大ノード数
const COST INF = 100000000;      // 十分大きい値

// グラフの辺の構造体
struct Edge {
    int rev, from, to;
    FLOW cap, icap;
    COST cost;
    Edge(int r, int f, int t, FLOW ca, COST co) : rev(r), from(f), to(t), cap(ca), icap(ca), cost(co) {}
};

// グラフ構造体
struct Graph {
    int V;
    vector<Edge> list[MAX_V];

    Graph(int n = 0) : V(n) { for (int i = 0; i < MAX_V; ++i) list[i].clear(); }
    void init(int n = 0) { V = n; for (int i = 0; i < MAX_V; ++i) list[i].clear(); }
    void resize(int n = 0) { V = n; }
    void reset() { for (int i = 0; i < V; ++i) for (int j = 0; j < list[i].size(); ++j) list[i][j].cap = list[i][j].icap; }
    inline vector<Edge>& operator [] (int i) { return list[i]; }

    Edge &redge(Edge &e) {
        if (e.from != e.to) return list[e.to][e.rev];
        else return list[e.to][e.rev + 1];
    }

    void addedge(int from, int to, FLOW cap, COST cost) {
        list[from].push_back(Edge((int)list[to].size(), from, to, cap, cost));
        list[to].push_back(Edge((int)list[from].size() - 1, to, from, 0, -cost));
    }
};

// 最小費用流を求める関数
COST MinCostFlow(Graph &G, int s, int t, FLOW inif) {
    COST dist[MAX_V];
    int prevv[MAX_V];
    int preve[MAX_V];

    COST res = 0;
    FLOW f = inif;
    while (f > 0) {
        fill(dist, dist + G.V, INF);
        dist[s] = 0;
        while (true) {
            bool update = false;
            for (int v = 0; v < G.V; ++v) {
                if (dist[v] == INF) continue;
                for (int i = 0; i < G[v].size(); ++i) {
                    Edge &e = G[v][i];
                    if (e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
                        dist[e.to] = dist[v] + e.cost;
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        update = true;
                    }
                }
            }
            if (!update) break;
        }

        if (dist[t] == INF) return 0;

        FLOW d = f;
        for (int v = t; v != s; v = prevv[v]) {
            d = min(d, G[prevv[v]][preve[v]].cap);
        }
        f -= d;
        res += dist[t] * d;
        for (int v = t; v != s; v = prevv[v]) {
            Edge &e = G[prevv[v]][preve[v]];
            Edge &re = G.redge(e);
            e.cap -= d;
            re.cap += d;
        }
    }
    return res;
}


int main() {

    char workers[5] = { 'A', 'B', 'C', 'D', 'E' };
    int jobs[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 従業員数と、仕事数
    int NUM_WORKER = 0, NUM_JOB = 0;
    cin >> NUM_WORKER >> NUM_JOB;

    // グラフの定義 (ノード数を引数に)
    Graph G(NUM_WORKER + NUM_JOB + 2);             // +2 は S, T の分

    // スーパーノード S, T の index
    int S_node = NUM_WORKER + NUM_JOB;
    int T_node = NUM_WORKER + NUM_JOB + 1;

    // グラフに枝を張っていく
    for (int i = 0; i < NUM_WORKER; ++i) {
        for (int j = 0; j < NUM_JOB; ++j) {
            int gain;
            cin >> gain;

            // 従業員 i から、仕事 j (index は j+NUM_WORKER) へと、容量 1, コスト -gain の枝を張る
            G.addedge(i, j + NUM_WORKER, 1, -gain);
        }
    }

    for (int i = 0; i < NUM_WORKER; ++i) {
        // S から従業員 i へと、容量 2, コスト 0 の枝を張る
        G.addedge(S_node, i, 2, 0);
    }

    for (int j = 0; j < NUM_JOB; ++j) {
        // 仕事 j から T へと、容量 1, コスト 0 の枝を張る
        G.addedge(j + NUM_WORKER, T_node, 1, 0);
    }

    // 最小費用流を求める
    COST res = MinCostFlow(G, S_node, T_node, NUM_JOB);


    // 出力
    cout << "Max Gain: " << -res << endl;

    // 誰がどの仕事に割当てられたかを出力する
    for (int i = 0; i < NUM_WORKER; ++i) {
        for (auto e : G[i]) {
            // 元々の容量 (e.icap) が 1 で、フローが流れて容量 (e.cap) が 0 になった部分が割り当てられたところ
            if (e.icap == 1 && e.cap == 0) {
                cout << "Worker " << workers[i] << " and " << "Job " << jobs[e.to - NUM_WORKER]
                << " are matched (gain: " << -e.cost << ")" << endl;
            }
        }
    }

    return 0;
}

// ==================== Clibor entry 025 ====================
//floor((A*i + B) / M) (0 <= i <= N-1)の総和
long long floor_sum(long long n, long long m, long long a, long long b) {
    long long ans = 0;
    if (a >= m) {
        ans += (n - 1) * n * (a / m) / 2;
        a %= m;
    }
    if (b >= m) {
        ans += n * (b / m);
        b %= m;
    }

    long long y_max = (a * n + b) / m, x_max = (y_max * m - b);
    if (y_max == 0) return ans;
    ans += (n - (x_max + a - 1) / a) * y_max;
    ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
    return ans;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(0);
  
  ll T, N, M, A, B;
  cin >> T;
  rep(i, T){
    cin >> N >> M >> A >> B;
    cout << floor_sum(N, M, A, B) << endl;
  }
}

// ==================== Clibor entry 026 ====================
// 逆元（modが素数以外）https://atcoder.jp/contests/abc186/tasks/abc186_e
ll modinv2(ll a, ll m) {  // ret = inv(a) mod m
  ll b = m, u = 1, v = 0;
  while (b) {
    ll t = a / b;
    a -= t * b;
    swap(a, b);
    u -= t * v;
    swap(u, v);
  }
  u %= m;
  if (u < 0) u += m;
  return u;
}

// ==================== Clibor entry 027 ====================
// CartesianTree return value : pair<graph, root>
// https://atcoder.jp/contests/abc311/submissions/44320808
template <typename T>
pair<vector<vector<ll>>, ll> CartesianTree(vector<T> &a) {
  ll N = (ll)a.size();
  vector<vector<ll>> g(N);
  vector<ll> p(N, -1), st;
  st.reserve(N);
  for (ll i = 0; i < N; i++) {
    ll prv = -1;
    while (!st.empty() && a[i] < a[st.back()]) {
      prv = st.back();
      st.pop_back();
    }
    if (prv != -1) p[prv] = i;
    if (!st.empty()) p[i] = st.back();
    st.push_back(i);
  }
  /*
    A = {3 1 4 1 5}
    p[0] = 1
    p[1] = -1 // root
    p[2] = 3
    p[3] = 1
    p[4] = 3
  */
  ll root = -1;
  for (ll i = 0; i < N; i++) {
    if (p[i] != -1)
      g[p[i]].push_back(i);
    else
      root = i;
  }
  return make_pair(g, root);
}

ll mins[310][310][310];
ll ranges[310][310][310];  // i, l, r
int main() {
  cincout();

  ll N, M;
  cin >> N >> M;
  vector<vector<ll>> A(N, vector<ll>(M));
  rep(i, N) rep(j, M) cin >> A[i][j];
  rep(i, N) rep(j, M) {
    ll m = A[i][j];
    for (ll k = j; k < M; ++k) {
      chmin(m, A[i][k]);
      mins[i][j][k + 1] = m;
      ranges[i][j][k + 1] = ranges[i][j][k] + A[i][k];
    }
  }
  ll ans = 0;
  rep(j, M) for (ll k = j; k < M; ++k) {
    vector<ll> B;
    vector<ll> acc(N);
    rep(i, N) {
      B.push_back(mins[i][j][k + 1]);
      acc[i] = ranges[i][j][k + 1] + (i ? acc[i - 1] : 0);
    }
    auto [g, root] = CartesianTree(B);
    function<void(ll, ll, ll)> dfs = [&](ll l, ll r, ll d) {
      ll ac = acc[r - 1] - (l ? acc[l - 1] : 0);
      // cerr << j << "," << k << " " << l << "," << r << "," << d << " " << ac << " " << mins[d][j][k + 1] << " " << ac * mins[d][l][r] << endl;
      chmax(ans, ac * mins[d][j][k + 1]);
      for (auto to : g[d]) {
        if (to < d) {
          dfs(l, d, to);
        } else {
          dfs(d + 1, r, to);
        }
      }
    };
    dfs(0, N, root);
  }
  cout << ans << endl;
}

// ==================== Clibor entry 036 ====================
setbuf(stdout, NULL);

// ==================== Clibor entry 042 ====================
#include "Example.hpp"

Example::Example()
{
}

Example::Example(Example const &src)
{
    *this = src;
}

Example::~Example()
{
}

Example& Example::operator=(const Example &src)
{
    if (this == &src)
        return (*this);
    // this->xxx = src.xxx
    return (*this);
}

// ==================== Clibor entry 043 ====================
// 行列DP
// https://atcoder.jp/contests/dp/tasks/dp_r
typedef vector<ll> Vec;
typedef vector<Vec> Mat;

void printVec(Vec a){
  cout << "[\t";
  ll asz = a.size();
  rep(i, asz) cout << a[i] << "\t";
  cout << "]" << endl;
}

void printMat(Mat a){
  ll asz = a.size();
  rep(i, asz) printVec(a[i]);
}

Vec mulMatVec(Mat a, Vec b){
  ll n = b.size();
  Vec ret(n, 0);
  rep(i, n) rep(j, n){
    (ret[i] += b[i] * a[i][j] % MOD) %= MOD;
  }
  return ret;
}

Mat mulMatMat(Mat a, Mat b){
  ll n = a.size();
  Mat ret(n, Vec(n, 0));
  rep(i, n) rep(j, n) rep(k, n){
    ( ret[i][j] += a[i][k] * b[k][j] % MOD ) %= MOD;
  }
  return ret;
}

Mat fastpow(Mat x, ll n){
  Mat ret(x.size(), Vec(x.size(), 0));
  ll xsz = x.size();
  rep(i, xsz) ret[i][i] = 1;
  while (n > 0){
    if (n%2 == 0){
      x = mulMatMat(x, x);
      n >>= 1;
    }
    else{
      ret = mulMatMat(ret, x);
      --n;
    }
  }
  return ret;
}

ll N, K;
bool A[55][55];

int main(){
  cincout();
  
  cin >> N >> K;
  Mat m(N, Vec(N, 0));
  Vec v(N, 1);
  
  rep(i, N) rep(j, N){
    cin >> A[i][j];
    m[i][j] = A[i][j];
  }

  m = fastpow(m, K);
  v = mulMatVec(m, v);
  
  ll ans = 0;
  rep(i, N) (ans += v[i]) %= MOD;
  cout << ans << endl;
}

// ==================== Clibor entry 044 ====================
// 最小包含円
// https://atcoder.jp/contests/abc151/tasks/abc151_f
using P=complex<ld>;
const ld eps = 1e-10;
ld cross(const P& a, const P& b) { return a.real()*b.imag() - a.imag()*b.real(); }
ld dot(const P& a, const P& b) { return a.real()*b.real() + a.imag()*b.imag(); }

template <class iter>
std::pair<P, ld> min_ball(iter left, iter right, int seed = 1333) {

    const int n = right - left;

    assert(n >= 1); // n>=1 しか想定していない
    if (n == 1) {
        return {*left, ld(0)};
    }

    std::mt19937 mt(seed); // 乱数生成
//    std::shuffle(left, right, mt);
	srand(time(0));
    std::random_shuffle(left, right); // simple but deprecated
    
//    for(auto it = left; it != right; ++it)
//    cout << *it << endl;

    iter ps = left;
    using circle = std::pair<P, ld>;

    auto make_circle_3 = [](const P &a, const P &b, const P &c) -> circle {
        ld A = std::norm(b - c), B = std::norm(c - a), C = std::norm(a - b),
           S = cross(b - a, c - a);
        P p = (A * (B + C - A) * a + B * (C + A - B) * b + C * (A + B - C) * c) / (4 * S * S);
        ld r2 = std::norm(p - a);
        return {p, r2};
    };

    auto make_circle_2 = [](const P &a, const P &b) -> circle {
        P c = (a + b) / (ld)2;
        ld r2 = std::norm(a - c);
        return {c, r2}; // 中点, 半径^2
    };

    auto in_circle = [](const P &a, const circle &c) -> bool {
        return std::norm(a - c.first) <= c.second + eps;
    };

    circle c = make_circle_2(ps[0], ps[1]);

    // MiniDisc
    for (int i = 2; i < n; ++i) {
        if (!in_circle(ps[i], c)) {
            // MiniDiscWithPoint
            c = make_circle_2(ps[0], ps[i]);
            for (int j = 1; j < i; ++j) {
                if (!in_circle(ps[j], c)) {
                    // MiniDiscWith2Points
                    c = make_circle_2(ps[i], ps[j]);
                    for (int k = 0; k < j; ++k) {
                        if (!in_circle(ps[k], c)) {
                            c = make_circle_3(ps[i], ps[j], ps[k]);
                        }
                    }
                }
            }
        }
    }
    return c;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(0);
  cout << fixed << setprecision(10);
  
  ll N;
  cin >> N;
  vector<P> ps(N);
  rep(i, N){
    ld x, y;
    cin >> x >> y;
    ps[i] = {x, y};
  }
  auto ret = min_ball(ps.begin(), ps.end());
  //  cout << "ret:" << ret.first << " " << ret.second << endl;
  // 中心の座標がret.first。全部の点と中心点との、最大距離が最小包含円の半径。
  P cent = ret.first;
  ld ans = -oo;
  rep(i, N){
    chmax(ans, abs(ret.first - ps[i]));
  }
  cout << ans << endl;
}

// ==================== Clibor entry 045 ====================
// MaxFlow
// https://atcoder.jp/contests/abc010/tasks/abc010_4

template <typename T>
struct MaxFlow {
  struct Edge {
    ll to, rev; T cap; // rev:逆向きの辺の番号
    Edge(ll to, ll rev, T cap) : to(to), rev(rev), cap(cap) { }
  };
  
  typedef vector<Edge> Edges;
  vector<Edges> G;
  ll V;
  vector<ll> level, iter;
  
  MaxFlow(ll V) : V(V) { G.resize(V); }
  
  void add_edge(ll from, ll to, T cap){
    G[from].emplace_back(to, G[to].size(), cap); // to, rev, cap
    G[to].emplace_back(from, (ll)G[from].size()-1, 0);
  }

  void bfs(ll source) {
    level.assign(V, -1);
    queue<ll> que;
    que.emplace(source);
    level[source] = 0;
    while(!que.empty()){
      ll v = que.front(); que.pop();
      rep(i, (ll)G[v].size()){
        Edge &e = G[v][i];
        if (e.cap > 0 && level[e.to]< 0){ 
          level[e.to] = level[v] + 1;
//        cout << "level[" << e.to << "]:" << level[e.to] << endl;
          que.emplace(e.to);
        }
      }
    }
  }
  
  T dfs(ll v, ll sink, T flow) {
    if (v == sink) return flow;
    for (ll &i = iter[v]; i < (ll)G[v].size(); ++i){
//      cout << "iter["<<v<<"]:"<< i << endl;
      Edge &e = G[v][i];
      if (e.cap > 0 && level[v] < level[e.to]) { //cap = 流量, v->e.toが先の深さなら。
        T d = dfs(e.to, sink, min(e.cap, flow));
        if (d > 0){ // dは末端から流せた量
          e.cap -= d; // capacity減らす。0以上
          G[e.to][e.rev].cap += d; // rev、逆流は増やす
          return d;
        }
      }
    }
    return 0;
  }
  T dinic(ll source, ll sink) {
    T flow = 0;
    while(1) {
      bfs(source); // levelを作る
      if ( level[sink] < 0 ) return flow;
      iter.assign(V, 0);
      T f;
      while (( f = dfs(source, sink, oo)) > 0 ) flow += f;
    }
  }
};

int main(){
  cincout();
  
  ll N, G, E;
  cin >> N >> G >> E;
  MaxFlow<ll> mf(N+1);
  rep(i, G){
    ll g;
    cin >> g;
    mf.add_edge(g, N, 1);
  }
  rep(i, E){
    ll a, b;
    cin >> a >> b;
    mf.add_edge(a, b, 1);
    mf.add_edge(b, a, 1);
  }
  
  cout << min( mf.dinic(0, N), G ) << endl;
}

// ==================== Clibor entry 046 ====================
// マラソン

constexpr int END_TIME = 1985; // 処理を打ち切る時間
const auto START_TIME = chrono::system_clock::now(); // 開始時刻
constexpr double start_temp = 110, end_temp = 0; // 最大点数変化、最小点数変化

int getTime() {
    auto end_time = chrono::system_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end_time-START_TIME).count();
}

// 温度関数
double get_temp() {
  return start_temp + (end_temp-start_temp) * getTime() / END_TIME; // 一定に温度を下げたいとき用
  //return start_temp*pow(end_temp/(double)start_temp, getTime()/(double)END_TIME); // 山登り結構いけるとき用
}

// 遷移確率
double prob(double new_score, double pre_score) {
  double temp = get_temp();
  return exp((new_score-pre_score)/temp);
}
double randouble() {
	return double(xorshift()) / double(uint64_t(-1));
}
struct WeightedSampler // エイリアス法
{
  ll n;
  std::vector<ld> prob;  // 成功確率
  std::vector<ll> alias; // 失敗時の飛び先
  vector<ll> similar_pairs;

  WeightedSampler() {}
  void init(vector<ld> &w, vector<ll> &simp)
  {
    similar_pairs = simp;
    n = (ll)w.size();
    prob.assign(n, 0.0);
    alias.assign(n, 0);

    // 1) 正規化して期待値=1の分布に変換
    ld sum = std::accumulate(w.begin(), w.end(), 0.0);
    std::vector<ld> P(n);
    for (ll i = 0; i < n; ++i)
    {
      P[i] = w[i] * n / sum;
    }

    // 2) 大小のグループに分ける
    std::queue<ll> small, large;
    for (ll i = 0; i < n; ++i)
    {
      if (P[i] < 1.0)
        small.push(i);
      else
        large.push(i);
    }

    // 3) Aliasテーブル構築ループ
    while (!small.empty() && !large.empty())
    {
      ll l = small.front();
      small.pop();
      ll g = large.front(); // popは後で
      prob[l] = P[l];
      alias[l] = g;
      P[g] = (P[g] + P[l]) - 1.0; // 大きい側の余りを調整

      large.pop();
      if (P[g] < 1.0)
        small.push(g);
      else
        large.push(g);
    }

    // 4) あまりはすべて 1 にしておく
    while (!large.empty())
    {
      prob[large.front()] = 1.0;
      large.pop();
    }
    while (!small.empty())
    {
      prob[small.front()] = 1.0;
      small.pop();
    }
  }

  // サンプリング：O(1)
  ll sample() const
  {
    ll i = randxor(0, n);
    ld u = randouble();
    return (u < prob[i] ? similar_pairs[i] : similar_pairs[alias[i]]);
  }
};

struct State {
  ll x, y;
  ll score{};
 
  bool operator<(State &b) { return score < b.score; }
  void eval();
};
State beam_search()
{
  int BEAMSIZE = 1000;
  int SHUFFLESIZE = 100;
  int L = 300;
  State start;        // 初期状態
  vector<State> cand; // セーブデータを、操作ごとに保存
  cand.push_back(start);

  rep(turn, L)
  { // L手先までみる
    vector<State> ncand;
    ncand.reserve(cand.size() * 4); // 容量確保
    for (auto s : cand)
    {
      rep(d, 4)
      {
        // 1手シミュレート
        State ns = s;
        ncand.push_back(ns);
      }
    }
    sort(all(ncand)); // scoreの高い順にならぶ
    // chokudaiサーチ。下位からも一定割合取得する
    if (ncand.size() > BEAMSIZE)
    {
      shuffle(ncand.begin() + BEAMSIZE - SHUFFLESIZE, ncand.end(),
              mt19937(seed));
    }
    ncand.resize(min(BEAMSIZE, (int)ncand.size())); // 足きり
    swap(cand, ncand);
  }
  return cand[0];
}

// ==================== Clibor entry 047 ====================
// LCA(最近共通祖先)
// https://atcoder.jp/contests/abc014/tasks/abc014_4
// グラフを表す構造体
using Graph = vector<vector<ll>>;

// LCA を求めるライブラリ
struct LCA {
    vector<vector<ll> > parent; // parent[d][v] := 2^d-th parent of v
    vector<ll> depth;
    LCA() { }
    LCA(const Graph &G, ll r = 0) { init(G, r); }
    void init(const Graph &G, ll r = 0) {
        ll V = (ll)G.size();
        ll h = 1;
        while ((1<<h) < V) ++h;
        parent.assign(h, vector<ll>(V, -1));
        depth.assign(V, -1);
        dfs(G, r, -1, 0);
        for (ll i = 0; i+1 < (ll)parent.size(); ++i)
            for (ll v = 0; v < V; ++v)
                if (parent[i][v] != -1)
                    parent[i+1][v] = parent[i][parent[i][v]];
    }
    void dfs(const Graph &G, ll v, ll p, ll d) {
        parent[0][v] = p;
        depth[v] = d;
        for (auto e : G[v]) if (e != p) dfs(G, e, v, d+1);
    }
    ll get(ll u, ll v) { // 頂点u,vの、最近共通祖先が得られる
        if (depth[u] > depth[v]) swap(u, v);
        for (ll i = 0; i < (ll)parent.size(); ++i)
            if ( (depth[v] - depth[u]) & (1<<i) )
                v = parent[i][v];
        if (u == v) return u;
        for (ll i = (ll)parent.size()-1; i >= 0; --i) {
            if (parent[i][u] != parent[i][v]) {
                u = parent[i][u];
                v = parent[i][v];
            }
        }
        return parent[0][u];
    }
};

int main(){
  cincout();
  
  ll N;
  cin >> N;
  Graph G(N);
  
  rep(i, N-1){
    ll x, y;
    cin >> x >> y;
    --x, --y;
    G[x].push_back(y);
    G[y].push_back(x);
  }
  
  LCA lca(G);
  ll Q;
  cin >> Q;
  rep(i, Q){
    ll a, b;
    cin >> a >> b;
    --a, --b;
    ll v = lca.get(a, b);
    cout << lca.depth[a] + lca.depth[b] - lca.depth[v]*2 + 1 << endl;
  }
}

// ==================== Clibor entry 048 ====================
// オイラー路
// http://algoogle.hadrori.jp/joi/sc2011shiritori/
// 問題を改変。有向文字列しりとりで、文字列と先頭と末尾でつなげられるか

/*
4
ab
ba
bc
cb
*/
ll n, deg[128], itr[128];
vector<string> words, ans;
vector<pll> G[128];

ll find_start() {
  vector<ll> hs, ts;
  for (ll i = 0; i < 26; i++) {
    if (deg[i] > 1) return -1;
    // スタートするアルファベット
    if (deg[i] == 1) hs.push_back(i);
    // ゴールするアルファベット
    if (deg[i] == -1) ts.push_back(i);
  }
  // どこから始めてもいい
  if (hs.size() == 0 && ts.size() == 0) return (words[0][words[0].size() - 1] - 'a');
  if (hs.size() != 1 || ts.size() != 1) return -1;
  return hs[0];
}

void build_graph() {
  ll i = 0;
  for (auto &w : words) {
    ll u = w[0] - 'a', v = w[w.size() - 1] - 'a';
    G[u].push_back(pll(v, i++));
  }
}

void euler(ll v) {
  for (ll &i = itr[v]; i < (ll)G[v].size();) {
    ll j = i++;
    euler(G[v][j].first);
    ans.push_back(words[G[v][j].second]);
  }
}

ll solve() {
  //        sort(begin(words), end(words));
  ll s = find_start();
  if (s < 0) return 0;
  build_graph();
  euler(s);
  if ((ll)ans.size() != n) return 0;
  return 1;
}

void input() {
  cin >> n;
  string s;
  for (ll i = 0; i < n; i++) {
    cin >> s;
    words.push_back(s);
    deg[s[0] - 'a']++;
    deg[s[s.size() - 1] - 'a']--;
  }
}

int main() {
  input();
  if (!solve())
    cout << 0 << endl;
  else
    cout << 1 << endl;
  return 0;
}

// ==================== Clibor entry 049 ====================
// string同士の掛け算
string mul_s(string a, string b){
  ll MKETA = 100000;
  ll calcs[MKETA] = {};
  ll asz = a.size();
  ll bsz = b.size();
  string ret;
  rep(i, asz){
    ll j = asz - i - 1; //1桁目
    ll anum = a[j] - '0';
    rep(k, bsz){
      ll m = bsz - k - 1;
      ll bnum = b[m] - '0';
      calcs[i+k] += anum*bnum;
    }
  }
  ll keta = 0;
  rep(i, MKETA){
    ll n = calcs[i];
    calcs[i+1] += n/10;
    calcs[i] %= 10;
    if (calcs[i]){
      chmax(keta, i+1);
    }
  }
  rep(i, keta){
    ret += calcs[i] + '0';
  }
  reverse(all(ret));
  return ret;
}

// ==================== Clibor entry 050 ====================
// BIT,index = 1 ~ (0を投げるととまる
// indexを+1して格納する。
// https://atcoder.jp/contests/abc174/submissions/21572028
template<ll BT>
struct Bit
{
  ll dat[BT+10]{};
  void add(ll i, ll x){
    ++i;
    for(; i<BT; i += i&-i) dat[i] += x;
  }
  ll sum(ll i){
    ++i;
    ll res = 0;
    for(; i>0; i -= i&-i) res += dat[i];
    return res;
  }
  ll rangesum(ll L, ll R){ // [L, R)
    return sum(R) - sum(L-1);
  }

  void debug(ll R){
    rep(i, R+1) cout << dat[i] << " ";
    cout << endl;
  }
};

// ==================== Clibor entry 051 ====================
// tupleの取り出し方
  ll N;
  cin >> N;
  vector<tll> T(N);
  rep(i, N){
    ll x, y, z;
    cin >> x >> y >> z;
    T[i] = {x, y, z};
  }
  rep(i, N){
    auto&[a, b, c] = T[i];
    cout << a << " " << b << " " << c << endl;
  }

// ==================== Clibor entry 052 ====================
// 全方位木DP
// https://atcoder.jp/contests/dp/tasks/dp_v
ll N, M;
ll DP[100010];
vector<ll> G[100010];

void dfs1(ll v, ll p){
  DP[v] = 1;
  for(auto u: G[v]){
    if (u==p) continue;
    dfs1(u, v);
    (DP[v] *= DP[u] + 1) %= M;
  }
}

void dfs2(ll v, ll p, ll D=0){
  ll sz = G[v].size();
  ll mul1[sz] = {};
  ll mul2[sz] = {};
  rep(i, sz){
    ll u = G[v][i];
    if (u==p){
      mul1[i] = mul2[i] = (D + 1) % M;
      (DP[v] *= D + 1) %= M;
      // 解答埋め
      // D=0の初回D[v]は、dfs1でもう解答が埋まっている。
      
      // 1は、DP[1]がdfs1ですでに-0以外埋まっている。
      // なので、D+1 = 1-0の要素をかけたらDP[1]が完成。
    }
    else{
      mul1[i] = mul2[i] = (DP[u] + 1) % M;
    }
  }
 
  rep(i, sz){
    if (i>0) (mul1[i] *= mul1[i-1]) %= M;
    ll j = sz-i-1;
    if (j<sz-1) (mul2[j] *= mul2[j+1]) %= M;
  }
  
  /*
  0 1
  1 2
  0 3
  0->1->2, 3の順番でdfs2()走査していく
  */
  rep(i, sz){
    ll u = G[v][i];
    if (u == p) continue;
    ll a=1, b=1;
    if (i>0) a = mul1[i-1];
    if (i<sz-1) b = mul2[i+1];
    dfs2(u, v, a*b%M);
  }
}

int main(){
  cincout();
  
  cin >> N >> M;
  rep(i, N-1){
    ll x, y;
    cin >> x >> y;
    --x;
    --y;
    G[x].push_back(y);
    G[y].push_back(x);
  }
  
  dfs1(0, -1); // DP[0]うめ
  dfs2(0, -1);
  rep(i, N) cout << DP[i] << endl;
}

// ==================== Clibor entry 055 ====================
// doubling
// https://atcoder.jp/contests/arc060/tasks/arc060_c

int main() {
  cincout();

  ll N, L, Q;
  ll MX = 21;
  cin >> N;
  vector<ll> X(N);
  vector DP(MX, vector<ll>(N, 0LL));
  rep(i, N) cin >> X[i];
  cin >> L >> Q;

  // doubling
  rep(i, N) {
    DP[0][i] =
        upper_bound(all(X), X[i] + L) - X.begin() - 1;  // 次の町のindexを入れる
  }
  rep(k, MX - 1) { rep(i, N) DP[k + 1][i] = DP[k][DP[k][i]]; }

 auto debug = [&]() {
    rep(i, MX) {
      rep(j, N) cerr << "DP[" << i << "][" << j << "] = " << DP[i][j] << "\n";
    }
  };
  //  debug();
  rep(i, Q) {
    ll a, b;
    cin >> a >> b;
    --a, --b;
    if (a > b) swap(a, b);
    ll ans = 0;

    for (ll k = MX - 1; k >= 0; --k) {
      if (DP[k][a] >= b) continue;  // bまであと1日でいける町を探す
      a = DP[k][a];                 // aを移動する
      ans += 1LL << k;              // 2^k日経過させる
    }
    ++ans;
    cout << ans << endl;
  }
}

// ==================== Clibor entry 057 ====================
// grundy
// https://atcoder.jp/contests/typical90/tasks/typical90_ae
ll grundy[55][1550]; // white, blue   //0==lose
ll W[100010];
ll B[100010];

void init(){
  ll fin = 50*51/2 + 50;
  rep(w, 51){ // white
    rep(b, fin + 1){
      bool mex[fin+1]{}; // 使ってる集合の要素
      if (w>0){
        mex[grundy[w-1][b+w]] = true;
      }
      if (b>1){
        for(ll j=1; j<=b/2; ++j) mex[grundy[w][b-j]] = true;
      }
      rep(i, fin+1){ // mex[0]==falseなら、必敗なのでgrudny=0
        if (mex[i] == false){
          grundy[w][b] = i;
          break;
        }
      }
    }
  }
}

int main(){
  cincout();
  
  init();
  
  ll N;
  cin >> N;
  rep(i, N) cin >> W[i];
  rep(i, N) cin >> B[i];
  
  ll sum = 0;
  rep(i, N){
    ll w=W[i];
    ll b=B[i];
    sum ^= grundy[w][b];
  }
  // 0が必敗
  if (sum==0) cout << "Second" << endl;
  else cout << "First" << endl;
}

// ==================== Clibor entry 058 ====================
// mo_algotirhm
// https://atcoder.jp/contests/abc242/tasks/abc242_g
// sqrt(100000)
#define bsize 316

bool qcomp(tll &a, tll &b) {
  auto [ast, afi, aid] = a;
  auto [bst, bfi, bid] = b;
  ast /= bsize;
  bst /= bsize;
  // startが同じかどうか
  if (ast < bst) {
    return true;
  }
  if (ast > bst) {
    return false;
  }
  // goalについて
  // 偶数番目はgoalが昇順
  if ((ast & 1) == 0) {
    if (afi < bfi) {
      return true;
    }
    if (afi > bfi) {
      return false;
    }
  } else {
  // 奇数番目はgoalが降順
    if (afi < bfi) {
      return false;
    }
    if (afi > bfi) {
      return true;
    }
  }
  // 同じならid順
  return (aid < bid);
}

vector<ll> a;
ll cnt[100010];
ll res = 0;
ll st, fi;

void mo_add(ll id) {
  ++cnt[a[id]];
  if (cnt[a[id]] % 2 == 0) {
    ++res;
  }
}

void mo_rem(ll id) {
  if (cnt[a[id]] % 2 == 0) {
    --res;
  }
  --cnt[a[id]];
}

ll mo_query(ll tst, ll tfi) {
  if (!(fi < tst)) {
    while (st < tst) {
      mo_rem(st);
      ++st;
    }
    while (tst < st) {
      --st;
      mo_add(st);
    }
  }
  while (fi < tfi) {
    ++fi;
    mo_add(fi);
  }
  while (tfi < fi) {
    mo_rem(fi);
    --fi;
  }

  while (st < tst) {
    mo_rem(st);
    ++st;
  }
  while (tst < st) {
    --st;
    mo_add(st);
  }
  return res;
}

int main() {
  cincout();

  ll N;
  cin >> N;
  a.resize(N);
  rep(i, N) cin >> a[i];
  ll Q;
  cin >> Q;
  vector<tll> QV(Q);
  rep(i, Q) {
    ll L, R;
    cin >> L >> R;
    --L, --R;
    QV[i] = {L, R, i};
  }
  // qcompでsort
  sort(all(QV), qcomp);
  /*
  image
  1 2 3 4 5
  |------>|
  >>|-----|
    |<----|
    ||
    >>||
      |->|
      >>||
  */


  vector<ll> ans(Q);
  mo_add(0);
  st = 0;
  fi = 0;
  rep(i, Q) {
    auto &[qst, qfi, qid] = QV[i];
    ans[qid] = mo_query(qst, qfi);
  }
  rep(i, Q) { cout << ans[i] << endl; }
}

// ==================== Clibor entry 059 ====================
// 外心点
// https://atcoder.jp/contests/abc151/submissions/58023121
// 3点の外心を求める関数
pair<ld, ld> Circumcenter(ld ax, ld ay, ld bx, ld by, ld cx, ld cy) {
  ld D = 2 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by));
  if (abs(D) < 1e-10) {
    // 3点が直線上にある場合
    return {oo, oo};  // 適切な処理を後で行うための印
  }
  ld ux = ((ax * ax + ay * ay) * (by - cy) + (bx * bx + by * by) * (cy - ay) + (cx * cx + cy * cy) * (ay - by)) / D;
  ld uy = ((ax * ax + ay * ay) * (cx - bx) + (bx * bx + by * by) * (ax - cx) + (cx * cx + cy * cy) * (bx - ax)) / D;
  return {ux, uy};
}

int main(){
  cincout();
  
  const ld eps = 1e-10;
  ll N;
  cin >> N;
  vector<ll> X(N), Y(N);
  rep(i, N){
    cin >> X[i] >> Y[i];
  }
  
  ld ans = oo;

  // 2点の最小半径
  rep(i, N){
    for(ll j = i + 1; j < N; ++j){
      ld r = euclidDist(X[i], Y[i], X[j], Y[j]) / 2;
      ld rx = (X[i] + X[j]) / 2.0;
      ld ry = (Y[i] + Y[j]) / 2.0;
      bool ok = true;
      rep(k, N){
        ld d = euclidDist(rx, ry, X[k], Y[k]);
        if (d > r + eps){
          ok = false;
          break;
        }
      }
      if (ok){
        chmin(ans, r);
      }
    }
  }

  // 3点の最小半径
  rep(i, N){
    for(ll j = i + 1; j < N; ++j){
      for(ll k = j + 1; k < N; ++k){
        auto [cx, cy] = Circumcenter(X[i], Y[i], X[j], Y[j], X[k], Y[k]);
        if (cx == oo && cy == oo) continue;  // 直線上にある場合は無視

        ld r = euclidDist(cx, cy, X[i], Y[i]);
        bool ok = true;
        rep(n, N){
          ld d = euclidDist(cx, cy, X[n], Y[n]);
          if (d > r + eps){
            ok = false;
            break;
          }
        }
        if (ok){
          chmin(ans, r);
        }
      }
    }
  }
  cout << ans << endl;
}

// ==================== Clibor entry 060 ====================
#pragma once
#include <algorithm>
#include <cstdint>
#include <limits>
#include <unordered_map>
#include <utility>
#include <vector>

// A board-copy-free layered beam.
// Problem must provide:
//   using Move, Undo, Score;
//   void enumerate(F emit) const;        // emit(Move)
//   Undo apply(Move);
//   void undo(const Undo&);
//   Score evaluate() const;              // smaller is better
//   uint64_t hash() const;
//   bool complete() const;
// Only one mutable Problem exists. Active nodes are visited in DFS order and
// the state moves between adjacent paths by undoing/applying their suffixes.
namespace inplace_beam {

template<class Problem>
class Search {
 public:
  using Move = typename Problem::Move;
  using Undo = typename Problem::Undo;
  using Score = typename Problem::Score;

  struct Config {
    int width = 1000;
    int depth = 16;
    bool deduplicate = true;
    int reserve_branching = 24;
  };

 private:
  struct Node { int parent; Move move; int depth; };
  struct Candidate {
    Score score;
    uint64_t hash;
    int parent_node;
    int parent_order;
    Move move;
  };

  Problem& problem_;
  Config config_;
  std::vector<Node> nodes_;
  std::vector<int> active_;
  std::vector<int> current_path_;
  std::vector<int> target_path_;
  std::vector<Undo> undo_path_;
  std::vector<Candidate> candidates_;
  std::unordered_map<uint64_t, size_t> hash_to_candidate_;

  void move_to(int node_id) {
    target_path_.clear();
    for (int at=node_id; at>0; at=nodes_[at].parent) target_path_.push_back(at);
    std::reverse(target_path_.begin(), target_path_.end());
    int common=0;
    while (common<(int)target_path_.size() && common<(int)current_path_.size()
           && target_path_[common]==current_path_[common]) ++common;
    while ((int)current_path_.size()>common) {
      problem_.undo(undo_path_.back());
      undo_path_.pop_back(); current_path_.pop_back();
    }
    for (int i=common;i<(int)target_path_.size();++i) {
      undo_path_.push_back(problem_.apply(nodes_[target_path_[i]].move));
      current_path_.push_back(target_path_[i]);
    }
  }

  std::vector<Move> restore_path(int parent, const Move& last) const {
    std::vector<Move> result{last};
    for (int at=parent;at>0;at=nodes_[at].parent) result.push_back(nodes_[at].move);
    std::reverse(result.begin(),result.end());
    return result;
  }

 public:
  Search(Problem& problem, Config config):problem_(problem),config_(config) {
    nodes_.push_back({-1,Move{},0}); active_.push_back(0);
    const size_t candidate_reserve=(size_t)config.width
                                  * std::max(1,config.reserve_branching);
    nodes_.reserve((size_t)config.width*(config.depth+1)+1);
    active_.reserve(config.width);
    candidates_.reserve(candidate_reserve);
    if (config.deduplicate) hash_to_candidate_.reserve(candidate_reserve*2);
    current_path_.reserve(config.depth);
    target_path_.reserve(config.depth);
    undo_path_.reserve(config.depth);
  }

  std::vector<Move> run() {
    bool found_complete=false;
    Score best_score=std::numeric_limits<Score>::max();
    int best_parent=-1;
    Move best_last{};
    for (int depth=0;depth<config_.depth && !active_.empty();++depth) {
      candidates_.clear();
      if (config_.deduplicate) hash_to_candidate_.clear();
      for (int order=0;order<(int)active_.size();++order) {
        int parent=active_[order]; move_to(parent);
        problem_.enumerate([&](const Move& move) {
          Undo undo=problem_.apply(move);
          Score score=problem_.evaluate();
          uint64_t hash=problem_.hash();
          if (problem_.complete()) {
            // Basic contract: complete is terminal, so do not put it back in
            // the beam. Problems where complete states remain expandable need
            // a problem-specific policy instead.
            if (!found_complete || score<best_score) {
              found_complete=true;
              best_score=score;
              best_parent=parent;
              best_last=move;
            }
            problem_.undo(undo);
            return;
          }
          Candidate candidate{score,hash,parent,order,move};
          if (config_.deduplicate) {
            auto [it,inserted]=hash_to_candidate_.emplace(hash,candidates_.size());
            if (inserted) {
              candidates_.push_back(candidate);
            } else if (score<candidates_[it->second].score) {
              // Keep the best representative before applying the beam width.
              candidates_[it->second]=candidate;
            }
          } else {
            candidates_.push_back(candidate);
          }
          problem_.undo(undo);
        });
      }
      if (candidates_.empty()) break;
      int keep=std::min(config_.width,(int)candidates_.size());
      if ((int)candidates_.size()>keep) {
        std::nth_element(candidates_.begin(),candidates_.begin()+keep,candidates_.end(),
          [](const Candidate&a,const Candidate&b){return a.score<b.score;});
        candidates_.resize(keep);
      }
      // Restores DFS order for cheap transitions in the next layer.
      std::sort(candidates_.begin(),candidates_.end(),[](const Candidate&a,const Candidate&b){
        if(a.parent_order!=b.parent_order)return a.parent_order<b.parent_order;
        return a.hash<b.hash;
      });
      active_.clear(); active_.reserve(candidates_.size());
      for (auto& c:candidates_) {
        nodes_.push_back({c.parent_node,c.move,depth+1});
        active_.push_back((int)nodes_.size()-1);
      }
    }
    move_to(0);
    // Path allocation/reconstruction happens exactly once, after the search.
    if (!found_complete) return {};
    return restore_path(best_parent,best_last);
  }
};
} // namespace inplace_beam

// NOTE: Problem::evaluate() should preferably be O(1). Update its score in
// apply() and restore it in undo() instead of rescanning the whole state.
// NOTE: Problem::hash() should preferably be O(1), using incremental Zobrist,
// XOR, or another reversible hash update in apply()/undo().
// NOTE: Candidate size affects cache efficiency when branching is large.
// Compact Move where the problem permits it; roughly 16-32 bytes per candidate
// is a useful target, but this generic template does not force packing.
// NOTE: parent_order sorting is appropriate for beams of thousands. At widths
// of tens or hundreds of thousands, parent_order's bounded integer range can
// support bucket/counting-sort-style ordering.
// NOTE: std::unordered_map is kept for simplicity. Large searches may benefit
// from open addressing, a flat hash table, or generation/stamp clearing.
// NOTE: Config::reserve_branching is problem dependent; set it near the average
// number of emitted moves per active state to reduce reallocations without
// excessive memory reservation.
// NOTE: This implementation treats complete as terminal. If complete means
// merely "currently valid but still improvable", customize the complete branch
// and define how such states compete with unfinished candidates.
// NOTE: 64-bit hash deduplication can collide. Strict applications may use a
// 128-bit hash, an extra fingerprint, or an equality check on collisions.

// ==================== Clibor entry 061 ====================
// Z_Algorithm
vector<int> Z_algorithm(string S)
{
  // https://atcoder.jp/contests/abc430/submissions/70621688
  int c = 0, n = S.size();
  vector<int> Z(n, 0);
  for (int i = 1; i < n; i++)
  {
    int l = i - c;
    if (i + Z[l] < c + Z[c])
    {
      Z[i] = Z[l];
    }
    else
    {
      int j = max(0, c + Z[c] - i);
      while (i + j < n && S[j] == S[i + j])
        j++;

      Z[i] = j;
      c = i;
    }
  }

  Z[0] = n;
  return Z;
}

int main()
{
  cincout();
  ll T;
  cin >> T;
  while (T--)
  {
    string A, B;
    cin >> A >> B;
    ll N = A.size();
    string S = B + "." + A + A;
    auto v = Z_algorithm(S);
    ll ans = -1;
    rep(i, S.size()){
      if (v[i] == N){
        ans = i - N - 1;
        break;
      }
    }
    cout << ans << endl;
  }
}
