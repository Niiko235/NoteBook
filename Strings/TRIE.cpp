#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

#define vi vector<int>
#define pb push_back
#define ff first
#define ss second
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
#define forn(i,n) for(int i = 0; i < n; i++)

// CODIGO SE TIENE QUE MANEJAR BAJO LA PLANTILLA DE CodeBlockers();

// Asegurarse que las letras que se le pasen al Trie sean extrictamente en minusculas
// o cambiar los argumentos dependiendo los caracteres que use (se puede optar por usar un mapa)

struct Node {
    int cont;
    Node* child[26];  //un arrego de punteros a objetos Node (26) palabras
  };

  struct Trie {
    Node* root;  //la raiz de nuetro arbol

    Trie() {
      root = new Node(); //inicializar la raiz
    }

    void insert(const string &s) {
      Node* curr = root;                              // puntero auxiliar
      for (int i = 0; i < sz(s); ++i) {
        if (curr->child[s[i] - 'a'] == NULL) {        //si esa letra no esta encendida
          curr->child[s[i] - 'a'] = new Node();       // crea otro Node* en esa poscion
        }
        curr->child[s[i] - 'a']->cont++;              // aumenta el # palabras en esa poscicion
        curr = curr->child[s[i] - 'a'];               // nos paramos en ese nuevo nodo
      }
    }

    pair<int, int> query(const string &s) {           //devuelve la posicion i (sz) y cuantas
      Node* curr = root;                              // palabras iguales hay hasta ese nodo
      for (int i = 0; i < sz(s); ++i) {
        if (curr->child[s[i] - 'a'] == NULL) {
          return make_pair(i, curr->cont);            //si no esta la palabra i != sz(string)
        }
        curr = curr->child[s[i] - 'a'];
      }
      return make_pair(sz(s), curr->cont);
    }
  };


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    return 0;
}
