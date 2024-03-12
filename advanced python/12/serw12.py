from __future__ import annotations
from flask import Flask, request, jsonify
from sqlalchemy.orm import sessionmaker
from sqlalchemy.orm import DeclarativeBase
from sqlalchemy import create_engine, Table, Column, Integer, ForeignKey, String
from sqlalchemy.orm import relationship, mapped_column, Mapped
from sqlalchemy.orm import validates
from typing import List

import sqlite3

db = sqlite3.connect("biblioteka4.db")
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

app = Flask(__name__)


@app.route('/books/<int:book_id>', methods=['GET'])
def api_get_book(book_id):
    book = session.query(Book).filter_by(book_id=book_id).first()
    # print("aaasdsadsad", book.title)
    if book:
        return jsonify({'tytul': book.title})
    return jsonify({'res': 'not found'})


@app.route('/books', methods=['POST'])
def api_add_book():
    data = request.get_json()
    print(data)
    authors = session.query(Autor).filter(Autor.author_id.in_(data['author_ids'])).all()

    if len(authors) != len(data['author_ids']):
        raise ValueError("One or more authors not found in the database.")

    new_book = Book(title=data['title'], year=data['year'],  current_holder_id=library_id)
    new_book.napisana_przez.extend(authors)

    session.add(new_book)
    session.commit()


@app.route('/books/<int:book_id>', methods=['PUT'])
def api_update_book(book_id):
    data = request.get_json()
    book = session.query(Book).filter_by(book_id=book_id).first()
    if book:
        book.title = data['title']
        book.author = data['author']
        book.year = data['year']
        session.commit()


@app.route('/books/<int:book_id>', methods=['DELETE'])
def api_delete_book(book_id):
    book = session.query(Book).filter_by(book_id=book_id).first()
    print(book.title)
    if book:
        session.delete(book)
        session.commit()
        print(book.title)


if __name__ == '__main__':
    app.run()
