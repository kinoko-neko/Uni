import b12
import argparse
import requests

# ...

# Adres serwera API
API_URL = 'http://127.0.0.1:5000'


def add_book(title, author, year, ids):
    data = {'title': title, 'author': author, 'year': year, 'author_ids': ids}
    requests.post(f'{API_URL}/books', json=data)


def get_book(book_id):
    response = requests.get(f'{API_URL}/books/{book_id}')
    return response


def update_book(book_id, title, author, year):
    data = {'title': title, 'author': author, 'year': year}
    requests.put(f'{API_URL}/books/{book_id}', json=data)


def delete_book(book_id):
    requests.delete(f'{API_URL}/books/{book_id}')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Client for library management')
    subparsers = parser.add_subparsers(help='sub-command help')

    parser.add_argument('--use-api', action='store_true', help='Use API for data operations')

    parser.add_argument('-aa', action='store_true', help='addauthor')
    parser_add_author = subparsers.add_parser('addauthor', help='addauthor help')
    parser_add_author.add_argument('name', help='author name')

    parser.add_argument('-ab', action='store_true', help='addbook')
    parser_add_book = subparsers.add_parser('addbook', help='addbook help')
    parser_add_book.add_argument('title', help='book title')
    parser_add_book.add_argument('year', help='book title')
    parser_add_book.add_argument('author', help='author')
    parser_add_book.add_argument('authors', nargs='+', help='author ids')

    parser.add_argument('-ap', action='store_true', help='addperson')
    parser_add_person = subparsers.add_parser('addperson', help='addperson help')
    parser_add_person.add_argument('name', help='person name')
    parser_add_person.add_argument('mail', help='person mail')

    parser.add_argument('--delete', nargs=2, help='Delete book, author, or person')
    parser.add_argument('--find', nargs=2, help='Find book, author, or person')

    parser.add_argument('--borrow', nargs=2, help='Borrow book')
    parser.add_argument('--ret', nargs=1, help='Return book')

    parser.add_argument('-ma', action='store_true', help='modifyauthor')
    parser_modify_author = subparsers.add_parser('modifyauthor', help='modifyauthor help')
    parser_modify_author.add_argument('name', help='author name')

    parser.add_argument('-mb', action='store_true', help='modifybook')
    parser_modify_book = subparsers.add_parser('modifybook', help='addbook help')
    parser_modify_book.add_argument('id', help='book id')
    parser_modify_book.add_argument('title', help='book title')
    parser_modify_book.add_argument('year', help='book title')
    parser_modify_book.add_argument('author', help='author')
    #parser_modify_book.add_argument('authors', nargs='+', help='authors ids')

    parser.add_argument('-mp', action='store_true', help='modifyperson')
    parser_modify_person = subparsers.add_parser('modifyperson', help='addperson help')
    parser_modify_person.add_argument('name', help='person name')
    parser_modify_person.add_argument('mail', help='person mail')

    args = parser.parse_args()
    print(args)

    api = False
    if args.use_api:
        api = True

    if args.ab:
        title = args.title
        year = int(args.year)
        author = args.author

        pom = []

        for i in range(len(args.authors)):
            pom.append(args.authors[i])

        if api:
            add_book(title, author, year, pom)
        else:
            b12.s_add_book(title, author, pom, year)
    elif args.aa:
        b12.s_add_author(args.name)
    elif args.ap:
        b12.s_add_person(args.addperson[0], args.addperson[1])
    elif args.delete:
        if args.delete[0] == 'b' and api:
            delete_book(args.delete[1])
        else:
            print("not implemented")
    elif args.find:
        if args.find[0] == 'b' and api:
            print(get_book(args.find[1]).json())
        else:
            print("not implemented")
    elif args.ma:
        print("not implemented")
    elif args.mb:
        title = args.title
        year = int(args.year)
        author = args.author

        if api:
            update_book(args.id, title, author, year)
        else:
            b12.s_update_book(args.id, title, author, year)

    elif args.mp:
        print("not implemented")
    elif args.borrow:
        b12.s_borrow_book(args.borrow[0], args.borrow[1])
    elif args.ret:
        b12.s_return_book(args.ret[0])

    else:
        print("wrong command --help for info on commands")

