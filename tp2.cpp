#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// Numero de vertices, arestas e querries.
int n, m, q;

// Dado um vertice u, gr[u] eh um vetor com os pares {v, w}, sendo v um vertice para o qual u vai por
// uma aresta de w de peso.
vector<pair<int, int>> gr[100];

// Minimo aceito por aresta e destino.
int minim, destination;
// Marcador de vertices ja visitados pra DFS.
vector<bool> vis;
// Retorna true se eh possivel alcancar o vertice destination saindo de i e sem visitar vertices jah
// visitados, false caso contrario.
bool dfs(int i) {
    if (i == destination)
        return true; 
    if (vis[i])
        return false;
    vis[i] = true;
    for (pair<int, int> pa : gr[i])
        // eh preciso checar se o tamanho da aresta eh pelo menos o minimo antes de andar nela.
        if (pa.second >= minim && dfs(pa.first))
            return true;
    return false;
}

// Em nossa busca, estamos limitando inferiormente o tamanho das arestas usadas nos caminhos:
// Caso nao seja possivel chegar ao destino com arestas de tamanho pelo menos k, entao eh trivial
// notar que nao eh possivel chegar com todas arestas maiores que k.
// Caso seja possivel chegar ao destino com arestas de tamanho pelo menos k, entao claramente eh
// possivel chegar com arestas de tamanho pelo menos x tal que x < k.
// Portanto podemos usar busca binária para encontrar o maior valor de k tal que eh possivel sair do
// ponto inicial e chegar ao final usando apenas arestas de tamanho maior ou igual a k, que eh
// precisamente o que queremos (veja a documentação).
int bin_search(int from) {
    int l = 1, r = 100000;

    while (l != r) {
        int mid = (l + r + 1) / 2;
        // resetando o vetor de visitados:
        vis.clear();
        vis.resize(n, false);
        // setando chute de menor aresta:
        minim = mid;
        // caso seja possivel com todas arestas >= isso, tiramos as menores do intervalo de teste.
        if (dfs(from))
            l = mid;
        // caso contrario, tiramos esse tamanho e maiores do intervalo de teste.
        else
            r = mid - 1;
    }
    return l;
}

int main() {
    // lendo tamanhos:
    cin >> n >> m >> q;
    // lendo grafo:
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        gr[u - 1].emplace_back(v - 1, w);
    }
    // lendo e respondendo querries:
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        destination = b-1;
        cout << bin_search(a - 1) << endl;
    }
}