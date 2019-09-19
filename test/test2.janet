(use ../build/jaylib)

(set-trace-log-callback nil)

(init-window 800 600 "Test Game")
(set-target-fps 60)

(def lenna (load-image-1 "test/lenna.png"))
(image-dither lenna 4 4 4 4)
(def lenna-t (load-texture-from-image lenna))

(def cells (gen-image-cellular 100 100 10))
(def cells-t (load-texture-from-image cells))

(while (not (window-should-close))
  (begin-drawing)
  (clear-background :green)
  
  (draw-texture lenna-t 100 100 :white)
  (draw-texture cells-t 600 0 :white)

  (end-drawing))

(close-window)
