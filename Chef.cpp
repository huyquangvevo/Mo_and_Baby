#include <bits/stdc++.h>
using namespace std;

#define ft first
#define sd second 
#define mp make_pair
#define pb push_back
#define pii pair<int, int>

const int MAXN = 200200;
int root[MAXN];

struct edge{
    int u, v;
};
struct query{
    int l, r;       // Rango de la pregunta [l, r]
    int bl, br;     // bl - bloque al que pertenece l
                    // br - bloque al que pertenece r

    int idx, ans;   // idx - indice de la pregunta en el orden de la entrada
                    // ans - respuesta de la pregunta
};

// Ordenar por bloque de inicio
// desempate por limite derecho de la query
bool blocks_comp(query a, query b){
    if(a.bl < b.bl)
        return true;
    if(a.bl == b.bl)
        return a.r < b.r;
    return false;
}

// Ordenar por el indice en la entrada
bool by_index(query a, query b){
    return a.idx < b.idx;
}

// Reset al vector de representantes
void reset_root(int frt, int last){
    for(int i=frt; i<=last; i++)
        root[i] = i;
}

// Funciones para Union-Find
int find_(int node){
    if( root[node] == node )  return node;
    return root[node] = find_(root[node]);
}

void union_(int ru, int rv){
    if(rand() % 2)
        root[ru] = rv;
    else
        root[rv] = ru;
}


// Funciones para union-find para deshacer uniones
int brute_find(int node){
    // No comprime caminos hacia el representante
    if( root[node] == node )    return node;
    return brute_find(root[node]);
}

int brute_connect(int ft_edge, int lt_edge, vector<edge>& E){
    vector<pii> used_roots;

    int connected = 0;
    for(int i= ft_edge; i<= lt_edge; i++){
        int ru = brute_find( E[i].u );
        int rv = brute_find( E[i].v );

        // Si estan en arboles distintos los conectamos
        // guardamos los nodos que se actualizaron
        if( ru != rv ){
            used_roots.pb( mp(ru, rv) );

            root[ru] = rv;

            connected ++;
        }
    }

    // Deshacemos las uniones 
    for(int i=0; i<used_roots.size(); i++){
        int ru = used_roots[i].ft;
        int rv = used_roots[i].sd;

        root[ru] = ru;
        root[rv] = rv;
    }

    // Devuelve cuantas componentes se conectaron
    return connected;
}

int main(){
     srand(time(NULL));
     int T; scanf("%d", &T);

     while(T-- > 0){
         int N, M, q; scanf("%d %d %d", &N, &M, &q);

        vector<edge> E(M);
        for(int i=0; i<M; i++){
            int u, v; scanf("%d %d", &u, &v);
            E[i].u = u, E[i].v = v;
        }

        int sq = (int)round(sqrt(M) +1.0);

        vector<query> Q(q);
        for(int i=0; i<q; i++){
            scanf("%d %d", &Q[i].l, &Q[i].r);
            Q[i].l --;
            Q[i].r --;

            // Calculamos en que bloque se encuentran l y r
            Q[i].bl = Q[i].l/ sq, 
            Q[i].br = Q[i].r/ sq;

            Q[i].idx = i;
        }

        sort(Q.begin(), Q.end(), blocks_comp);

        int ind = 0;            // Query que se esta atendiendo

        // Iteramos para las preguntas que empiezan en el bloque k
        for(int k=0; k<=sq; k++){
            reset_root(0, N);

            int last_edge = sq*(k +1);  // Ultima arista por ser conectada
            int components = N;         // Cuantas componentes hay

            while(ind < q && Q[ind].bl == k){
                if(Q[ind].bl == Q[ind].br){
                    // Si l y r estan en el mismo bloque, calculamos sin actualizar raices
                    Q[ind].ans = N -brute_connect(Q[ind].l, Q[ind].r, E);
                }else{
                    while(last_edge <= Q[ind].r){
                        int ru = find_(E[last_edge].u);
                        int rv = find_(E[last_edge].v);
                        
                        if( ru != rv ){
                            union_(ru, rv);

                            components --;
                        }

                        last_edge ++;
                    }

                    Q[ind].ans = components -brute_connect(Q[ind].l, sq*(k +1) -1, E);
                }

                ind ++;
            }
        }

        sort(Q.begin(), Q.end(), by_index);

        for(int i=0; i<q; i++)
            printf("%d\n", Q[i].ans);
     }
}
