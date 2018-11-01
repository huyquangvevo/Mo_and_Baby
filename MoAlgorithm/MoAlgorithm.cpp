#include<stdio.h>
#include<math.h>
#include<vector>
#include<iostream>
#include"hash_structure.h"

using namespace std;

int N,Q,S;
const int n_max = 100000;
int A[n_max],AP[n_max];
int Freq[n_max];
int maxMode=0;
HashMo* sHash;

struct Query {
	int left;
	int right;
};

vector<int> Fre[100];

Query queries[n_max];

void init(){
	
	scanf("%d %d",&N,&Q);
	
	for(int i=0;i<N;i++){
		scanf("%d",&A[i]);
		AP[i] = 0;
	}
	for(int i=0;i<Q;i++){
		scanf("%d %d",&queries[i].left,&queries[i].right);
	}	
	
	S = floor(sqrt(N));
	

}

bool cmpQuery(Query A,Query B){
	
	if(A.left/S != B.left/S){
		return A.left/S < B.left/S;
	}
	
	return A.right < B.right;

}

void swap(int a,int b){
	Query t = queries[a];
	queries[a] = queries[b];
	queries[b] = t;
}

int Partition(int L,int R){
	
	int i,j;
	Query p = queries[L];
	i=L;
	j=R+1;
	while(i<j){
		i++;
		while((i<R)&&(cmpQuery(queries[i],p)))
			i++;
		j--;
		while((j>L)&&(!cmpQuery(queries[j],p)))
			j--;
		swap(i,j);
	}
	swap(i,j);
	swap(j,L);
	return j;	
}

void quick_sort(int left,int right){
	
	int pivot;
	if(left<right){
		pivot = Partition(left,right);
		if(cmpQuery(queries[left],queries[pivot]))
			quick_sort(left,pivot-1);
		if(right>pivot)
			quick_sort(pivot+1,right);
	}
	
}

void printTest(){
	
	for(int i=0;i<Q;i++)
		printf("\n%d %d\n",queries[i].left,queries[i].right);
	int count[N];	
	for(int i = 0;i<N;i++){
		count[N] = 0;
	}
	
	for(int i=0;i<Q;i++){
		for(int j=queries[i].left;i<queries[i].right;i++)
			count[j]++;
	}
	
	printf("%d",S);
	
	
}

void printQuery(Query q){
	for(int i=0;i<N;i++)
		if(i>=q.left && i<=q.right)
			printf(" %d",A[i]);
		else 
			printf("  ",A[i]);
}

void printAll(){
	printf("\nDay so:\n");
	for(int i=0;i<N;i++){
		printf("%3d",A[i]);
	}
	printf("\n");
	for(int i=0;i<N;i++)
		printf("%3d",i);
}

void printDQuery(Query a,Query b){
	printf("\nQuery 1 (%2d - %2d): ",a.left,a.right);
	printQuery(a);
	printf("\nQuery 2 (%2d - %2d): ",b.left,b.right);
	printQuery(b);
}

void insElement(int value){
	sHash[Freq[value]].remove(value);
	Freq[value] += 1;
//	printf("\nFreq: %d",Freq[value]);

	sHash[Freq[value]].add(value);
	if(Freq[value]>maxMode)
		maxMode = Freq[value];					
}

void delElement(int value){
	sHash[Freq[value]].remove(value);
			//	printf("\nShash:\n");
			//	sHash[Freq[value]].printHash();
	Freq[value] -= 1;
	sHash[Freq[value]].add(value);
			//	sHash[Freq[value]].printHash();

	if(sHash[maxMode].isEmpty())
		maxMode--;
			
}


int getMode(Query preQ,Query curQ){
	maxMode = 0;
	printDQuery(preQ,curQ);
	//printf("\nQuery 1: %d - %d \nQuery 2: %d - %d\n",preQ.left,preQ.right,curQ.left,curQ.right);
	if(preQ.left<=curQ.left){
		for(int i=preQ.left;i<curQ.left;i++){
			delElement(A[i]);
		}
		
		
			sHash[1].printHash();
		
		for(int i=preQ.right+1;i<curQ.right;i++){
			insElement(A[i]);
		}
			sHash[1].printHash();
	
	}
		printf("\nMax: %d\n",maxMode);
	
}





int main(){
	
	init();
	quick_sort(0,Q-1);
	sHash = new HashMo[n_max];
	printAll();
	for(int i=0;i<n_max;i++)
		Freq[i] = 0;
//	for(int i=0;i<N;i++)
//		Freq[A[i]] += 1;
	
	for(int i=queries[0].left;i<=queries[0].right;i++){
		Freq[A[i]] += 1;
		sHash[Freq[A[i]]].add(A[i]);
		
	}
	
	for(int i=0;i<Q-1;i++)
		getMode(queries[i],queries[i+1]);
						
}
