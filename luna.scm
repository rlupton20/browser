(define view (new-view))

(load-uri view "http://www.google.com")
(focus-view view)

(define (dispatch-keypress keyseq)
  (cond
   ((string=? keyseq "H") (back-page view))
   (else #f)))
