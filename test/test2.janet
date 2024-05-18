(use ../build/jaylib)

(set-trace-log-callback nil)

(init-window 800 600 "Test Game")
(set-target-fps 60)

(def lenna (load-image-1 "test/lenna.png"))
(image-dither lenna 4 4 4 4)
(def lenna-t (load-texture-from-image lenna))

(def lenna-bmp (slurp "test/lenna.bmp"))
(def lenna-b (load-image-from-buffer ".bmp" lenna-bmp))
(image-dither lenna-b 4 4 4 4)
(def lenna-bt (load-texture-from-image lenna-b))

(def gen-bmp (get-bitmap-header-buffer 100 100))
(each byte (range 0 (* 100 100))
  (buffer/push-byte gen-bmp 0)    #b
  (buffer/push-byte gen-bmp 0)    #g
  (buffer/push-byte gen-bmp 0xff) #r
  )
(def gen-i (load-image-from-buffer ".bmp" gen-bmp))
(def gen-t (load-texture-from-image gen-i))

(def cells (gen-image-cellular 100 100 10))
(def cells-t (load-texture-from-image cells))

(def nine-patch (load-image-1 "test/nine-patch.png"))
(def nine-patch-t (load-texture-from-image nine-patch))

(while (not (window-should-close))
  (begin-drawing)
  (clear-background :green)
  
  (draw-texture lenna-t 100 100 :white)
  (draw-texture lenna-bt 200 200 :white)
  (draw-texture cells-t 600 0 :white)
  (draw-texture-n-patch nine-patch-t [[0 0 96 96] 32 32 32 32 :npatch-nine-patch] [0 0 96 138] [0 0] 0 :white)

  (end-drawing))

(close-window)
