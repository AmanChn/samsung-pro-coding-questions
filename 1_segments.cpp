/*
You are given a path on an infinite 2d lattice. The path consists of line segments parallel to either the x or y axis. VVA
Example : 1, 1 to 1, 3 to 6, 3 to 6, 6 to bla bla
Also there is a set of points given . You have to find how many of the given points lie on the path. The input was as follow
N M as two variables
There were n numbers that denoted x coordinates of n points
There were n numbers again which denoted y coordinates of those n points

So total there is the info of n points in space
Now there are two more arrays of size m , one consisting of x coordinates and other y coordinates correspondingly
These points are the turning points in a path.
Examples.
The Input Arrays
1. General Variables:N = 3 (Number of points to check)
                     M = 3 (Number of turning points in the path)
2. Target Points Information (N) items:
pX = [2, 4, 1]
pY = [5, 3, 5]
This gives us three coordinates to check: (2, 5), (4, 3), and (1, 5).
3. Path Turning Points (M) items:
tX = [1, 1, 2] 
tY = [1, 5, 5]
This creates a continuous path through these coordinates: (1, 1)  (1, 5) (2, 5)
In the given path , we have to find how many of the given n points lie.
*/

#include <bits/stdc++.h>
using namespace std;

void mergeoverlappingarr(vector<pair<int,int>> &arr){
    if( arr.size() == 0 ) return;
    
    sort(arr.begin(),arr.end());
    
    vector<pair<int,int>> merged;
    merged.push_back(arr[0]);
    
    for( int i=1; i<arr.size(); i++ ){
        if( merged[i-1].second >= arr[i].first ){
            merged[i-1] = {merged[i-1].first, max(merged[i-1].second,arr[i].second)};
        }
        else{
            merged.push_back(arr[i]);
        }
    }
    
    arr = merged;
}

bool existinHorizontal(int x, int y, unordered_map<int,vector<pair<int,int>>> &horizontal){
    auto it = horizontal.find(y);
    
    if( it == horizontal.end() ) return false;
    
    vector<pair<int,int>> arr = it->second;
    
    int s=0, e=arr.size()-1;
    
    while( s<=e ){
        int mid = s + (e-s)/2;
        
        if( arr[mid].first <= x && arr[mid].second >= x ) return true;
        
        if( arr[mid].first > x  ){
            e = mid-1;
        }
        else{
            s = mid+1;
        }
    }
    
    return false;
}

bool existinVertical(int x, int y, unordered_map<int,vector<pair<int,int>>> &vertical){
    auto it = vertical.find(x);
    
    if( it == vertical.end() ) return false;
    
    vector<pair<int,int>> arr = it->second;
    
    int s=0, e=arr.size()-1;
    
    while( s<=e ){
        int mid = s + (e-s)/2;
        
        if( arr[mid].first <= y && arr[mid].second >= y ) return true;
        
        if( arr[mid].first > y  ){
            e = mid-1;
        }
        else{
            s = mid+1;
        }
    }
    
    return false;
}


int countpointsonpath(int n, int m, vector<int> &Px,vector<int> &Py,vector<int> &Tx,vector<int> &Ty){
    unordered_map<int,vector<pair<int,int>>> vertical;
    unordered_map<int,vector<pair<int,int>>> horizontal;
    
    // make map of vertical and horizontallines
    for( int i=0; i<m-1; i++ ){
        int x1 = Tx[i], x2 = Tx[i+1];
        int y1 = Ty[i], y2 = Ty[i+1];
        
        if( x1 == x2 ){ // vertical
            vertical[x1].push_back({ min(y1,y2) , max(y1,y2) });
        }
        else{ //horizontal
            horizontal[y1].push_back({ min(x1,x2), max(x1,x2) });
        }
    }
    
    // merge overlapping intervals
    for( auto& arr : vertical ){
        mergeoverlappingarr(arr.second);
    }
    
    for( auto& arr : horizontal ){
        mergeoverlappingarr(arr.second);
    }
    
    // find the point in countpointsonpath
    int ans=0;
    for( int i=0; i<n; i ++ ){
        int x = Px[i], y = Py[i];
        
        if( existinHorizontal(x,y,horizontal) || existinVertical(x,y,vertical) ){
            ans++;
        }
    }
    
    return ans;
}

int main()
{
    int n,m;
    n = 6, m = 6;
    // cin>>n>>m;
    
    vector<int> Px (n),Py(n),Tx(m),Ty(m);
    
    Px = {2,4,3,5,1,5};
    Py = {2,2,5,6,4,4};
    Tx = {1,5,5,2,2,6};
    Ty = {2,2,6,6,4,4};
    
    // for(int i=0; i<n; i++) cin>>Px[i];
    // for(int i=0; i<n; i++) cin>>Py[i];
    // for(int i=0; i<m; i++) cin>>Tx[i];
    // for(int i=0; i<m; i++) cin>>Ty[i];
    
    cout<<countpointsonpath(n,m,Px,Py,Tx,Ty);
    
    return 0;
}
