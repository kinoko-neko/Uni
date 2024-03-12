
def memoize(f):
    cache = {}

    def fun(x):
        if x not in cache:
            cache[x] = f(x)
        return cache[x]
    return fun

@memoize
def sudan(x):
    if x[0] == 0:
        return x[1] + x[2]
    if x[2] == 0:
        return x[1]
    return sudan( ( x[0]-1,sudan((x[0],x[1],x[2]-1)),sudan((x[0],x[1],x[2]-1))+x[2] ) )


def sudan2(x):
    if x[0] == 0:
        return x[1] + x[2]
    if x[2] == 0:
        return x[1]
    return sudan2( ( x[0]-1,sudan2((x[0],x[1],x[2]-1)),sudan2((x[0],x[1],x[2]-1))+x[2] ) )

print(sudan((1,1000,490))) #dla 1 1000 500 limit stosu
print(sudan2((1,25,25)))# tu już zajmuje kilka sekund
