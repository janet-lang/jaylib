(use ../build/jaylib)

(set-config-flags
  :msaa-4x-hint)

(init-window 800 600 "Chart")
(init-audio-device)
(set-target-fps 60)

(def m (load-music-stream "test/bach.ogg"))
(play-music-stream m)
(set-music-volume m 1)

(def s (load-sound "test/snd1.wav"))

(defn- point/distance [p1 p2] 
    (def (x1 y1) p1)
    (def (x2 y2) p2)
    (math/sqrt (+ 
        (math/pow (- x2 x1) 2)
        (math/pow (- y2 y1) 2))))

(defn- norm [max min v] 
    (/ (- v min) (- max min)))

(defn- point-for-time [t] 
    (def x (+ (/ (get-screen-width) 2)  (* (math/sin t) 200)))
    (def y (+ (/ (get-screen-height) 2) (* (math/cos t) 200)))
    [x y])

(defn- color-for-circle [x y t] 
    (def dist (point/distance [x y] (point-for-time t)))
    [ 
        (norm 0 (+ (get-screen-width) 100) dist) 
        (norm 0 (+ (get-screen-height) 100) dist) 
        (math/abs (math/sin (/ t 2.7)))
    ])

(while (not (window-should-close))
  (begin-drawing)

  (clear-background [0 0 0])

  (update-music-stream m)
  (def t (get-time))
  (begin-scissor-mode 100 10 200 340)
  (loop [x :range [20 (+ 40 (get-screen-width)) 40]
         y :range [20 (+ 40 (get-screen-height)) 40]]
    (draw-circle x y 20 (color-for-circle x y t)))
  (end-scissor-mode)

  (end-drawing)

  (when (key-pressed? :space)
    (play-sound s)
    (take-screenshot "screenshot.png")))

(close-window)