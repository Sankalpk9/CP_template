//Light9
// Sieve
bool p[m];
void sieve()
{
    memset(p,true,sizeof(p));
    for(int i=2;i*i<=m;i++)
    {
        if(p[i])
        {
            for(int j=i*i;j<=m;j+=i)
                p[j]=false;
        }
    }
}

//Disjoint set union
struct dsu{
vector<int> par,ran,siz;
int c;
dsu(int n): par(n+1),ran(n+1,0),siz(n+1,1),c(n){
    for(int i=1;i<=n;i++)
        par[i]=i;
}
int fp(int i) {return (par[i]==i ? i:par[i]=fp(par[i]));}
bool same(int i,int j){ return fp(i)==fp(j);}
int getsize(int i){ return siz[fp(i)];}
int coun() {return c;}
int unio(int i,int j)
{
    if((i=fp(i))==(j=fp(j))) return -1;
    else c--;
    if(ran[i]>ran[j]) swap(i,j);
    par[i]=j;
    siz[j]+=siz[i];
    if(ran[i]==ran[j]) ran[j]++;
    return j;
}
};
// Trie (to find how many strings of a given prefix)
struct Node{
 Node* links[26];
 int cp=0;
 int cw=0;
};
class Trie{
private: Node* root;
public:
    Trie(){
    root=new Node();
    }
    void insert(string s){
        Node* t=root;
    for(int i=0;i<s.length();i++){
        if(!t->links[s[i]-'a']) t->links[s[i]-'a']=new Node();
        t=t->links[s[i]-'a'];
        t->cp++;
        }
        t->cw++;
    }
    int countwords(string s){
       Node* t=root;
       for(int i=0;i<s.length();i++){
        if(!t->links[s[i]-'a']) return 0;
        t=t->links[s[i]-'a'];
       }
       return t->cw;
   }
    int countprefix(string s){
    Node* t=root;
    for(int i=0;i<s.length();i++){
        if(!t->links[s[i]-'a']) return 0;
        t=t->links[s[i]-'a'];
    }
    return t->cp;
   }
   void erase(string s){
    Node* t=root;
    for(int i=0;i<s.length();i++){
        if(t->links[s[i]-'a']) t=t->links[s[i]-'a'],t->cp--;
        else {return;}
    }
    t->cw--;
   }

};
// Trie to find max xor value between x and a[i];
struct Node{
   Node* links[2];
};
class Trie{
  private: Node* root;
  public:
  Trie(){root=new Node();}
  void insert(int n){
      Node* t=root;
      for(int i=31;i>=0;i--){
          int bit=(n>>i)&1;
          if(!t->links[bit]) t->links[bit]=new Node();
          t=t->links[bit];
      }
    }
  int findmax(int n){
      Node* t=root;
      int ans=0;
      for(int i=31;i>=0;i--){
          int bit=(n>>i)&1;
          if(t->links[!bit]) ans+=(1<<i),t=t->links[!bit];
         else  t=t->links[bit];
      }
      return ans;
  }

};
/Segment tree(to find sum of a given range in logn time && update values in a given range in logn time )
  int a[100005];
int seg[4*100005];
int lazy[4*100005];
void build(int id,int l,int r){ // to build the segment tree
if(l==r){
    seg[id]=a[l];
    return;
}
int mid=(l+r)/2;
build(2*id+1,l,mid);
build(2*id+2,mid+1,r);
seg[id]=seg[2*id+1]+seg[2*id+2]; // for max of range just change this statement

}
int query(int id,int low,int high,int l,int r){ // query to find max in a range
  if(r<low || l>high) return INT_MIN;
  if(low>=l && high<=r) return seg[id];
  int mid=(low+high)/2;
  int left=query(2*id+1,low,mid,l,r);
  int right=query(2*id+2,mid+1,high,l,r);
  return max(left,right);

}
void pointupdate(int id,int l,int r,int i,int val){ // to update only one value in the array
if(l==r) a[l]+=val,seg[id]+=val;
else {
    int mid=(l+r)/2;
    if(i>=l && i<=mid) pointupdate(2*id+1,l,mid,i,val);
    else pointupdate(2*id+2,mid+1,r,i,val);
    seg[id]=seg[2*id+1]+seg[2*id+2];
}

}
void rangeupdate(int id,int low,int high,int l,int r,int val){ // to update the whole range
 if(lazy[id]){
    seg[id]+=(lazy[id]*(high-low+1));
    if(low!=high) lazy[2*id+1]+=lazy[id],lazy[2*id+2]+=lazy[id]; }
    lazy[id]=0;
    if(r<low || l>high || low>high) return;
    if(low>=l && high<=r){
        seg[id]+=(high-low+1)*val;
        if(low!=high) lazy[2*id+1]+=val,lazy[2*id+2]+=val;
        return;
    }
    int mid=(low+high)/2;
    rangeupdate(2*id+1,low,mid,l,r,val);
    rangeupdate(2*id+2,mid+1,high,l,r,val);
    seg[id]=seg[2*id+1]+seg[2*id+2];
}
int querysumlazy(int id,int low,int high,int l,int r){ // to find the sum of a given range
   if(lazy[id]){
    seg[id]+=(lazy[id]*(high-low+1));
    if(low!=high) lazy[2*id+1]+=lazy[id],lazy[2*id+2]+=lazy[id]; }
    lazy[id]=0;
  if(r<low || l>high || low>high) return 0;
  if(low>=l && high<=r) return seg[id];
  int mid=(low+high)/2;
  int x=querysumlazy(2*id+1,low,mid,l,r);
  int y=querysumlazy(2*id+2,mid+1,high,l,r);
  return x+y;

}
// Binary exponentiaion
int be(int x,int y)
{
    int ans=1;
    x=x%mod;
    if(x==0) return 0;
    while(y>0)
    {
        if(y&1) ans=(ans*x)%mod;
        y=y>>1;
        x=(x*x)%mod;
    }
    return ans;
}
// Modulo multiplicative inverse
int mi(int x,int y)
{
    return be(x,y);
}
 // max heap
 priority_queue<int> ma;
 //min heap
 priority_queue <int, vector<int>, greater<int>> mi;
