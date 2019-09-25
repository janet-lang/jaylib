(use ../build/jaylib)

(set-config-flags :msaa-4x-hint)

(init-window 800 600 "Test Game")
(set-target-fps 60)

(def lenna (load-image-1 "test/lenna.png"))
(image-dither lenna 4 4 4 4)
(def lenna-t (load-texture-from-image lenna))
(gen-texture-mipmaps lenna-t)

(def c (camera-3d :target [0 3 0]
                  :up [0 1 0]
                  :fovy 60
                  :type :perspective
                  :position [6 3 6]))

(set-camera-mode c :orbital)

(while (not (window-should-close))
  (update-camera c)
  (begin-drawing)
  (clear-background :black)
  
  (begin-mode-3d c)
  (draw-gizmo [0 0 0])
  (each x [1 2.4 3.3 3.9 4.4 5]
    (def s (/ 2 x))
    (draw-cube-texture lenna-t [2 x 2] s s s :white))
  (end-mode-3d)

  (end-drawing))

(close-window)
