const ll mod=1e9+7;
const int maxsz=3e5+7;
template<typename key,typename val>
class hash_map{public:
  struct node{key u;val v;int next;};
  vector<node> e;
  int head[maxsz],nume,numk,id[maxsz];
  int geths(PII &u){
	int x=(1ll*u.fr*mod+u.sc)%maxsz;
	if(x<0) return x+maxsz;
	return x;
  }
  val& operator[](key u){
	int hs=geths(u);
	for(int i=head[hs];i;i=e[i].next)if(e[i].u==u) return e[i].v;
	if(!head[hs])id[++numk]=hs;
	if(++nume>=e.size())e.resize(nume<<1);
	return e[nume]=(node){u,0,head[hs]},head[hs]=nume,e[nume].v;
  }
  void clear(){
	for(int i=0;i<=numk;i++) head[id[i]]=0;
	numk=nume=0;
  }
};
hash_map<PII,int> G;
//pair 的 hash_map

truct hash_map {  // 哈希表模板
  struct data {
    long long u;
    int v, nex;
  };                // 前向星结构
  data e[SZ << 1];  // SZ 是 const int 表示大小
  int h[SZ], cnt;
  int hash(long long u) { return u % SZ; }
  int& operator[](long long u) {
    int hu = hash(u);  // 获取头指针
    for (int i = h[hu]; i; i = e[i].nex)
      if (e[i].u == u) return e[i].v;
    return e[++cnt] = (data){u, -1, h[hu]}, h[hu] = cnt, e[cnt].v;
  }
  hash_map() {
    cnt = 0;
    memset(h, 0, sizeof(h));
  }
};