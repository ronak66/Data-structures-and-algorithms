
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<unordered_map>
using namespace std;


template <class W>
class Heap{

  const W INF;//=(numeric_limits<W>::infinity());
  struct Node{
      W priority;
      int key;
      Node(W p=0,int k=-1){
          priority=p;
          key=k;
      }
  };
  Node *root;
  int *mapping;
  int n;
  int maxSize;
  int type;
  int c(Node n1,Node n2){
      return type*n1.priority<type*n2.priority;
  }
  void swap(Node &n1,Node &n2){

    Node t=n1;
    n1=n2;
    n2=t;
    swap(mapping[n1.key],mapping[n2.key]);
  }
  void swap(int &n1,int &n2){

    int t=n1;
    n1=n2;
    n2=t;
  }

public:
  Heap(int type,int maxSize): INF(1){ //Build a new heap from an existing array
    this->root=new Node[maxSize];
    this->maxSize=maxSize;
    this->mapping=new int[maxSize];
    this->n=maxSize;
    this->type=type;
    for(int i=0;i<maxSize;i++){
        root[i].priority=INF*type;
        root[i].key=i;
        mapping[i]=i;
    }
  }

  W getDistance(int i){
      return root[mapping[i]].priority;
  }

  int size(){
      return n;
  }
  void bottomUpHeapify(int index){
    int t=index;
    int p=(t-1)/2;
    while (t&&c(root[t],root[p])){
      swap(root[t],root[p]);
      t=p;
      p=(t-1)/2;
    }
  }
  int viewTop(){
      return root[0].key;
  }
  bool isEmpty(){
    return !n;
  }
  void topDownHeapify(int index){
    int t=index;
    int r=t*2+2;
    int l=t*2+1;
    int j;
    while(r<n){
      if(c(root[t],root[r])&&c(root[t],root[l]))return;
      if(c(root[l],root[r]))j=l;
      else j=r;
      swap(root[j],root[t]);
      t=j;
      r=t*2+2;
      l=t*2+1;
    }
    if(l==n-1 && c(root[l],root[t]))swap(root[t],root[l]);
  }
  int deleteTopNode(){
    swap(root[0],root[--n]);
    topDownHeapify(0);
    return root[n].key;
  }
  void viewHeap(){
    for(int i=0;i<n;i++)
      cout<<root[i]<<" ";
    cout<<endl;
  }
  void updateKey(int key,int x){
    int index=mapping[key];
    Node n(x,-1);
    root[index].priority=x;
    bottomUpHeapify(index);
  }

};


template <class T, class W>
class Graph{
protected:
    class Edge{
    public:
        W weight;
        int destination;
    Edge(W weight,int destination){
        this->weight=weight;
        this->destination=destination;
        }
    };
    const W INF;
    vector<T> inverseVertices;
    unordered_map<T, int> vertices;
    vector< vector<Edge > > adjList;
    int size;
public:
    Graph() : INF(1){size=0;}
    void insertNode(T n){
        vertices[n]=size;
        inverseVertices.push_back(n);
        vector<Edge> list;
        adjList.push_back(list);
        size++;
    }
    void insertEdge(T n1, T n2,W weight=1){
        Edge e(weight,vertices[n2]);
        adjList[vertices[n1]].push_back(e);
    }
    void showNodes(){
        for(int i=0;i<size;i++){
            cout<<inverseVertices[i]<<endl;
        }
        cout<<endl;
        for(int i=0;i<size;i++){
            cout<<vertices[inverseVertices[i]]<<endl;
        }
    }
    Graph reverseGraph(){
        Graph <T,W>G;
        for(int i=0;i<size;i++){
            G.insertNode(inverseVertices[i]);
        }
        for(int i=0;i<size;i++){
            for(typename vector< Edge >::iterator j=adjList[i].begin();j!=adjList[i].end();j++){
                G.insertEdge(inverseVertices[j->destination],inverseVertices[i],j->weight);
            }
        }
        return G;
    }
    void BFS(T root){
        int startNode=vertices[root];
        bool *visited=new bool[size]();
        int *PI=new int[size]();
        queue<int> BFSqueue;
        BFSqueue.push(startNode);
        PI[startNode]=startNode;
        visited[startNode]=true;
        while(BFSqueue.empty()==false){
            int node=BFSqueue.front();
            BFSqueue.pop();

            cout<<inverseVertices[node]<<" "<<inverseVertices[PI[node]]<<endl;

            for(typename vector< Edge >::iterator i=adjList[node].begin();i!=adjList[node].end();i++){
                int adjNode=i->destination;
                if(visited[adjNode]==false){
                    visited[adjNode]=true;
                    PI[adjNode]=node;
                    BFSqueue.push(adjNode);
                }
            }
        }
        delete[] visited;
        delete[] PI;
    }
    void DKS(T root){
        int startNode=vertices[root];
        bool *visited=new bool[size]();
        int *PI=new int[size]();
        Heap<W> DKSqueue(1,size);
        DKSqueue.updateKey(startNode,0);
        PI[startNode]=startNode;
        visited[startNode]=true;
        while(DKSqueue.isEmpty()==false){
            int node=DKSqueue.viewTop();
            DKSqueue.deleteTopNode();
            visited[node]=true;
            W dist=DKSqueue.getDistance(node);

            for(typename vector< Edge >::iterator i=adjList[node].begin();i!=adjList[node].end();i++){
                int adjNode=i->destination;
                if(visited[adjNode]==false){
                    if(dist+i->weight<DKSqueue.getDistance(adjNode)){
                        DKSqueue.updateKey(adjNode,dist+i->weight);
                        PI[adjNode]=node;
                    }
                }
            }
        }
        for(int i=0;i<size;i++){
            cout<<inverseVertices[i]<<" distance:"<<DKSqueue.getDistance(i)<<"Pi:"<<inverseVertices[PI[i]]<<endl;
        }
        delete[] visited;
        delete[] PI;
    }
    void DFS(T root){
        int startNode=vertices[root];
        bool *visited=new bool[size]();
        int *PI=new int[size]();
        stack<int> DFSstack;
        DFSstack.push(startNode);
        PI[startNode]=startNode;
        while(DFSstack.empty()==false){
            int node=DFSstack.top();
            if(!visited[node]){
                cout<<inverseVertices[node]<<" "<<inverseVertices[PI[node]]<<endl;
                visited[node]=true;
            }

            DFSstack.pop();
            for(typename vector< Edge >::iterator i=adjList[node].begin();i!=adjList[node].end();i++){
                int adjNode=i->destination;
                if(visited[adjNode]==false){
                    PI[adjNode]=node;
                    DFSstack.push(adjNode);
                }
            }
        }
        delete[] visited;
        delete[] PI;
    }
    vector<int> DFStopologialSort(){
        bool visited[size];
        for(int i=0;i<size;i++)visited[i]=0;
        int PI[size];
        int start[size];
        int finish[size];
        int t=0;
        vector<int> sorted;
        for(int i=0;i<size;i++){
            if(visited[i]==false){
                DFS_r(i,visited,PI,start,finish,t,sorted);
            }
        }
        // for(int i=0;i<size;i++){
        //     cout<<i<<":\t"<<start[i]<<" "<<finish[i]<<endl;
        // }
        reverse(sorted.begin(),sorted.end());
        return sorted;
    }

