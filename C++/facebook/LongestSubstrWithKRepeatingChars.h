#include <bits/stdc++.h>
using namespace std;

string longest(string str, int k) {
    unordered_map<char, int> map;
    int i=0,j=0;
    int mxLen = 0;
    pair<int,int> mxPair;
    int cnt = 0;
    
    while(j<str.length()) {
        map[str[j]]++;
        if(map[str[j]] == 2) cnt++;
        if(cnt > k) {
            if(j-i>mxLen) {
                cout<<i<<" "<<j-1<<endl;
                mxLen = j-i;
                mxPair = {i,j-1};
            }
            while(i<=j && cnt > k) {
                if(map[str[i]] == 2) cnt--;
                map[str[i]]--;
                i++;
            }
        }
        j++;
    }
    if(j-i>mxLen) {
        cout<<i<<" "<<j-1<<endl;
        mxLen = j-i;
        mxPair = {i,j-1};
    }
    
    return str.substr(mxPair.first,mxPair.second-mxPair.first+1);
}

int main()
{
    string str = "cbdbdcbdbcaa";
    string res = longest(str, 2);
    cout<<res<<endl;
    
    return 0;
}
