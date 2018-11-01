#include<stdio.h>
#include<math.h>
#include<vector>
#include<iostream>

using namespace std;

int N,Q,S;
const int n_max = 100000;
int A[n_max],AP[n_max];
int max = 0;

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

int getMode(Query preQ,Query curQ){
	
	if(preQ.left<curQ.left){
		for(int i=preQ.left;i<curQ.left;i++){
			int value =  A[i];
			for(int j=0;j<Fre[AP[value]].size();j++){
				if(value == Fre[AP[value]][j]){
					Fre[AP[value]].erase(j);
					break;
				}
			}
			
			AP[value] -= 1;
			Fre[AP[value]].push_back(value);
			if(Fre[max].size() == 0){
				max -= 1;
			}
			
		}
		
		for(int i=preQ.right+1;i<curQ.left;i++){
			
			int value = A[i];
			for(int j=0;j<Fre[AP[value]].size();j++){
				
				if(value == Fre[AP[value]][j]){
					Fre[AP[value]].erase(j);
					break;
				}
				
			}
			
			AP[value] += 1;
			Fre[AP[value]].push_back(value);
			
			if(AP[value]>max) 
				max = AP[value];
			
		}
	}
	
	
	
}





int main(){
	
	init();
	quick_sort(0,Q-1);
	

						
}
