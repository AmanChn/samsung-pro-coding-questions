/*Test - 5 
Q1.
You are given an array of strings. You can merge two strings, arr[i] and arr[j], only if,
i < j  and the last letter of arr[i] == first letter of arr[j]
Eg, you have two strings -> “123” and “389” -> after merging it becomes “123389”
You can keep merging strings like this, but the ‘final’ string you form must be such that the first letter of the string should be the same as the last letter.
Eg, after merging several strings, the ‘final’ string becomes -> “123389…………1”
Print the max length of the ‘final’ string that can be formed in this way.
Test case - 1:
Array of strings = [“14”, “123”, “323”, “321”,  “421”, “535”]
Possible ‘final’ strings -> “323”, “535”, “14421”, “123323321”, “123321”
Ans = 9 (which is the length of “123323321”) 
Test case – 2:
Array of strings = [“14”, “15”, “89”, “22”]
Possible ‘final’ strings -> “22”
Ans = 2 (which is the length+ of “22”)
1 <= ai <=1e9.  1 <=N<= 1e5
/*
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        vector<string> arr(n);
        
        for(int i=0;i<n;i++){
            cin >> arr[i];
        }
       
        // mp[a][b] = Max len of a valid chain whose first char is 'a' and last char is digit 'b'
        vector<vector<long long>> mp(10, vector<long long>(10, 0));
       
        // starting from last because string can be forme with i<j
        // & also as the current state depends on the future state so we will have ans for future available to use
        for (long long i = n - 1; i >= 0; i--) {
            int first = arr[i][0] - '0';
            int last = arr[i].back() - '0';
            long long len = arr[i].size();
            
            // check with all 10 numers that if a str starting with 'last' char is there or not
            for (long long j = 0; j <= 9; j++) {
                if (mp[last][j] != 0) {
                    mp[first][j] = max(mp[first][j], mp[last][j] + len); // we can make a new str and increase the size
                }
            }
            
            //if no chain starts from last, then the current string alone should still be a valid chain.
            mp[first][last] = max(mp[first][last], len); // to consider single strings
        }
       
        // as the final str need to have both 'first' and 'last' char same, find the max in diagonal
        long long res = 0;
        for (long long i = 0; i <= 9; i++) {
            res = max(res, mp[i][i]);
        }
       
        cout << res << endl;
    }
    
    return 0;
}


/*
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mx = 1e5+1;
vector<string>v;
int n;
long long dp[mx][10][10];
long long solve(int i, int st, int end){
  if(i==n){
    return (st==end)?0:INT_MIN;
  }
  if(dp[i][st][end]!=-1) return dp[i][st][end];
  ll ans=solve(i+1, st, end);
  if(st==end) ans=max(ans, 0LL);
  if(v[i][0]-'0'==end) ans= max( ans, solve(i+1,st,v[i].back()-'0')+(int)v[i].size());
  return dp[i][st][end]=ans;
}
int main(){
  int t;cin>>t;
  while(t--){
    cin>>n;
    v.resize(n);
    memset(dp,-1,sizeof (dp));
    for(int i=0;i<n;i++)cin>>v[i];
    int ans = 0;
    for(int i=0;i<n;i++){
      ans=max((ll)ans,solve(i,v[i][0]-'0',v[i][0]-'0'));
    }
    cout<<ans<<endl;
  }
}
*/
