from decimal import Decimal

def vat_faktura(lista):
	pom=0.0
	for val in lista:
		pom+=val*0.23
	return pom

def vat_faktura_dec(lista):
	pom=Decimal(0.0)
	for val in lista:
		pom+=val*Decimal("0.23")
	return pom

	
def vat_paragon(lista):
	suma=sum(lista)
	return suma*0.23

def vat_paragon_dec(lista):
	suma=sum(lista)
	return suma*Decimal("0.23")

zakupy = [1.0]+ [0.01]*10000	
pom = ["1.0"]+ ["0.01"]*10000
zakupydec =[]

for i in range(0,len(pom)):
	zakupydec.append(Decimal(pom[i]));

print(vat_faktura(zakupy))
print(vat_paragon(zakupy))
print(vat_faktura(zakupy) == vat_paragon(zakupy))

print(vat_faktura_dec(zakupydec))
print(vat_paragon_dec(zakupydec))
print(vat_faktura_dec(zakupydec) == vat_paragon_dec(zakupydec))
