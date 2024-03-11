#lang racket

(provide (struct-out column-info)
         (struct-out table)
         (struct-out and-f)
         (struct-out or-f)
         (struct-out not-f)
         (struct-out eq-f)
         (struct-out eq2-f)
         (struct-out lt-f)
         table-insert
         table-project
         table-sort
         table-select
         table-rename
         table-cross-join
         table-natural-join)

(define-struct column-info (name type) #:transparent)

(define-struct table (schema rows) #:transparent)

(define cities
  (table
   (list (column-info 'city    'string)
         (column-info 'country 'string)
         (column-info 'area    'number)
         (column-info 'capital 'boolean))
   (list (list "Wrocław" "Poland"  293 #f)
         (list "Warsaw"  "Poland"  517 #t)
         (list "Poznań"  "Poland"  262 #f)
         (list "Berlin"  "Germany" 892 #t)
         (list "Munich"  "Germany" 310 #f)
         (list "Paris"   "France"  105 #t)
         (list "Rennes"  "France"   50 #f))))

(define countries
  (table
   (list (column-info 'country 'string)
         (column-info 'population 'number))
   (list (list "Poland" 38)
         (list "Germany" 83)
         (list "France" 67)
         (list "Spain" 47))))

(define (empty-table columns) (table columns '()))


;sprawdza czy b jest typu a

(define (pomi a b)
  (match a
    ['number (number? b)]
    ['string (string? b)]
    ['boolean (boolean? b)]
    ['symbol (symbol? b)]
   ))

(define (sprawdz row tab)
  (define (pom15 t1 t2)
        (if (null? t1) #t (and (pomi (column-info-type (car t2)) (car t1)) (pom15 (cdr t1) (cdr t2))) ) )   
  (if (= (length row) (length (table-schema tab)))
      (pom15 row (table-schema tab)) 
      #f
      )
  )
; Wstawianie

(define (table-insert row tab)
  (if (sprawdz row tab) (table (table-schema tab) (cons row (table-rows tab) ))
      (error "zle dane")) 
  ;; uzupełnij
  )

; Projekcja

(define (make-schema cols schema)
  (define (znajdzinfo nazwa opis)
    (if (null? opis) (error "zle dane2")
    (if (equal? nazwa  (column-info-name (car opis)) )
        (car opis) (znajdzinfo nazwa (cdr opis))
        ) )
    )
  (if (null? cols) (list )
      (cons  (znajdzinfo (car cols) schema) (make-schema (cdr cols) schema) ) 
      )
  )

;tworz naglowek
(define (wierszuj cols row info)
  (define (znajdzelem wiersz nazwa inf2)
    (if (null? wiersz) (error "zle dane3")
        (if (equal? nazwa (column-info-name (car inf2 ))) 
            (car wiersz) (znajdzelem (cdr wiersz) nazwa (cdr inf2))
            )
    ))
  (if (null? cols) (list )
      (cons (znajdzelem row  (car cols) info ) (wierszuj (cdr cols) row info)) )
  ); szukana czesc wiersza


(define (table-project cols tab)
  (define (pom2 rows)
 (if (null? rows) (empty-table (make-schema cols (table-schema tab)) )
      (table-insert (wierszuj cols (car rows) (table-schema tab)) (pom2 (cdr rows)) ) 
      )
    )
  (pom2 (table-rows tab))
  )

; Sortowanie
(define (wliscie elem lista)
      (if (null? lista) #f (if (equal? (car lista) elem) #t
                               (wliscie elem (cdr lista)) ) ))

(define (table-sort cols tab)
  (define (znajdzschemat kolejnosc opis)
    
    (if (null? opis) (list ) 
    (if   (wliscie (column-info-name (car opis)) cols )
       (cons (car kolejnosc) (znajdzschemat (cdr kolejnosc) (cdr opis) ))
      (cons (column-info-name (car opis)) (znajdzschemat kolejnosc (cdr opis)))
    )
    ) )
  (table-project  (znajdzschemat cols (table-schema tab)) tab) )

; Selekcja

(define-struct and-f (l r))
(define-struct or-f (l r))
(define-struct not-f (e))
(define-struct eq-f (name val)) ; wartość kolumny name równa val
(define-struct eq2-f (name name2)); wartości kolumn name i name2 równe
(define-struct lt-f (name val)); wartość kolumny name mniejsza niż val

(define (getwal name schema wiersz)
  (if (null? wiersz) (error "brak kolumny")
      (if (equal? name (column-info-name (car schema)))
          (car wiersz)
          (getwal name (cdr schema) (cdr wiersz))
          )
      )
  )

(define (test-eq name val schema wiersz)
  (equal? val (getwal name schema wiersz))
  )

(define (test-eq2 name name2 schema wiersz)
  (equal? (getwal name schema wiersz) (getwal name2 schema wiersz))
)

(define (test-lt name val schema wiersz)
  (< (getwal name schema wiersz) val)
  )

(define (eval form schema wiersz)
  (cond
    [(and-f? form) (and (eval (and-f-l form) schema wiersz) (eval (and-f-r form) schema wiersz))]
    [(or-f? form) (or (eval (or-f-l form) schema wiersz) (eval (or-f-r form) schema wiersz))]
    [(not-f? form) (not (eval (not-f-e form) schema wiersz))]
    [(eq-f? form) (test-eq (eq-f-name form) (eq-f-val form) schema wiersz)]
    [(eq2-f? form) (test-eq2 (eq2-f-name form) (eq2-f-name2 form) schema wiersz)]
    [(lt-f? form) (test-lt (lt-f-name form) (lt-f-val form) schema wiersz)]
    )
  )

(define (table-select form tab)
  (define (wez wiersze)
    (if (null? wiersze) (list )
        (if (eval form (table-schema tab) (car wiersze) )
            (cons (car wiersze) (wez (cdr wiersze)))
            (wez (cdr wiersze))
            )
        )
    )
  (table (table-schema tab) (wez (table-rows tab)))
 
  )

; Zmiana nazwy

(define (table-rename col ncol tab)
  (define (nowyschemat lista)
    (if (null? lista) (error "brak kolumny o tej nazwie")
        (if (equal? col (column-info-name (car lista)))
            (cons (column-info ncol (column-info-type (car lista))) (cdr lista))
            (cons (car lista) (nowyschemat (cdr lista)))
        )))
  (table (nowyschemat (table-schema tab)) (table-rows tab))
  )

; Złączenie kartezjańskie



(define (table-cross-join tab1 tab2)
  (define (nowewiersze t1 t2)
    (if (null? t1) (list )
        (append (map (lambda (wiersz) (append (car t1) wiersz) ) t2) (nowewiersze (cdr t1) t2))
        ) 
    )
  (table (append (table-schema tab1) (table-schema tab2)) (nowewiersze (table-rows tab1) (table-rows tab2)))

  )

; Złączenie

(define (newname kol)
  (column-info (string->symbol (string-append (symbol->string (column-info-name kol)) "v2")) (column-info-type kol))
  )

(define (newname2 kol)
  (string->symbol (string-append (symbol->string kol) "v2"))
  )

(define (wliscie2 elem lista)
      (if (null? lista) #f (if (equal? (column-info-name (car lista)) elem) #t
                               (wliscie2 elem (cdr lista)) ) ))

(define (renamowanie s1 s2)
  (if (null? s2) (cons (list ) (list ) )
  (if (wliscie2 (column-info-name (car s2)) s1)  
 (cons (cons  (newname (car s2)) (car (renamowanie s1 (cdr s2)) ))
       (cons (column-info-name (car s2)) (cdr (renamowanie s1 (cdr s2)) ) ))
 (cons (cons (car s2) (car (renamowanie s1 (cdr s2)) ))
       (cdr (renamowanie s1 (cdr s2)) ))
      )) ); zwraca liste i  liste powtorek

(define (makewar lista)
  (if (null? (cdr lista)) (eq2-f (car lista) (newname2 (car lista)) )
(and-f (makewar (cdr lista)) (eq2-f (car lista) (newname2 (car lista)) ))
      )
  )

(define (wliscie3 elem lista)
      (if (null? lista) #f
          (if (equal?  (newname2 (car lista)) elem) #t
                               (wliscie3 elem (cdr lista)) ) ))

(define (makekolumny schema powtorki)
  (if (null? schema) (list)
      (if (wliscie3  (column-info-name (car schema)) powtorki)
          (makekolumny (cdr schema) powtorki)
          (cons (column-info-name (car schema)) (makekolumny (cdr schema) powtorki))
      ))
   )

(define (table-natural-join tab1 tab2)
  (define pom8 (renamowanie (table-schema tab1) (table-schema tab2)) )
  ( define pom9 (table (car pom8) (table-rows tab2)) )
  ( define pom10 (table-cross-join tab1 pom9))
  (define newrows (table-select (makewar (cdr pom8)) pom10))
  (define nowekolumny (makekolumny (table-schema pom10) (cdr pom8)) )
  (table-project nowekolumny newrows)
  ;; uzupełnij
  )

