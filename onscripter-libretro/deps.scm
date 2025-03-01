(use-modules
 (gnu packages base)
 (gnu packages compression)
 (gnu packages fontutils)
 (gnu packages image)
 (gnu packages sdl)
 (gnu packages xiph)
 (gnu packages mp3)
 (guix download)
 (guix git-download)
 (guix gexp)
 (guix packages))


(define onscripter-source
  (let ((version "20230825"))
    (origin
      (method git-fetch)
      (uri (git-reference
            (url "https://github.com/ogapee/onscripter")
            (commit version)))
      (file-name (git-file-name "onscripter" version))
      (sha256
       (base32 "074qh2bx7aqzqy3rfkvhhw2m3k48y9kf06f8k53ngyqmx6s579jx")))))


(computed-file
 "libretro-onscripter-deps"
 (with-imported-modules '((guix build utils))
   #~(begin
       (use-modules (ice-9 match)
                    (guix build utils))
       (setenv "PATH"
               (string-join '(#$(file-append tar "/bin")
                              #$(file-append xz "/bin")
                              #$(file-append gzip "/bin")
                              #$(file-append bzip2 "/bin"))
                            ":"))
       (for-each
        (match-lambda
          ((name pkg)
           (let ((dest (string-append #$output "/" name)))
             (mkdir-p dest)
             (if (file-is-directory? pkg)
                 (copy-recursively pkg dest)
                 (invoke "tar" "-C" dest
                         "--strip-components=1"
                         "-xvf" pkg)))))
        '(("bzip2" #$(package-source bzip2))
          ("freetype" #$(package-source freetype))
          ("libogg" #$(package-source libogg))
          ("libvorbis" #$(package-source libvorbis))
          ("libmad" #$ (package-source libmad))
          ("libjpeg-turbo" #$(package-source libjpeg-turbo))
          ("libpng" #$(package-source libpng))
          ("zlib" #$(package-source zlib))
          ("sdl" #$(package-source sdl))
          ("sdl-image" #$(package-source sdl-image))
          ("sdl-mixer" #$(package-source sdl-mixer))
          ("sdl-ttf" #$(package-source sdl-ttf))
          ("onscripter" #$onscripter-source))))))
