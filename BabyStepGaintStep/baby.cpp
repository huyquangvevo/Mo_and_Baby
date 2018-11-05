#include<stdio.h>
#include<map>
#include<bits/stdc++.h>

using namespace std;

int n,a,b;
map<int,int> hBaby;


unsigned long long powInt(unsigned int p,unsigned int q){
	if(q==0)
		return 1;
	else 
		return p*powInt(p,q-1);	
}

int pow_m(unsigned int x,unsigned int y,int m){
	return (int) (powInt(x,y)%m);
}

int babyStep_gaintStep(){
	unsigned long long m = ceil(sqrt(n));
	unsigned int e = 1;
	for(unsigned int j=0;j<m;++j){
		hBaby.insert(pair<unsigned int,unsigned int>(e,j));
		printf(" %d - %d\n",e,j);
		e = (e*a)%n;
	};
	printf("\n");
	int factor = pow_m(a,n-m-1,n);
	e = b;
	printf("\nfactor = %d",factor);	
	for(int i=0;i<m;++i){
		
		printf("\n %d ",e);

		if(hBaby.find(e)!=hBaby.end()){
			printf("\n index = %d",hBaby.at(e));
			return i*m+hBaby.at(e);
		}
		e = (e*factor)%n;
	}
	
	return -1;
	
}

int main(){
	printf("Input: ");
	scanf("%d %d %d",&n,&a,&b);
	int result = babyStep_gaintStep();
	if(result!=-1)
		printf("\nOutput: %d",result);
	else 
		printf("\n*** Not result ***");
	

	
}
