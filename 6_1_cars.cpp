/*
Basically there is a matrix of size M x M where N cars are there. They are at a starting position xi, yi. 
You have to park them at some position in the matrix (p, q) in minimum number of drives. 
If it is not possible to park them in matrix (p,q) then return -1. 

The restrictions are:
You have to move all the cars simultaneously.
You can move 1 distance exactly in 1st drive, 2 distance in 2nd drive and so on.
The paths of cars can overlap.

M range till ±10^17
N range till 100
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

//---------------------------------------------------------------
// Returns total distance travelled after k drives
//---------------------------------------------------------------
i128 totalDistance(ll k)
{
    return (i128)k * (k + 1) / 2;
}

//---------------------------------------------------------------
// Binary search minimum k such that
// 1+2+...+k >= maxDistance
//---------------------------------------------------------------
ll minimumTurns(ll maxDistance)
{
    ll low = 0;
    ll high = 2000000000LL;

    while(low < high)
    {
        ll mid = (low + high) / 2;

        if(totalDistance(mid) >= maxDistance)
            high = mid;
        else
            low = mid + 1;
    }

    return low;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while(T--)
    {
        int N;
        cin >> N;

        long long p,q;
        cin >> p >> q;

        vector<pair<ll,ll>> cars(N);

        ll maxDist = 0;

        vector<int> parity;

        //-------------------------------------------------------
        // Calculate Manhattan distance of every car
        //-------------------------------------------------------

        for(int i=0;i<N;i++)
        {
            cin>>cars[i].first>>cars[i].second;

            ll dist=
            abs(cars[i].first-p)+
            abs(cars[i].second-q);

            maxDist=max(maxDist,dist);

            parity.push_back(dist&1);
        }

        //-------------------------------------------------------
        // All cars must have same parity
        //-------------------------------------------------------

        bool ok=true;

        for(int i=1;i<N;i++)
        {
            if(parity[i]!=parity[0])
            {
                ok=false;
                break;
            }
        }

        if(!ok)
        {
            cout<<-1<<"\n";
            continue;
        }

        //-------------------------------------------------------
        // Minimum turns required only by distance
        //-------------------------------------------------------

        ll turns=minimumTurns(maxDist);

        //-------------------------------------------------------
        // Fix parity if needed
        //-------------------------------------------------------

        while( (totalDistance(turns)-maxDist)%2!=0 )
            turns++;

        cout<<turns<<"\n";
    }
}

/*
#include <bits/stdc++.h>
using namespace std;


typedef long long ll;
typedef long double ld;


int main() {
    int t;
    cin >> t;
   
    while (t--) {
        ll n, m;
        cin >> n >> m;
       
        vector<pair<ll, ll>> points(n);
        pair<ll, ll> destination;
        cin >> destination.first >> destination.second;
       
        for (auto &point : points) {
            cin >> point.first >> point.second;
        }
       
        set<ll> parities;
        for (const auto &point : points) {
            parities.insert((abs(destination.first - point.first) + abs(destination.second - point.second)) % 2);
        }
       
        if (parities.size() > 1) {
            cout << "-1\n";
            continue;
        }
       
        ll parity = *parities.begin();
        ll max_distance = 0;
       
        for (const auto &point : points) {
            ll distance = abs(destination.first - point.first) + abs(destination.second - point.second);
            max_distance = max(max_distance, distance);
        }
       
        ll lo = 0, hi = (ll)(sqrtl(max_distance * 2) + 1), ans = hi;
       
        while (lo <= hi) {
            ll mid = lo + (hi - lo) / 2;
            ll sum = (mid * (mid + 1)) / 2;
           
            if (sum >= max_distance) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
       
        ll total_sum = (ans * (ans + 1)) / 2;
       
        if ((total_sum % 2) == parity) {
            cout << ans << "\n";
        } else {
            ll next_sum1 = ((ans + 1) * (ans + 2)) / 2;
            ll next_sum2 = ((ans + 2) * (ans + 3)) / 2;
           
            if ((next_sum1 % 2) == parity) {
                cout << ans + 1 << "\n";
            } else {
                cout << ans + 2 << "\n";
            }
        }
    }
    return 0;
}

*/
