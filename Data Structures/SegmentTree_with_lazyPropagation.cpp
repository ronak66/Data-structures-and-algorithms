#include<iostream>
#include<math.h>
#include<limits.h>
using namespace std;

/*
LINEAR RANGE UPDATE FN
void updateRange(int node, int start, int end, int l, int r, int val) {
    // out of range
    if (start > end or start > r or end < l)
        return;

    // Current node is a leaf node
    if (start == end)
    {
        // Add the difference to current node
        tree[node] += val;
        return;
    }

    // If not a leaf node, recur for children.
    int mid = (start + end) / 2;
    updateRange(node*2, start, mid, l, r, val);
    updateRange(node*2 + 1, mid + 1, end, l, r, val);

    // Use the result of children calls to update this node
    tree[node] = tree[node*2] + tree[node*2+1];
}

*/
class segmentTree{
  int *tree;
  int size;
  int *lazy;
  int n;
public:
  segmentTree(int *A,int n){
    int h=(int)(ceil(log2(n)));
    this->size=2*(int)pow(2, h) - 1;
    this->n=n;
    tree=new int[this->size];
    lazy=new int[this->size];
    for(int i=0;i<this->size;i++)tree[i]=INT_MAX;
    for(int i=0;i<this->size;i++)lazy[i]=0;
    cout<<size<<":"<<n<<endl;
    constructTree(A,0,n-1,0);
    viewTree();
  }
  int constructTree(int *A,int l,int r,int i){
    if(l==r){
      tree[i]=A[l];
      return tree[i];
    }
    int mid=(l+r)/2;
    tree[i]=constructTree(A,l,mid,2*i+1)+constructTree(A,mid+1,r,2*i+2);
    return tree[i];
  }
  int RSQ(int ql,int qr){
    // return RSQ_r(ql,qr,0,n-1,0);
    return queryRange(0,0,n-1,ql,qr);
  }

  int RSQ_r(int ql,int qr,int l,int r,int i){
    if(ql<=l&&qr>=r)return tree[i];
    if(ql>r||qr<l)return 0;
    int mid=(l+r)/2;
    return RSQ_r(ql,qr,l,mid,2*i+1)+RSQ_r(ql,qr,mid+1,r,2*i+2);
  }

  void update(int i,int val){
    update_r(0,n-1,0,i,val);
    viewTree();
  }
  void updateRange(int val,int l,int r){
    updateRange_r(0,0,n-1,l,r,val);
  }
  void update_r(int l,int r,int treeIndex,int i,int val){
    if(l==r){
      tree[treeIndex]+=val;
      return;
    }
    int mid=(l+r)/2;
    if(i<=mid)update_r(l,mid,treeIndex*2+1,i,val);
    if(i>mid)update_r(mid+1,r,treeIndex*2+2,i,val);
    tree[treeIndex]=tree[treeIndex*2+1]+tree[treeIndex*2+2];
  }

  void updateRange_r(int i, int start, int end, int l, int r, int val){
    if(lazy[i] != 0)
    {
        // This i needs to be updated
        tree[i] += (end - start + 1) * lazy[i];    // Update it
        if(start != end)
        {
            lazy[i*2+1] += lazy[i];                  // Mark child as lazy
            lazy[i*2+2] += lazy[i];                // Mark child as lazy
        }
        lazy[i] = 0;                                  // Reset it
    }
    if(start > end or start > r or end < l)              // Current segment is not within range [l, r]
        return;
    if(start >= l and end <= r)
    {
        // Segment is fully within range
        tree[i] += (end - start + 1) * val;
        if(start != end)
        {
            // Not leaf i
            lazy[i*2+1] += val;
            lazy[i*2+2] += val;
        }
        return;
    }
    int mid = (start + end) / 2;
    updateRange_r(i*2+1, start, mid, l, r, val);        // Updating left child
    updateRange_r(i*2 + 2, mid + 1, end, l, r, val);   // Updating right child
    tree[i] = tree[i*2+1] + tree[i*2+2];        // Updating root with max value
}

int queryRange(int i, int start, int end, int l, int r){
    if(start > end || start > r || end < l)
        return 0;         // Out of range
    if(lazy[i] != 0)
    {
        // This i needs to be updated
        tree[i] += (end - start + 1) * lazy[i];            // Update it
        if(start != end)
        {
            lazy[i*2+1] += lazy[i];         // Mark child as lazy
            lazy[i*2+2] += lazy[i];    // Mark child as lazy
        }
        lazy[i] = 0;                 // Reset it
    }
    if(start >= l and end <= r)             // Current segment is totally within range [l, r]
        return tree[i];
    int mid = (start + end) / 2;
    int p1 = queryRange(i*2+1, start, mid, l, r);         // Query left child
    int p2 = queryRange(i*2 + 2, mid + 1, end, l, r); // Query right child
    return (p1 + p2);
}

  void viewTree(){
      for(int i=0;i<size;i++)
        cout<<tree[i]<<" ";
      cout<<endl;
  }
};

int main(){
  int arr[] = {6, 4, 12,1};
  int n = sizeof(arr)/sizeof(arr[0]);
  segmentTree ST(arr,n);
  cout<<ST.RSQ(0,3)<<endl;
  ST.updateRange(1,1,1);
  cout<<ST.RSQ(0,3)<<endl;
}
