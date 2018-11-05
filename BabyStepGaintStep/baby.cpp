#include<stdio.h>
#include"hash_structure.h"
#include<map>

int n,a,b;
map<int,int> hBaby;

using namespace std;

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
		e = (e*a)%n;
	//	printf(" %d ",e);
	};
	printf("\n");
	int factor = pow_m(a,n-m-1,n);
	e = b;
//	printf("\nfactor = %d",factor);	
	for(int i=0;i<m;++i){
		
		if(hBaby.find(e)!=hBaby.end()){
			return i*m+hBaby.at(e);
		}
		e = (e*factor)%n;
	}
	
	return NULL;
	
}

int main(){
	printf("Input: ");
	scanf("%d %d %d",&n,&a,&b);
	int result = babyStep_gaintStep();
	if(result!=NULL)
		printf("\nOutput: %d",result);
	else 
		printf("\n*** Not result ***");
	

	
}
