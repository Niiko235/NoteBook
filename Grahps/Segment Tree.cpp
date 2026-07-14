struct SegmentTree { 
  int size;
  ll neutro = 0; // OPERADOR NEUTRO PARA LA SUMA
  vi tree;

  SegmentTree(vi &a){
    size = sz(a);
    tree.assign(size*4, 0); // CAMBIAR AQUI TAMBIEN EL NEUTRO
    build(1, 0, size-1, a);
  }

  void build (int v, int tl, int tr, vi &a){
    if(tl == tr){
      tree[v] = a[tl];
      return;
    }

    int mid = (tl+tr)/2;

    // build a mi hijo izquierdo
    build(v*2, tl, mid, a);

    // build a mi hijo derecho
    build(v*2 + 1, mid + 1, tr, a);

    tree[v] = tree[v*2] + tree[v*2+1];
  }

  void show(){
    for(auto &i : tree){
      cout << i << endl;
    }
  }

  ll query(int v, int l, int r, int tl, int tr){
    if(l <= tl && r >= tr){
      return tree[v];
    }
    if(r < tl || l > tr){
      return neutro;
    }

    int mid = (tl + tr)/2;

    ll hijoIzq = query(v*2, l, r, tl, mid);
    ll hijoDer = query(v*2+1, l, r, mid+1, tr);

    return hijoIzq + hijoDer;
    
  }

  ll query(int l, int r){
    return query(1, l, r, 0, size-1);
  }


  void updt(int v, int tl, int tr, int k, ll x){

    if(tl == tr){
      tree[v] = x;
      return;
    }
    int mid = (tl+tr)/2;

    if(k <= mid){ // actualizar hijo izquierdo
      updt(v*2, tl, mid, k, x);
    }else{        // actualizar hijo derecho
      updt(v*2+1, mid+1, tr, k, x);
    }
   
    tree[v] = tree[v*2] + tree[v*2+1];
    
  }

  void updt(int k, ll x){
    updt(1, 0, size-1, k, x);
  }


};