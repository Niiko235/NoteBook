struct LCA{
    vi first, deep, arbolito, euler, vs;
    int n, m;

    LCA(vector<vi> &ady, int root = 0){
      n = sz(ady);
      first.resize(n);
      deep.resize(n);
      euler.reserve(n*2);
      vs.assign(n, 0);
      dfs(ady, root, 0);
      m = sz(euler);
      arbolito.resize(m*4);
      build(1, 0, m-1);
    }

    void dfs(vector<vi> &ady, int i, int h){
      vs[i] = 1;
      deep[i] = h;
      first[i] = sz(euler);
      euler.pb(i);
      for(int &j : ady[i]){
        if(!vs[j]){
          dfs(ady, j, h+1);
          euler.pb(i);
        }
      }
    }

    void build(int node, int l, int r){
      if(l == r){
        arbolito[node] = euler[l]; 
        return;
      }
      int mid = (l+r)/2;
      build(node*2, l, mid);
      build(node*2+1, mid+1, r);

      int hijoIzq = arbolito[node*2];
      int hijoDer = arbolito[node*2+1];

      arbolito[node] = (deep[hijoIzq] < deep[hijoDer] ? hijoIzq : hijoDer);
    }

    int query(int node, int l, int r, int tl, int tr){
      if(l >= tl && r <= tr){
        return arbolito[node];
      }
      if(r < tl || l > tr){
        return -1;
      }

      int mid = (l+r)/2;

      int hijoIzq = query(node*2, l, mid, tl, tr);
      int hijoDer = query(node*2+1, mid+1, r, tl, tr);

      if(hijoIzq == -1) return hijoDer;
      if(hijoDer == -1) return hijoIzq;

      return (deep[hijoIzq] < deep[hijoDer] ? hijoIzq : hijoDer); 
    }

    int lca(int u, int v){
      int l = first[u], r = first[v];
      if(r < l) swap(l,r);
      return query(1, 0, m-1, l, r);
    }
};