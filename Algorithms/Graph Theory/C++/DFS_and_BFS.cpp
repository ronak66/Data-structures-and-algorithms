#include<iostream>
#include<vector>
#include<utility>
#include<queue>
#define pu push_back
#define m make_pair
using namespace std;

// class Graph
// {
//   int n;
//   vector< pair <int,int> > adj;
//   Graph(int vertices)
//   {
//     n = vertices;
//     adj = new vector< pair <int,int> >[n];
//   }
//   addEdge(int u,int v,int key = 1)
//   {
//     adj[u].pu(m(v,key));
//   }
// }

void print(vector<int> *adj,int n)
{
  for(int i=0;i<n;i++)
  {
    cout<<i<<": ";
    for(int j=0;j<adj[i].size();j++)cout<<adj[i][j]<<" ";cout<<endl;
  }
}
void addEdge(int u,int v, int key,vector< pair <int,int> >adj[])
{
  adj[u].pu(m(v,key));
  adj[v].pu(m(u,key));
  // cout<<adj[u].back().first<<" "<<adj[u].back().second<<endl;
}

void bfs(vector < pair <int,int> > adj[],int n)
{
  queue<int> q;
  q.push(1);
  // int n = adj.size();
  int* visited = (int*)calloc(n,sizeof(int));
  while(!q.empty())
  {
    int u = q.front();
    cout<<u<<" ";
    visited[u] = 1;
    q.pop();
    for(int i=0;i<adj[u].size();i++)
    {
      if(visited[adj[u][i].first]==0){q.push(adj[u][i].first);visited[adj[u][i].first] = 1;}
    }
  }
}

void dfs(vector < pair <int,int> > adj[],int u,int visited[])
{
  if(visited[u]!=0) return;
  cout<<u<<" ";
  visited[u] = 1;
  for(int i=0;i<adj[u].size();i++)
  {
    dfs(adj,adj[u][i].first,visited);
  }
}
int main()
{
  int n;
  cin>>n;
  vector <pair <int,int> > adj[n];
  int q;
  cin>>q;
  for(int h=0;h<q;h++)
  {
    int a,b,key;
    cin>>a>>b>>key;
    addEdge(a,b,key,adj);
  }

  cout<<"BFS: ";
  bfs(adj,n);
  cout<<endl;
  int* visited1 = (int*)calloc(n,sizeof(int));
  cout<<"DFS: ";
  dfs(adj,1,visited1);
  cout<<endl;
}
