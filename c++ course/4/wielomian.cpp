#include<bits/stdc++.h>
#include "wielomian.hpp"

wielomian::wielomian (int st=0, double wsp=1.0){
	w= new double[1];
	n=0;
} // konstruktor jednomianu
	
wielomian::wielomian (int st, const double wsp[]){
	if(st<0) throw invalid_argument("wielomian o ujemnym rozmiarze\n");
	n=st;
	w= new double[st+1];
	for(int i=0;i<=n;i++) w[i]=wsp[i];
	if(w[n]==0 && n!=0) throw invalid_argument("wielomian n-ty stopnia o współczynniku 0\n");
}
 // konstruktor wielomianu
 
wielomian::wielomian (std::initializer_list<double> wsp){
	n=wsp.size()-1;
	w=new double[n+1];
	
	int pomi=0;
	for(auto x : wsp){
    w[pomi]=x; pomi++;
  }
  
} // lista współczynników

wielomian::wielomian (const wielomian &q){
	w=NULL;
	
	n=q.n;
	w= new double [n+1];
	for(int i=0;i<=n;i++) w[i]=q.w[i];
} // konstruktor kopiujący


wielomian::wielomian (wielomian &&q){
	n=q.n;
	w=q.w;
	q.w=NULL;
} // konstruktor przenoszący
	
wielomian & wielomian::operator =(const wielomian &q){
	if(&q!=this){
		this->~wielomian();
		n=q.n;
		w= new double [n+1];
		for(int i=0;i<=n;i++) w[i]=q.w[i]; 
	}
	return *this;
} // przypisanie kopiujące
	
wielomian & wielomian::operator =(wielomian &&q){
	if(&q!=this){
		std::swap(this->n,q.n);
		std::swap(this->w,q.w);
	}
	return *this;
} // przypisanie przenoszące

wielomian::~wielomian (){
	delete[] w; 
} 

istream& operator >> (istream &we, wielomian &q){
	int pomi;
	we>>pomi;
	if(pomi<0) throw invalid_argument("wielomian ujemnego stopnia");
	q.w=new double [pomi+1];
	q.n=pomi;
	for(int i=0;i<=pomi;i++) we>>q.w[i];
	return we;
}

ostream& operator << (ostream &wy, const wielomian &q){
	wy<<q.n<<"\n"<<q.w[0];
	for(int i=1;i<=q.n;i++) wy<<" + "<<q.w[i];
	return wy;
}

wielomian operator + (const wielomian &u, const wielomian &v){
	int pomi=max(u.n,v.n);
	int pom2=min(u.n,v.n);
	double *t= new double[pomi+1];
	for(int i=0;i<=pom2;i++) t[i]=u.w[i]+v.w[i];
	for(int i=pom2+1;i<=pomi;i++){
		if(u.n<pomi) t[i]=v.w[i]; else t[i]=u.w[i];
	}
	
	if(pomi!=0 && t[pomi]==0){
		int n2=0;
		for(int i=pomi;i>=0;i--){
			if(t[i]){ n2=i; break; }
		}
		double *t2= new double[n2+1];
		for(int i=0;i<=n2;i++) t2[i]=t[i];
		return wielomian(n2,t2);
	}
	return wielomian(pomi,t);
}

wielomian operator - (const wielomian &u, const wielomian &v){
	int pomi=max(u.n,v.n);
	int pom2=min(u.n,v.n);
	double *t= new double[pomi+1];
	for(int i=0;i<=pom2;i++) t[i]=u.w[i]-v.w[i];
	for(int i=pom2+1;i<=pomi;i++){
		if(u.n<pomi) t[i]=-v.w[i]; else t[i]=u.w[i];
	}
	
	if(pomi!=0 && t[pomi]==0){
		int n2=0;
		for(int i=pomi;i>=0;i--){
			if(t[i]){ n2=i; break; }
		}
		double *t2= new double[n2+1];
		for(int i=0;i<=n2;i++) t2[i]=t[i];
		return wielomian(n2,t2);
	}
	
	return wielomian(pomi,t);
}

