(use ../build/jaylib)

(init-window 100 100 "Test Game")
(set-target-fps 60)
(hide-cursor)

(while (not (window-should-close))
  (begin-drawing)

  (clear-background [0 0 0])
  (let [[x y] (get-mouse-position)]
    (draw-circle-gradient x y 31.4 :lime :red)
    (draw-poly [500 200] 5 40 0 :magenta)
    (draw-line-bezier
      [(- x 100) y]
      [(+ x 100) (+ y 50)]
      4 :pink)
    (draw-line-ex
      [x (- y 10)]
      [x (+ y 10)]
      4 :sky-blue)
    (draw-line-strip
      [[x 0] [x 100] [50 y] [10 180]]
      :ray-white))

  (end-drawing))

(close-window)
