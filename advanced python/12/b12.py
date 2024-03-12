from __future__ import annotations
from sqlalchemy.orm import sessionmaker
from sqlalchemy.orm import DeclarativeBase
from sqlalchemy import create_engine, Table, Column, Integer, ForeignKey, String
from sqlalchemy.orm import relationship, mapped_column, Mapped
from sqlalchemy.orm import validates
from typing import List

import sqlite3


db = sqlite3.connect("biblioteka2.db")

library_id = 1


class Base(DeclarativeBase):
    pass


autorstwa = Table(
    "author_book",
    Base.metadata,
    Column("book_id", ForeignKey("Books.book_id"), primary_key=True),
    Column("author_id", ForeignKey("Authors.author_id"), primary_key=True)
)


class Autor(Base):
    __tablename__ = 'Authors'
    author_id = Column(Integer, primary_key=True)
    name = Column(String)
    napisal = relationship("Book", secondary=autorstwa, back_populates="napisana_przez")

    @validates("name")
    def validate_name(self, key, name):
        if len(name) < 3:
            raise ValueError("Nazwisko za krótkie")
        return name


class Book(Base):
    __tablename__ = 'Books'
    book_id = Column(Integer, primary_key=True)
    title = Column(String)
    author = Column(String)
    year = Column(Integer)
    current_holder_id = Column(Integer, ForeignKey('People.person_id'))
    person = relationship("Person", back_populates='posiada')
    napisana_przez = relationship("Autor", secondary=autorstwa, back_populates="napisal")

    @validates("year")
    def validate_year(self, key, year):
        if year < 1700:
            raise ValueError("Rok zbyt wczesny")
        return year


class Person(Base):
    __tablename__ = 'People'
    person_id = Column(Integer, primary_key=True)
    name = Column(String)
    email = Column(String)
    posiada = relationship("Book", back_populates="person")

    @validates("name")
    def validate_name(self, key, name):
        if len(name) < 3:
            raise ValueError("Nazwisko za krótkie")
        return name


engine = create_engine("sqlite:///biblioteka4.db", echo=True)
Session = sessionmaker(bind=engine)
session = Session()


def s_add_book(title, author, author_ids, year):
    authors = session.query(Autor).filter(Autor.author_id.in_(author_ids)).all()

    if len(authors) != len(author_ids):
        raise ValueError("One or more authors not found in the database.")

    # Create a new Book instance
    new_book = Book(title=title, year=year, current_holder_id=library_id)

    # Add the authors to the book
    new_book.napisana_przez.extend(authors)

    # Add the book to the database session
    session.add(new_book)
    session.commit()


def s_add_author(name):
    new_author = Autor(name=name)
    session.add(new_author)
    session.commit()


def s_add_person(name, email):
    new_person = Person(name=name, email=email)
    session.add(new_person)
    session.commit()


# Funkcja wypożyczająca książkę
def s_borrow_book(book_id, person_id):
    book = session.query(Book).filter_by(book_id=book_id).first()
    book.current_holder_id = person_id
    session.commit()


def s_return_book(book_id):
    book = session.query(Book).filter_by(book_id=book_id).first()
    book.current_holder_id = library_id
    session.commit()


def s_api_get_book(book_id):
    book = session.query(Book).filter_by(book_id=book_id).first()
    return book


def s_update_book(book_id, title, author, year):
    book = session.query(Book).filter_by(book_id=book_id).first()
    if book:
        book.title = title
        book.author = author
        book.year = year
        session.commit()


def api_delete_book(book_id):
    book = session.query(Book).filter_by(book_id=book_id).first()
    if book:
        session.delete(book)
        session.commit()
