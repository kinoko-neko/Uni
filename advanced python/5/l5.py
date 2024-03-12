class brakzmiennej(Exception):
    pass


class dzielenieprzezzero(Exception):
    pass


class Wyrazenie:
    def oblicz(self, zmienne):
        raise NotImplementedError("Metoda 'oblicz' musi być zaimplementowana w klasach potomnych.")

    def __str__(self):
        raise NotImplementedError("Metoda '__str__' musi być zaimplementowana w klasach potomnych.")

    def __add__(self, other):
        return Dodaj(self, other)

    def __sub__(self, other):
        return Odejmij(self, other)

    def __mul__(self, other):
        return Razy(self, other)

    def __truediv__(self, other):
        return Dziel(self, other)


class Zmienna(Wyrazenie):
    def __init__(self, nazwa):
        self.nazwa = nazwa

    def oblicz(self, zmienne):
        if self.nazwa in zmienne:
            return zmienne[self.nazwa]
        else:
            raise brakzmiennej("Nie znaleziono zmiennej: " + self.nazwa)

    def uprosc(self):
        return self
    def __str__(self):
        return self.nazwa


class Stala(Wyrazenie):
    def __init__(self, wartosc):
        self.wartosc = wartosc

    def oblicz(self, zmienne):
        return self.wartosc

    def uprosc(self):
        return self

    def __str__(self):
        return str(self.wartosc)


class Dodaj(Wyrazenie):
    def __init__(self, lewy, prawy):
        self.lewy = lewy
        self.prawy = prawy

    def oblicz(self, zmienne):
        return self.lewy.oblicz(zmienne) + self.prawy.oblicz(zmienne)

    def uprosc(self):
        lewy = self.lewy.uprosc()
        prawy = self.prawy.uprosc()
        if isinstance(lewy, Stala):
            if isinstance(prawy, Stala):
                return Stala(lewy.wartosc+prawy.wartosc)
            elif lewy.wartosc == 0:
                return prawy
        elif isinstance(prawy, Stala) and prawy.wartosc == 0:
            return lewy
        return Dodaj(lewy, prawy)

    def __str__(self):
        return f"({self.lewy} + {self.prawy})"


class Odejmij(Wyrazenie):
    def __init__(self, lewy, prawy):
        self.lewy = lewy
        self.prawy = prawy

    def oblicz(self, zmienne):
        return self.lewy.oblicz(zmienne) + self.prawy.oblicz(zmienne)

    def uprosc(self):
        lewy = self.lewy.uprosc()
        prawy = self.prawy.uprosc()
        if isinstance(lewy, Stala):
            if isinstance(prawy, Stala):
                return Stala(lewy.wartosc-prawy.wartosc)
            elif lewy.wartosc == 0:
                return -prawy
        elif isinstance(prawy, Stala) and prawy.wartosc == 0:
            return lewy
        return Odejmij(lewy, prawy)

    def __str__(self):
        return f"({self.lewy} - {self.prawy})"


class Razy(Wyrazenie):
    def __init__(self, lewy, prawy):
        self.lewy = lewy
        self.prawy = prawy

    def oblicz(self, zmienne):
        return self.lewy.oblicz(zmienne) * self.prawy.oblicz(zmienne)

    def uprosc(self):
        lewy = self.lewy.uprosc()
        prawy = self.prawy.uprosc()

        if isinstance(lewy, Stala) and isinstance(prawy, Stala):
            return Stala(lewy.wartosc * prawy.wartosc)
        if (isinstance(lewy, Stala) and lewy.wartosc == 0) or (isinstance(prawy, Stala) and prawy.wartosc == 0):
            return Stala(0)
        if isinstance(lewy, Stala) and lewy.wartosc == 1:
            return prawy
        if isinstance(prawy, Stala) and prawy.wartosc == 1:
            return lewy
        return Razy(lewy, prawy)

    def __str__(self):
        return f"({self.lewy} * {self.prawy})"


class Dziel(Wyrazenie):
    def __init__(self, lewy, prawy):
        self.lewy = lewy
        self.prawy = prawy

    def oblicz(self, zmienne):
        mian = self.prawy.oblicz(zmienne)
        if mian == 0:
            raise dzielenieprzezzero(f"Dzielenie przez zero: {self.left.oblicz(zmienne)}/0")
        return self.lewy.oblicz(zmienne) / mian

    def uprosc(self):
        lewy = self.lewy.uprosc()
        prawy = self.prawy.uprosc()

        if isinstance(prawy, Stala):
            if prawy.wartosc == 0:
                raise dzielenieprzezzero(f"Dzielenie przez zero: {lewy}/0")
            if prawy.wartosc == 1:
                return lewy
            if isinstance(lewy, Stala):
                return Stala(lewy.wartosc/prawy.wartosc)
        if isinstance(lewy, Stala) and lewy.wartosc == 0:
            return Stala(0)

        return Dziel(lewy, prawy)

    def __str__(self):
        return f"({self.lewy} / {self.prawy})"


z1 = {"x": 9, "y": 3, "z": 15}
z2 = {"x": 3}

w1 = Dziel(Dodaj(Razy(Zmienna("x"), Stala(4)), Zmienna("y")), Zmienna("y"))
print(w1)
print(w1.oblicz(z1))

try:
    print(w1.oblicz(z2))
except brakzmiennej as e:
    print("expt:", e)


w2 = Dziel(Zmienna("x"), Odejmij(Stala(15), Stala(15)))
print(w2)
try:
    print(w2.uprosc())
except dzielenieprzezzero as e:
    print("expt:", e)
