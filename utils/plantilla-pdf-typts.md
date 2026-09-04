Esta plantilla fue hecha para genenrar los codigos en pdf y de esa forma porder crear un notebook fisico para competencias

# Que hacer con esta plantilla

Lo unico que tienes que hacer es copiar el codigo en la siguiente herramienta: 
- https://typst.app/play/

# Como la uso? 

Simplemente remplezar el codigo que esta entre comillas por el codigo suyo, tambien tienes que ajustar el header dependiendo el codigo, su complejidad y a la tematica que corresponda.

con esos cambios y pegando el codigo en el link que dejamos arriba, ya se te generara la nueva pagina para el notebook

# Colores para cada tematica 
```
#ff0000 -> String
#0096FF -> Grafos
#00C44F -> Estructuras
#FF6B00 -> Flujos
#CC00CC -> Matematicas
#00BBBB -> Geometria
```

```
#set page(
  paper: "a4",
  margin: (x: 0.8cm, y: 0.8cm),
)

#set text(font: "roboto", size: 9pt)
#set par(leading: 0.55em)

// ── HEADER ──────────────────────────────────────────────────────────────────
#block(
  width: 100%,
  fill: rgb("#CC00CC"),
  inset: (x: 10pt, y: 7pt),
  [
    #grid(
      columns: (1fr, 2fr, 1fr),
      align: (left + horizon, center + horizon, right + horizon),
      [
        #set text(size: 20pt, style: "italic", fill: white)
        _log(n)_
      ],
      [
        #set text(size: 25pt, weight: "bold", fill: white)
        criba  \
        #set text(size: 16pt, weight: "regular", fill: white)
        convencional
      ],
      [
        #set text(size: 25pt, weight: "bold", fill: white, )
        Matematicas
      ],
    )
  ]
)

#line(length: 100%, stroke: 0.5pt + luma(180))
#v(0.4em)

// ── OBJETIVO ────────────────────────────────────────────────────────────────
// #text(weight: "bold")[Objetivo:] Estructura de datos para insertar strings y consultar cuántas veces aparece un prefijo, útil para conteo de prefijos y autocompletado.

// #v(0.6em)

// ── CÓDIGO ──────────────────────────────────────────────────────────────────
#block(
  fill: luma(245),
  radius: 4pt,
  inset: (x: 10pt, y: 8pt),
  width: 100%,
  par(leading: 0.9em, text(size: 11pt, 
    raw(lang: "cpp",
"/*
Math/Sieve.cpp
*/

#define int int64_t
vector<int> segmented_criba(int l, int r) {
    l = max<int>(l, 2ll);
    vector<bool> vis(r - l + 1);
    for (int& pp : prime) {
        if ((int)pp * pp > r) break;
        int mn = (l + pp - 1) / pp;
        if (mn == 1ll) mn++;
        mn *= pp;
        for (int i = mn; i <= r; i += pp) {
            vis[i - l] = true;
        }
    }
    vector<int> ans;
    forn(i, sz(vis)) if (!vis[i]) ans.pb(l + i);
    return ans;
}"
  )))
)
```












# en latex? 

## Colores

```
255,0,0     -> Strings
0,150,255   -> Grafos
0,196,79    -> Estructuras
255,107,0   -> Flujos
204,0,204   -> Matematicas
0,187,187   -> Geometria
```

esos colores los colocamos donde dice headerred y cambiamos por el codigo que necesitemos

```
\documentclass[9pt]{article}

% ── PAQUETES ────────────────────────────────────────────────────────────────
\usepackage[a4paper, margin=0.8cm, top=0.7cm, bottom=0.7cm]{geometry}
\usepackage[T1]{fontenc}
\usepackage[utf8]{inputenc}
\usepackage[sfdefault]{roboto}
\usepackage{xcolor}
\usepackage{tcolorbox}
\usepackage{minted}         % requiere: pip install Pygments  +  -shell-escape
\usepackage{array}
\usepackage{tabularx}
\usepackage{booktabs}
\usepackage{parskip}

\tcbuselibrary{skins, breakable}

% ── COLORES ─────────────────────────────────────────────────────────────────
\definecolor{codebg}{RGB}{245,245,245}
\definecolor{headerred}{RGB}{255,0,0}
\definecolor{graystr}{RGB}{130,130,130}

% ── ESTILO MINTED ───────────────────────────────────────────────────────────
\setminted{
  style       = friendly,
  fontsize    = \footnotesize,
  breaklines  = true,
  linenos     = true,
  numbersep   = 6pt,
  bgcolor     = codebg,
}

\pagestyle{empty}

% ────────────────────────────────────────────────────────────────────────────
\begin{document}

% ── HEADER ──────────────────────────────────────────────────────────────────
\begin{tcolorbox}[
  colback  = headerred,
  colframe = headerred,
  arc      = 4pt,
  boxrule  = 0pt,
  left     = 8pt, right = 8pt,
  top      = 5pt, bottom = 5pt,
]
  \color{white}
  \begin{minipage}[c]{0.2\linewidth}
    \raggedright\textit{O(L)}
  \end{minipage}%
  \begin{minipage}[c]{0.6\linewidth}
    \centering
    {\LARGE\bfseries Trie}\\[-2pt]
    {\small Prefijos y búsqueda}
  \end{minipage}%
  \begin{minipage}[c]{0.2\linewidth}
    \raggedleft{\LARGE\bfseries Strings}
  \end{minipage}
\end{tcolorbox}
\vspace{0.3em}

% ── OBJETIVO ────────────────────────────────────────────────────────────────
\noindent\textbf{Objetivo:} Estructura de datos para insertar strings y
consultar cuántas veces aparece un prefijo, útil para conteo de prefijos
y autocompletado.

\vspace{0.5em}

% ── CÓDIGO ──────────────────────────────────────────────────────────────────
\begin{minted}{cpp}
// query(s) devuelve cuantos caracteres de s existen como prefijo y cuantas
//     veces ha sido insertado.

struct Node {
    int cont;           // Cuantas palabras pasan por este nodo
    Node* child[26];    // Hijos (una letra por cada caracter 'a'-'z')

    Node() {
        cont = 0;
        fill(child, child + 26, nullptr);
    }
};

struct Trie {
    Node* root;

    Trie() { root = new Node(); }

    void insert(const string &s) {
        Node* curr = root;
        for (char c : s) {
            int idx = c - 'a';
            if (curr->child[idx] == nullptr) {
                curr->child[idx] = new Node();
            }
            curr = curr->child[idx];
            curr->cont++;
        }
    }

    // Devuelve {l, c}, donde:
    // - l = longitud del prefijo encontrado (puede ser < s.size())
    // - c = cuantas veces se insert ese prefijo
    pair<int, int> query(const string &s) {
        Node* curr = root;
        for (int i = 0; i < (int)s.size(); ++i) {
            int idx = s[i] - 'a';
            if (curr->child[idx] == nullptr) {
                return {i, curr->cont};  // prefijo hasta i-1 existe
            }
            curr = curr->child[idx];
        }
        return {(int)s.size(), curr->cont};
    }
};

//Trie trie;
//trie.insert("app"); trie.insert("apple"); trie.insert("app");

//auto res1 = trie.query("applesauce"); {5, 1}  "apple" existe y fue inser 1 vez
//auto res2 = trie.query("april");      {2, 3} porque "ap" fue prefijo 3 veces
\end{minted}

\end{document}
```