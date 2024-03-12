#include<bits/stdc++.h>
#include "bst.hpp"
using namespace std;

template <class T, class f>
bst<T,f>::bst(){ korzen = NULL;};

template <class T, class f>
void bst<T,f>::insert(T val){
	if(korzen==nullptr){
		korzen = new node(val);
	}
	else korzen->insert(val);
}

template <class T, class f>
bst<T,f>::bst(std::initializer_list<T> wsp){
	
	bool nf= true;
	
	for(auto x : wsp){
		if(nf){
			nf= false; korzen = new node(x);
		}
    else korzen->insert(x);
  }
  
} 

template <class T, class f>
bool bst<T,f>::node::find(T w){
	if(w==val) return true;
  if(f::lt(val,w)){
  	if(prawy==NULL) return false;
		return prawy->find(w);
		
	}
	else{
		if(lewy==NULL) return false;
		return lewy->find(w);
	}
}

template <class T, class f>
bst<T,f>::~bst(){
	korzen->del();
}

template <class T, class f>
void bst<T,f>::node::del(){
	if(prawy!=NULL) prawy->del();
	if(lewy!=NULL) lewy->del();
	val=0;
	delete prawy;
	delete lewy;
}


template <class T, class f>
void bst<T,f>::erase(T a){
	if(korzen==NULL) return;
	if(korzen->prawy==NULL && korzen->lewy==NULL && korzen->val==a){korzen=NULL; return;}
	korzen=korzen->erase(a);
}

template <class T, class f>
typename bst<T,f>::node* bst<T,f>::node::erase(T w){
	if(w==val) return NULL;
  if(f::lt(val,w)){
		if(lewy==NULL) return this;
		lewy=lewy->erase(w);
	}
	else{
		if(prawy==NULL) return this;
		prawy=prawy->erase(w);
	}
}

template <class T, class f>
typename bst<T,f>::node* bst<T,f>::node::erase_root(node* r){
         if( r==NULL || r->val == 0)return NULL;
         if(r->prawy == NULL) return r->lewy;
         node* x = r->prawy; //metoda: wez za nowy korzen najmniejszy el w prawym podrzewie
         while (x->lewy!=NULL) x = x->lewy;
         x->lewy = r->lewy;
         return r->prawy;
}

template <class T, class f=por<T> >
string wyp(typename bst<T,f>::node* &x){
	 string v="";
	 if (x->lewy != NULL) v.append(wyp(x->lewy));
   v.push_back(x->val); v.push_back(' ');
   if (x->prawy != NULL) v.append(wyp(x->prawy));
   return v;
}

template <class T, class f=por<T> >
ostream& operator << (ostream &wy, const bst<T,f> &x){
	string pomi=wyp<T,f>(x.korzen);
	wy<<pomi;
	return wy;
}




