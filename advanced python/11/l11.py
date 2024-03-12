from __future__ import annotations
import sys
from sqlalchemy.orm import DeclarativeBase
from sqlalchemy import create_engine, Table, Column, Integer, ForeignKey, String
from sqlalchemy.orm import relationship, mapped_column, Mapped
from sqlalchemy.orm import sessionmaker
from sqlalchemy.orm import validates
from typing import List
import random
import sqlite3

db = sqlite3.connect("biblioteka.db")

# w Tabeli 'biblioteka' jest w tabeli person
# kiedy książka nie jest wypożyczona to
# current_holder_id = 0; (id biblioteki)

library_id = 1


class Base(DeclarativeBase):
    pass


autorstwa = Table(
    "author_book",
    Base.metadata,
    Column("book_id", ForeignKey("Books.book_id")),
    Column("author_id", ForeignKey("Authors.author_id")))


class Autor(Base):
    __tablename__ = 'Authors'
    name = mapped_column(String)
    author_id = mapped_column(Integer, primary_key=True)

    napisal: Mapped[List[Book]] = relationship(secondary=autorstwa)

    @validates("name")
    def validate_name(self, key, name):
        if len(name) < 3:
            raise ValueError("Nazwisko za krótkie")
        return name


class Book(Base):
    __tablename__ = 'Books'
    book_id = mapped_column(Integer, primary_key=True)
    title = mapped_column(String)
    author = mapped_column(String)
    year = mapped_column(Integer)
    current_holder_id = Column(Integer, ForeignKey('People.person_id'))
    person = relationship("Person", back_populates='posiada')
    napisana_przez: Mapped[List[Autor]] = relationship(secondary=autorstwa)

    @validates("year")
    def validate_year(self, key, year):
        if year < 1700:
            raise ValueError("Rok zbyt wczesny")
        return year


class Person(Base):
    __tablename__ = 'People'
    person_id = mapped_column(Integer, primary_key=True)
    name = mapped_column(String)
    email = mapped_column(String)
    posiada: Mapped[List[Book]] = relationship("Book", back_populates="person")

    @validates("name")
    def validate_name(self, key, name):
        if len(name) < 3:
            raise ValueError("Nazwisko za krótkie")
        return name


engine = create_engine("sqlite:///biblioteka.db", echo=True)
Base.metadata.create_all(engine)

Session = sessionmaker(bind=engine)
session = Session()


def add_book(title, author, author_ids, year):
    new_book = Book(title=title, author=author, year=year, current_holder_id=library_id)
    # autorzy = []
    for i in author_ids:
        a_i = session.query(Autor).filter(Autor.author_id == i).first()
        a_i.napisal.append(new_book)
        new_book.napisana_przez.append(a_i)
        autorzy.append(a_i)
    # print(autorzy)
    # new_book.napisana_przez.append()
    session.add(new_book)
    session.commit()


def add_author(name):
    new_author = Autor(name=name)
    session.add(new_author)
    session.commit()


def add_person(name, email):
    new_person = Person(name=name, email=email)
    session.add(new_person)
    session.commit()


# Funkcja wypożyczająca książkę
def borrow_book(book_id, person_id):
    book = session.query(Book).filter_by(book_id=book_id).first()
    book.current_holder_id = person_id
    session.commit()


# Funkcja oddająca książkę
def return_book(book_id):
    book = session.query(Book).filter_by(book_id=book_id).first()
    book.current_holder_id = library_id
    session.commit()

help_message = " --return [book_id]  - oddaje książke o danym id\n --add book [title] [author] [year] [number of authors]  [autor_id]  - dodaje książkę \n -add author [name] - dodaje autora \n -add person [name] [email] - dodaje osobe \n --borrow [book_id] [person_id] - wypozycza ksiazke na dana osobe\n --help informacja o poleceniach"


if __name__ == '__main__':
    if len(sys.argv) == 1:
        print("need arguments --help for info on commands")

    elif sys.argv[1] == '--add':
        if sys.argv[2] == 'book':
            pom = []
            for i in range(7, 7+int(sys.argv[6])):
                pom.append(sys.argv[i])
            add_book(sys.argv[3], sys.argv[4], pom, int(sys.argv[5]))
        elif sys.argv[2] == 'author':
            add_author(sys.argv[3])
        elif sys.argv[2] == 'person':
            add_person(sys.argv[3], sys.argv[4])
        else:
            print("wrong operation --help for info on commands")
    elif sys.argv[1] == '--delete':
        print("not implemented")
    elif sys.argv[1] == '--find':
        print("not implemented")
    elif sys.argv[1] == '--modify':
        print("not implemented")
    elif sys.argv[1] == '--borrow':
        borrow_book(sys.argv[2], sys.argv[3])
    elif sys.argv[1] == '--return':
        return_book(sys.argv[2])
    elif sys.argv[1] == '--help':
        print(help_message)
    else:
        print("wrong command --help for info on commands")
