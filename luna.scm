(define view (new-view))

(load-uri view "http://www.google.com")
(focus-view view)

(define (handle-keypress)
  (back-page view))