wielomian operator * (const wielomian &u, const wielomian &v){
	int pomi=u.n+v.n;
	double *t=new double [pomi+1];
	for(int i=0;i<=pomi;i++) t[i]=0.0;
	
	for(int i=0;i<=u.n;i++){
		for(int j=0;j<=v.n;j++){
			t[i+j]+=u.w[i]*v.w[j];
		}
	}
	return wielomian(pomi,t);
}

wielomian operator * (const wielomian& q, double c){
	if(c==0.0) return wielomian({0});
	int pomi=q.n;
	double *t= new double[pomi+1];
	for(int i=0;i<=pomi;i++) t[i]=q.w[i]*c;
	return wielomian(pomi,t);
}

wielomian & wielomian::operator += (const wielomian &v){
	int pomi=max(n,v.n);
	int pom2=min(n,v.n);
	double *t= new double[pomi+1];
	
	for(int i=0;i<=pom2;i++) t[i]=w[i]+v.w[i];
	for(int i=pom2+1;i<=pomi;i++){
		if(n<pomi) t[i]=v.w[i]; else t[i]=w[i];
	}
	
	if(pomi!=0 && t[pomi]==0){
		int n2=0;
		for(int i=pomi;i>=0;i--){
			if(t[i]){ n2=i; break; }
		}
		double *t2= new double[n2+1];
		for(int i=0;i<=n2;i++) t2[i]=t[i];
		this->n=n2;
		this->w=t2;
		return *this;
	}
	
	this->n=pomi;
	this->w=t;
	return *this;
}

wielomian & wielomian::operator -= (const wielomian &v){
	int pomi=max(n,v.n);
	int pom2=min(n,v.n);
	
	if(pomi==pom2){
		int dif=-1;
		for(int i=pomi;i>=0;i--){
			if(v.w[i]!=w[i]){ dif=i; break;}
		}	
		if(dif==-1){
			double *t= new double[1]; t[0]=0.0;
			this->n=0;
			this->w=t; return *this;
		}
		double *t= new double[dif+1];
		for(int i=0;i<=dif;i++) t[i]=w[i]-v.w[i];
		this->n=dif;
		this->w=t;
		return *this;
	}
	else{
		double *t= new double[pomi+1];
		for(int i=0;i<=pom2;i++) t[i]=w[i]-v.w[i];
		for(int i=pom2+1;i<=pomi;i++){
			if(n<pomi) t[i]=-v.w[i]; else t[i]=w[i];
		}
		this->n=pomi;
		this->w=t;
		return *this;
	}
	
	
}

wielomian & wielomian::operator *= (const wielomian &v){
	int pomi=n+v.n;
	double *t=new double [pomi+1];
	for(int i=0;i<=pomi;i++) t[i]=0.0;
	
	for(int i=0;i<=n;i++){
		for(int j=0;j<=v.n;j++){
			t[i+j]+=w[i]*v.w[j];
		}
	}
	this->n=pomi;
	this->w=t;
	return *this;
}

wielomian & wielomian::operator *= (double c){
	if(c==0.0){
		this->n=0;
		double *t= new double[1]; t[0]=0.0;
		this->w=t;
		return *this;
	}
	for(int i=0;i<=n;i++) w[i]*=c;
	return *this;
	
}

double wielomian::operator () (double x) const{
	double wyn=0.0;
	for(int i=n;i>=0;i--) 
		wyn=wyn*x+w[i];
  return wyn;
} // wartość wielomianu dla x

double wielomian::operator [] (int i) const{
	if(i<0) throw invalid_argument("ujemny stopien\n");
	if(i>n) throw invalid_argument("odwołanie do za dużego stopnia\n");
	return w[i];
} // do odczytu współczynnika

double& wielomian::operator [] (int i){
	if(i<0) throw invalid_argument("ujemny stopien\n");
	if(i>n) throw invalid_argument("odwołanie do za dużego stopnia\n");
	return w[i];
} // do zapisu współczynnika
int wielomian::get_stopien(){return n;};
