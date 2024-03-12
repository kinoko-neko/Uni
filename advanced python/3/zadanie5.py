def max_sublist(lista):
    pocz = 0
    best = (0, 0)
    best_sum = lista[0]
    akt = 0
    for i in range(0, len(lista)):
        akt += lista[i]
        if (akt > best_sum):
            best_sum = akt
            best = (pocz, i)

        if akt < 0:
            akt = 0
            pocz = i + 1
    return best


l1 = [-1, -2, -3, -4, -5]
l2 = [1, 2, 3, 4, 5]
l3 = [20, -1, 0, 1, 3, -7, 2]

print(max_sublist(l1))

print(max_sublist(l2))

print(max_sublist(l3))
