#include<bits/stdc++.h>
#include<vector>
#include<map>
#include<iostream>

using namespace std;

class HashMo {
	
	vector<int> arr;
	map<int,int> Map;
	
	public:
		void add(int x){
			if(Map.find(x) != Map.end())
				return;
			int index = arr.size();
			arr.push_back(x);
			
			Map.insert(std::pair<int,int>(x,index));
			
		};
		
		void remove(int x){
			if(Map.find(x) == Map.end())
				return;
				
			int index = Map.at(x);
//			printf("\n%d\n",index);
			Map.erase(x);
			
			int last = arr.size()-1;
//			printf("\n%d\n",last);
			swap(arr[index],arr[last]);
///			printf("\n%d - %d\n",arr[index],arr[last]);
			arr.pop_back();
//			printf("\n%d - %d\n",arr[index], Map.at(arr[index]));
			Map.at(arr[index]) = index;	
//			printf("\n%d",Map.at(arr[index]));
		}
		
		int search(int x){
			if(Map.find(x)!=Map.end())
				return Map.at(x);
			return -1;
		}; 
		
		int getRandom(){
			srand(time(NULL));
			int random_index = rand() % arr.size();
			return arr.at(random_index);
		}
		
		void printHash(){
			int i;
			for(i=0;i<arr.size();i++);
				printf(" %d ",arr.at(i));
		}
		
}; 
