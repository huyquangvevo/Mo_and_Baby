#include <bits/stdc++.h>
using namespace std;
#include<iostream>
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
    int l, r;       // left, right cau truy van
    int bl, br;     // bl - block tinh theo left
                    // br - block tinh theo right

    int idx, ans;   // idx - chi so theo thu tu cau truy van
                    // ans - ket qua cau truy van
};

// So sanh 2 cau truy van
bool blocks_comp(query a, query b){
    if(a.bl < b.bl) // so sanh theo left
        return true;
    if(a.bl == b.bl)
        return a.r < b.r; // so sanh theo right
    return false;
}

// Sap xep cau truy van theo thu tu ban dau
bool by_index(query a, query b){
    return a.idx < b.idx;
}

// Khoi tao lai trang thai root cua cac nut
void reset_root(int frt, int last){
    for(int i=frt; i<=last; i++)
        root[i] = i;
}

// Tim goc cua 1 nut co cap nhat root
int find_(int node){
    if( root[node] == node )  return node;
    return root[node] = find_(root[node]);
}

// Hop 2 set lai, lay bat ky 1 trong 2 root cua 2 set lam root chung set moi
void union_(int ru, int rv){
    if(rand() % 2)
        root[ru] = rv;
    else
        root[rv] = ru;
}

//        vector<edge> E(M);

// Tim root cua mot nut, khong cap nhat cac root khac
int brute_find(int node){
    // Neu tim thay thi tra ve nut
    if( root[node] == node )    return node;
    // Nguoc lai tim kiem de qui
    return brute_find(root[node]);
}

int brute_connect(int ft_edge, int lt_edge, vector<edge>& E){
    vector<pii> used_roots;

    int connected = 0;
    for(int i= ft_edge; i<= lt_edge; i++){
    	// Tim root cua 2 dinh
        int ru = brute_find( E[i].u );
        int rv = brute_find( E[i].v );

        // Neu khong cung root, hop 2 set lai
        if( ru != rv ){
        	// Luu tru trang thai truoc khi ket hop
            used_roots.pb( mp(ru, rv) );
			// Hop 2 set lai thanh set moi
            root[ru] = rv;
			// Tang so thanh phan duoc ket noi len 1
            connected ++;
        }
    }

    // Khoi phuc lai trang thai truoc khi ket hop 
    for(int i=0; i<used_roots.size(); i++){
        int ru = used_roots[i].ft;
        int rv = used_roots[i].sd;
		
        root[ru] = ru;
        root[rv] = rv;
    }

    // Tra ve so thanh phan duoc ket noi
    return connected;
}

int main(){
     srand(time(NULL));
     int T; scanf("%d", &T);

     while(T-- > 0){
        int N, M, q; 
		scanf("%d %d %d", &N, &M, &q);
        vector<edge> E(M);
        for(int i=0; i<M; i++){
            int u, v; scanf("%d %d", &u, &v);
			E[i].u = u, E[i].v = v;
        }

        int sq = (int)round(sqrt(M) +1.0);

        vector<query> Q(q);
        for(int i=0; i<q; i++){
            scanf("%d %d", &Q[i].l, &Q[i].r);
			// Giam left va right di 1
            // Vi chi so canh bat dau tu 1 
            Q[i].l --;
            Q[i].r --;

            // Tinh toan block theo left va right
            Q[i].bl = Q[i].l/ sq, 
            Q[i].br = Q[i].r/ sq;

            Q[i].idx = i;
        }
		
		// Sap xep block theo Mo algorithm
        sort(Q.begin(), Q.end(), blocks_comp);

        int ind = 0;            // chi so cau truy van

        // Vong lap tinh ket qua moi cau truy van
        for(int k=0; k<=sq; k++){
            reset_root(0, N);

            int last_edge = sq*(k +1);  // Dua  left ve cuoi block chua left
            int components = N;         // So thanh phan lien thong  ban dau bang N

            while(ind < q && Q[ind].bl == k){
                if(Q[ind].bl == Q[ind].br) {
                    // Neu left va right thuoc cung 1 block
                    // Thuc hien tinh toan bang viec them tu left den right
                    // Khong cap nhat trang thai root cac nut 
                    Q[ind].ans = N -brute_connect(Q[ind].l, Q[ind].r, E);
                }else{
                	// Thuc hien them vao so canh tu last_edge den right cua cau truy van
                    while(last_edge <= Q[ind].r){
                        int ru = find_(E[last_edge].u); // Tim root dinh u, cap nhat root cac nut lien quan
                        int rv = find_(E[last_edge].v); // Tim root dinh v, cap nhat root cac nut lien quan
                        // Neu root[u] khac root[v]
                        if( ru != rv ){
                        	// ket hop 2 set lai
                            union_(ru, rv);
							// giam so thanh phan lien thong di 1
                            components --;
                        }

                        last_edge ++;
                    }
					// Thuc hien them cac canh tu left den cuoi block chua cau truy van
					// Nhung khong cap nhat trang thai root cac nut de thuc hien cho cau truy van sau 
                    Q[ind].ans = components -brute_connect(Q[ind].l, sq*(k +1) -1, E);
                }

                ind ++;
            }
        }
		// Sap xep lai truy van theo thu tu ban dau
        sort(Q.begin(), Q.end(), by_index);

        for(int i=0; i<q; i++)
            printf("%d\n", Q[i].ans);
     }
}
