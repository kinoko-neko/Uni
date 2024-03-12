import random
import requests


def uprosc_zdanie(tekst, dl, slowa):
    lista_slow = []
    for slowo in tekst.split():
        if len(slowo) <= dl+1:
            if not ( len( slowo ) == dl+1 and slowo[-1].isalpha( ) ):
                lista_slow.append(slowo)

    skasuj = random.sample(range(0, len(lista_slow)), max(0, len(lista_slow)- slowa))
    skasuj.sort(reverse=True)

    for i in skasuj:
        lista_slow.pop(i)

    if (len(lista_slow) > 0 and lista_slow[-1][-1].isalpha()):
        lista_slow[-1] = lista_slow[-1] + "."
    if len(lista_slow) > 0:
        lista_slow[0] = lista_slow[0][0].upper() + lista_slow[0][1:]
    return " ".join(lista_slow)


tekst = "Podział peryklinalny inicjałów wrzecionowatych \
kambium charakteryzuje się ścianą podziałową inicjowaną \
w płaszczyźnie maksymalnej."
print(uprosc_zdanie(tekst, 10, 5))
"""
r = requests.get('https://wolnelektury.pl/media/book/txt/prus-zemsta.txt')

print(uprosc_zdanie(r.text, 10, 50))
"""
