

// complexity O(V*E) --> para problemsa mas ajustados usar el hopcroft karp o(v*sqrt(E))

struct mbm {
  int l, r;
  vector<int> partner;
  vector<bool> vs;
  vector<vector<int> > ady;

  mbm(int l, int r) : l(l), r(r), partner(r), vs(l), ady(l) {}

  bool matching(int v) {
    if (vs[v]) return false;
    vs[v] = true;
    for (int &u : ady[v]) {
      if (partner[u] == -1 || matching(partner[u])) {
        partner[u] = v;
        return true;
      }
    }
    return false;
  }

  vector<pair<int, int> > go_matching() {
    vector<pair<int, int> > ans;
    fill(all(partner), -1);
    forn (i, l) {
      fill(all(vs), false);
      matching(i);
    }
    forn (i, r) if (partner[i] != -1) ans.pb({partner[i], i});
    return ans;
  }
};

