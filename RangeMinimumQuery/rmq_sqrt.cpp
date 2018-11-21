#include <stdio.h>
#include<bits/stdc++.h>

#define MAXN 100000000
#define MAXQ 100000000


using namespace std;

struct Query{
	int l;
	int r;
};

int n,q,A[MAXN],p,M[10000],sizeBlock;

Query Q[MAXQ];

void init(){
	
//	printf("Input: \n");
	scanf("%d",&n);
	
	// size of M
	p = ceil(sqrt(n));
	
	// size of a block
	sizeBlock = p-1;
	
	// init A
	for(int i=0;i<n;i++){
		scanf("%d",&A[i]);	
	}
	
	scanf("%d",&q);

	// init Q
	for(int i=0;i<q;i++)
		scanf("%d %d",&Q[i].l,&Q[i].r);
	
}

void preRMQ(){
	int minRange = A[0];
	int k=0;
	
	M[k] = 0;
	
	// compute array M
	
	for(int i=0;i<n;i++){
		if(A[i]<minRange){
			minRange = A[i];
			M[k] = i;
		};
			
		// if this is end of block, step to next block
		if(((i+1)%(sizeBlock))==0&&(i+1<n)){
			k++;
			minRange = A[i+1];
			M[k] = i+1;
		}
	}	
}


int getRMQ(Query query){
		
	int minRMQ = A[query.l];
	int indexMin = query.l;
	
	for(int i=query.l;i<=query.r;i++){
		
		// if this is a subset and a block
		if(i%sizeBlock==0&&(i+sizeBlock<=query.r)){
			if(A[M[i/sizeBlock]]<minRMQ){
				indexMin = M[i/sizeBlock];
				minRMQ = A[indexMin];
			};
			i += sizeBlock-1;
		} else {
			if(A[i]<minRMQ){
				minRMQ = A[i];
				indexMin = i;
			};
		}
		
	}
	
	return A[indexMin];
}

int main(){
	init();
	preRMQ();
//	printf("Output :\n\n");
	
	for(int i=0;i<q;i++){
//		printf("\tQuery %-3d [%3d - %-3d]: \t",i,Q[i].l,Q[i].r);
		printf("%d \n",getRMQ(Q[i]));
	}
}
