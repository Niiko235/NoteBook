struct Lazy{

    int size;
    vi tree, lazy;
    int neutro = 0;

    Lazy(vi &a){
        size = sz(a);
        tree.assign(4 * sz(a), 0);
        lazy.assign(4*sz(a), 0);
        build(1, 0, sz(a)-1, a);
    }

    void build(int v, int tl, int tr, vi &a){
        if(tl == tr){
            tree[v] = a[tl];
            return;
        }

        int mid = (tr+tl)/2;

        build(v*2, tl, mid, a);
        build(v*2+1, mid+1, tr, a);

        tree[v] = tree[v*2] + tree[v*2+1];
    }

    void push(int v, int tl, int tr){
        
        int mid = (tr+tl)/2;

        // Actualizar hijo izq
        tree[v*2] += (mid - tl + 1) * lazy[v];
        lazy[v*2] += lazy[v];

        // Actualizar hijo Der
        tree[v*2+1] += (tr - mid) * lazy[v];
        lazy[v*2+1] +=  lazy[v];

        lazy[v] = neutro;
    }

    void updt(int v, int l, int r, int tl, int tr, int val){
        if(l <= tl && r >= tr){
            tree[v] += (tr - tl + 1) * val;
            lazy[v] += val;
            return;
        }
        if(tr < l || tl > r){
            return;
        }
        push(v,tl, tr);
        int mid = (tr + tl)/2;
        updt(v*2, l, r, tl, mid, val);
        updt(v*2+1, l, r, mid+1, tr, val);

        tree[v] = tree[v*2] + tree[v*2+1];
    }

    void updt(int l, int r, int val){
        updt(1, l, r, 0, size-1, val);
    }

    int query(int v, int l, int r, int tl, int tr){
         if(l <= tl && r >= tr){
            return tree[v];
        }
        if(tr < l || tl > r){
            return neutro;
        }
        push(v,tl, tr);
        int mid = (tr + tl)/2;
        return query(v*2, l, r, tl, mid) + query(v*2+1, l, r, mid+1, tr);
    }

    int query(int l, int r){
        return query(1, l, r, 0, size-1);
    }


};