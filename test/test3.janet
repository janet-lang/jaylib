(use ../build/jaylib)

(init-window 100 100 "Game of Life")
(set-target-fps 60)

(def- window
  (seq [x :range [-1 2]
         y :range [-1 2]
         :when (not (and (zero? x) (zero? y)))]
       [x y]))

(defn- neighbors
  [[x y]]
  (map (fn [[x1 y1]] [(+ x x1) (+ y y1)]) window))

(defn tick
  "Get the next state in the Game Of Life. Cells outside the screen
  are set to dead."
  [state]
  (def cell-set (frequencies state))
  (def neighbor-set (frequencies (mapcat neighbors state)))
  (def maxx (/ (get-screen-width) 20))
  (def maxy (/ (get-screen-height) 20))
  (seq [coord :keys neighbor-set
         :let [count (get neighbor-set coord)
               [x y] coord]
         :when (and (>= x 0) (>= y 0) (<= x maxx) (<= y maxy))
         :when (or (= count 3) (and (get cell-set coord) (= count 2)))]
      coord))

(var state @[[10 10] [10 11] [10 12] [10 13] [10 14]])
(var counter 0)

(while (not (window-should-close))

  # Press space to clear screen
  (when (key-pressed? :space)
    (set state @[]))

  # Press the left mouse button to add cells
  (when (mouse-button-down? :left)
    (def [mx my] (get-mouse-position))
    (array/push state [(math/floor (/ mx 20)) (math/floor (/ my 20))]))

  # Update state every 10 frames
  (when (= 10 (++ counter))
    (set state (tick state))
    (set counter 0))

  # Draw cells
  (begin-drawing)
  (clear-background :black)
  (each [x y] state (draw-rectangle (* 20 x) (* 20 y) 18 18 :yellow))
  (end-drawing))

(close-window)
