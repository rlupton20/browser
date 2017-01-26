(define view (new-view))

(load-uri view "http://www.google.com")
(focus-view view)

(define catch-keypress
  (lambda (f)
    #t))

(define (dispatch-keypress mask keyseq)
  #f)
