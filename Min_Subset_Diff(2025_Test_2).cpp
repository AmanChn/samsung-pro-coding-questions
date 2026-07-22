/*
There are a total of N cargoes. The weight of the ith cargo is given as L[i]. (0<=i<N).
There is a compartment A and B on the left and right side of the airplane, respectively.
The two compartments are large enough to carry all the cargoes. 
N cargoes should be loaded and distributed among compartment A and B.
When the cargoes are loaded in a way that makes the difference between (The toal weight of cargoes in compartment A) and  (The toal weight of cargoes in compartment B).
You are required to print the diff between  (The toal weight of cargoes in compartment A) and  (The toal weight of cargoes in compartment B). testcases: N=5, l[]=[3,3,7,3,1]. ans: 1 explaination: divide into 3,3,3 and 7,1

Simplified Qn:[
Given a list L[0..N-1], divide it into two groups A and B such that:
Every item is in either A or B (no item left behind)
You minimize: abs(sum(A) - sum(B))
]

*/
#include <iostream>
#include <bitset>
#include <vector>
#include <numeric>
using namespace std;

int main()
{
    int N = 5;
    vector<int> L = {3, 3, 7, 3, 1};

    int total = accumulate(L.begin(), L.end(), 0);
    
    // dp[s] = 1 if subset sum 's' is possible
    bitset<10001> dp; // Set according to maximum possible total sum
    dp[0] = 1; // Empty subset

    for (int x : L)
    {
        // Shift all existing sums by x and OR them
        dp |= (dp << x);
    }

    //If one subset has sum S then other subset has Total-S
    //abs((Total-S)-S) = abs(Total-2S)
    //So we simply want a subset whose sum is as close as possible to Total/2
    
    // Find subset whose sum is closest to total/2
    int best = 0;
    for (int i = total / 2; i >= 0; --i)
    {
        if (dp[i])
        {
            best = i;
            break;
        }
    }

    cout << "Minimum difference: " << abs(total - 2 * best) << endl;
    return 0;
}
