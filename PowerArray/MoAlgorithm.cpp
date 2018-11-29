#include<stdio.h>
#include<math.h>
#include<vector>
#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

int N,Q,S;
const int n_max = 200001;
int A[n_max];
int Freq[1000001];
long long result[n_max];
long long sum;
struct Query {
	int left;
	int right;
	int index;
};

//vector<int> Fre[100];

Query queries[n_max];

void init(){
	
	scanf("%d %d",&N,&Q);
	
	for(int i=1;i<=N;i++){
		scanf("%d",&A[i]);
		//AP[i] = 0;
	}
	for(int i=0;i<Q;i++){
		scanf("%d %d",&queries[i].left,&queries[i].right);
		queries[i].index = i;
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




void insElement(int value){
	sum += (2*Freq[value] + 1)*value;
	Freq[value] += 1;			
}

void delElement(int value){
	sum -= (2*Freq[value]-1)*value;
	Freq[value] -= 1;
}


long long getMode(Query preQ,Query curQ){
//	printDQuery(preQ,curQ);
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
	
//	cout << sub("12","10") << endl;
	
	
	init();
	quick_sort(0,Q-1);
//	printAll();

	for(int i=0;i<n_max;i++)
		Freq[i] = 0;
//	cout << "Query 0: " << queries[0].left << " - " << queries[0].right << endl;
	for(int i=queries[0].left;i<=queries[0].right;i++){
		insElement(A[i]);
	}
	
	result[queries[0].index] = sum ;
	
		
	for(int i=0;i<Q-1;i++)
		result[queries[i+1].index] = getMode(queries[i],queries[i+1]);
	
	for(int i=0;i<Q;i++)
		cout << result[i] << endl;
					
}
