#include<bits/stdc++.h>
#define pu push_back
#define m make_pair
#define INF 1000000001
using namespace std;

map <long long int,long long int> d;
map <long long int,long long int> ::iterator it;
long long int* parent;
vector< pair<long long int,long long int> >prt;
vector < pair <long long int,long long int> > *adj;

void addEdge(long long int u,long long int v,long long int key)
{
  adj[u].pu(m(v,key));
  adj[v].pu(m(u,key));
}

// void print(vector< pair <long long int,long long int> > heap)
// {
//   cout<<endl;
//   cout<<string((int)8*heap.size(),'-')<<endl;
//   for(long long int i=0;i<heap.size();i++)
//   {
//     cout<<"( "<<heap[i].first<<" "<<heap[i].second<<" ) ";
//   }
//   cout<<endl;
//   cout<<string((int)8*heap.size(),'-')<<endl;
//   cout<<endl;
// }
//
// void printm()
// {
//   cout<<"MAP"<<endl;
//   for(it = d.begin();it!=d.end();it++) cout<<(it->first)<<" "<<(it->second)<<endl;
// }
//
// void printprt()
// {
//   cout<<endl<<"----"<<endl;
//   cout<<"PRIORITY"<<endl;
//   for(long long int i=0;i<prt.size();i++) cout<<prt[i].first<<" "<<prt[i].second<<endl;
//   cout<<"----"<<endl<<endl;
// }
//
// void printcolour(long long int* l,long long int n)
// {
//   cout<<endl;
//   cout<<"Colour"<<endl;
//   for(int i=0;i<n;i++) cout<<l[i]<<" ";
//   cout<<endl<<endl;
// }
void bottomupheapify(vector< pair<long long int,long long int> > &l,long long int n,long long int index)
{
  d[l[index].first] = index;
  while(index>0 && l[(index-1)/2].second>l[index].second)
  {
    //Swapping for the map
    d[l[index].first] = (index-1)/2;
    d[l[(index-1)/2].first] = index;
    //Swapping the elements
    long long int k = l[index].second;
    long long int k1 = l[index].first;
    l[index].second = l[(index-1)/2].second;
    l[index].first = l[(index-1)/2].first;
    l[(index-1)/2].second = k;
    l[(index-1)/2].first = k1;
    index = (index-1)/2;
  }
}

void topdownheapify(vector< pair<long long int,long long int> >&l,long long int n,long long int index)
{
  while(2*index+1<n)
  {
    long long int left = 2*index+1,right = 2*index+2,c;
    if(right<n)
    {
      if(l[left].second<l[index].second && l[left].second<l[right].second) c = left;
      else if(l[right].second<l[index].second) c = right;
      else break;
    }
    else if(right>=n)
    {
      if(l[left].second<l[index].second) c = left;
      else break;
    }
    else break;
    long long int k = l[index].second;
    long long int k1 = l[index].first;
    l[index].second = l[c].second;
    l[index].first = l[c].first;
    l[c].second = k;
    l[c].first = k1;
    d[l[index].first] = index;
    index = c;
    d[l[index].first] = index;
  }
}

void insert(vector< pair<long long int,long long int> >&l,long long int n,pair <long long int,long long int> p)
{
  // cout<<"Entered: "<<p.first<<" n: "<<n<<endl;
  l.push_back(p);
  // print(l);
  bottomupheapify(l,n,n-1);
  // print(l);
  // cout<<"Exit: "<<p.first<<" "<<d[p.first]<<endl;
}

void deletemin(vector< pair<long long int,long long int> >&l, long long int n)
{
  long long int k = l[0].second;
  long long int k1 = l[0].first;
  l[0].second = l[n-1].second;
  l[0].first = l[n-1].first;
  l[n-1].second = k;
  l[n-1].first = k1;
  d[l[0].first] = 0;
  d[l[n-1].first] = n-1;
  d.erase(l[n-1].first);
  l.pop_back();
  topdownheapify(l,n-1,0);
}

void delete1(vector< pair<long long int,long long int> >&l,long long int n,long long int key)
{
  long long int index = d[key];
  l[index].second = l[0].second-1;
  bottomupheapify(l,n,index);
  deletemin(l,n);
}

