(use-modules
 (ice-9 getopt-long)
 (ice-9 match)
 (ice-9 iconv)
 (ice-9 ftw)
 (ice-9 regex)
 (ice-9 textual-ports)
 (ice-9 binary-ports))


(define (die message)
  (with-output-to-port (current-error-port)
    (lambda ()
      (display message)
      (newline)))
  (exit 1))

(define (display-help)
  (display "Usage: guile pscript.scm [OPTION]... DIRECTORY
Convert script in DIRECTORY to UTF-8 encoded 'pscript.dat'.

  -h, --help              Display this help and exit
  -f, --from-code=NAME    encoding of original script (default to GB18030)
"))

(define (encrypt/1 bv)
  (call-with-input-bytevector
   bv (lambda (in)
        (call-with-output-bytevector
         (lambda (out)
           (let loop ((x (get-u8 in)))
             (when (not (eof-object? x))
               (put-u8 out (logxor x #x84))
               (loop (get-u8 in)))))))))

(define* (read-script gamedir encoding)
  (chdir gamedir)
  (let ((f? (lambda (filename) (search-path (list gamedir) filename)))
        (f<? (lambda (f1 f2)
               (< (string->number (string-drop-right f1 4))
                  (string->number (string-drop-right f2 4))))))
    (cond
     ((f? "nscript.dat")
      => (lambda (file)
           (bytevector->string
            (encrypt/1 (call-with-input-file file get-bytevector-all))
            encoding)))
     ((or (f? "0.txt") (f? "00.txt"))
      (with-output-to-string
        (lambda ()
          (for-each
           (lambda (f)
             (call-with-input-file f
               (lambda (p)
                 (display (get-string-all p))
                 (newline))
               #:encoding encoding))
           (scandir
            gamedir (lambda (f) (string-match "^[0-9]+[.]txt$" f)) f<?)))))
     ((f? "pscript.dat")
      => (lambda (file)
           (bytevector->string
            (encrypt/1 (call-with-input-file file get-bytevector-all))
            "UTF-8")))
     (else (die "Missing script")))))

(define (main)
  (let* ((opts (getopt-long (command-line)
                            '((help      (single-char #\h) (value #f))
                              (from-code (single-char #\f) (value #t)))))
         (help?     (option-ref opts 'help #f))
         (from-code (option-ref opts 'from-code "GB18030")))
    (when help?
      (display-help)
      (exit 0))
    (match (cdar opts)
      ((gamedir)
       (chdir gamedir)
       (when (file-exists? "pscript.dat")
         (die "pscript.dat found, nothing to do!"))
       (call-with-output-file "pscript.dat"
         (lambda (out)
           (put-bytevector
            out (encrypt/1 (string->bytevector
                            (read-script gamedir from-code)
                            "UTF-8")))))
       (display "DONE!\n")
       (display "To use pscript.dat, you need delete 0.txt/00.txt/nscript.dat!\n"))
      (_ (display-help)
         (newline)
         (die "Missing DIRECTORY")))))

(main)
