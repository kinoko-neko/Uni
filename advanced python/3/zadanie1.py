
def maxpal(napis):
    best_len = 1
    best = (0, 0)
    siz = len(napis)
    for i in range(0, siz):
        lewy = i
        prawy = i
        pom = 1
        while (lewy-1 >= 0 and prawy+1 < siz and napis[lewy - 1] == napis[prawy + 1]):
            lewy -= 1
            prawy += 1
            pom += 2
        if pom > best_len:
            best_len = pom
            best = (lewy, prawy)

        lewy = i + 1
        prawy = i
        pom = 0
        while (lewy-1 >= 0 and prawy+1 < siz and napis[lewy - 1] == napis[prawy + 1]):
            lewy -= 1
            prawy += 1
            pom += 2
        if pom > best_len:
            best_len = pom
            best = (lewy, prawy)

    if best_len < 2:
        return {}
    return {best}


print(maxpal("abaaba"))

print(maxpal("bababa"))

print(maxpal("asfsa"))

print(maxpal("bababf"))

print(maxpal("asv"))
