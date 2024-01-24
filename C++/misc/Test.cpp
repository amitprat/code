#include <iostream>
#include <queue>
using namespace std;
int main()
{
    cout<<"Hello world!"<<endl;
    
    priority_queue<int> pq;
    pq.push(1);

    while(!pq.empty()) {
        cout<<pq.top()<<" ";
        pq.pop();
    }

    return 0;
}