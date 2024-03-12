import urllib.request
import requests
from bs4 import BeautifulSoup
import json
import pandas as pd
import numpy as np
from matplotlib import pyplot as plt

"""
tab = ["https://stat.gov.pl/obszary-tematyczne/ceny-handel/wskazniki-cen/wskazniki-cen-towarow-i-uslug-konsumpcyjnych-pot-inflacja-/miesieczne-wskazniki-cen-towarow-i-uslug-konsumpcyjnych-od-1982-roku/"]
http://api.nbp.pl/api/exchangerates/rates/{table}/{code}/{startDate}/{endDate}/
http://api.nbp.pl/api/exchangerates/rates/a/pln/2022-01-01/2022-01-31/
"""
rates1 = [4.537109107142857, 4.495674749999999, 4.596934321428571, 4.561549785714286, 4.528248321428571, 4.502009071428571, 4.559295, 4.570062535714285, 4.564441499999999, 4.590821464285713, 4.648794500000001, 4.617403321428571, 4.550923, 4.563122642857143, 4.764674285714285, 4.647431357142857, 4.655778535714285, 4.642393964285715, 4.762947178571429, 4.714745642857143, 4.734065285714285, 4.808286892857142, 4.697138392857143, 4.68196525]


rates2 = [4.5353642857142855, 4.497992857142858, 4.595907142857143, 4.565732142857143, 4.532292857142857, 4.499160714285714, 4.559914285714287, 4.571435714285714, 4.561539285714285, 4.589717857142857, 4.6477321428571425, 4.615432142857143, 4.551653571428572, 4.550864285714286, 4.767103571428571, 4.645357142857144, 4.657846428571427, 4.645178571428572, 4.76597857142857, 4.721489285714287, 4.728510714285714, 4.815485714285715, 4.695867857142858, 4.679796428571429,]
"""
rates2 = []
#
#tekst = urllib.request.urlopen("http://data.fixer.io/api/2023-01-01?access_key=apikey8&symbols=PLN")
"http://data.fixer.io/api/date?access_key=apikey&symbols=PLN"

years = ['2021', '2022']
mon = ['01','02','03','04','05','06','07','08','09','10','11','12']
days = ['01','02','03','04','05','06','07','08','09','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28']
# biore probki do 28 bo tyle ma luty

# do pobrania z datafixer to samo ale tam trzeba apikey

f = open("rates2.txt", "w")
for year in years:
    for month in mon:
        suma = 0
        for day in days:
            tekst = requests.get("https://api.frankfurter.app/"+year+"-"+month+'-'+day+"?to=PLN")
            y = tekst.json()
            rate = y['rates']['PLN']
            suma += rate
        print(suma/28)
        rates2.append(suma/28)
        f.write(str(suma/28))
        f.write("\n")
f.close()
#print(rates2)
"""
rates3 = []
for i in range(12):
    rates3.append((rates1[i]+rates2[i]+rates1[12+i]+rates2[12+i])/4)

#plt.figure(figsize=(8, 6)) # Rozmiar wykresu
figure, axis = plt.subplots(3, 1)
#plt.title("kurs zlotego 2021-2022")
plt.xlabel("Miesiąc")
plt.ylabel("Wartość zlotego w euro")
axis[0].set_xticks(range(1, 13))
axis[1].set_xticks(range(1, 13))
axis[2].set_xticks(range(1, 13))
axis[0].plot(range(1, 13), rates1[:12], label="kurs zlotego 2021 (1)", color="pink")
axis[0].plot(range(1, 13), rates2[:12], label="kurs zlotego 2021 (2)", color="blue")
axis[0].set_title("kurs zlotego 2021")
#axis[0],set_xlabel("")
axis[1].plot(range(1, 13), rates1[12:], label="kurs zlotego 2022 (1)", color="pink")
axis[1].plot(range(1, 13), rates2[12:], label="kurs zlotego 2022 (2)", color="blue")
axis[1].set_title("kurs zlotego 2022")
axis[2].plot(range(1, 13), rates3, color="green")
axis[2].set_title("kurs zlotego 2023(predict)")
plt.legend() # Wygenerowanie legendy
plt.tight_layout();
plt.savefig("wykres.png") # Zapisanie wykresu do pliku
plt.show() # Wyświetlenie wykresu w oknie
