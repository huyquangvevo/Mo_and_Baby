#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>
#include <bits/stdc++.h>

using namespace std;

const int n_max = 200001;
int T,n,m,q,u,v,S;
int root[n_max];


//vector<int> adj[n_max];
// Cau truc du lieu cho 1 cau truy van
struct Query {
	int left,right,id,ans,block;
	Query(int l_,int r_,int id_,int ans_,int block_){
		left = l_; // chi so bat dau
		right = r_; // chi so ket thuc
		id = id_; // chi so cau truy van
		ans = ans_; // ket qua truy van
		block = block_; // block cua truy van
	}
};

// cau truc du lieu canh
struct Edge {
	int u,v;
	Edge(int u_,int v_){
		u = u_;
		v = v_;
	}
};

//vector<Query> queries;
vector<Edge> edge;	

// So sanh 2 truy van
bool compQuery(Query A,Query B){
	// Neu A,B khac block so sanh theo left
	if( A.block != B.block){
		return A.block<B.block;
	}
	// nguoc lai so sanh theo right
	return A.right < B.right;
	
}

// So sanh thu tu truy van de tra ve ket qua dung thu tu
bool compIndex(Query A,Query B){
	return ((A.id < B.id)?true:false); 
}

// Khoi phuc lai trang thai ban dau
void reset_root(){
	for(int i=1;i<=n;i++)
		root[i] = i;
}

// khoi tao cac root cua tung nut den khi tim duoc root nho nhat
int find_(int node){
	if(root[node] == node)
		 return node;
	else 
		return root[node] = find_(root[node]);
}


// Tim root cua 1 nut
int brute_find(int node){
	if(root[node] == node) 
		return node;
	else
		brute_find(root[node]);
}

// Ket hop 2 set, lay root co chi so nho hon lam root chung cho ca 2 set
void union_(int u,int v){
	if(rand()%2){
		root[u] = v;
	} else {
		root[v] = u;
	}
}


void printRoot(){
	cout << "\nRoot:" << endl;
	for(int i=1;i<=n;i++)
		cout << i << " : " << root[i] << endl;
}

int brute_connect(int l,int r){
	int connects = 0;
	for(int i=l;i<=r;i++){
		int ru = find_(edge[i].u);
		int rv = find_(edge[i].v);

		if(ru!=rv){
			union_(ru,rv);
			connects ++;
		}
	}
	return connects;
};

int brute_connectVer2(int l,int r){
		// Luu lai cac cap canh da insert de thuc hien restore
		vector<pair<int,int> > used;
		// Bien chi so thanh phan da ket noi lai
		int con = 0;
		
		for(int i=l;i<=r;i++){
			int ru = brute_find(edge[i].u); // root dinh u
			int rv = brute_find(edge[i].v); // root dinh v
			
			if(ru!=rv){
			//	used.push_back(make_pair(ru,edge[i].u)); // Them canh da insert
			//	used.push_back(make_pair(rv,edge[i].v)); // Them canh da insert
				used.push_back(make_pair(ru,rv));
			//	root[ru] = rv;
			//	cout << "\nConnect : " << ru << " - " << rv << endl;
				root[ru] = rv;
			//	union_(edge[i].u,edge[i].v); // hop 2 set con
				con ++; // tang so thanh phan da ket noi
			}	
		}
		
	//	printRoot();
		
		for(int i=0;i<used.size();i++){
			int u = used[i].first; // lay dinh u
			int v = used[i].second; // lay dinh v
			
			root[v] = v;
			root[u] = u; //khoi phuc lai root dinh u
			//root[v] = v; //khoi phuc lai root dinh v
 		}
 		
 		return con;
		
}





// Tim tat ca cac cau cua do thi ban dau

//const int 

int main(){
	cin >> T ;
	
	for(int t=0;t<T;t++){

//		queries.clear();
		edge.clear();
		
		cin >> n >> m >> q;
		reset_root();
	//	S = floor(sqrt(n));
		S=(int)round(sqrt(m) +1.0);
		edge.push_back(Edge(0,0));
		int u,v;
		vector<Query> queries;

		for(int i=1;i<=m;i++){
			cin >> u >> v;
		//	edge[i] = Edge(u,v);
			edge.push_back(Edge(u,v));
		}
		
		
		for(int i=0;i<q;i++){
			cin >> u >> v;
		//	queries[i] = Query(u,v,i,0,(u-1)/S);
			queries.push_back(Query(u,v,i,0,(u-1)/S));
		}
		
		sort(queries.begin(),queries.end(),compQuery);

	//	reset_root();
		
		int last_edge = -1;
		int block = -1;
		int pre_right = 0;
		int components = n;
		for(int inq=0;inq<q;inq++){
			if((queries[inq].left-1)/S == (queries[inq].right-1)/S){
				reset_root();
				queries[inq].ans = n - brute_connectVer2(queries[inq].left,queries[inq].right);
			} else {
				if(queries[inq].block!=block){
					reset_root(); // reset lai root
					block = queries[inq].block; // block nhan gia tri moi
					last_edge = (block+1)*S+1; // dua left ve cuoi block cua cau truy van
					pre_right = queries[inq].right;
					components = n;
									//	cout << "Block: " << block << endl;

					queries[inq].ans = components - brute_connect(last_edge,queries[inq].right); // insert cac canh tu last_edge den right
					components = queries[inq].ans;
				//	printRoot();
					queries[inq].ans -= brute_connectVer2(queries[inq].left,last_edge-1); // insert cac canh tu 
				
				//	printRoot();
				} else {
					queries[inq].ans = components - brute_connect(pre_right+1,queries[inq].right); // insert tu r1+1 den r2 co cap nhat root
					pre_right = queries[inq].right;
					components = queries[inq].ans;
					queries[inq].ans -= brute_connectVer2(queries[inq].left,last_edge-1); // insert tu l2 den cuoi block cua truy van truoc do sau do thuc hien restore
				}
			}
				
		}
		// Sap xep lai cac truy van theo thu tu ban dau
		sort(queries.begin(),queries.end(),compIndex);
		// In ket qua
		for(int i=0;i<q;i++)
			cout << queries[i].ans << endl;
	
	}	
	
}
