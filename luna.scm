(define view (new-view))

(load-uri view "http://www.google.com")
(focus-view core view)

(if (back-page-p view)
    (load-uri view "http://www.github.com"))
