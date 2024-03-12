#include<bits/stdc++.h>
#include "bst.cpp"
using namespace std;

int main(){
	
	bst<int> b1 = bst<int>(); 
	b1.insert(5); b1.insert(6); b1.insert(3);
	cout<<b1.find(5)<<" "<<b1.find(6)<<" "<<b1.find(3)<<"\n";
	
	bst<int> b2 = bst<int>({4,1,3,3,5,2,6});
	
	cout<<b2.find(1)<<" "<<b2.find(10)<<" "<<b2.find(3)<<" "<<b2.find(1)<<"\n";
	b2.erase(1);
	cout<<b2.find(1);
}


