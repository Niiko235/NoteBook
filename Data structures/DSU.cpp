struct dsu {
  vector<int> pad, tam;
  int size;

  dsu(int n): pad(n), tam(n, 1), size(n) {
    iota(all(pad), 0);
  }

  void make() {
    pad.pb(sz(pad));                     // crea otro nodo en el dsu
    tam.pb(1);
    size++;
  }

  int find(int v) {
    if (v == pad[v]) return v;
    return pad[v] = find(pad[v]);        // devuelve el nodo padre de sa componente
  }

  void unite(int a, int b) {
    a = find(a);                         // PADRE de a
    b = find(b);						             // PADRE DE b
    if (a != b) {						             // Si no tiene el mismo padre
      if (tam[a] < tam[b]) swap(a, b);   // la componente mas grande absorve la mas pequeña
      pad[b] = a;                        // ahora el papá de B será A
      tam[a] += tam[b];                  // actualizamos el tamaño del padre
      size--;                            // numero de componentes desminuye!!
    }
  }

  int same(int a, int b) {               // comporobar que sea la misma componete
    return find(a) == find(b);
  }

  int count(int v) {                     // Tamaño de la componete
    return tam[find(v)];
  }
};