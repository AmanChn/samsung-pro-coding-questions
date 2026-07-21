/*Q3. There are 'n' stones in a row from 0 to n-1. For every ith stone , there are 2 values associated with it, 
a[i] and b[i] . You have to remove all the stones from the row one by one. Removing the ith stone follows the rule:
If (i-1)th and (i+1)th stones are still present , then , cost of removing the ith stone is b[i].
if either (i-1)th or (i+1)th stone is present , then cost of removing the ith stone is a[i].
if neither (i-1)th nor (i+1)th stone is present , the cost of removing the ith stone is 0.

Find the minimum total cost of removing all the stones.

Constraints : 1 <= n <= 50000 1 <= a[i] , b[i] <= 1000

 https://codeforces.com/blog/entry/117311
 see comments (approach by vgtcross)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long min_removal_cost(int n, const vector<long long>& a, const vector<long long>& b) {
    // dp[i][0] = min cost for stones 1..i if stone i+1 is removed before stone i
    // dp[i][1] = min cost for stones 1..i if stone i+1 is removed after stone i
    vector<vector<long long>> dp(n, vector<long long>(2, 0));
    
    // Base Case (stone 0)
    // dp[0][0]: stone 1 is removed BEFORE stone 0 => stone 0 has no neighbours when removed
    dp[0][0] = 0;

    // dp[0][1]: stone 1 is removed AFTER stone 0 => right neighbour exists
    dp[0][1] = a[0];

    for(int i = 1; i < n; i++){
        // stone i+1 is removed BEFORE stone i
        dp[i][0] = min(
            dp[i-1][0] + a[i],   // remove i before i-1
            dp[i-1][1]           // remove i after i-1
        );

        // stone i+1 is removed AFTER stone i
        dp[i][1] = min(
            dp[i-1][0] + b[i],   // both neighbours alive
            dp[i-1][1] + a[i]    // only right neighbour alive
        );
    }

    return dp[n-1][0];
}

int main() {
    int n;
    cin >> n;
   
    vector<long long> a(n), b(n);
 
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
   
    cout << min_removal_cost(n, a, b) << endl;
    return 0;
}
