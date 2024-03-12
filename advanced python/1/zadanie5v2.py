
lista_slow=["Cyprian", "cyberotoman", "cynik", "ceniąc",  "czule"]


def common_prefix(lista):
	mini=1999999
	use=[True]*len(lista)
	for i in range(0,len(lista)):
		mini=min(len(lista[i]),mini)
#		lista2[i]=lista[i].lower()
	dl=0
	wyn=""
	print(mini)
	slownik={}
	
	args=len(lista)
	for i in range(0,mini):
		for j in range(0,args):
			if(use[j]):
				akt=lista[j][0:i+1].lower()
				if akt in slownik:
					pom=slownik[akt]+1
					if (pom>2 and dl<i+1):
						dl=i+1
						wyn=akt
					slownik[akt]=pom
				else:
					slownik[akt]=1
		
		for j in range(0,args):
			if use[j] and (3>slownik[lista[j][0:i+1].lower()]):
				use[j]=False			
		slownik.clear()
	
	return wyn
	
print(common_prefix(lista_slow))
					
