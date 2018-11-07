#include<stdio.h>

#define MAXIND 1000
#define MAXN 1000

void initialize(int node, int b,int e,int M[MAXIND],int A[MAXN],int N){
	
	if(b==e)
		M[node] = b;
	else {
		initialize(2*node,b,(b+e)/2,M,A,N);
		initialize(2*node+1,(b+e)/2+1,e,M,A,N);
		
		if(A[M[2*node]]<=A[M[2*node+1]])
			M[node] = M[2*node];
		else 
			M[node] = M[2*node+1];
	}
	
}

int query(int node,int b,int e,int M[MAXIND],int A[MAXN],int i,int j){

	int p1,p2;
	
	// not intersect
	if(i>e||j<b)
		return -1;
	
	// is subset
	if(b>=i && e<= j)
		return M[node];
		
	// min of left children tree,min of right children tree
	p1 = query(2*node,b,(b+e)/2,M,A,i,j);
	p2 = query(2*node+1,(b+e)/2+1,e,M,A,i,j);
	
	if(p1 == -1)
		return M[node] = p2;
	if(p2 == -1)
		return M[node] = p1;
	
	if(A[p1]<=A[p2])
		return M[node] = p1;
	
	return M[node] = p2;	
	
}
