
znaki=[" ",".",",",":",";","!",".","?"]

def wyczysc(napis):
	for znak in znaki:
		napis=napis.replace(znak,"")
	return napis
		
def palindrom(napis):
	napis2=wyczysc(napis).lower()
	dl=len(napis2)
	prawy=dl-1
	for i in range(0,(dl//2) +1):
		if(napis2[i]!=napis2[prawy]):
			return False
		prawy-=1
	return True
	
print(palindrom("Kobyła ma mały bok."))
