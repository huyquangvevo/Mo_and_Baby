#include<stdio.h>
#include<math.h>
#include<vector>
#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

int N,Q,S;
const int n_max = 200000;
int A[n_max],AP[n_max];
int Freq[n_max];
string result[n_max];
int maxMode=0;
string sum;
struct Query {
	int left;
	int right;
	int index;
};

vector<int> Fre[100];

Query queries[n_max];

void init(){
	
	scanf("%d %d",&N,&Q);
	
	for(int i=1;i<=N;i++){
		scanf("%d",&A[i]);
		AP[i] = 0;
	}
	for(int i=0;i<Q;i++){
		scanf("%d %d",&queries[i].left,&queries[i].right);
		queries[i].index = i;
	}	
	
	S = floor(sqrt(N));
	

}

string add(string a,string b){
	
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	
	string c;
	int max_len;
	
	if(a.length()<b.length()){
		max_len = b.length();
		for(int i=a.length();i<b.length();i++)
			a[i] = '0';
	} else {
		max_len = a.length();
		for(int i=b.length();i<a.length();i++)
			b[i] = '0';
	}
	
	int nho = 0,sum_;
	for(int i=0;i<max_len;i++){
		 sum_ = a[i]-'0'+b[i]-'0'+nho;
		 c += sum_%10+'0';
		 nho = sum_/10;
		 
	}
	if(nho==1)
		c+=nho+'0';
	reverse(c.begin(),c.end());
	return c;
}

string sub(string a,string b){
	
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	
	string c;
	int max_len;
	
	if(a.length()<b.length()){
		max_len = b.length();
		for(int i=a.length();i<b.length();i++)
			a[i] = '0';
	} else {
		max_len = a.length();
		for(int i=b.length();i<a.length();i++)
			b[i] = '0';
	}
	
	int nho = 0,sub_;
	for(int i=0;i<max_len;i++){
		if(a[i]>=b[i]){
		 	sub_ = a[i]-'0' - (b[i]-'0'+nho);
		 	nho = 0;
		}
		else {
			sub_ = a[i] + 10 -'0' - (b[i] - '0' + nho);
			nho = 1;
		}
		 c += sub_%10+'0';
		 
	}
	
	reverse(c.begin(),c.end());
	int k = 0;
	while(c[k]=='0')
		k++;
	c = c.substr(k,c.length()-k);
//	cout<< "C: "<<c<<endl;
	return c;
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

int modeArr;

string toString(int n){
	string c;
	while(n!=0){
		c += n%10+'0';
		n = n/10;
	}
	reverse(c.begin(),c.end());
	return c;
}

void insElement(int value){
//	sum += (2*Freq[value] + 1)*value;
//	Freq[value] += 1;
	sum = add(sum,toString((2*Freq[value] + 1)*value));
	Freq[value] += 1;			
}

void delElement(int value){
	sum = sub(sum,toString((2*Freq[value]-1)*value));
	Freq[value] -= 1;
}





string getMode(Query preQ,Query curQ){
	modeArr = A[curQ.left];
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
//	cout << sum << endl;		
	//	printf("\n\tSum: %d ",sum);
	
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
	
//	printf("\nSum 1: %d\n",sum);
		
	for(int i=0;i<Q-1;i++)
		result[queries[i+1].index] = getMode(queries[i],queries[i+1]);
	
	for(int i=0;i<Q;i++)
		cout << result[i] << endl;
					
}