//to find kth element in set (unique all elements)
     set<int> st;
        auto it=st.begin();
       advance(it,i);
       cout<<*it<<endl;
 // decimal to binary conversion
 void decToBinary(int n)
{

    int binaryNum[1000];
    int i = 0;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int j = i - 1; j >= 0; j--){
        cout<<binaryNum[j];
}

// Ordered set
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update> ;

// permutations of an array
int t; cin>>t;
 while(t--){
 int n; cin>>n;
int a[n];
for(int i=0;i<n;i++)a[i]=i+1;
sort(a,a+n);
do{


}while(next_permutation(a,a+n));
 }

// grid dfs bfs
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
int dx[]={1,1,1,0,0,-1,-1,-1};
int dy[]={0,1,-1,1,-1,0,1,-1};
int vis[1001][1001];
char a[1001][1001];
bool isvalid(int i,int j){
if(i<0 || j<0 || i>=n || j>=m) return false ;
if(vis[i][j] || a[i][j]=='#') return false ;
return true;
}

//factors
        for(int i=1;i*i<=n;i++){
            if(n%i==0){
                if(n/i==i) v.push_back(n/i);
                else v.push_back(i),v.push_back(n/i);
            }
        }

// longest increasing subsequence in nlogn
      int lis(int n, vector<int> a)
    {

       vector<int> v;
       v.push_back(a[0]);
       for(int i=1;i<n;i++){
           if(v.back()<a[i])
           v.push_back(a[i]);
           else
           {
               int j=lower_bound(v.begin(),v.end(),a[i])-v.begin();
               v[j]=a[i];
           }
       }
       return v.size();
    }
// palindrome check
      bool checkp(string s){
           int n=s.length();
           int i=0,j=n-1;
           while(i<=j) {if(s[i]!=s[j]) return false; i++;j--;}
          return true;

       }

// bitmasking to find all the subsets
       for(int i=0;i<(1<<n);i++){
        vector<int> v;
        for(int j=0;j<n;j++){
            if(i&(1<<j)) v.push_back(a[j]);
        }

// Bipartite graph
    vector<vector<int>> g(200001);
    for(int i=1;i<=n;i++){ // useful function
            if(c[i]==-1){
                if(!bip(i,c)){f=0; break;}
            }
        }
   bool bip(int n,vector<int>& c){
 if(c[n]==-1) c[n]=1;
 for(auto it: g[n]){
    if(it==n) continue;
    if(c[it]==-1){
        c[it]=1-c[n];
        if(!bip(it,c)) return false;}
        else if(c[it]==c[n]) return false;

 }
 return true;
}
// kruskal's algo (to find minimum spanning tree->make a graph such that k nodes contain k-1 edges with minimum cost )
int kruskals(int a, vector<vector<int> > &b) { // return sum of edges
    vector<vector<int>> g;
    for(int i=0;i<b.size();i++){
        int u=b[i][0];
        int v=b[i][1];
        int w=b[i][2];
       g.push_back({w,u,v});
    }
    sort(g.begin(),g.end());
    dsu d(a);
    int ans=0;
    for(int i=0;i<g.size();i++){
        int u=g[i][1];
        int v=g[i][2];
        int w=g[i][0];
        if(!d.same(u,v)) ans+=w,d.unio(u,v);
    }
    return ans;
}
//Dijsktra algo (to find shortest distance from source to every vertex in weighted graph)
vector<lli> dijsktra(int nodes,vector<vector<pair<int,int>>>& g,int source){ // return distance vector
    vector<lli> dis(nodes+1,INT_MAX);
    dis[source]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
    q.push({0,source});
    while(!q.empty()){
        pair<int,int> p=q.top(); q.pop();
        int w=p.first;
        int n=p.second;
        for(auto it:g[n]){
            int c=it.first; int d=it.second;
            if(dis[c]>d+w) dis[c]=d+w,q.push({dis[c],c});
        }
    }
    return dis;

}

//Cycle in directed graph
bool check(  vector<vector<int>>& g,vector<int>& vis,vector<int>& dfs,int i){
    vis[i]=1;
    dfs[i]=1;
    for(auto it:g[i]){
        if(!vis[it] && check(g,vis,dfs,it)) return true;
        else if(dfs[it]) return true;
    }
    dfs[i]=0;
    return false ;
}

