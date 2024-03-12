#include<bits/stdc++.h>
using namespace std;

template<class T>
class por { 
  public:
	static bool lt (T a, T b){ return a < b; }
};

template<class T>
class por2 { public:
	static bool lt (T a, T b) { return a < b; }
};

template<class T,class f> class bst;
template<class T,class f> string wyp(typename bst<T,f>::node* w);

template<class T, class f>
ostream& operator<< (ostream &wy, const bst<T,f> &w);

template<class T, class f=por<T> >
class bst{
	class node{
		public:
		node *lewy;
		node *prawy;
		T val;
		
		node(T w){
			lewy=NULL; prawy=NULL;
			val = w;
		}
		
		void insert(T w){
			if(w==val) return;
			if(f::lt(val,w)){
				if(prawy==NULL){
					prawy= new node(w);
				}
				else prawy->insert(w);
				
			}
			else{
				if(lewy==NULL){
					lewy= new node(w);
				}
				else lewy->insert(w);
			}
			
		}
		
		bool	 find(T w);
		node* erase(T w);
		node* erase_root(node* r);
		void del();
		
		
	};
	

	protected:
	node *korzen;
	public:
	
	bst();
	bst(std::initializer_list<T> wsp);
//	bst(const bst &w); // konstruktor kopiujący
//	bst (bst &&w); // konstruktor przenoszący
	//bst& operator =(const bst &w); // przypisanie kopiujące
//	bst& operator =(bst &&w); // przypisanie przenoszące
	
	
	~bst();
	void insert(T a);
	void erase(T a);
	bool find(T a){ return korzen->find(a);} 
	

	friend string wyp<T,f>(typename bst<T,f>::node* w);
	friend ostream& operator << <T,f>(ostream &wy, const bst<T,f> &w);
};