// void decreasekey(vector <long long int> &l,long long int n, long long int key,long long int value) // Decreases key TO value
// {
//   int index = d[key];
//   l[index] = value;
//   bottomupheapify(l,n,index);
// }
//
// void increasekey(vector <long long int> &l,long long int n, long long int key,long long int value)
// {
//   int index = d[key];
//   l[index] = value;
//   topdownheapify(l,n,index);
// }

void dijkstra(long long int s,long long int n)
{
  vector< pair <long long int,long long int> >heap; //Initialising the heap
  // Priority
  long long int* colour = new long long int[n];
  for(long long int i=0;i<n;i++) {colour[i] = 0;parent[i] = i;}
  for(long long int i=0;i<n;i++) prt.pu(m(i,INF));
  prt[s].second = 0;
  parent[s] = s;
  // Dijkstra initialisation
  heap.pu(prt[s]);
  long long int counter = 1;
  colour[s] = 1;
  while(!heap.empty())
  {
    pair <long long int,long long int> p = heap[0];
    long long int u = p.first;
    long long int pr = p.second;
    // cout<<"Min: "<<u<<" "<<pr<<endl;
    deletemin(heap,counter);
    // print(heap);
    counter--;
    // printm();
    colour[u] = 2;
    // cout<<"u: "<<u<<" pr: "<<pr<<endl;
    for(long long int i=0;i<adj[u].size();i++)
    {
      // printprt();
      // printcolour(colour,n);
      // for(int i=0;i<n;i++)
      // {
      //   cout<<"i: "<<i<<" parent: "<<parent[i]<<endl;
      // }
      long long int v = adj[u][i].first;
      long long int w = adj[u][i].second;
      pair <long long int,long long int> p1;
      if(colour[v]==0)
      {
        counter++;
        colour[v] = 1;
        p1 = m(v,w+pr);
        prt[v] = p1;
        // cout<<"Inserting "<<p1.first<<endl;
        insert(heap,counter,p1);
        // cout<<"Succesful! "<<p1.first<<endl;
        // printm();
        parent[v] = u;
      }
      else if(colour[v]==1)
      {
        p1 = m(v,min(w+pr,prt[v].second));
        if(w+pr<prt[v].second)parent[v] = u;
        prt[v] = p1;
        long long int index = d[v];
        heap[index].second = p1.second;
        // cout<<"Heapify "<<p1.first<<endl;
        topdownheapify(heap,counter,index);
        // cout<<"Succesful Heapify! "<<p1.first<<endl;
        // printm();
      }
    }
    // cout<<endl;
    // print(heap);
  }
}
int main()
{
  long long int n;
  long long int s;//Source
  long long int q;
  cin>>n>>s>>q;
  adj = new vector < pair <long long int,long long int> >[n];
  for(long long int h=0;h<q;h++)
  {
    long long int a,b,key;
    cin>>a>>b>>key;
    addEdge(a,b,key);
  }
  for(long long int i=0;i<n;i++)
  {
    cout<<i<<" : ";
    for(long long int j=0;j<adj[i].size();j++) cout<<adj[i][j].first<<" ";
    cout<<endl;
  }
  cout<<endl;
  parent = new long long int[n];
  dijkstra(s,n);
  for(long long int i=0;i<prt.size();i++) cout<<prt[i].first<<" "<<prt[i].second<<endl;
  for(int i=0;i<n;i++)
  {
    cout<<"i: "<<i<<" parent: "<<parent[i]<<endl;
  }
}

/*
5 1 7
0 3 3
2 3 4
1 3 3
1 2 5
4 3 5
1 4 6
2 4 7

8 1 11
1 2 50
2 3 35
3 4 30
3 5 25
2 4 25
0 2 60
6 2 40
4 6 45
0 6 20
6 7 20
0 7 10

0 : 1 7
1 : 0 7 2
2 : 1 5 3 8
3 : 2 5 4
4 : 3 5
5 : 6 2 3 4
6 : 7 5 8
7 : 0 1 8 6
8 : 7 6 2

*/
