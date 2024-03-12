import urllib.request
import re


def crawl(start, distance, action):
    odw = {}
    pattern = re.compile(r'<a\s+(?:[^>]*?\s+)?href="([^"]*)"')

    def linki(tekst):
        return pattern.findall(tekst)

    def pom(akt, depth):
        if depth >= distance:
            return
        if akt in odw:
            return
        tekst = ""
        try:
            tekst = urllib.request.urlopen(akt).read().decode('utf-8')
        except:
            return
        odw[akt] = action(tekst)

        strony = linki(tekst)

        for strona in strony:
            if strona not in odw:
                pom(strona, depth+1)

    pom(start, 0)
    return odw.items()


for url, wynik in crawl("http://www.ii.uni.wroc.pl", 2, lambda text: "Python" in text):
    print(f"{url}: {wynik}")
