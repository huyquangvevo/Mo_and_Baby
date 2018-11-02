#include<stdio.h>
#include"hash_structure.h"

int main(){
	HashMo h;
	h.add(10);
	h.add(20);
	h.add(30);
	h.add(40);
	h.add(20);
	h.add(40);
	h.printHash();
//	h.printMap();
//	cout << h.search(30) <<endl;
	h.remove(20);
//	h.add(50);
	h.printHash();
//	cout << h.search(50) <<endl;
//	cout << h.getRandom() << endl;
//	exit(0);
}