    void stronglyConnectedComponents(){
        vector<int> topologicalSort=DFStopologialSort();
        Graph reverseG=reverseGraph();
        bool visited[size];
        for(int i=0;i<size;i++)visited[i]=0;
        int PI[size];
        int start[size];
        int finish[size];
        int t=0;
        vector<int> tree;
        vector<int> countries;
        // cout<<"following are connected components:\n";
        for(vector<int>::iterator i=topologicalSort.begin();i!=topologicalSort.end();i++){
            if(visited[*i]==false){
                reverseG.DFS_r(*i,visited,PI,start,finish,t,tree);

            // for(vector<int>::iterator j=tree.begin();j!=tree.end();j++){
            //     cout<<inverseVertices[*j]<<" ";
            // }
            // cout<<tree.size()<<endl;
            countries.push_back(tree.size());
            tree.clear();
        }

        }
        int cs=size;
        long long int ans=0;

        for(int i=0;i<countries.size();i++){
            cs-=countries[i];
            ans+=countries[i]*cs;
        }
        cout<<ans<<endl;

    }
    void DFS_r(int node,bool *visited,int *PI,int *start,int *finish,int &t,vector<int> &sorted){
        start[node]=t++;
        visited[node]=true;
        for(typename vector< Edge >::iterator i=adjList[node].begin();i!=adjList[node].end();i++){
            int adjNode=i->destination;
            if(visited[adjNode]==false){
                PI[adjNode]=node;
                DFS_r(adjNode,visited,PI,start,finish,t,sorted);
            }
        }
        finish[node]=t++;
        sorted.push_back(node);
    }


    template <class L, class M>
    friend ostream& operator<<(ostream& os, const Graph<L,M>&);
};

template<class T,class W>
class UDgraph: public Graph<T,W>{
public:
    void insertEdge(T n1, T n2,W weight=1){
        Graph<T,W>::insertEdge(n1,n2,weight);
        Graph<T,W>::insertEdge(n2,n1,weight);
    }

