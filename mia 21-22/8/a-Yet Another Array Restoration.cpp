#include<bits/stdc++.h>
using namespace std;

int t,n,x,y;

void t1(int m){
	while(m--){
		cout<<x<<' ';
	}
}

void t2(){
	for(int i=y;i>y-n;i--)
		cout<<i<<' ';
}

void t3(){
	int dif;
	for(int i=y-x;i>1;i--){
		if( (y-x)%i==0 && (y-x)/i<=n-1){
			dif=i;
		}
	}

	int y2=y;
	int n2=0;

	//cout<<y<<' '
	for(int i=y;i>0 && n2<n;i-=dif){
		n2++;
		cout<<i<<' ';
	}
	for(int i=y+dif;n2<n;i+=dif){
		n2++;
		cout<<i<<' ';
	}

}

void t4(){
	for(int i=1;i<=n;i++)
		cout<<i<<' ';
}

int main(){
//	ios_base::sync_with_stdio(0);
//	cin.tie(0);
//	cout.tie(0);

	cin>>t;

	while(t--){
		cin>>n>>x>>y;
		if(x==y){
		//	printf("t1: ");
			t1(n);//te same elementy
		}
		else{
			if(y>n){
				if(x>y-n){
		//			printf("t2: ");
					t2();//różnica 1 i max to y
				}
				else{
		//			printf("t3: ");
					t3();
				}
			}
			else{//y<n
	//			printf("t4: ");
				t4();//1-n
			}

		}
		cout<<"\n";
	}

}
