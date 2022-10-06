#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable" 
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wsign-compare"
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back

const int N = 2e5 + 4;
const ll P = 233;
const int A = 26;
const int MOD = 1e9 + 123;
ll h[N], pwr[N], inv[N];
vector<ll> prefix_sum;
map<ll, ll> M;
int n, q; ll l, r; 
char s[200005];
int tree[N][26], idx;
int len[N], link[N], t;

//------------ Hash code Starts
ll bigMod (ll a, ll e) {
  if (e == -1) e = MOD - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % MOD;
    a = a * a % MOD, e >>= 1;
  }
  return ret;
}

void init_hash(){
  pwr[0] = inv[0] = 1;
  ll INV_P = bigMod(P, -1);
  for (int i = 1; i < N; ++i) {
    pwr[i] = pwr[i - 1] * P % MOD;
    inv[i] = inv[i - 1] * INV_P % MOD;
  }
}
void build_hash(){
  for (int i = 1; i <= n; ++i) {
    h[i] = (h[i - 1] + (s[i] - 'a' + 1) * pwr[i]) % MOD;
  }
}
ll get_hash(int l, int r){
  ll one = (h[r] - h[l - 1]) * inv[l] % MOD;
  if (one < 0) one += MOD; 
  return one;
}
// -------------------Hash code ends

struct struct_pair{
  int idx, len;
  struct_pair(){}
  struct_pair(int a, int b){
    idx = a; len = b;
  }
  bool operator<(struct_pair other)const{
    int mx = min(len, other.len); mx--; 
    int lo = 0, hi = mx, mid;
    while(lo <= hi){
      mid = (lo + hi) / 2;
      if(get_hash(idx, idx + mid) == get_hash(other.idx,other.idx + mid))lo = mid + 1;
      else hi = mid - 1;
    }
    if(lo == mx + 1)return len < other.len; // emon case aabaa aabaabaa
    return s[idx + lo] < s[other.idx + lo];
  }
};

vector<struct_pair> vsp;

//------------Palindromic Tree Starts
void extend(int p) {
  while(s[p - len[t] - 1] != s[p]) t = link[t];
  int x = link[t], c = s[p] - 'a';
  while(s[p - len[x] - 1] != s[p]) x = link[x];
  if(!tree[t][c]) {
  tree[t][c] = ++idx;
  len[idx] = len[t] + 2;
  link[idx] = len[idx] == 1 ? 2 : tree[x][c];
  vsp.push_back(struct_pair(p - len[idx] + 1, len[idx]));
  } t = tree[t][c];
}
//------------Palindromic Tree Ends.

int main(){
  scanf("%d", &n);
  scanf("%s", s + 1);
  
  len[1] = -1; link[1] = 1;
  len[2] = 0; link[2] = 1;
  idx = t = 2;
  
  for(int i = 1; i <= n; i++) extend(i);
  init_hash();
  build_hash();
  sort(vsp.begin(), vsp.end());
  int distpal = vsp.size();
  ll sum = 0;
  for(int i = 0; i < distpal; i++){
    sum += vsp[i].len;
    prefix_sum.pb(sum);
    M[sum] = i + 1;
  }
  
  scanf("%d", &q);
  for(int cs = 1; cs <= q; cs++){
    scanf("%lld %lld", &l, &r);
    int idxl = lower_bound(prefix_sum.begin(), prefix_sum.end(), l) - prefix_sum.begin();
    auto idxr = lower_bound(prefix_sum.begin(), prefix_sum.end(), r);
    if(idxr == prefix_sum.end()){
      printf("-1\n"); continue;
    }
    ll prevsum = 0;
    if(idxl)prevsum = prefix_sum[idxl - 1];
    int idx = vsp[idxl].idx + (l - prevsum) - 1;
    while(l <= r){
      printf("%c", s[idx]);
      idx++;
      if(M.find(l) != M.end())idx = vsp[M[l]].idx;
      l++; 
    }
    printf("\n");
  }  
}
