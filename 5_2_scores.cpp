/*
Q2. 
2 arrays given
a = [1, 2, 3, 4, 5]
b = [6, 7, 8, 9, 10]
Value of an array is the total score of elements, 
and score of element is 1 if it is less than or equal to D and 2 if it is greater than D, 
Find D such that A_score - B_Score is maximum
 
constraints -
0 <= D <= 1e9
1 <= a[i] <= 1e8
1 <= b[i] <= 1e8
1 <= a.size(), b.size() <= 1e5

*/

#include <bits/stdc++.h>
using namespace std;
int maxDiffD(const vector<int> &a, const vector<int> &b)
{
    vector<int> sorted_a = a, sorted_b = b;
    sort(sorted_a.begin(), sorted_a.end());
    sort(sorted_b.begin(), sorted_b.end());

    set<int> s;
    for (int x : sorted_a) s.insert(x);
    for (int x : sorted_b) s.insert(x);

    vector<int> candidate_d; //to store all unique elemets from both array which will be search space for d
    candidate_d.push_back(*s.begin() - 1); //adding 1 less than min value at start
    for (int x : s) candidate_d.push_back(x);
    candidate_d.push_back(*s.rbegin() + 1); // adding 1 more than max value at end

    int mx = INT_MIN, bestD = 0;
    for (int d : candidate_d){
     
        // find the itr to first value that is bigger than d then do itr subtraction sa.begin() to get 
        // the number of elements in the vector  that are less than or equal to d
        int ca = upper_bound(sorted_a.begin(), sorted_a.end(), d) - sorted_a.begin();
        int cb = upper_bound(sorted_b.begin(), sorted_b.end(), d) - sorted_b.begin();

        //array Score = (#elements ≤ D) × 1 + (#elements > D) × 2
        //let count = number of elements ≤ D
        //score = count + (n-count)×2 = 2n-count
        int score_a = ca + (sorted_a.size() - ca) * 2;
        int score_b = cb + (sorted_b.size() - cb) * 2;

        int diff = score_a - score_b;
        if (diff > mx){
            mx = diff;
            bestD = d;
        }
    }
 
    return bestD;
}

int main()
{
    int t;cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        vector<int> a(n), b(m);
     
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < m; i++) cin >> b[i];
     
        cout << "Optimal D: " << maxDiffD(a, b) << endl;
    }
 
    return 0;
}

/*
#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n; 
    
    vector<int> a(n), b(n), all;
    
    for(int i = 0; i<n; i++) cin>>a[i], all.push_back(a[i]);
    for(int i = 0; i<n; i++) cin>>b[i], all.push_back(b[i]);
    
    int m = all.size();
    
    int ans = 0;
    
    for(int i = 0; i<m; i++){
        int x, y;
        int val1 = upper_bound(a.begin(), a.end(), all[i]) - a.begin();
        int val2 = upper_bound(b.begin(), b.end(), all[i]) - b.begin();
        
        if(val1 == n) x = 0;
        else x = n + 1 - val1;
        
        if(val2 == n) y = 0;
        else y = n + 1 - val2;
        
        // cout<<all[i]<<" : "<<x<<" "<<y<<endl;
        
        ans = max(ans, x - y);
    }
    cout<<ans<<endl;
    return 0;
}
*/
