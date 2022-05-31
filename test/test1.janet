(use ../build/jaylib)

(set-trace-log-callback |(print $0 ": " $1))

(set-config-flags
  :msaa-4x-hint)

(init-window 1200 800 "test Game")
(set-target-fps 60)
(hide-cursor)

(var rot 0)

(while (not (window-should-close))
  (++ rot)
  (begin-drawing)

  (clear-background :ray-white)
  (let [[x y] (get-mouse-position)]
    (draw-circle-gradient x y 31.4 :lime :red)
    (draw-poly [500 200] 5 40 rot :magenta)
    (draw-line-bezier
      [(- x 100) y]
      [(+ x 100) (+ y 50)]
      4 :pink)
    (draw-line-ex
      [x (- y 10)]
      [x (+ y 10)]
      4 :sky-blue))

  (if (key-pressed? :space)
    (trace-log :info (string/repeat "BLAH" 1000)))

  (draw-line-strip (seq [x :range [0 (+ (get-screen-width) 5)]]
                        [x (+ 400 (* 30 (math/sin (* x 0.04))))]) :red)

  (draw-fps 10 10)
  (draw-text "Hello, world!" 100 100 (math/floor (+ 20 (* 5 (math/random)))) :blue)

  (end-drawing))

(close-window)