    void spanTree(T root,int type=1){
        int startNode=this->vertices[root];
        bool *visited=new bool[this->size]();
        int *PI=new int[this->size]();
        Heap<W> DKSqueue(type,this->size);
        DKSqueue.updateKey(startNode,0);
        PI[startNode]=startNode;
        visited[startNode]=true;
        while(DKSqueue.isEmpty()==false){
            int node=DKSqueue.viewTop();
            DKSqueue.deleteTopNode();
            visited[node]=true;
            W dist=DKSqueue.getDistance(node);

            for(typename vector<typename Graph<T,W>::Edge >::iterator i=this->adjList[node].begin();i!=this->adjList[node].end();i++){
                int adjNode=i->destination;
                if(visited[adjNode]==false){
                    if(type*(i->weight)<type*DKSqueue.getDistance(adjNode)){
                        DKSqueue.updateKey(adjNode,i->weight);
                        PI[adjNode]=node;
                    }
                }
            }
        }
        for(int i=0;i<this->size;i++){
            cout<<this->inverseVertices[i]<<" Edge:"<<DKSqueue.getDistance(i)<<"  Pi:"<<this->inverseVertices[PI[i]]<<endl;
        }
        delete[] visited;
        delete[] PI;

    }
    int getComponent(int i,int *parentComp){
        vector<int> list;
        while(parentComp[i]!=i){
            list.push_back(i);
            i=parentComp[i];
        }
        for(typename vector<int>::iterator j = list.begin();j!=list.end();j++){
            parentComp[*j]=i;
        }
        return i;

    }
    struct kruskalEdge{
        int n1, n2;
        W weight;

        static bool lessThan(kruskalEdge e1, kruskalEdge e2){
            return e1.weight < e2.weight;
        }

        static bool greaterThan(kruskalEdge e1, kruskalEdge e2){
            return e1.weight > e2.weight;
        }

        kruskalEdge(int a, int b, int w){
            n1 = a;
            n2 = b;
            weight = w;
        }
    };
    void kruskal(T root,bool min=1){





        vector<kruskalEdge> edgeList;
        int temp = 0;
    	for(typename vector<vector<typename Graph<T, W>::Edge> >::iterator i = this->adjList.begin(); i != this->adjList.end(); ++i, ++temp){
    		for(typename vector<typename Graph<T, W>::Edge>::iterator j = i->begin(); j != i->end(); ++j){
    			if(j->destination >= temp){
    				kruskalEdge newEdge(temp, j->destination, j->weight);
    				edgeList.push_back(newEdge);
    			}
    		}
    	}

        sort(edgeList.begin(), edgeList.end(), ((min) ? (kruskalEdge::lessThan) : (kruskalEdge::greaterThan)));

        int *compSize = new int[this->size];	//Size of each component
	    int *parentComp = new int[this->size];
        vector<kruskalEdge> spanTree;

        fill(compSize, compSize + this->size, 1);
    	for(int i = 0; i < this->size; ++i){
    		parentComp[i] = i;
    	}

    	for(typename vector<kruskalEdge>::iterator i = edgeList.begin(); i != edgeList.end(); ++i){
            int component1=getComponent(i->n1,parentComp);
            int component2=getComponent(i->n2,parentComp);
    		if(component1 != component2 ){
                spanTree.push_back(*i);
                if(compSize[component1]<compSize[component2]){
                    int t=component1;
                    component1=component2;
                    component2=t;
                }
                compSize[component1]+=compSize[component2];
                parentComp[component2]=component1;
    		}
    	}

		for(typename vector<kruskalEdge>::iterator j = spanTree.begin(); j != spanTree.end(); ++j){
			cout<<"Node 1: "<<this->inverseVertices[j->n1]<<"\tNode 2: "<<this->inverseVertices[j->n2]<<"\tEdge Weight: "<<j->weight<<endl;
		}


    	delete[] compSize;
    	delete[] parentComp;
        }
};

template <class T, class W>
ostream& operator<<(ostream& os,const Graph<T,W>& g){
    for(int i=0;i<g.adjList.size();i++){
        os<<g.inverseVertices[i]<<"->";
        for(int j=0;j<g.adjList[i].size();j++){
            os<<g.adjList[i][j].weight<<","<<g.inverseVertices[g.adjList[i][j].destination]<<"\t";
        }
        os<<endl;
    }
    return os;
}

int main(){
    // Graph<char,int> G;
	// G.insertNode('A');
	// G.insertNode('B');
	// G.insertNode('C');
	// G.insertNode('D');
	// G.insertNode('E');
	// G.insertNode('F');
    // G.insertEdge('A', 'B',4);
	// G.insertEdge('B', 'C');
    // G.insertEdge('D', 'B',3);
	// G.insertEdge('E', 'D',7);
	// G.insertEdge('E', 'C',8);
	// G.insertEdge('C', 'F');
	// G.insertEdge('E', 'A',3);

    // G.BFS('A');cout<<endl;
    // G.DFS('A');cout<<endl;
    // vector<int> sorted=G.DFStopologialSort();cout<<endl;
    // for(vector<int>::iterator i=sorted.begin();i!=sorted.end();i++)
    //     cout<<*i<<" ";
    UDgraph<int,int> G;
    int n1,n2,n,p;
    cin>>n>>p;
    for(int i=0;i<n;i++)G.insertNode(i);
    for(int j=0;j<p;j++){
        cin>>n1>>n2;
        G.insertEdge(n1,n2);
    }

    // cout<<G;
    G.stronglyConnectedComponents();
}
