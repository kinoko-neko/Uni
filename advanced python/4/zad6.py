
def brut(v1, v2):
    s1 = len(v1)
    s2 = len(v2)

    def isok(img):
        # print("aaaa")
        for i in range(s1):
            suma = sum(img[i])
            if suma != v1[i]:
                return False

        for j in range(s2):
            suma = sum(img[i][j] for i in range(s1))
            if suma != v2[j]:
                return False

        return True

    def gen(img, row, col):
        if row == s1:
            if isok(img):
                yield [list(row) for row in img]
            return
        if col == s2:
            for res in gen(img, row + 1, 0):
                yield res
            return
        img[row][col] = 0
        for res in gen(img, row, col + 1):
            yield res
        img[row][col] = 1
        for res in gen(img, row, col + 1):
            yield res

    tab = [[0] * s2 for _ in range(s1)]
    for img in gen(tab, 0, 0):
        yield img


v1 = [0, 2, 1]
v2 = [2, 2, 1]

for i in brut(v1, v2):
    print(i)

print("done")
