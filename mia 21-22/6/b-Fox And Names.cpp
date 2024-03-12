#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
using namespace std;

string imiona[102];
int n;
bool onie;
bool t[26][26];//by nie dać dwa razy tej samej krawędzi
vector<int>v[26];
int st[26];

void wczyt(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n;

	for(int i=0;i<n;i++)
		cin>>imiona[i];
}

void kraw(int a, int b){
	for(int i=0;i<min(imiona[a].size(),imiona[b].size());i++){
		if(imiona[a][i]!=imiona[b][i]){
			if(!t[imiona[a][i]-'a'][imiona[b][i]-'a']){
				t[imiona[a][i]-'a'][imiona[b][i]-'a']=true;
				v[imiona[a][i]-'a'].pb(imiona[b][i]-'a');
				st[imiona[b][i]-'a']++;
			}
			return;
		}
	}
	if(imiona[a].size()>imiona[b].size()) onie=true;
}

void buduj(){

	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			kraw(i,j);
}

queue<int>q;
int x;
string wyn;
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	wczyt();

	buduj();
	int n2=26;

	for(int i=0;i<26;i++){
		if(!st[i]) q.push(i);
	}

	while(!q.empty()){
		x=q.front(); q.pop(); n2--;
		wyn.pb(char(x+'a'));
		for(int i=0;i<v[x].size();i++){
			st[v[x][i]]--;
			if(!st[v[x][i]]) q.push(v[x][i]);
		}
	}

	if(n2 || onie) cout<<"Impossible";
	else cout<<wyn;

	return 0;
}
