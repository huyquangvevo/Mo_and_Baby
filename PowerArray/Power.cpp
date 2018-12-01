#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>

using namespace std;
const int n_max = 200000;


struct Query{
	int left,right; // Range cau truy van
	int block; 	// Block cau truy van
	int id; 	// id _ thu tu cau truy van
	long long ans;	// ans _ ket qua
	Query(int l_,int r_,int b_,int i_,long long a_){
		left = l_; right = r_; block = b_; id = i_;ans = a_;
	}
};

int A[n_max],n,q,u,v,S;
vector<Query> Q;
vector<int> Freq(1000000,0);
long long sum = 0;

// So sanh 2 truy van
bool compareQuery(Query A,Query B){
	// Neu khac block sap xep theo left
	if(A.block != B.block)
		return A.block < B.block;
	// Neu cung  block sap xep theo right	
	return A.right < B.right;
}

// Sap xep lai truy van theo thu tu ban dau
bool by_index(Query A,Query B){
	return ((A.id<B.id)?true:false);
}

// Them phan tu
void insElement(int value){
	// Tinh tong moi, cong thuc thu duoc thong qua danh gia
	sum += ((long long)(2*Freq[value] + 1))*((long long)value);
	Freq[value] += 1; // Tang so lan xuat hien value len 1
}

// Xoa phan tu
void delElement(int value){
	// Tinh tong moi, cong thuc thu duoc thong qua danh gia
	sum -= ((long long)(2*Freq[value]-1))*((long long)value);
	Freq[value] -= 1; // Giam so lan xuat hien value di 1
}

// Tinh ket qua truy van
long long getAns(Query preQ,Query curQ){
	if(preQ.left<=curQ.left) 
		for(int i=preQ.left;i<curQ.left;i++)
			delElement(A[i]);
	else
		for(int i=curQ.left;i<preQ.left;i++)
			insElement(A[i]);
	
	if(preQ.right<=curQ.right)	
		for(int i=preQ.right+1;i<=curQ.right;i++)
			insElement(A[i]);
	else
		for(int i=curQ.right+1;i<=preQ.right;i++)
			delElement(A[i]);
	
	return sum;
			
}


int main(){
	cin >> n >> q;
	// Nhap mang
	for(int i=0;i<n;i++){
		cin >> A[i];
	}
	// Tinh kich thuoc block
	S = (int)round(sqrt(n)+1.0);
	// Nhap truy van
	for(int i=0;i<q;i++){
		cin >> u >> v;
		u --; // Giam left,right
		v --; // Vi mang bat dau tu 1
		Q.push_back(Query(u,v,u/S,i,0));
	}
	// Sap xep truy van theo Mo algorithm
	sort(Q.begin(),Q.end(),compareQuery);

	// Tinh ket qua truy van dau tien phuc vu cho truy van tiep theo  
	for(int i=Q[0].left;i<=Q[0].right;i++)
		insElement(A[i]);
	
	Q[0].ans = sum;
	// Tinh ket qua cac truy van
	for(int i=0;i<q-1;i++)
		Q[i+1].ans = getAns(Q[i],Q[i+1]);
	
	// Sap xep lai truy van theo thu tu ban dau	
	sort(Q.begin(),Q.end(),by_index);
	// In ket qua
	for(int i=0;i<Q.size();i++)
		cout << Q[i].ans << endl;
		
	
}


