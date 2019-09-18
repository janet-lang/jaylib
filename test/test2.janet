(use ../build/jaylib)

(set-trace-log-callback nil)

(init-window 800 600 "Test Game")
(set-target-fps 60)

(def lenna (load-image-1 "test/lenna.png"))
(image-dither lenna 4 4 4 4)
(def lenna-t (load-texture-from-image lenna))

(while (not (window-should-close))
  (begin-drawing)
  (clear-background :green)
  
  (draw-texture lenna-t 100 100 :white)

  (end-drawing))

(close-window)
