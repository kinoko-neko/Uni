#include <stdio.h>
#include <stdlib.h>
#include "2.h"

int main(){
	int a,b,c,d,x;
	scanf("%d %d %d %d %d",&x,&a,&b,&c,&d);
	Ulamek * u1=nowy_ulamek(a,b);
	Ulamek * u2=nowy_ulamek(c,d);
	
	if(x==0){
	show(add2(u1,u2));
	add1(u1,u2);
	show(u2);
	}
	if(x==1){
	show(sub2(u1,u2));
	sub1(u1,u2);
	show(u2);
	}
	
	if(x==2){
	show(mult2(u1,u2));
	mult1(u1,u2);
	show(u2);
	}
	
	if(x==3){
	show(div2(u1,u2));
	div1(u1,u2);
	show(u2);
	}
	
}
