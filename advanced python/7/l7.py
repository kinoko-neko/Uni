import urllib.request
import re
import threading


def crawl(start, distance, action):
    odw = {}
    # po fakcie ale to z wykladu tez dziala
    # adres = '([a-zA-Z]+.)*[a-zA-Z]+'
    # automat = re.compile('http://' + adres)
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
        threads = []
        for strona in strony:
            if strona not in odw:
                thread = threading.Thread(target=pom, args=(strona, depth + 1))
                threads.append(thread)
                thread.start()
                # pom(strona, depth+1)

        for thread in threads:
            thread.join()

    pom(start, 0)
    return odw.items()


for url, wynik in crawl("http://www.ii.uni.wroc.pl", 2, lambda text: "Python" in text):
    print(f"{url}: {wynik}")
