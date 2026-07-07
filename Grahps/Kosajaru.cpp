const int MAXN = 1E5 + 5; 

vi ady[MAXN];  //grafo 
vi rg[MAXN];   //grafo inverso


struct ksj {
  vi id;                    // a que componente pertenece cada nodo
  vector <vi> scc, dag;     // grupo de componentes / grafo condensado
  vector <bool> vs;         // visitados
  int  tagscc;              // numero de componentes 
  vi curComp;               // vec temporal para crear las componentes
  stack <int> st;     


  ksj(int n): id(n), vs(n, 0){
    tagscc = 0;
    run(n);
  }

  void dfs1(int u, stack<int> &st){
    vs[u] = 1;
    for(int v: ady[u]){
      if(!vs[v]) dfs1(v, st); //toca mandar la pila por parametros sino, overflow
    }

    st.push(u);
  }

  void dfs2(int u){
    vs[u] = 1;
    id[u] = tagscc;
    curComp.pb(u);
    for(int v: rg[u]){
      if(!vs[v])dfs2(v);
    }
  }

  void run(int n){

    for(int i = 0; i < n; i++){
      if(!vs[i])dfs1(i, st);
    }


    fill(vs.begin(), vs.end(), 0);

    //aqui se crean las componentes en un grafo dirigido
    while(!st.empty()){
      int u = st.top(); st.pop();
      if(vs[u]) continue;
      curComp.clear();
      dfs2(u);
      scc.pb(curComp);
      tagscc++;
    }

    // aqui construimos el grafo condensado
    dag.resize(tagscc);   
    forn(i,n){
      for(auto j : ady[i]){
        if(id[i] != id[j]){
          dag[id[i]].pb(id[j]);
        }
      }
    }
  }
};












