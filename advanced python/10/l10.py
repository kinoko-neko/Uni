import matplotlib.image as mpimg
import matplotlib.pyplot as plt
import numpy as np

def happier(obraz1, alpha):
    obraz = obraz1
    for i in range(obraz.shape[0]):
        for j in range(obraz.shape[1]):
            if abs(obraz[i, j, 0] - obraz[i, j, 1])<alpha and abs(obraz[i, j, 1] - obraz[i, j, 2])<alpha:
                obraz[i, j] = np.mean(obraz[max(0, i-1):min(i+2, obraz.shape[0]), max(0, j-1):min(j+2, obraz.shape[1])], axis=(0, 1))
    return obraz


def sadder(obraz1, alpha):
    obraz = obraz1
    for i in range(obraz.shape[0]):
        for j in range(obraz.shape[1]):
            #print(obraz[i, j])
            #r, g, b = obraz[i, j]
            # print(str(r)+" "+str(g)+" "+str(b))
            obraz[i, j, 0] = obraz[i, j, 0] * alpha
            obraz[i, j, 1] = obraz[i, j, 1] * alpha
            obraz[i, j, 2] = obraz[i, j, 2] * alpha
    return obraz


img = mpimg.imread("grzyb.png")
#imgplot = plt.imshow(img)
#imgplot = plt.imshow(sadder(img, 0.6))
imgplot = plt.imshow(happier(img, 0.1))
plt.show()
#plt.show(happier(img, 2))
#plt.show(sadder(img))
