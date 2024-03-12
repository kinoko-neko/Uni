import requests


def kompresja(tekst):
    stos = []
    licznik = 0
    temp = ''
    cnt = 0
    for i in range(len(tekst)):
        if temp == tekst[i]:
            cnt += 1
        else:
            stos.append((temp, cnt))
            licznik += 1
            cnt = 1
            temp = tekst[i]
    stos.pop(0)
    stos.append((temp, cnt))
    return stos


def znaki(krotka):
    return [krotka[0]]*krotka[1]


def dekompresja(tekst):
    lista = []
    for i in tekst:
        lista += znaki(i)
    return ''.join(lista)


tekst = 'suuper'

print(kompresja(tekst))
print(dekompresja(kompresja(tekst)))


r = requests.get('https://wolnelektury.pl/media/book/txt/prus-zemsta.txt')
#print(kompresja(r.text))
print(dekompresja(kompresja(r.text)))

