(use ../build/jaylib)

(set-config-flags
  :msaa-4x-hint)

(init-window 100 100 "Chart")
(set-target-fps 60)

(while (not (window-should-close))
  (begin-drawing)

  (clear-background [0 0 0])

  (loop [x :range [20 (+ 40 (get-screen-width)) 40]
         y :range [20 (+ 40 (get-screen-height)) 40]]
    (draw-circle x y 20 [(math/random)
                         (math/random)
                         (math/random)]))

  (end-drawing))

(close-window)
