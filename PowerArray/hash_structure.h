#include<bits/stdc++.h>
#include<vector>
#include<map>
#include<iostream>

using namespace std;

class HashMo {
	
	map<int,int> Map;
	
	public:
		vector<int> arr;
		
		void add(int x){
			if(Map.find(x) != Map.end()){
				return;
			}
			int index = arr.size();
			arr.push_back(x);
			
			Map.insert(std::pair<int,int>(x,index));
			
		};
		
		
		void remove(int x){
			if(Map.find(x) == Map.end())
				return;
			int index = Map.at(x);
			Map.erase(x);
			if(arr.size()>0){
				int last = arr.size()-1;
				swap(arr[index],arr[last]);
				arr.pop_back();
			}
		}
		
		bool isEmpty(){
			return arr.size()==0?true:false;
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
			printf("\n Hash array: ");
			for(int i=0;i<arr.size();i++)
				printf(" %d ",arr[i]);
			printf("\n");
		}
		
}; 
