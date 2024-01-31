/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;

class Maxheap {
    vector<pair<int,int>> v;
    unordered_map<int,int> posMap;
public:
  void insert(int key)  {
      if(posMap.find(key) != posMap.end()) {v[posMap[key]].second++;}
      else {
          v.push_back({key,1});
          posMap[key] = v.size()-1;
      }
      upHeapify(posMap[key]);
  }
  pair<int,int> top() {
      return v[0];
  }
  pair<int,int> pop() {
      auto t = top();
      v[0] = v[v.size()-1];
      v.pop_back();
      posMap.erase(t.first);
      downHeapify(0);
      
      return t;
  }
  bool empty() {
      return v.empty();
  }
  string to_string() {
      stringstream ss;
      ss<<"vector(";
      for(auto i : v) ss<<"("<<i.first<<","<<i.second<<")"<<" ";
      ss<<")"<<endl;
      ss<<"PosMap(";
      for(auto m:posMap) ss<<"("<<m.first<<","<<m.second<<")"<<" ";
      ss<<")"<<endl;
      
      return ss.str();
  }
private:
  void upHeapify(int pos) {
      int p = parent(pos);
      while(pos != 0 && v[p].second < v[pos].second) {
          swap(posMap[v[pos].first],posMap[v[p].first]);
          swap(v[pos],v[p]);
          pos = p;
          p = parent(p);
      }
  }
  void downHeapify(int pos) {
      int mx = pos;
      int l = left(pos);
      if(l<v.size() && v[l].second>v[mx].second) mx=l;
      int r = right(pos);
      if(r<v.size() && v[r].second>v[mx].second) mx=r;
      if(pos != mx) {
          swap(posMap[v[pos].first],posMap[v[mx].first]);
          swap(v[pos],v[mx]);
          downHeapify(mx);
      }
  }
  int left(int key) {return 2*key+1;}
  int right(int key) {return 2*key+2;}
  int parent(int key) {return key/2;}
};

class HashStack {
    Maxheap heap;
public:
    void push(int item) {
        heap.insert(item);
    }
    int top() {
        auto t =  heap.top();
        return t.first;
    }
    int pop() {
        auto t = heap.pop();
        return t.first;
    }
    bool empty() {
        return heap.empty();
    }
    string to_string() {return heap.to_string();}
};

int main()
{
    HashStack obj;
    obj.push(1);
    obj.push(2);
    obj.push(2);
    obj.push(3);
    obj.push(4);
    obj.push(5);
    obj.push(4);
    obj.push(4);
    obj.push(1);
    obj.push(2);
    obj.push(2);
    obj.push(3);
    obj.push(4);
    obj.push(5);
    obj.push(4);
    obj.push(4);
    obj.push(1);
    obj.push(1);
    obj.push(2);
    obj.push(2);
    obj.push(3);
    obj.push(4);
    obj.push(5);
    obj.push(9);
    obj.push(7);
    obj.push(6);
    obj.push(8);
    obj.push(6);
    obj.push(9);
    obj.push(6);
    obj.push(8);
    cout<<"ToString: "<<obj.to_string()<<endl;
    cout<<"Array: ";
    while(!obj.empty()) cout<<obj.pop()<<" ";
    cout<<endl;
    
    return 0;
}
