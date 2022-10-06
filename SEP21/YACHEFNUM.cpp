#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long 
#define pb(e) push_back(e)
#define sv(a) sort(a.begin(),a.end())
#define sa(a,n) sort(a,a+n)
#define mp(a,b) make_pair(a,b)
#define vf first
#define vs second
#define ar array
#define all(x) x.begin(),x.end()
const int inf = 0x3f3f3f3f;
const int mod = 1000000007; 
const double PI=3.14159265358979323846264338327950288419716939937510582097494459230;
bool remender(ll a , ll b){return a%b;}

//freopen("problemname.in", "r", stdin);
//freopen("problemname.out", "w", stdout);

vector<int> v;

pair<ll,ll> dp[1002][1002][2][2][2];
ll dp1[1002][2][2][2];

ll zeros(int i , int start , int tight , int came){
  if(i == v.size())return came;
  if(dp1[i][start][tight][came] != -1)return dp1[i][start][tight][came];
  int last = 9;
  if(tight == 1)last = v[i];
  ll res = 0;
  for(int j = 0; j <= last; j++){
    if(j == 0){
      if(start == 1){
        res += zeros(i + 1 , start , 0 , 0);
        res %= mod;
      }
      else {
        res += zeros(i + 1 , 0 , (j == last ? tight : 0) , 1);
        res %= mod;
      }
    }
    else {
      res += zeros(i + 1 , 0 , (j == last ? tight : 0) , came);
      res %= mod;
    }
  }
  return dp1[i][start][tight][came] = res;
}

pair<ll,ll> rec(int i , int cnt , int which , int start, int tight){
  if(i == (v.size())){
    return mp(1,0);
  }
  if(dp[i][cnt][which][start][tight].vf != -1)return dp[i][cnt][which][start][tight];
  int last = 9;
  if(tight == 1)last = v[i];
  if(last == 0){
    return mp(0,0);
  }
  ll res = 0, ways = 0;
  if(start == 1){
    pair<ll,ll> p = rec(i + 1 , cnt , which , start , 0);
    res += p.vs;
    ways += p.vf;
  }
  for(int j = 1; j <= last; j++){
    int c = cnt , add = 0 , wh = which;
    if(j % 2 == 0){
      if(c == 0){
        if(j == 2 || j == 6)c = 1;
        else if(j == 4)c = 2;
        else if(j == 8)c = 3;
        wh = 0;
      }
      else {
        if(which == 0){
          if(j == 2 || j == 6)c++;
          else if(j == 4)c+=2;
          else if(j == 8)c += 3;
        }
        else {
          add++;
          c--;
          if(j == 4 || j == 8){
            if(c == 0){
              wh = 0;
              if(j == 4)c = 1;
              else c = 2;
            }
            else {
              add++;
              c--;
              if(j == 8){
                if(c == 0){
                  wh = 0;
                  c = 1;
                }
                else {
                  c--;
                  add++;
                }
              }
            }
          }
        }
      }
    }
    if(j == 5){
      if(c == 0){
        c = 1;
        wh = 1;
      }
      else {
        if(which == 1)c++;
        else {
          add++;
          c--;
        }
      }
    }
    c = min(c , 1000);
    if(j == v[i]){
      pair<ll,ll> p = rec(i + 1 , c , wh , 0 , tight);
      res += add*p.vf+p.vs;
      res %= mod;
      ways += p.vf;
      ways %= mod;
    }
    else {
      pair<ll,ll> p = rec(i + 1 , c , wh , 0 , 0);
      res += add*p.vf + p.vs;
      res %= mod;
      ways += p.vf;
      ways %= mod;
    }
  }
  return dp[i][cnt][which][start][tight] = mp(ways , res);
}

void solve(){
  string s;
  getline(cin , s);
  int n = s.size();
  ll ans = 0;
  for(int i = 0; i < n; i++){
    if(s[i] == ' '){
      memset(dp,-1,sizeof dp);
      memset(dp1,-1,sizeof dp1);
      ans -= (rec(0,0,0,1,1).vs + zeros(0,1,1,0))%mod;
      v.clear();
      continue;
    }
    v.pb(s[i]-'0');
  }
  memset(dp,-1,sizeof dp);
  memset(dp1,-1,sizeof dp1);
  ans += (rec(0,0,0,1,1).vs + zeros(0,1,1,0))%mod;
  ans += mod;
  ans %= mod;
  cout << ans << '\n';
}

int main() {
ios_base::sync_with_stdio(false);
cin.tie(NULL);
  //int t;cin >> t;while(t--)
  solve();
  return 0;
}
